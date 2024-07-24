#include "common/tlv.h"
#include <string.h>

void init_tlv(TLV *tlv) {
    tlv->type = MSG_TYPE_UNREAD;
    tlv->length = 0;
    tlv->value = NULL;
}

void free_tlv(TLV *tlv) {
    if (tlv != NULL) {
        if (tlv->value != NULL) {
            free(tlv->value);
        }
    }
}

void reset_tlv(TLV *tlv) {
    free_tlv(tlv);
    init_tlv(tlv);
}

ssize_t write_tlv(int fd, TLV *tlv) {
    ssize_t all_ret = 0;
    ssize_t ret = 0;
    ret = write(fd, &tlv->type, sizeof(tlv->type));
    if (ret == 0) {
        return ret;
    }
    all_ret += ret;

    ret = write(fd, &tlv->length, sizeof(tlv->length));
    if (ret == 0) {
        return ret;
    }
    all_ret += ret;

    ret = write(fd, tlv->value, tlv->length);
    if (ret == 0) {
        return ret;
    }
    all_ret += ret;
    return all_ret;
}

