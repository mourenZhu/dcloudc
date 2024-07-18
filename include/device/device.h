#ifndef __DEVICE_H_
#define __DEVICE_H_

typedef struct device_info 
{
    char type_name[64];
    char device_time[128];
    char *device_version;
    
} DeviceInfoT;

int init_device_info(DeviceInfoT *devinfop);

int update_device_info(DeviceInfoT *devinfop);

void free_device_info(DeviceInfoT *devinfop);

#endif