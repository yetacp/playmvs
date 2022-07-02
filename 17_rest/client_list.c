/* ================================================================== */
/* Client list screen */
/* ================================================================== */

#include "main.h"
#include "screens/frm_client_list.h"
#include "sendmessage.h"

void clientList_OnInit(void)
{
    sclist();

    char d[11];
    getDate(d);
    fssSetField(FSCLIST_00001, d);

    char *REQUEST = "GET /api/clients HTTP/1.1\nHost: 127.0.0.1\n\n\n";
    char buffer[RESPONSE_SIZE + 1];

    strcpy(buffer, REQUEST);
    if (sendmessage("127.0.0.1", 3000, buffer, RESPONSE_SIZE) > 0)
    {
        char line[256];
        int line_number = 0;
        int line_position = 0;
        int buffer_position = 0;
        char last_char = buffer[0];
        Boolean afterEmptyLine = false;

        do
        {
            line[line_position] = buffer[buffer_position];
            if (buffer[buffer_position] == '\r')
            {
                // ignore return
                buffer_position++;
                continue;
            }
            if (buffer[buffer_position] == '\n')
            {
                if (afterEmptyLine)
                {
                    line[line_position] = 0; /* NULL terminated string */
                    line_number++;
                    printf("LINE %.02d: %s\n", line_number, line);
                    line_position = 0;
                }
                if (last_char == '\n')
                {
                    afterEmptyLine = true;
                }
                last_char = '\n';
            }
            else
            {
                last_char = buffer[buffer_position];
                line_position++;
            }

            buffer_position++;
        } while (buffer[buffer_position]);
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