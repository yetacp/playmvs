/*-----------------------------------------------------------------------------
|  Copyright (c) 2012-2013, Tommy Sprinkle (tommy@tommysprinkle.com)
|
|  All rights reserved. Redistribution and use in source and binary forms,
|  with or without modification, are permitted provided that the following
|  conditions are met:
|
|    * Redistributions of source code must retain the above copyright notice,
|      this list of conditions and the following disclaimer.
|    * Redistributions in binary form must reproduce the above copyright
|      notice, this list of conditions and the following disclaimer in the
|      documentation and/or other materials provided with the distribution.
|    * Neither the name of the author nor the names of its contributors may
|      be used toendorse or promote products derived from this software
|      without specific prior written permission.
|
|   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
|   "AS IS" AND ANYEXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
|   LIMITED TO, THE IMPLIED WARRANTIESOF MERCHANTABILITY AND FITNESS
|   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENTSHALL THE
|   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
|   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
|   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
|   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
|   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
|   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
|   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
|   OF THE POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../08_fss/fss.h"

static int procAID(void);
static int cmdShift(char *cmd, char *buf);
static int menu(void);

char *strupr(char s[])
{
   char *p;
   for (p = s; *p; ++p)
      *p = toupper(*p);
   return (s);
}

int main(int argc, char **argv)
{
   fssInit(); // Initialize Full Screen Environment

   menu(); // Call main menu routine

   fssTerm(); // Terminate Full Screen Environment

   return 0;
}

#define DASHES "---------------------------------"

//
//-- Main MENU Loop
//
static int menu(void)
{
   char cmd[80];
   char wk[80];

#include "mdef.h"

   fssSetCursor("COMMAND");     // Default location for cursor
   fssSetField("MSG1", DASHES); // No error message
   fssSetColor("MSG1", 0);      // Default color
   do
   {
      fssRefresh();                // Display screen & wait for input
      fssSetCursor("COMMAND");     // Default cursor location
      fssSetField("MSG1", DASHES); // No error message
      fssSetColor("MSG1", 0);      // Default color
      procAID();                   // Process AID

      strcpy(cmd, fssGetField("COMMAND")); // copy contents of Command field
      if (cmdShift(cmd, wk))               // shift off first token
      {
         if (!strcmp("END", wk)) // is it END
         {
            if (cmdShift(cmd, wk)) // No operands allowed
            {
               fssSetField("MSG1", "Invalid Operand for END");
               fssSetColor("MSG1", fssYELLOW); // Set color for Err Msg
               fssSetCursor("COMMAND");        // Set cursor
            }
            else
            {
               fssReset(); // Done with current screen
               return 0;   // Exit
            }
         }
         if (!strcmp("EXIT", wk)) // Is Command "EXIT"
         {
            fssReset(); // Ignore any operands
            return 0;
         }
         else if (!strcmp("1", wk)) // Option = 1
         {
            system("DABROW");           // Call DABROWSE utility
            fssSetField("COMMAND", ""); // Clear Command
         }
         else if (!strcmp("S", wk)) // Option = S
         {
            system("SSTAT");            // Call System Status
            fssSetField("COMMAND", ""); // Clear Command
         }
         else
         {
            fssSetField("MSG1", "Invalid Command");
            fssSetColor("MSG1", fssYELLOW); // Set highlight color
            fssSetCursor("COMMAND");
         }
      }

   } while (1); // LOOP

   fssTerm(); // Terminate Full Screen Environment

   return 0;
}

//
//-- Process AID
//
static int procAID(void)
{
   int aid;
   char wk[80];

   wk[0] = '\0';                           // Clear work string
   aid = fssGetAID();                      // Get AID value
   if (aid == fssPFK03 || aid == fssPFK15) // PFK 3 or 15
      strcpy(wk, "END ");
   if (aid == fssPFK04 || aid == fssPFK16) // PFK 4 or 16
      strcpy(wk, "EXIT ");
   else if (aid == fssPFK08 || aid == fssPFK20) // PFK 8 or 20
      strcpy(wk, "DOWN ");
   else if (aid == fssPFK07 || aid == fssPFK19) // PFK 7 or 19
      strcpy(wk, "UP ");

   strcat(wk, fssGetField("COMMAND")); // add contenst of Command
   fssSetField("COMMAND", strupr(wk)); // put back updated Command

   return 0;
}

//
//-- Shift off Command Token
//
static int cmdShift(char *cmd, char *buf)
{
   int len;
   char *p;
   char *p1;

   p = cmd;          // set pointer to beginning of string
   while (*p == ' ') // skip over any blanks
      p++;

   if (!*p) // return zero if end of string
      return 0;

   p1 = p;                 // remember start of token
   while (*p && *p != ' ') // scan for end of token
      p++;

   len = p - p1;         // calc length of token
   memcpy(buf, p1, len); // return token;
   *(buf + len) = '\0';

   strcpy(cmd, p); // shift contents over
   return 1;       // token returned
}
