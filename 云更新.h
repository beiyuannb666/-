#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LENGTH 1024

// 用于从源字符串中提取子字符串
char *getSubstring(const char *const src, const char *const startTag, const char *const endTag) {
    const char *start = strstr(src, startTag);
    if (start == nullptr) {
        return nullptr;
    }
    start += strlen(startTag);

    const char *end = strstr(start, endTag);
    if (end == nullptr) {
        return nullptr;
    }

    size_t length = end - start;
    if (length == 0) {
        return nullptr;
    }

    char *result = (char *)malloc(sizeof(char) * (length + 1));
    if (result == nullptr) {
        return nullptr;
    }
    strncpy(result, start, length);
    result[length] = '\0';

    return result;
}

// 获取云端链接
char *获取云端链接() {
    char url[128];
    sprintf(url, "curl -s %s", "https://sharechain.qq.com/0e3f751a897830f3df3bc384a88b1233?qq_aio_chat_type=2");
    FILE *fp = popen(url, "r");
    if (fp == nullptr) {
        return nullptr;
    }
    char buf[MAX_LENGTH];

    while (fgets(buf, MAX_LENGTH, fp) != nullptr) {
        char bti[256];
        sscanf(buf, " <title>%[^<]</title>", bti);
        char *链接文本 = strstr(buf, "[链接]");
        if (链接文本 != nullptr) {
            pclose(fp);
            return getSubstring(链接文本, "[链接]", "[链接]");
        }
    }

    pclose(fp);
    return nullptr;
}

// 获取云端版本号
int 获取云端版本号() {
    char url[128];
    sprintf(url, "curl -s %s", "https://sharechain.qq.com/0e3f751a897830f3df3bc384a88b1233?qq_aio_chat_type=2");
    FILE *fp = popen(url, "r");
    if (fp == nullptr) {
        return 0; // or any suitable default value
    }
    char buf[MAX_LENGTH];

    while (fgets(buf, MAX_LENGTH, fp) != nullptr) {
        char bti[256];
        sscanf(buf, " <title>%[^<]</title>", bti);
        char *version = strstr(buf, "[版本号]");
        if (version != nullptr) {
            pclose(fp);
            version = getSubstring(version, "[版本号]", "[版本号]");
            int convertedVersion = atoi(version);
            free(version);
            return convertedVersion;
        }
    }

    pclose(fp);
    return 0; // or any suitable default value
}

// 获取云端公告
char *获取云端公告() {
    char url[128];
    sprintf(url, "curl -s %s", "https://sharechain.qq.com/0e3f751a897830f3df3bc384a88b1233?qq_aio_chat_type=2");
    FILE *fp = popen(url, "r");
    if (fp == nullptr) {
        return nullptr;
    }
    char buf[MAX_LENGTH];

    while (fgets(buf, MAX_LENGTH, fp) != nullptr) {
        char bti[256];
        sscanf(buf, " <title>%[^<]</title>", bti);
        char *公告文本 = strstr(buf, "[公告]");
        if (公告文本 != nullptr) {
            pclose(fp);
            return getSubstring(公告文本, "[公告]", "[公告]");
        }
    }

    pclose(fp);
    return nullptr;
}

char *获取公告() {
    char url[128];
    sprintf(url, "curl -s %s", "https://sharechain.qq.com/0e3f751a897830f3df3bc384a88b1233?qq_aio_chat_type=2");
    FILE *fp = popen(url, "r");
    if (fp == nullptr) {
        return nullptr;
    }
    char buf[MAX_LENGTH];

    while (fgets(buf, MAX_LENGTH, fp) != nullptr) {
        char bti[256];
        sscanf(buf, " <title>%[^<]</title>", bti);
        char *公告文本 = strstr(buf, "[公告]");
        if (公告文本 != nullptr) {
            pclose(fp);
            return getSubstring(公告文本, "[清枫]", "[清枫]");
        }
    }

    pclose(fp);
    return nullptr;
}

// 获取云端文件名
char *获取云端文件名() {
    char url[128];
    sprintf(url, "curl -s %s", "https://sharechain.qq.com/0e3f751a897830f3df3bc384a88b1233?qq_aio_chat_type=2");
    FILE *fp = popen(url, "r");
    if (fp == nullptr) {
        return nullptr;
    }
    char buf[MAX_LENGTH];

    while (fgets(buf, MAX_LENGTH, fp) != nullptr) {
        char bti[256];
        sscanf(buf, " <title>%[^<]</title>", bti);
        char *文件名 = strstr(buf, "[文件名]");
        if (文件名 != nullptr) {
            pclose(fp);
            return getSubstring(文件名, "[文件名]", "[文件名]");
        }
    }

    pclose(fp);
    return nullptr;
}

// 云更新
void 云更新() {
    puts("正在验证服务器端...");
    
    // 检查 curl 是否可用
    FILE *test = popen("which curl 2>/dev/null", "r");
    bool curl_ok = false;
    if (test) {
        char buf[64];
        if (fgets(buf, sizeof(buf), test)) curl_ok = true;
        pclose(test);
    }
    
    if (!curl_ok) {
        puts("[!] 设备未安装 curl，跳过云更新检查");
        puts("    如需自动更新，请安装 curl 或 Termux");
        return;  // 直接返回，不阻塞程序运行
    }
    
    int 云端版本 = 获取云端版本号();
    char *更新公告 = 获取云端公告();
    int 当前版本 = 1;  // 或使用 APP_VERSION 宏

    if (云端版本 <= 当前版本) {
        if (更新公告 && 更新公告[0] != '\0') {
            printf("云端公告: %s\n", 更新公告);
        } else {
            puts("云端公告: 暂无");
        }
        puts("当前是最新版。\n");
        if (更新公告) free(更新公告);
    } else {
        printf("程序版本过低，开始下载更新...\n");
        if (更新公告) {
            printf("更新公告: %s\n", 更新公告);
            free(更新公告);
        }
        
        char *下载链接 = 获取云端链接();
        char *更新文件名 = 获取云端文件名();
        
        if (下载链接 && 更新文件名) {
            printf("更新目标: %s\n", 更新文件名);
            char cmd[MAX_LENGTH];
            snprintf(cmd, sizeof(cmd), "curl -L %s -o %s", 下载链接, 更新文件名);
            int ret = system(cmd);
            if (ret == 0) {
                puts("更新完毕，请手动替换程序。");
            } else {
                puts("下载失败，请手动更新。");
            }
            free(下载链接);
            free(更新文件名);
        } else {
            puts("获取更新信息失败。");
        }
        exit(0);
    }
}