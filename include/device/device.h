#ifndef DEVICE_H
#define DEVICE_H

typedef struct device_info 
{
    char type_name[64];
    char device_time[128];
    char *device_version;
    char macaddrs[18];
    char ipv4s[16];
    char ipv6s[43];
} DeviceInfoT;

int init_device_info(DeviceInfoT *devinfop);

int update_device_info(DeviceInfoT *devinfop);

void free_device_info(DeviceInfoT *devinfop);

#endif