#include <stdio.h>

int first = 0x01020304;
int second = 0x05060708;
int sum = 0x090A0B0C;

int main(int argc, char *argv[])
{
   if (argc == 3)
   {
      // Breakpoint - after print argv
      printf("char * argv[] = %s %s %s\n", argv[0], argv[1], argv[2]);
      asm("WTO   'After print argv'");
      asm("DDTBRK");

      // Breakpoint - After convert to number
      first = atoi(argv[1]);
      second = atoi(argv[2]);
      asm("WTO   'After convert to number'");
      asm("DDTBRK");

      // Breakpoint - After sum
      sum = first + second;
      asm("WTO   'After sum'");
      asm("DDTBRK");

      printf("%d + %d = %d\n", first, second, sum);
   }
   else
   {
      // Breakpoint - argc != 3
      asm("WTO   'argc != 3'");
      asm("DDTBRK");
      printf("Incorrect number of parameters\n");
   }
   return 0;
}
