#ifndef _REMOTE_LOGC_H_
#define _REMOTE_LOGC_H_

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// change this to match your destination (server) IP address
#define RLOGC_IP_ADDRESS "REPLACE WITH YOUR IP"
#define RLOGC_PORT 11909

static void RLogCv(const char* format, va_list args)
{
    #if DEBUG
        char buffer[5120];
        vsnprintf(buffer, sizeof(buffer), format, args);

        int sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sd <= 0)
        {
            printf("[RemoteLog] Error: Could not open socket\n");
            return;
        }

        int broadcastEnable = 1;
        int ret = setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
        if (ret)
        {
            printf("[RemoteLog] Error: Could not set socket to broadcast mode\n");
            close(sd);
            return;
        }

        struct sockaddr_in broadcastAddr;
        memset(&broadcastAddr, 0, sizeof(broadcastAddr));
        broadcastAddr.sin_family = AF_INET;
        inet_pton(AF_INET, RLOGC_IP_ADDRESS, &broadcastAddr.sin_addr);
        broadcastAddr.sin_port = htons(RLOGC_PORT);

        ret = sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr*)&broadcastAddr, sizeof(broadcastAddr));
        if (ret < 0)
        {
            printf("[RemoteLog] Error: Could not send broadcast\n");
            close(sd);
            return;
        }
        close(sd);
    #endif
}

static void RLogC(const char* format, ...)
{
    #if DEBUG
        va_list args;
        va_start(args, format);
        RLogCv(format, args);
        va_end(args);
    #endif
}
#endif
