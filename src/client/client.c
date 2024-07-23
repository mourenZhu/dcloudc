#include "client/client.h"
#include "common/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "device/device.h"
#include "common/tlv.h"
#include <cjson/cJSON.h>


int init_client_conf(ClientConfT *cconf)
{
    memset(cconf->server_ipv4, 0, sizeof(cconf->server_ipv4));
    return 0;
}

int free_client_conf(ClientConfT *cconf)
{
    return 0;
}

void *send_msg(void * arg);
void *recv_msg(void *arg);

int start_cloud_client(ClientConfT *cconf)
{
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void *thread_return;

    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(cconf->server_ipv4);
    serv_addr.sin_port = htons(cconf->server_port);

    if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        log_error("connect() error");
    }

    pthread_create(&snd_thread, NULL, send_msg, (void *)&sock);
    pthread_create(&rcv_thread, NULL, recv_msg, (void *)&sock);
    pthread_join(snd_thread, &thread_return);
    pthread_join(rcv_thread, &thread_return);
    close(sock);
    return 0;
}

void *send_msg(void *arg) {
    int sock = *((int *)arg);
//    char name_msg[NAME_SIZE+BUF_SIZE];
    while (1) {
        DeviceInfoT devinfop;
        init_device_info(&devinfop);
        update_device_info(&devinfop);

        cJSON *info = cJSON_CreateObject();
        cJSON_AddStringToObject(info, "type_name", devinfop.type_name);
        cJSON_AddStringToObject(info, "device_version", devinfop.device_version);
        cJSON_AddStringToObject(info, "device_time", devinfop.device_time);
        char *json = cJSON_PrintUnformatted(info);

        TLV tlv = {};
        init_tlv(&tlv);
        tlv.type = MSG_TYPE_DEVICE_INFO;
        tlv.value = json;
        tlv.length = strlen(tlv.value);
        log_info("tlv data: type %d, length %ld, value %s", tlv.type, tlv.length, tlv.value);
        log_info("write ret: %d", write_tlv(sock, &tlv));

        cJSON_Delete(info);
        free_tlv(&tlv);

        sleep(3);
    }
    return NULL;
}

void *recv_msg(void *arg) {
//    int sock = *((int *)arg);
//    char name_msg[NAME_SIZE+BUF_SIZE];
//    int str_len;
    while (1) {
//        str_len = read(sock, name_msg, NAME_SIZE+BUF_SIZE-1);
//        if (str_len == -1) {
//            return (void *)-1;
//        }
//        name_msg[str_len] = 0;
//        fputs(name_msg, stdout);
    }
    return NULL;
}