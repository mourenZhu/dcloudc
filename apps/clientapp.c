#include <stdio.h>
#include "common/conf.h"
#include "common/log.h"
#include "device/device.h"

#define DEFAULT_CONF_PATH "client.conf"

char serverip[1024] = {0};
char serverport[64] = {0};

int main(int argc, char *argv[]) {
    log_info("device cloud client start");

    get_conf_value(DEFAULT_CONF_PATH, "server_ip", serverip);
    get_conf_value(DEFAULT_CONF_PATH, "server_port", serverport);
    log_info("server ip: %s,server port: %s", serverip, serverport);

    DeviceInfoT devinfop;
    init_device_info(&devinfop);
    update_device_info(&devinfop);
    log_info("type_name: %s, device_version: %s, device_time: %s",
             devinfop.type_name, devinfop.device_version, devinfop.device_time);
    free_device_info(&devinfop);
    return 0;
}