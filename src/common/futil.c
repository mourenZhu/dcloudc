#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/futil.h"

#define DEFAULT_FILE_BUFFER_SIZE 1024

static char PROC_DIR[] = "/proc";

char* read_file_to_string(const char* filename)
{
    FILE* file = NULL;
    char* buffer = NULL;
    if (strncmp(PROC_DIR, filename, sizeof(PROC_DIR) - 1) == 0) {
        // 在/proc目录下的文件只有在读的时候才能获取到有多大
        file = fopen(filename, "r"); // 以二进制模式打开文件
        if (file == NULL) {
            perror("Failed to open file");
            return NULL;
        }

        char sbuffer[DEFAULT_FILE_BUFFER_SIZE] = {0};

        // 读取文件内容
        if (fgets(sbuffer, sizeof(sbuffer), file) == NULL) {
            perror("Failed to read file");
            fclose(file);
        }
        size_t string_len = strlen(sbuffer) + 1;
        buffer = (char*)malloc(string_len * sizeof(char));
        if (buffer == NULL) {
            perror("Failed to allocate memory");
            fclose(file);
            return NULL;
        }
        memset(buffer, 0, (string_len * sizeof(char)));
        strcpy(buffer, sbuffer);
    }
    else {
        file = fopen(filename, "rb"); // 以二进制模式打开文件
        if (file == NULL) {
            perror("Failed to open file");
            return NULL;
        }

        // 获取文件大小
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        rewind(file);

        // 分配内存来存储文件内容
        buffer = (char*)malloc((fileSize + 1) * sizeof(char));
        if (buffer == NULL) {
            perror("Failed to allocate memory");
            fclose(file);
            return NULL;
        }
        // 读取文件内容到缓冲区
        size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
        if (bytesRead != fileSize) {
            perror("Failed to read file");
            free(buffer);
            fclose(file);
            return NULL;
        }

        // 添加字符串终止符
        buffer[fileSize] = '\0';
    }

    fclose(file);
    return buffer;
}
