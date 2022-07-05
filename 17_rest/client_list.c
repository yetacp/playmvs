/* ================================================================== */
/* Client list screen */
/* ================================================================== */
#include <stdlib.h>
#include "main.h"
#include "screens/frm_client_list.h"

void clientList_OnInit(void)
{
    int index[10];
    int i;
    char d[11];
    char t[6];

    getDateTime(d, t);

    sclist();
    fssSetField(FSCLIST_00001, d);
    fssSetField(FSCLIST_00002, t);

    char *buffer = malloc(RESPONSE_SIZE + 1);
    strcpy(buffer, FIND_CLIENTS);
    if (sendmessage(SERVER_IP, SERVER_PORT, buffer, RESPONSE_SIZE) > 0)
    {
        int line_number = 0;
        int position = 0;
        char lastChar = buffer[position];
        bool afterFirstLine = false;
        int initial = 0;

        printf("         0         1         2         3     \n");
        printf("         012345678901234567890123456789012345\n");
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
                    int length = position - initial;
                    printf("LINE %.02d: %.*s\n         ", line_number, length, &buffer[initial]);
                    int total = split(buffer, initial, index, ';');
                    for (i = 0; i < total; i++)
                    {
                        printf("%d:%d ", i, index[i]);
                    }
                    printf("\n");
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
    free(buffer);
}

void clientList_OnSetCursor(void)
{
    fssSetCursor(FSCLIST_00003);
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