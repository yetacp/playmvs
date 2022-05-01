********************************************
* struct REGS
* {
*   unsigned int R0;
*   unsigned int R1;
*   unsigned int R15;
* };
* void EXEC(struct REGS *regs);
********************************************
         COPY  PDPTOP
         CSECT
* Program text area
         DS    0F
* X-func EXEC prologue
EXEC     PDPPRLG CINDEX=0,FRAME=88,BASER=12,ENTRY=YES
         B     @@FEN0
         LTORG
@@FEN0   EQU   *
         DROP  12
         BALR  12,0
         USING *,12
@@PG0    EQU   *
         LR    11,1
         L     10,=A(@@PGT0)
* Function EXEC code
* Initialize registers
         L     2,4(11) *  regs
         L     0,0(3)  *  regs->R0
         L     1,4(3)  *  regs->R1
         L     15,8(3) *  regs->R15
* Execute service
         BALR  14,15
* Return registers
         ST    0,0(3)  *  regs->R0
         ST    1,4(3)  *  regs->R1
         ST    15,8(3) *  regs->R15
         L     15,0
* Function EXEC epilogue
         PDPEPIL
* Function EXEC literal pool
         DS    0F
         LTORG
* Function EXEC page table
         DS    0F
@@PGT0   EQU   *
         DC    A(@@PG0)
         END
