#include "device/device.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "common/log.h"
#include "common/futil.h"

int get_time_str(char *timestrp);

int init_device_info(DeviceInfoT *devinfop)
{
    memset(devinfop->type_name, 0, sizeof(devinfop->type_name));
    memset(devinfop->device_time, 0, sizeof(devinfop->device_time));
    memset(devinfop->macaddrs, 0, sizeof(devinfop->macaddrs));
    memset(devinfop->ipv4s, 0, sizeof(devinfop->ipv4s));
    memset(devinfop->ipv6s, 0, sizeof(devinfop->ipv6s));
    devinfop->device_version = NULL;
    return 0;
}

int update_device_info(struct device_info *devinfop)
{
    sprintf(devinfop->type_name, "test");

    if (devinfop->device_version != NULL) {
        free(devinfop->device_version);
    }
    devinfop->device_version = read_file_to_string("/proc/version");
    char *device_version = devinfop->device_version;
    size_t len = strlen(device_version);
    while (len > 0 && (device_version[len - 1] == '\t' || device_version[len - 1] == '\n' || device_version[len - 1] == '\r')) {
        device_version[len - 1] = '\0';
        len--;
    }

    get_time_str(devinfop->device_time);
    return 0;
}

void free_device_info(DeviceInfoT *devinfop)
{
    if (devinfop->device_version != NULL) {
        free(devinfop->device_version);
    }
}


int get_time_str(char *timestrp)
{
    // 获取当前时间
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime); // 获取当前时间（秒数）
    timeinfo = localtime(&rawtime); // 转换为本地时间

    strftime(timestrp, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    return 0;
}
