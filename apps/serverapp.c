#include <stdio.h>
#include "common/log.h"
#include "common/conf.h"
#include "server/server.h"
#include <pthread.h>
#include <stdlib.h>

#define DEFAULT_CONF_PATH "server.conf"

char serverport[64] = {0};

void *server_thread(void *arg);

int main(int argc, char *argv[])
{
    log_info("device cloud server start");
    get_conf_value(DEFAULT_CONF_PATH, "server_port", serverport);
    ServerConfT serverConf;
    init_server(&serverConf);
    serverConf.server_port = atoi(serverport);

    pthread_t server_thread_t;
    pthread_create(&server_thread_t, NULL, server_thread, (void *)&serverConf);
    pthread_join(server_thread_t, NULL);
    log_info("server listener stop");
    free_server(&serverConf);
    return 0;
}

void *server_thread(void *arg)
{
    ServerConfT *sconf = (ServerConfT *)arg;
    start_server(sconf);
    return NULL;
}
