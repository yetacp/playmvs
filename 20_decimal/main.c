#include <stdio.h>
int main(int argc, char *argv[])
{
   char *input = "12345678";
   char *output = "00000000";

   asm("PACK  0(8,%[output]),0(8,%[input])"
       : /* No output operands */
       : /* Input operands */
       [input] "r"(input),
       [output] "r"(output)
       : "0", "1", "15");
   int i;
   for (i = 0; i < 8; i++)
   {
      printf("%.2X ", output[i]);
   }
   return 0;
}

asm("\nINPUT\tDC    CL8'12345678'");
asm("\nOUTPUT\tDS    PL8");