#include "server/server.h"
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include <arpa/inet.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#include "common/log.h"
#include "common/tlv.h"

#define SOCK_MAX_WAIT_SEC 5

size_t bufferevent_read_to_tlv(struct bufferevent *bev, TLV *tlv);


static void
echo_read_cb(struct bufferevent *bev, void *ctx)
{
    /* This callback is invoked when there is data to read on bev. */
    struct evbuffer *input = bufferevent_get_input(bev);
    struct evbuffer *output = bufferevent_get_output(bev);

    TLV tlv = {};
    init_tlv(&tlv);
    if (bufferevent_read_to_tlv(bev, &tlv) == -1) {
        int fd = bufferevent_getfd(bev);
        log_error("fd %d read err, start close", fd);
        free_tlv(&tlv);
        close(fd);
        bufferevent_free(bev);
        return;
    }

    log_info("tlv data: type %d, length %ld, value %s", tlv.type, tlv.length, tlv.value);
    free_tlv(&tlv);
    /* Copy all the data from the input buffer to the output buffer. */
//    evbuffer_add_buffer(output, input);
}

static void
echo_event_cb(struct bufferevent *bev, short events, void *ctx)
{
    if (events & BEV_EVENT_ERROR)
        perror("Error from bufferevent");
    if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
        log_info("events: %d ,event close", events);
        bufferevent_free(bev);
    }
}

static void
accept_conn_cb(struct evconnlistener *listener,
               evutil_socket_t fd, struct sockaddr *address, int socklen,
               void *ctx)
{
    /* We got a new connection! Set up a bufferevent for it. */
    struct event_base *base = evconnlistener_get_base(listener);
    struct bufferevent *bev = bufferevent_socket_new(
            base, fd, BEV_OPT_CLOSE_ON_FREE);
    struct timeval timeout_read = {.tv_sec = 5};

    bufferevent_set_timeouts(bev, &timeout_read, NULL);
    log_info("new conn fd = %d", fd);
    bufferevent_setcb(bev, echo_read_cb, NULL, echo_event_cb, NULL);

    bufferevent_enable(bev, EV_READ|EV_WRITE);
}

static void
accept_error_cb(struct evconnlistener *listener, void *ctx)
{
    struct event_base *base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    log_error("Got an error %d (%s) on the listener. "
                    "Shutting down.\n", err, evutil_socket_error_to_string(err));
    event_base_loopexit(base, NULL);
}



void init_server(ServerConfT *sconf)
{

}

int start_server(ServerConfT *sconf)
{
    struct event_base *base;
    struct evconnlistener *listener;
    struct sockaddr_in sin;

    int port = sconf->server_port;

    if (port<=0 || port>65535) {
        log_error("Invalid server port: %d", port);
        return 1;
    }

    base = event_base_new();
    if (!base) {
        log_error("Couldn't open event base");
        return 1;
    }

    /* Clear the sockaddr before using it, in case there are extra
     * platform-specific fields that can mess us up. */
    memset(&sin, 0, sizeof(sin));
    /* This is an INET address */
    sin.sin_family = AF_INET;
    /* Listen on 0.0.0.0 */
    sin.sin_addr.s_addr = htonl(0);
    /* Listen on the given port. */
    sin.sin_port = htons(port);

    listener = evconnlistener_new_bind(base, accept_conn_cb, NULL,
                                       LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
                                       (struct sockaddr*)&sin, sizeof(sin));
    if (!listener) {
        perror("Couldn't create listener");
        return 1;
    }
    evconnlistener_set_error_cb(listener, accept_error_cb);

    log_info("libevent listener start");
    event_base_dispatch(base);
    return 0;
}

void free_server(ServerConfT *sconf)
{

}

size_t bufferevent_read_to_tlv(struct bufferevent *bev, TLV *tlv) {
    size_t recv_len = 0;
    size_t recv_cnt = 0;
    size_t recv_total = 0;
//    struct timeval read_before, read_after;

    size_t buffer_len = evbuffer_get_length(bufferevent_get_input(bev));
    log_info("buffer_len = %d", buffer_len);

//    gettimeofday(&read_before, NULL);
    while (recv_len < sizeof(tlv->type)) {
        recv_cnt = bufferevent_read(bev, &tlv->type, sizeof(tlv->type));
        recv_len += recv_cnt;
        log_info("recv_len = %d", recv_len);
        sleep(1);

//        gettimeofday(&read_after, NULL);
//        if (read_after.tv_sec - read_before.tv_sec > SOCK_MAX_WAIT_SEC) {
//            return -1;
//        }
    }
    log_info("tlv->type=%d", tlv->type);
    recv_total += recv_len;

//    gettimeofday(&read_before, NULL);
    recv_len = 0; recv_cnt = 0;
    char length_c[sizeof(tlv->length)];
    memset(length_c, 0, sizeof(tlv->length));
    while (recv_len < sizeof(tlv->length)) {
        recv_cnt = bufferevent_read(bev, &length_c[recv_len], sizeof(tlv->length));
        recv_len += recv_cnt;
        log_info("recv_len = %d", recv_len);
        sleep(1);

//        gettimeofday(&read_after, NULL);
//        if (read_after.tv_sec - read_before.tv_sec > SOCK_MAX_WAIT_SEC) {
//            return -1;
//        }
    }
    recv_total += recv_len;
    memcpy(&tlv->length, length_c, sizeof(tlv->length));
    log_info("tlv->length=%d", tlv->length);

//    gettimeofday(&read_before, NULL);
    recv_len = 0; recv_cnt = 0;
    tlv->value = malloc(tlv->length + 1);
    while (recv_len < tlv->length) {
        recv_cnt = bufferevent_read(bev, &tlv->value[recv_len], tlv->length);
        recv_len += recv_cnt;
        log_info("recv_len = %d", recv_len);
        sleep(1);

//        gettimeofday(&read_after, NULL);
//        if (read_after.tv_sec - read_before.tv_sec > SOCK_MAX_WAIT_SEC) {
//            return -1;
//        }
    }
    log_info("tlv->value=%s", tlv->value);
    recv_total += recv_len;

    return recv_total;
}

