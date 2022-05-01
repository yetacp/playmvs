#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../08_fss/fss.h"
#include "aux.h"
#include "panels.h"

int main(int argc, char **argv)
{
    fssInit();
    int i;

    for (i = 0; i < 15; i++)
    {
        TextRow t = textRows[i];
        fssTxt(t.row, t.col, t.attr, t.msg);
    }

    for (i = 0; i < 65; i++)
    {
        FieldRow f = fieldRows[i];
        fssFld(f.row, f.col, f.attr, f.value, f.len, f.msg);
    }

    fssSetField("PRT04", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    fssRefresh();
    fssTerm();
    return 0;
}
