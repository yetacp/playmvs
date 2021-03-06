//HMVS01A JOB (TSO),'VM TOY',
//           CLASS=A,MSGCLASS=A,MSGLEVEL=(1,1),
//           USER=HMVS01,PASSWORD=CUL8TR,
//           REGION=8192K,
//           NOTIFY=HMVS01
/* ------------------------------------------
//CP01     EXEC PGM=IEBGENER
//SYSUT1   DD DATA,DLM=$$
::A vm.s
$$
//SYSUT2   DD DSN=HMVS01.SOURCE(VM),DISP=SHR
//SYSPRINT DD SYSOUT=*
//SYSOUT   DD SYSOUT=*
//SYSIN    DD *
/* ------------------------------------------
//CP02     EXEC PGM=IEBGENER
//SYSUT1   DD DATA,DLM=$$
::A vmcode.s
$$
//SYSUT2   DD DSN=HMVS01.SOURCE(VMCODE),DISP=SHR
//SYSPRINT DD SYSOUT=*
//SYSOUT   DD SYSOUT=*
//SYSIN    DD *
/* ------------------------------------------
//CP03     EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
PROC 0
    ALLOC FI(SYSIN)    DA(*)
    ALLOC FI(SYSPRINT) DA(*)
    ALLOC FI(SYSTERM)  DA(*)
    CALL 'HMVS01.LOAD(VM)'
    FREE FI(SYSIN, SYSPRINT, SYSTERM)
EXIT
$$
//SYSUT2     DD DSN=HMVS01.CLIST(VM),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM01    EXEC ASMFC,
//         MAC1='SYS2.MACLIB',
//         MAC2='PDPCLIB.MACLIB',
//         PARM='OBJ'
//SYSUT1   DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2   DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3   DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN    DD DSN=HMVS01.SOURCE(VM),DISP=SHR
//SYSGO    DD DSN=HMVS01.OBJ(VM),DISP=SHR
/* ------------------------------------------
//ASM02    EXEC ASMFC,
//         MAC1='SYS2.MACLIB',
//         MAC2='PDPCLIB.MACLIB',
//         PARM='OBJ'
//SYSUT1   DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2   DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3   DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN    DD DSN=HMVS01.SOURCE(VMCODE),DISP=SHR
//SYSGO    DD DSN=HMVS01.OBJ(VMCODE),DISP=SHR
/* ------------------------------------------
//LINK    EXEC LKED
//SYSLMOD DD DSN=HMVS01.LOAD(VM),DISP=SHR
//SYSLIB   DD DSN=PDPCLIB.NCALIB,DISP=SHR
//PRIVLIB  DD DSN=HMVS01.OBJ,DISP=SHR
//SYSIN    DD *
 INCLUDE SYSLIB(MVSSTART)
 INCLUDE SYSLIB(START)
 INCLUDE SYSLIB(MVSSUPA)
 INCLUDE SYSLIB(STDIO)
 INCLUDE SYSLIB(STDLIB)
 INCLUDE SYSLIB(CTYPE)
 INCLUDE SYSLIB(STRING)
 INCLUDE SYSLIB(TIME)
 INCLUDE SYSLIB(ERRNO)
 INCLUDE SYSLIB(ASSERT)
 INCLUDE SYSLIB(LOCALE)
 INCLUDE SYSLIB(MATH)
 INCLUDE SYSLIB(SETJMP)
 INCLUDE SYSLIB(SIGNAL)
 INCLUDE PRIVLIB(VMCODE)
 INCLUDE PRIVLIB(VM)
 ENTRY @@MAIN
 NAME VM(R)
//
