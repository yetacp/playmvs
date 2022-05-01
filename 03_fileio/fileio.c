#include <stdio.h>

int main(int argc, char *argv[])
{
   if (argc == 1)
   {
      FILE *fp = fopen("dd:output", "w");
      int i;
      for (i = 1; i <= 100; i++)
      {
         fprintf(fp, "Writing line number %d.\n", i);
      }
      fclose(fp);
   }
   else
   {
      printf("Incorrect number of parameters %d\n", argc);
   }
   return 0;
}
