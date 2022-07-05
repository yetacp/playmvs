#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screens/frm_main.h"
#include "main.h"

/* Warning: no problem with long names for static members */

/* ================================================================== */
/* Main screen */
/* ================================================================== */

Screen screens[SCREEN_MAX];

static void main_OnInit(void)
{
    char d[11];
    char t[6];

    getDateTime(d, t);
    smain();
    fssSetField(FSMAIN_00001, d);
    fssSetField(FSMAIN_00002, t);
    fssSetField(FSMAIN_00003, " ");
}

static void main_OnSetCursor(void)
{
    fssSetCursor(FSMAIN_00003);
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

/* Table for event oriented programming :) */

Screen screens[SCREEN_MAX] = {
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
