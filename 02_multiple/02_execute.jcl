//HMVS01A JOB (TSO),'HELLO',
//           CLASS=A,MSGCLASS=A,MSGLEVEL=(1,1),
//           USER=HMVS01,PASSWORD=CUL8TR,
//           REGION=8192K,
//           NOTIFY=HMVS01
//GO       EXEC PGM=HELLO
//STEPLIB   DD DSN=HMVS01.LOAD,DISP=SHR
//SYSPRINT  DD SYSOUT=*
//SYSTERM   DD SYSOUT=*
//SYSIN     DD *
/*