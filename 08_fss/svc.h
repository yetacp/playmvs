#ifndef SVC
#define SVC

typedef struct REGS
{
   unsigned int R0;
   unsigned int R1;
   unsigned int R15;
} REGS;

void EXSVC(int svc, REGS *regs);

void EXEC(REGS *regs);

#endif
