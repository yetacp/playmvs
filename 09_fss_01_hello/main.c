#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../08_fss/fss.h"

int main(int argc, char **argv)
{
    // Initialize the FSS Environment
    // Place TSO Terminal Into Full Screen Mode
    fssInit();
    // Add a Text Field to the Screen
    fssTxt(10, 20, fssPROT, "Hello, Good World!");
    // Display the Screen and Wait for Input
    fssRefresh();
    // Terminate the FSS Environment
    // Remove the Terminal from Full Screen Mode
    fssTerm();
    return 0;
}
