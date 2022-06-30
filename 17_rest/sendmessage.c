#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sendmessage.h"
#include "../15_tcpip/ezasmi.h"

Sint32 sendmessage(char *ip, int port, char *buffer, int size)
{
    Sint32 errno;
    Uint32 dstaddr;

    /* IP to binary representation */
    Sint32 retcode = ez_pton(ip, &dstaddr, &errno);

    if (retcode < 0)
    {
        printf("ez_pton error");
        return -1;
    }

    /* Create socket */
    Socket socket;
    socket.afinet = 2;
    socket.port = port;
    socket.ipaddr = dstaddr;

    Sint16 desc = (Sint16)ez_socket(&errno);
    if (desc < 0)
    {
        printf("ez_socket error");
        return -1;
    }

    /* Open connection */
    retcode = ez_conn(&desc, &socket, &errno);
    if (retcode < 0)
    {
        printf("ez_conn error");
        return -1;
    }

    /* Send request */
    retcode = ez_send(&desc, strlen(buffer), buffer, &errno);
    if (retcode < 0)
    {
        printf("ez_send error");
        return -1;
    }

    /* Receive response */
    Sint32 received = 0;
    retcode = 1;
    /* Clear buffer */
    memset(buffer, 0, size + 1);

    while (retcode > 0)
    {
        retcode = ez_recv(&desc, size, buffer, &errno);
        if (retcode < 0)
        {
            return -1;
        }
        else
        {
            received += retcode;
        }
    }

    /* Close connection */
    retcode = ez_close(&desc, &errno);
    if (retcode < 0)
    {
        printf("ez_close error");
        return -1;
    }

    return received;
}
