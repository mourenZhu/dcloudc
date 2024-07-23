#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>

typedef struct client_conf
{
    char server_ipv4[1024];
    int server_port;
} ClientConfT;

int init_client_conf(ClientConfT *cconf);

int free_client_conf(ClientConfT *cconf);

int start_cloud_client(ClientConfT *cconf);

#endif