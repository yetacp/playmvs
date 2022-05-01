#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../08_fss/fss.h"
#define FLD_USER_ID "userid"
#define FLD_PASSWORD "password"
#define FLD_HELLO "hello"
#define FLD_MSG "msg"

void init(void)
{
    // Initialize the FSS Environment
    // Place TSO Terminal Into Full Screen Mode
    fssInit();
    // Add Fields to the Screen
    fssFld(8, 20, fssPROT | fssHI, FLD_MSG, 40, "");
    fssTxt(10, 20, fssPROT | fssHI, "USERID");
    fssTxt(10, 29, fssPROT | fssHI, "==>");
    fssFld(10, 33, 0, FLD_USER_ID, 8, "");
    fssTxt(11, 20, fssPROT, "PASSWORD");
    fssTxt(11, 29, fssPROT | fssHI, "==>");
    fssFld(11, 33, fssNON, FLD_PASSWORD, 8, "");
    // Set default location for Cursor
    fssSetCursor(FLD_USER_ID);
}

int validate()
{
    int valid = 0;
    // Clear Error Message
    fssSetField(FLD_MSG, "");
    // If a required field is blank,
    // Set the error message and place
    // the cursor in that field.
    if (fssIsBlank(fssGetField(FLD_USER_ID)))
    {
        fssSetField(FLD_MSG, "Enter Your USERID");
        fssSetCursor(FLD_USER_ID);
    }
    else if (fssIsBlank(fssGetField(FLD_PASSWORD)))
    {
        fssSetField(FLD_MSG, "Enter Your Password");
        fssSetCursor(FLD_PASSWORD);
    }
    else
    {
        valid = 1; // All required data supplied
    }
    return valid;
}

void showMessage()
{
    char userid[9];
    char password[9];
    char work[64];
    //---------------------------------------------------------
    // Save User Input Data - It will be lost with fssReset()
    //---------------------------------------------------------
    strcpy(userid, fssGetField(FLD_USER_ID));
    strcpy(password, fssGetField(FLD_PASSWORD));
    fssReset(); // Create New Screen
    fssTxt(10, 30, fssPROT + fssPINK + fssREVERSE, "+------------------------------+");
    fssTxt(11, 30, fssPROT + fssPINK + fssREVERSE, "|");
    fssFld(11, 32, fssPROT + fssYELLOW, FLD_HELLO, 27, "");
    fssTxt(11, 61, fssPROT + fssPINK + fssREVERSE, "|");
    fssTxt(12, 30, fssPROT + fssPINK + fssREVERSE, "+------------------------------+");
    // Set default cursor location
    fssSetCursor(FLD_HELLO);
    // Build & Set Dynamic Field Contents
    strcpy(work, "Hi ");
    strcat(work, userid);
    fssSetField(FLD_HELLO, work);
    // Display and Wait for Input
    fssRefresh();
}

int main(int argc, char **argv)
{
    int aid;
    int exit;
    init();
    // Loop until PFK03 or PFK15 or Userid & Password Supplied
    exit = 0;
    do
    {
        // Display the Screen and Wait for Input
        fssRefresh();
        // Get AID value
        aid = fssGetAID();
        if (aid == fssPFK03 || aid == fssPFK15)
        {
            exit = 1;
            break;
        }
    } while (!validate());
    if (!exit)
    {
        showMessage();
    }
    // Terminate the FSS Environment
    // Remove the Terminal from Full Screen Mode
    fssTerm();
    return 0;
}
