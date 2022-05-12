#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../08_fss/fss.h"
#include "../08_fss/aux.h"
#include "screens/frm_main.h"
#include "screens/frm_client_list.h"
#include "screens/frm_client_new.h"
#include "screens/frm_client_edit.h"
#include "main.h"

/* Warning no problem with long names for static members */

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

static int main_OnHandle(int aid, EnumScreen *screen)
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
}

static void clientList_OnSetCursor(void)
{
    fssSetCursor(FSCLIST_00002);
}

static int clientList_OnHandle(int aid, EnumScreen *screen)
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

static int clientNew_OnHandle(int aid, EnumScreen *screen)
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

static int clientEdit_OnHandle(int aid, EnumScreen *screen)
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
     .onHandle = main_OnHandle,
     .onFinalize = main_OnFinalize},
    {.onInit = clientList_OnInit,
     .onSetCursor = clientList_OnSetCursor,
     .onHandle = clientList_OnHandle,
     .onFinalize = NULL},
    {.onInit = clientNew_OnInit,
     .onSetCursor = clientNew_OnSetCursor,
     .onHandle = clientNew_OnHandle,
     .onFinalize = NULL},
    {.onInit = clientEdit_OnInit,
     .onSetCursor = clientEdit_OnSetCursor,
     .onHandle = clientEdit_OnHandle,
     .onFinalize = NULL}};

/* Main loop */

int main(int argc, char **argv)
{
    EnumScreen current_screen = SCREEN_MAIN;
    fssInit();
    screens[current_screen].onInit();
    int exit = 0;
    int last_screen = 0;
    do
    {
        fssRefresh();
        last_screen = current_screen;
        exit = screens[current_screen].onHandle(fssGetAID(), &current_screen);
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
    fssTerm();
    return 0;
}
