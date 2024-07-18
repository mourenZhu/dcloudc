#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/conf.h"
#include "common/log.h"

#define MAX_LINE_LENGTH 1024

// 去除字符串两端的空白字符
void trim(char *str) 
{
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
    while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')) {
        str++;
    }
}

int get_conf_value(const char *cpath, const char *key, char *value)
{
    FILE *fp;
    char line[MAX_LINE_LENGTH];

    // 打开配置文件
    fp = fopen(cpath, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    // 逐行读取配置文件
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        // 忽略空行和注释行
        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }

        // 分割键值对
        char *separator = strchr(line, '=');
        if (separator != NULL) {
            *separator = '\0';
            if (strncmp(key, line, separator - line) == 0) {
                strncpy(value, separator + 1, MAX_LINE_LENGTH);
                trim(value);
                break;
            }
        }
    }

    // 关闭文件
    fclose(fp);
    
    return 0;
}

