#ifndef __MAIN_H__
#define __MAIN_H__

typedef enum EnumScreen
{
    SCREEN_MAIN,
    SCREEN_LIST,
    SCREEN_NEW,
    SCREEN_EDIT,
    SCREEN_MAX
} EnumScreen;

typedef struct Screen
{
    void (*onInit)(void);
    void (*onSetCursor)(void);
    int (*onHandle)(int aind, EnumScreen *screen);
    int (*onFinalize)(void);
} Screen;

#endif