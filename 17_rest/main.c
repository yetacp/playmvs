#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../08_fss/fss.h"
#include "../08_fss/aux.h"
#include "../08_fss/screen.h"
#include "../15_tcpip/ezasmi.h"
#include "screens/frm_main.h"
#include "screens/frm_client_list.h"
#include "screens/frm_client_new.h"
#include "screens/frm_client_edit.h"
#include "main.h"

#define RESPONSE_SIZE 1024

typedef int Boolean;
#define true (1)
#define false (0)

/* Warning: no problem with long names for static members */

/* ================================================================== */
/* API REST */
/* ================================================================== */

static Sint32 sendmessage(char *ip, int port, char *buffer, int size)
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

/* ================================================================== */
/* Main screen */
/* ================================================================== */
static void main_OnInit(void)
{
    smain();
    fssSetField(FSMAIN_00001, "01/02/1900");
    fssSetField(FSMAIN_00002, " ");
}

static void main_OnSetCursor(void)
{
    fssSetCursor(FSMAIN_00002);
}

static int main_OnSubmit(int aid, int *screen)
{
    if (aid == fssPFK03 || aid == fssPFK15)
    {
        return 1;
    }
    char *option = fssGetField(FSMAIN_00002);
    switch (option[0])
    {
    case '1':
    case 'C':
    case 'c':
        *screen = SCREEN_LIST;
        break;
    case '7':
    case 'X':
    case 'x':
        return 1;
    default:
        break;
    }

    return 0;
}

static int main_OnFinalize(void)
{
}

/* ================================================================== */
/* Client list screen */
/* ================================================================== */

static void clientList_OnInit(void)
{
    sclist();

    char *request = "GET /api/clients HTTP/1.1\nHost: 127.0.0.1\n\n\n";
    char buffer[RESPONSE_SIZE + 1];

    strcpy(buffer, request);
    if (sendmessage("127.0.0.1", 3000, buffer, RESPONSE_SIZE) > 0)
    {
        char line[256];
        int line_number = 0;
        int line_position = 0;
        int buffer_position = 0;
        char last_char = buffer[0];
        Boolean afterEmptyLine = false;

        do
        {
            line[line_position] = buffer[buffer_position];
            if (buffer[buffer_position] == '\r')
            {
                // ignore return
                buffer_position++;
                continue;
            }
            if (buffer[buffer_position] == '\n')
            {
                if (afterEmptyLine)
                {
                    line[line_position] = 0; /* NULL terminated string */
                    line_number++;
                    printf("LINE %.02d: %s\n", line_number, line);
                    line_position = 0;
                }
                if (last_char == '\n')
                {
                    afterEmptyLine = true;                    
                }
                last_char = '\n';
            }
            else
            {
                last_char = buffer[buffer_position];
                line_position++;
            }

            buffer_position++;
        } while (buffer[buffer_position]);
    }
}

static void clientList_OnSetCursor(void)
{
    fssSetCursor(FSCLIST_00002);
}

static int clientList_OnSubmit(int aid, int *screen)
{
    switch (aid)
    {
    case fssPFK03:
    case fssPFK15:
        *screen = SCREEN_MAIN;
        break;
    case fssPFK05:
        *screen = SCREEN_NEW;
        break;
    default:
        break;
    }
    return 0;
}

/* ================================================================== */
/* Client new screen */
/* ================================================================== */

static void clientNew_OnInit(void)
{
    scnew();
}

static void clientNew_OnSetCursor(void)
{
    fssSetCursor(FSCNEW_00002);
}

static int clientNew_OnSubmit(int aid, int *screen)
{
    if (aid == fssPFK03 || aid == fssPFK15)
    {
        *screen = SCREEN_LIST;
    }
    return 0;
}

/* ================================================================== */
/* Client edit screen */
/* ================================================================== */

static void clientEdit_OnInit(void)
{
    scedit();
}

static void clientEdit_OnSetCursor(void)
{
    fssSetCursor(FSCEDIT_00002);
}

static int clientEdit_OnSubmit(int aid, int *screen)
{
    if (aid == fssPFK03 || aid == fssPFK15)
    {
        *screen = SCREEN_LIST;
    }
    return 0;
}

/* Table for event oriented programming :) */

static Screen screens[SCREEN_MAX] = {
    {.onInit = main_OnInit,
     .onSetCursor = main_OnSetCursor,
     .onSubmit = main_OnSubmit,
     .onFinalize = main_OnFinalize},
    {.onInit = clientList_OnInit,
     .onSetCursor = clientList_OnSetCursor,
     .onSubmit = clientList_OnSubmit,
     .onFinalize = NULL},
    {.onInit = clientNew_OnInit,
     .onSetCursor = clientNew_OnSetCursor,
     .onSubmit = clientNew_OnSubmit,
     .onFinalize = NULL},
    {.onInit = clientEdit_OnInit,
     .onSetCursor = clientEdit_OnSetCursor,
     .onSubmit = clientEdit_OnSubmit,
     .onFinalize = NULL}};

/* Main loop */

int main(int argc, char **argv)
{
    int exit = 0;
    int last_screen = 0;

    fssInit();

    ez_begin();

    int current_screen = SCREEN_MAIN;
    screens[current_screen].onInit();
    do
    {
        fssRefresh();
        last_screen = current_screen;
        exit = screens[current_screen].onSubmit(fssGetAID(), &current_screen);
        if (last_screen != current_screen)
        {
            if (screens[last_screen].onFinalize)
            {
                screens[last_screen].onFinalize();
            }
            fssReset();
            screens[current_screen].onInit();
        }
        screens[current_screen].onSetCursor();
    } while (!exit);

    ez_end();

    fssTerm();

    return 0;
}
