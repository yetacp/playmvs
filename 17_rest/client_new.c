/* ================================================================== */
/* Client new screen */
/* ================================================================== */

#include "main.h"
#include "screens/frm_client_new.h"

void clientNew_OnInit(void)
{
    char d[11];
    char t[6];

    getDateTime(d, t);
    scnew();
    fssSetField(FSCNEW_00001, d);
    fssSetField(FSCNEW_00002, t);
}

void clientNew_OnSetCursor(void)
{
    fssSetCursor(FSCNEW_00003);
}

int clientNew_OnSubmit(int aid, int *screen)
{
    if (aid == fssPFK03 || aid == fssPFK15)
    {
        *screen = SCREEN_LIST;
    }
    return 0;
}
