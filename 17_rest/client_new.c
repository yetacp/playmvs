/* ================================================================== */
/* Client new screen */
/* ================================================================== */

#include "main.h"
#include "screens/frm_client_new.h"

void clientNew_OnInit(void)
{
    scnew();
    char d[11];
    getDate(d);
    fssSetField(FSCNEW_00001, d);
}

void clientNew_OnSetCursor(void)
{
    fssSetCursor(FSCNEW_00002);
}

int clientNew_OnSubmit(int aid, int *screen)
{
    if (aid == fssPFK03 || aid == fssPFK15)
    {
        *screen = SCREEN_LIST;
    }
    return 0;
}
