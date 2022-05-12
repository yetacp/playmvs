#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../08_fss/fss.h"
#include "../08_fss/aux.h"
#include "screens/frm_main.h"
#include "screens/frm_client_list.h"
#include "screens/frm_client_new.h"
#include "screens/frm_client_edit.h"

int main(int argc, char **argv)
{
    int aid;
    int exit;

    fssInit();
    sclilist();
    fssSetField(FSCLILIST_00001, "10/11/1980");

    exit = 0;
    do
    {
        fssRefresh();
        aid = fssGetAID();
        if (aid == fssPFK03 || aid == fssPFK15)
        {
            exit = 1;
            break;
        }
        fssSetCursor(FSCLILIST_00002);
    } while (1);

    fssTerm();
    return 0;
}
