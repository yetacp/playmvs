#ifndef __MAIN__
#define __MAIN__

#define SKIP_EXIT()            \
     asm("L     13,4(,13)"); \
     asm("LM    0,12,20(13)")

typedef struct Customer
{
    char customerNumber[6];
    char name[20];
    char lastName[30];
    char address[30];
    char city[20];
    char state[2];
    char zip[10];
} Customer;

void EODAD(void);
void SYNAD(void);
void LERAD(void);

#endif
