#ifndef __AUX_H__
#define __AUX_H__
typedef char Sint8;
typedef short Sint16;
typedef int Sint32;

typedef struct TextRow
{
    Sint8 row;
    Sint8 col;
    int attr;
    char *msg;
} TextRow;

typedef struct FieldRow
{
    Sint8 row;
    Sint8 col;
    int attr;
    char *value;
    Sint8 len;
    char *msg;
} FieldRow;
#endif
