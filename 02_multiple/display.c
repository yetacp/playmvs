#include <stdio.h>
#include "display.h"

void display_message(char *msg)
{
     int i;
     for (i = 0; i < 10; i++)
     {
          printf("Hello %s, %d!\n", msg, i);
     }
}
