#include "common/tlv.h"
#include <string.h>

void init_tlv(TLV *tlv) {

}

void free_tlv(TLV *tlv) {
    if (tlv->value != NULL) {
        free(tlv->value);
    }
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

