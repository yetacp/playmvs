#include <stdio.h>
int main(int argc, char *argv[])
{
   if (argc == 3)
   {
      /* print argv parameters */
      printf("char * argv[] = %s %s %s\n", argv[0], argv[1], argv[2]);
      /* convert to number and sum */
      int first = atoi(argv[1]);
      int second = atoi(argv[2]);
      int sum = first + second;
      printf("%d + %d = %d\n", first, second, sum);
   }
   else
   {
      printf("Incorrect number of parameters\n");
   }
   return 0;
}
