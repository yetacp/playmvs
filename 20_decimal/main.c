#include <stdio.h>
#include <string.h>

void pack8(char *output, char *input)
{
    asm("PACK  0(7,%[output]),0(8,%[input])"
        : /* No output operands */
        : /* Input operands */
        [input] "r"(input),
        [output] "r"(output)
        : "0", "1", "15");
}

void add7(char *output, char *input)
{
    asm("AP    0(7,%[output]),0(7,%[input])"
        : /* No output operands */
        : /* Input operands */
        [input] "r"(input),
        [output] "r"(output)
        : "0", "1", "15");
}

void sub7(char *output, char *input)
{
    asm("SP    0(7,%[output]),0(7,%[input])"
        : /* No output operands */
        : /* Input operands */
        [input] "r"(input),
        [output] "r"(output)
        : "0", "1", "15");
}

void display(char *name, char *buffer)
{
    int i;
    printf("%s", name);
    for (i = 0; i < 7; i++)
    {
        printf("%.2X", buffer[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    const char *LZEROS = "00000000";
    const char *L12345678 = "12345678";
    const char *L00000011 = "00000011";

    char a[8];
    char b[8];
    char pa[7];
    char pb[7];

    
    strncpy(a, L12345678, 8);
    pack8(pa, a);
    strncpy(b, L00000011, 8);
    pack8(pb, b);

    printf("\nInitial values\n");
    display("A=", pa);
    display("B=", pb);

    add7(pa, pb);
    printf("\nAfter addition\n");
    display("A=", pa);
    display("B=", pb);

    sub7(pa, pb);
    printf("\nAfter subtraction\n");
    display("A=", pa);
    display("B=", pb);

    return 0;
}
