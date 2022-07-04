//HMVS01A JOB (TSO),'MYDB',
//           CLASS=A,MSGCLASS=A,MSGLEVEL=(1,1),
//           USER=HMVS01,PASSWORD=CUL8TR,
//           REGION=8192K,
//           NOTIFY=HMVS01
//CLIST   EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
PROC 0
    ALLOC FI(SYSIN)    DA(*)
    ALLOC FI(SYSPRINT) DA(*)
    ALLOC FI(SYSTERM)  DA(*)
    CALL 'HMVS01.LOAD(REST)'
    FREE FI(SYSIN, SYSPRINT, SYSTERM)
EXIT
$$
//SYSUT2     DD DSN=HMVS01.CLIST(REST),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//SOURCE  EXEC PGM=PDSLOAD
//STEPLIB  DD  DSN=SYSC.LINKLIB,DISP=SHR
//SYSPRINT DD  SYSOUT=*
//SYSUT2   DD  DSN=HMVS01.SOURCE,DISP=SHR
//SYSUT1   DD  DATA,DLM=$$
./ ADD NAME=CEDIT
::A client_edit.s
./ ADD NAME=CLIST
::A client_list.s
./ ADD NAME=CNEW
::A client_new.s
./ ADD NAME=FCEDIT
::A frm_client_edit.s
./ ADD NAME=FCLIST
::A frm_client_list.s
./ ADD NAME=FMAIN
::A frm_main.s
./ ADD NAME=FCNEW
::A frm_client_new.s
./ ADD NAME=REST
::A main.s
$$
/* ------------------------------------------
//TCSASM PROC M=
//ASM     EXEC  PGM=IFOX00,REGION=1024K,
//         PARM='LINECOUNT(45)'
//SYSLIB   DD    DISP=SHR,DSN=SYS1.MACLIB
//         DD    DISP=SHR,DSN=SYS2.MACLIB
//         DD    DISP=SHR,DSN=SYS2.SXMACLIB
//         DD    DISP=SHR,DSN=SYS1.AMODGEN
//         DD    DISP=SHR,DSN=PDPCLIB.MACLIB
//         DD    DISP=SHR,DSN=HMVS01.SOURCE
//SYSUT1   DD    DSN=&&SYSUT1,UNIT=VIO,SPACE=(1700,(600,100))
//SYSUT2   DD    DSN=&&SYSUT2,UNIT=VIO,SPACE=(1700,(300,50))
//SYSUT3   DD    DSN=&&SYSUT3,UNIT=VIO,SPACE=(1700,(300,50))
//SYSPRINT DD    SYSOUT=*
//SYSIN    DD    DISP=SHR,DSN=HMVS01.SOURCE(&M)
//SYSPUNCH DD    DISP=SHR,DSN=HMVS01.OBJ(&M)
//   PEND
//CEDIT    EXEC TCSASM,M=CEDIT
//CLIST    EXEC TCSASM,M=CLIST
//CNEW     EXEC TCSASM,M=CNEW
//FCEDIT   EXEC TCSASM,M=FCEDIT
//FCLIST   EXEC TCSASM,M=FCLIST
//FCNEW    EXEC TCSASM,M=FCNEW
//FMAIN    EXEC TCSASM,M=FMAIN
//REST     EXEC TCSASM,M=REST
//SENDMSG  EXEC TCSASM,M=SENDMSG
//* -----------------------------------
//LINK  EXEC LKED
//SYSLMOD  DD DSN=HMVS01.LOAD(REST),DISP=SHR
//PDPLIB   DD DSN=PDPCLIB.NCALIB,DISP=SHR
//EZALIB   DD DSN=SYS2.LINKLIB,DISP=SHR
//OBJLIB   DD DSN=HMVS01.OBJ,DISP=SHR
//LOADLIB  DD DSN=HMVS01.LOAD,DISP=SHR
//SYSIN    DD DATA,DLM=$$                                   
 INCLUDE PDPLIB(MVSSTART)
 INCLUDE PDPLIB(MVSSUPA)
 INCLUDE PDPLIB(START)
 INCLUDE PDPLIB(ASSERT)
 INCLUDE PDPLIB(CTYPE)
 INCLUDE PDPLIB(ERRNO)
 INCLUDE PDPLIB(SETJMP)
 INCLUDE PDPLIB(SIGNAL)
 INCLUDE PDPLIB(STDIO)
 INCLUDE PDPLIB(STDLIB)
 INCLUDE PDPLIB(STRING)
 INCLUDE PDPLIB(TIME)
 INCLUDE EZALIB(EZASOH03)
 INCLUDE LOADLIB(EZASMI)
 INCLUDE LOADLIB(FSS)
 INCLUDE OBJLIB(CEDIT)
 INCLUDE OBJLIB(CLIST)
 INCLUDE OBJLIB(CNEW)
 INCLUDE OBJLIB(FCEDIT)
 INCLUDE OBJLIB(FCLIST)
 INCLUDE OBJLIB(FCNEW)
 INCLUDE OBJLIB(FMAIN)
 INCLUDE OBJLIB(REST)
 ENTRY @@MAIN
 NAME REST(R)                                 
$$                                                         
//