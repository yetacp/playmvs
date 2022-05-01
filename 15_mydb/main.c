#include <stdio.h>
#include "ezasmi.h"

#define MAX_SOCKET 8
#define RESPONSE_SIZE 4096

int main(int argc, char *argv[])
{
    Sint32 errno, retcode;
    Uint32 dstaddr;

    char response[RESPONSE_SIZE];
    char *request = "GET /index.html HTTP/1.1\nHost: 127.0.0.1\n\n\n";

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

    retcode = ez_recv(&desc, RESPONSE_SIZE, response, &errno);
    if (retcode < 0)
    {
        printf("ez_recv error");
        return -1;
    }

    retcode = ez_close(&desc, &errno);
    if (retcode < 0)
    {
        printf("ez_close error");
        return -1;
    }

    ez_end();

    return 0;
}
