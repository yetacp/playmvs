#!/usr/bin/python3
# -*- coding: utf-8 -*-

list = ["lapi", "lauxlib", "lbaselib", "lcode", "lcorolib", "lctype", "ldblib",
        "ldebug", "ldo", "ldump", "lfunc", "lgc", "linit", "liolib", "llex", "lmathlib",
        "lmem", "loadlib", "lobject", "lopcodes", "loslib", "lparser", "lstate",
        "lstring", "lstrlib", "ltable", "ltablib", "ltm", "lundump", "lutf8lib", 
        "lvm", "lzio", "lua"]

with open("jcldep.m4", "w") as jf:
    count = 0
    for file in list:
        count = count + 1
        print("{count} {file}".format(count=count, file=file))
        jf.write("""jcl/{count:02d}.done: {f1}.s
\t@echo "Preparing EBCDIC for {f1}..."
\t@$(RDRPREP) jcl/{count:02d}.jcl tmp.jcl_E
\t@echo "Installing {f1}..."
\tnc -w1 $(HERCHOST) $(HERCPORT) < tmp.jcl_E
\ttouch jcl/{count:02d}.done
\tsleep 2

""".format(count=count, f1=file))
        with open("jcl/{count:02d}.jcl".format(count=count), "w") as f:
            f.write("""//HMVS01A JOB (TSO),'LUA{count:02d}',
//           CLASS=A,
//           MSGCLASS=A,
//           MSGLEVEL=(1,1),
//           USER=HMVS01,PASSWORD=CUL8TR,
//           REGION=8192K,
//           NOTIFY=HMVS01
/* ------------------------------------------
//CP1      EXEC PGM=IEBGENER
//SYSUT1     DD DATA,DLM=$$
::A {f1}.s
$$
//SYSUT2     DD DSN=HMVS01.SOURCE(LUA{count:02d}),DISP=SHR
//SYSPRINT   DD SYSOUT=*
//SYSOUT     DD SYSOUT=*
//SYSIN      DD *
/* ------------------------------------------
//ASM1     EXEC ASMFC,
//           MAC1='SYS2.MACLIB',
//           MAC2='PDPCLIB.MACLIB',
//           PARM='OBJ'
//SYSUT1     DD DSN=&&SYSUT1,UNIT=SYSDA,SPACE=(1700,(600,100))
//SYSUT2     DD DSN=&&SYSUT2,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSUT3     DD DSN=&&SYSUT3,UNIT=SYSDA,SPACE=(1700,(300,50))
//SYSIN      DD DSN=HMVS01.SOURCE(LUA{count:02d}),DISP=SHR
//SYSGO      DD DSN=HMVS01.OBJ(LUA{count:02d}),DISP=SHR
/* ------------------------------------------
//CLEANUP   EXEC  PGM=IDCAMS
//SYSPRINT   DD SYSOUT=*
//SYSIN      DD *
  DELETE HMVS01.SOURCE(LUA{count:02d})
  SET MAXCC=0
  SET LASTCC=0
//
""".format(count=count, f1=file, f2=file.upper()))
