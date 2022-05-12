#ifndef __SCREEN_H__
#define __SCREEN_H__

typedef struct Screen
{
    void (*onInit)(void);
    void (*onSetCursor)(void);
    int (*onSubmit)(int aind, int *screen);
    int (*onFinalize)(void);
} Screen;

#endif
