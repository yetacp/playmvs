#!/usr/bin/python
# -*- coding: utf-8 -*-

list = ["alloc", "chainr", "excp", "finddevt", "fss", "tso", "svc"]

print("""//HMVS01A JOB  CLASS=A,MSGCLASS=A,MSGLEVEL=(1,1),
//           USER=HMVS01,PASSWORD=CUL8TR,
//           REGION=8192K,
//           NOTIFY=HMVS01""")

count = 0
for file in list:
    count = count + 1
    print("""/* ------------------------------------------
//CP{count}      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A {f1}.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE({f2}),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM{count}     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE({f2}),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ({f2}),DISP=SHR""".format(\
   count=count, f1=file, f2=file.upper()))