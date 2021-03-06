//HMVS01A JOB (TSO),'FSS',
//           CLASS=A,
//           MSGCLASS=A,
//           MSGLEVEL=(1,1),
//           USER=HMVS01,PASSWORD=CUL8TR,
//           REGION=8192K,
//           NOTIFY=HMVS01
/* ------------------------------------------
//CP1      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A alloc.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(ALLOC),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM1     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(ALLOC),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(ALLOC),DISP=SHR
/* ------------------------------------------
//CP2      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A chainr.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(CHAINR),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM2     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(CHAINR),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(CHAINR),DISP=SHR
/* ------------------------------------------
//CP3      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A excp.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(EXCP),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM3     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(EXCP),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(EXCP),DISP=SHR
/* ------------------------------------------
//CP4      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A finddevt.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(FINDDEVT),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM4     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(FINDDEVT),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(FINDDEVT),DISP=SHR
/* ------------------------------------------
//CP5      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A fss.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(FSS),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM5     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(FSS),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(FSS),DISP=SHR
/* ------------------------------------------
//CP6      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A tso.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(TSO),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM6     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(TSO),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(TSO),DISP=SHR
/* ------------------------------------------
//CP7      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A svc.asm
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(SVC),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//CP8      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A exec.asm
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(EXEC),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM1     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(SVC),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(SVC),DISP=SHR
/* ------------------------------------------
//ASM2     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(EXEC),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(EXEC),DISP=SHR
/* ------------------------------------------
//LINK     EXEC LKED
//SYSLMOD DD DSN=HMVS01.LOAD(FSS),DISP=SHR
//SYSLIB    DD DSN=PDPCLIB.NCALIB,DISP=SHR
//PRIVLIB   DD DSN=HMVS01.OBJ,DISP=SHR
//SYSIN     DD DATA,DLM=$$
 INCLUDE PRIVLIB(FSS)
 INCLUDE PRIVLIB(TSO)
 INCLUDE PRIVLIB(SVC)
 NAME FSS(R)
$$
//
