#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>

typedef struct server_conf
{
    int server_port;
} ServerConfT;

void init_server(ServerConfT *sconf);

int start_server(ServerConfT *sconf);

void free_server(ServerConfT *sconf);

#endif