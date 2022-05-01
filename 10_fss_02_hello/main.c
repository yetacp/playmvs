#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../08_fss/fss.h"
#define FLD_HELLO "hello"

int main(int argc, char **argv)
{
    int color;
    int aid;
    color = fssBLUE;
    // Initialize the FSS Environment
    // Place TSO Terminal Into Full Screen Mode
    fssInit();
    // Add a Text Field to the Screen
    fssFld(10, 20, fssPROT, FLD_HELLO, 15, "Hello, World!");
    // Loop until PFK03 or PFK15
    do
    {
        switch (color)
        {
        case fssBLUE:
            color = fssRED;
            break;
        case fssRED:
            color = fssPINK;
            break;
        case fssPINK:
            color = fssGREEN;
            break;
        case fssGREEN:
            color = fssTURQ;
            break;
        case fssTURQ:
            color = fssYELLOW;
            break;
        case fssYELLOW:
            color = fssWHITE;
            break;
        case fssWHITE:
            color = fssBLUE;
            break;
        default:
            color = fssBLUE;
        }
        // Set Field Color
        fssSetColor(FLD_HELLO, color);
        // Display the Screen and Wait for Input
        fssRefresh();
        // Get AID value
        aid = fssGetAID();
    } while (aid != fssPFK03 && aid != fssPFK15);
    // Terminate the FSS Environment
    // Remove the Terminal from Full Screen Mode
    fssTerm();
    return 0;
}
