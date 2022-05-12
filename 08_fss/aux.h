#ifndef __AUX_H__
#define __AUX_H__

#include "types.h"

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
