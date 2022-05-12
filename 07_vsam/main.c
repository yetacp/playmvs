#include <stdio.h>
#include <string.h>
#include "vsam.h"
#include "main.h"

static int eof = 0;

int main()
{
     ExitList mstexl;
     RequestParameterList seqret;
     AccessMethodControlBlock vsamfile;

     Customer inrec;
     char userkey[6];

     v_el(&mstexl, EODAD,SYNAD,LERAD);
     v_acb(&vsamfile, &mstexl);
     v_rpl(&seqret, &vsamfile, &inrec, userkey);

     printf("Opening...\n");
     int ok = v_open(&vsamfile, 128);
     do
     {
          v_get(&seqret);
          if (!eof)
          {
               printf("%.20s %.30s - %.20s - %.2s\n",
                      inrec.name,
                      inrec.lastName,
                      inrec.city,
                      inrec.state);
          }
     } while (!eof);
     printf("Closing...\n");

     v_close(&vsamfile, 128);
     return 0;
}

void EODAD(void)
{
     eof = 1;
     printf("EODAD\n");
     SKIP_EXIT();
}

void SYNAD(void)
{
     eof = 1;
     printf("SYNAD\n");
     SKIP_EXIT();
}

void LERAD(void)
{
     eof = 1;
     printf("LERAD\n");
     SKIP_EXIT();
}
