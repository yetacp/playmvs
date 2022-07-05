/* ================================================================== */
/* Client edit screen */
/* ================================================================== */

#include "main.h"
#include "screens/frm_client_edit.h"

void clientEdit_OnInit(void)
{
    char d[11];
    char t[6];
    getDateTime(d, t);

    scedit();
    fssSetField(FSCEDIT_00001, d);
    fssSetField(FSCEDIT_00002, t);
}

void clientEdit_OnSetCursor(void)
{
    fssSetCursor(FSCEDIT_00003);
}

int clientEdit_OnSubmit(int aid, int *screen)
{
    if (aid == fssPFK03 || aid == fssPFK15)
    {
        *screen = SCREEN_LIST;
    }
    return 0;
}
