//HMVS01A JOB (LUA),
//          'RUN LUA',
//          CLASS=A,
//          MSGCLASS=A,
//          MSGLEVEL=(1,1),
//          USER=HMVS01,
//          PASSWORD=CUL8TR,
//          REGION=8192K,
//          NOTIFY=HMVS01
//RUN      EXEC PGM=LUA,PARM='DD:PROG'
//STEPLIB   DD DSN=HMVS01.LOAD,DISP=SHR
//PROG      DD DSN=HMVS01.SOURCE(LUATEST),DISP=SHR
//SYSPRINT  DD SYSOUT=*
//SYSTERM   DD SYSOUT=*
//SYSIN     DD *
/*
