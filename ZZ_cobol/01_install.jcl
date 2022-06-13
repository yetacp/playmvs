//HMVS01A JOB (TSO),
//           'COB01',
//           CLASS=A,
//           MSGCLASS=A,
//           MSGLEVEL=(1,1),
//           USER=HMVS01,
//           PASSWORD=CUL8TR,
//           REGION=8192K,
//           NOTIFY=HMVS01
/* -------------------------------------
//REPEAT    EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A repeat.cob
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(REPEAT),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//DISPLAY   EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A display.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(DISPLAY),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* -------------------------------------
//ASM01    EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(DISPLAY),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(DISPLAY),DISP=SHR
/* -------------------------------------
//COMPILE  PROC HLQ='HMVS01',MEMBER='DUMMY'
//COB      EXEC  PGM=IKFCBL00,REGION=4096K,
//         PARM='LOAD,PMAP,SIZE=4096K,BUF=1024K'
//STEPLIB   DD DISP=SHR,DSN=SYSC.LINKLIB
//SYSLIB    DD DISP=SHR,DSN=SYS1.MACLIB
//          DD DISP=SHR,DSN=SYS1.AMODGEN
//SYSUT1    DD DSN=&&SYSUT1,UNIT=VIO,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=VIO,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=VIO,SPACE=(1700,(300,50))
//SYSUT4    DD DSN=&&SYSUT3,UNIT=VIO,SPACE=(1700,(300,50))
//SYSPRINT  DD SYSOUT=*
//SYSIN     DD DISP=SHR,DSN=&HLQ..SOURCE(&MEMBER)
//SYSLIN    DD DISP=SHR,DSN=&HLQ..OBJ(&MEMBER)
//SYSPUNCH  DD DUMMY
//JOIN     EXEC PGM=IEBGENER
//SYSPRINT  DD SYSOUT=*
//SYSIN     DD DUMMY
//SYSUT1    DD DISP=SHR,DSN=&HLQ..OBJ(&MEMBER)
//          DD DISP=SHR,DSN=&HLQ..OBJ(DISPLAY)
//SYSUT2    DD DSN=&&TEMPLINK,
//           DISP=(NEW,PASS,DELETE),
//           DCB=(BLKSIZE=80,LRECL=80,RECFM=F),
//           UNIT=SYSALLDA,VOL=SER=PUB001,
//           SPACE=(CYL,(1,1))
//LINK     EXEC PGM=IEWL,PARM='XREF,LIST,LET',REGION=1024K
//SYSLMOD   DD DISP=SHR,DSN=&HLQ..LOAD(&MEMBER)
//SYSLIB    DD DISP=SHR,DSN=SYSC.COBLIB
//          DD DISP=SHR,DSN=SYS1.LINKLIB
//          DD DISP=SHR,DSN=PDPCLIB.NCALIB
//SYSPRINT  DD SYSOUT=A
//SYSUT1    DD UNIT=SYSALLDA,VOL=SER=PUB001,
//             SPACE=(1024,(200,20))
//SYSLIN    DD DSN=&&TEMPLINK,DISP=(OLD,DELETE,DELETE)
//         PEND
/* -------------------------------------
//REPEAT EXEC COMPILE,MEMBER=REPEAT
//