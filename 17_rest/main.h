#ifndef __MAIN_H__
#define __MAIN_H__

#include "../08_fss/fss.h"
#include "../08_fss/aux.h"
#include "../08_fss/screen.h"
#include "../15_tcpip/ezasmi.h"

typedef int bool;
#define true (1)
#define false (0)

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 3000
#define RESPONSE_SIZE 2048

#define FIND_CLIENTS "GET /api/clients HTTP/1.1\nHost: 127.0.0.1\n\n\n"

typedef enum EnumScreen
{
    SCREEN_MAIN,
    SCREEN_LIST,
    SCREEN_NEW,
    SCREEN_EDIT,
    SCREEN_MAX
} EnumScreen;

extern Screen screens[SCREEN_MAX];

#define getDateTime GETDATE
extern void getDateTime(char *_sdate, char *_stime);

#define split SPLIT
extern int split(char *buffer, int initial, int *index, char separator);

#define clientList_OnInit ON001
extern void clientList_OnInit(void);

#define clientList_OnSetCursor ON002
extern void clientList_OnSetCursor(void);

#define clientList_OnSubmit ON003
extern int clientList_OnSubmit(int aid, int *screen);

#define clientNew_OnInit ON004
extern void clientNew_OnInit(void);

#define clientNew_OnSetCursor ON005
extern void clientNew_OnSetCursor(void);

#define clientNew_OnSubmit ON006
extern int clientNew_OnSubmit(int aid, int *screen);

#define clientEdit_OnInit ON007
extern void clientEdit_OnInit(void);

#define clientEdit_OnSetCursor ON008
extern void clientEdit_OnSetCursor(void);

#define clientEdit_OnSubmit ON009
extern int clientEdit_OnSubmit(int aid, int *screen);

#endif
