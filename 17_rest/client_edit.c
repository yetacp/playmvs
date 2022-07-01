/* ================================================================== */
/* Client edit screen */
/* ================================================================== */

#include "main.h"
#include "screens/frm_client_edit.h"

void clientEdit_OnInit(void)
{
    scedit();

    char d[11];
    getDate(d);
    fssSetField(FSCEDIT_00001, d);
}

void clientEdit_OnSetCursor(void)
{
    fssSetCursor(FSCEDIT_00002);
}

int clientEdit_OnSubmit(int aid, int *screen)
{
    if (aid == fssPFK03 || aid == fssPFK15)
    {
        *screen = SCREEN_LIST;
    }
    return 0;
}
