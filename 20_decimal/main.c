#include <stdio.h>
#include <string.h>

void m_pack(char *packed, char *zoned)
{
    asm("PACK  0(15,%[packed]),0(15,%[zoned])"
        :
        : [packed] "r"(packed), [zoned] "r"(zoned)
        : "0", "1", "15");
}

void m_add(char *accumulator, char *term)
{
    asm("AP    0(15,%[accumulator]),0(15,%[term])"
        :
        : [accumulator] "r"(accumulator), [term] "r"(term)
        : "0", "1", "15");
}

void m_sub(char *accumulator, char *subtraend)
{
    asm("SP    0(15,%[accumulator]),0(15,%[subtraend])"
        :
        : [accumulator] "r"(accumulator), [subtraend] "r"(subtraend)
        : "0", "1", "15");
}

void m_mul(char *accumulator, char *factor)
{
    asm("MP    0(15,%[accumulator]),8(7,%[factor])" /* Hack. Truncate factor */
        :
        : [accumulator] "r"(accumulator), [factor] "r"(factor)
        : "0", "1", "15");
}

void m_div(char *accumulator, char *divisor)
{
    asm("DP    0(15,%[accumulator]),8(7,%[divisor])" /* Hack. Truncate divisor */
        :
        : [accumulator] "r"(accumulator), [divisor] "r"(divisor)
        : "0", "1", "15");
}

int m_cvb(char *decimal)
{
    int result;
    asm("CVB   %[result],7(0,%[decimal])" /* Hack. Truncate decimal */
        : [result] "=r"(result)
        : [decimal] "r"(decimal)
        : "0", "1", "15");
    return result;
}

#define VLEN 15

void display(char *name, char *packed)
{
    printf("%s", name);
    int i;
    for (i = 0; i < VLEN; i++)
    {
        printf("%.2X", packed[i]);
        if (i == 7)
        {
            printf(" ");
        }
    }
    printf("\n");
}

void packer(char *packed, char *zoned)
{
    char tmp[VLEN];
    strncpy(tmp, zoned, VLEN);
    m_pack(packed, tmp);
}

int main(int argc, char *argv[])
{
    char packed_a[VLEN];
    char packed_b[VLEN];
    char packed_c[VLEN];

    int a;

    /*                123456789012345 */
    packer(packed_a, "000000001234567");
    packer(packed_b, "000000000000123");
    packer(packed_c, "000000000000100");

    packed_a[VLEN - 1] = packed_a[VLEN - 1] & 0xF0 | 0x0D;

    printf("Initial values\n");
    display("  A = ", packed_a);
    display("  B = ", packed_b);
    display("  C = ", packed_c);

    m_add(packed_a, packed_b);
    printf("\n!\nAfter A = A + B\n");
    display("  A = ", packed_a);

    a = m_cvb(packed_a);
    printf("  CVB(A) = %d", a);

    m_sub(packed_a, packed_b);
    printf("\n!\nAfter A = A - B\n");
    display("  A = ", packed_a);
    a = m_cvb(packed_a);
    printf("  CVB(A)= %d", a);

    m_mul(packed_a, packed_b);
    printf("\n!\nAfter A = A * B\n");
    display("  A = ", packed_a);
    a = m_cvb(packed_a);
    printf("  CVB(A) = %d", a);

    m_add(packed_a, packed_c);
    printf("\n!\nAfter A = A + C\n");
    display("  A = ", packed_a);
    a = m_cvb(packed_a);
    printf("  CVB(A) = %d", a);

    m_div(packed_a, packed_b);
    printf("\n!\nAfter A = A / B\n");
    display("  A = ", packed_a);

    return 0;
}
