#ifndef TLV_H
#define TLV_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

enum {
    MSG_TYPE_UNREAD, /*在初始化TLV时，代表还未读取消息*/
    MSG_TYPE_REGISTER,
    MSG_TYPE_LOGIN,
    MSG_TYPE_LOGOUT,
    MSG_TYPE_HEARTBEAT,
    MSG_TYPE_ACK,
    MSG_TYPE_DEVICE_INFO,
    MSG_TYPE_MAX = MSG_TYPE_DEVICE_INFO
};

typedef struct tlv {
    u_int8_t type;
    u_int64_t length;
    char *value;
}TLV;

typedef struct tlv_prot {
    TLV *tlv;

}TLV_PROT;


void init_tlv(TLV *tlv);

void free_tlv(TLV *tlv);

void reset_tlv(TLV *tlv);

ssize_t write_tlv(int fd, TLV *tlv);

#endif