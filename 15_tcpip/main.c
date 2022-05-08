#include <stdio.h>
#include "ezasmi.h"

#define MAX_SOCKET 8
#define RESPONSE_SIZE 1024

int main(int argc, char *argv[])
{
    Sint32 errno, retcode;
    Uint32 dstaddr;

    char response[RESPONSE_SIZE + 1];
    char *request = "GET /api/clients HTTP/1.1\nHost: 127.0.0.1\n\n\n";

    ez_begin();

    errno = retcode = 256;
    dstaddr = 256;

    retcode = ez_pton("127.0.0.1", &dstaddr, &errno);
    printf("dsaddr=0x%lX \n", dstaddr);

    if (retcode < 0)
    {
        printf("ez_pton error");
        return -1;
    }

    Sint16 desc = (Sint16)ez_socket(&errno);
    if (desc < 0)
    {
        printf("ez_socket error");
        return -1;
    }

    Socket socket;
    socket.afinet = 2;
    socket.port = 3000;
    socket.ipaddr = dstaddr;

    retcode = ez_conn(&desc, &socket, &errno);
    if (retcode < 0)
    {
        printf("ez_conn error");
        return -1;
    }

    retcode = ez_send(&desc, strlen(request), request, &errno);
    if (retcode < 0)
    {
        printf("ez_send error");
        return -1;
    }

    Sint32 total_size = 0;
    retcode = 1;
    while (retcode > 0)
    {
        memset(response, 0, RESPONSE_SIZE + 1);
        retcode = ez_recv(&desc, RESPONSE_SIZE, response, &errno);
        if (retcode < 0)
        {
            printf("ez_recv error");
            return -1;
        }
        else
        {
            total_size += retcode;
            printf("%s", response);
        }
    }
    printf("\nTotal size: %ld bytes\n", total_size);

    retcode = ez_close(&desc, &errno);
    if (retcode < 0)
    {
        printf("ez_close error");
        return -1;
    }

    ez_end();

    return 0;
}
