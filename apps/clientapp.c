#include <stdio.h>
#include "common/conf.h"
#include "common/log.h"

#include "client/client.h"
#include <stdlib.h>

#define DEFAULT_CONF_PATH "client.conf"


int main(int argc, char *argv[]) {
    log_info("device cloud client start");

    ClientConfT client_conf;
    init_client_conf(&client_conf);
    get_conf_value(DEFAULT_CONF_PATH, "server_ip", client_conf.server_ipv4);
    char server_port[20] = {0};
    get_conf_value(DEFAULT_CONF_PATH, "server_port", server_port);
    client_conf.server_port = atoi(server_port);
    log_info("server ip: %s,server port: %d", client_conf.server_ipv4, client_conf.server_port);
    start_cloud_client(&client_conf);



    free_client_conf(&client_conf);

    return 0;
}