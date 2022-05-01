#!/usr/bin/python
# -*- coding: utf-8 -*-

list = ["lapi", "lauxlib", "lbaselib", "lcode", "lcorolib", "lctype", "ldblib", \
     "ldebug", "ldo", "ldump", "lfunc", "lgc", "linit", "liolib", "llex", "lmathlib", \
	 "lmem", "loadlib", "lobject", "lopcodes", "loslib", "lparser", "lstate", \
	 "lstring", "lstrlib", "ltable", "ltablib", "ltm", "lundump", "lutf8lib", "lvm", "lzio"]

count = 0
for file in list:
    count = count + 1
    print("{count} {file}".format(count=count, file=file))
    f = open("jcl/{count:02d}.jcl".format(count=count), "w")
    f.write("""//HMVS01A JOB  CLASS=A,MSGCLASS=A,MSGLEVEL=(1,1),
//           USER=HMVS01,PASSWORD=CUL8TR,
//           REGION=8192K,
//           NOTIFY=HMVS01
/* ------------------------------------------
//CP01      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A {f1}.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(LUA{count:02d}),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM01     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1    DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2    DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3    DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN     DD DSN=HMVS01.SOURCE(LUA{count:02d}),DISP=SHR
//SYSGO     DD DSN=HMVS01.OBJ(LUA{count:02d}),DISP=SHR
/* ------------------------------------------
//DELETE    EXEC  PGM=IDCAMS
//MYMEMBER  DD DISP=SHR,DSN=HMVS01.SOURCE({f2})
//SYSPRINT  DD    SYSOUT=A
//SYSIN     DD    *
     DELETE HMVS01.SOURCE(LUA{count:02d}) FILE(MYMEMBER)-
     /*
//
""".format(count=count, f1=file, f2=file.upper()))
    f.close()
