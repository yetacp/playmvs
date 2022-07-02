/* ================================================================== */
/* Client list screen */
/* ================================================================== */

#include "main.h"
#include "screens/frm_client_list.h"
#include "sendmessage.h"

void clientList_OnInit(void)
{
    char *FIND_CLIENTS = "GET /api/clients HTTP/1.1\nHost: 127.0.0.1\n\n\n";
    char d[11];
    char buffer[RESPONSE_SIZE + 1];

    sclist();
    getDate(d);
    fssSetField(FSCLIST_00001, d);

    strcpy(buffer, FIND_CLIENTS);
    if (sendmessage(SERVER_IP, SERVER_PORT, buffer, RESPONSE_SIZE) > 0)
    {
        int line_number = 0;
        int position = 0;
        char lastChar = buffer[position];
        bool afterFirstLine = false;
        int initial = 0;

        while (buffer[position])
        {
            switch (buffer[position])
            {
            case '\r':
                // ignore
                position++;
                continue;
            case '\n':
                if (afterFirstLine)
                {
                    line_number++;
                    printf("LINE %.02d: %.*s\n", line_number, position - initial, &buffer[initial]);   
                }
                else if (lastChar == '\n')
                {
                    afterFirstLine = true;
                }
                initial = position + 1;
                break;
            default:

                break;
            }
            lastChar = buffer[position];
            position++;
        }
    }
}

void clientList_OnSetCursor(void)
{
    fssSetCursor(FSCLIST_00002);
}

int clientList_OnSubmit(int aid, int *screen)
{
    switch (aid)
    {
    case fssPFK03:
    case fssPFK15:
        *screen = SCREEN_MAIN;
        break;
    case fssPFK05:
        *screen = SCREEN_NEW;
        break;
    default:
        break;
    }
    return 0;
}