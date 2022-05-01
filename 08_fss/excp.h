/*-----------------------------------------------------------------
 |  Copyright (c) 2012-, Tommy Sprinkle (tommy@tommysprinkle.com)  
 |  Licensed under the NEW BSD Open Source License
  -----------------------------------------------------------------*/

#ifndef EXCP
#define EXCP

struct sEXCP
{
   unsigned char  mbbcchhr[8];
   int            keylen;
   int            datalen;
   unsigned char *count;
   unsigned char *key;
   unsigned char *data;
};

typedef void* excpfile;

excpfile xOPEN(char *ddname);
excpfile xOPENV(char *ddname);
int      xCLOSE(excpfile ef);
int      xREAD(excpfile ef, struct sEXCP *excp, int tt, int r);
int      xTREAD(excpfile ef, struct sEXCP *excp, int tt);

#endif
