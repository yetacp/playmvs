/* ================================================================== */
/* Client list screen */
/* ================================================================== */

#include "main.h"
#include "screens/frm_client_list.h"
#include "sendmessage.h"

int split(char *buffer, int initial, int *index, char separator)
{
    int total = 0;
    int position = initial;
    int start = initial;

    while (buffer[position] != 0)
    {
        if (buffer[position] == separator || buffer[position] == '\n')
        {
            index[total] = position - start > 0 ? start - initial : -1;
            start = position + 1;
            total++;
            if (buffer[position] == '\n')
            {
                break;
            }
        }
        position++;
    }
    return total;
}

void clientList_OnInit(void)
{
    char *FIND_CLIENTS = "GET /api/clients HTTP/1.1\nHost: 127.0.0.1\n\n\n";
    char d[11];
    int index[10];
    char buffer[RESPONSE_SIZE + 1];
    int i;

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