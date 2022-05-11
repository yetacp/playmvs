#ifndef __AUX_H__
#define __AUX_H__
typedef struct
{
    int row;
    int col;
    int attr;
    char *msg;
} TextRow;

typedef struct
{
    int row;
    int col;
    int attr;
    char *value;
    int len;
    char *msg;
} FieldRow;
#endif
