//AWESOME  JOB  (SETUP),
//             'Build Netsol',
//             CLASS=A,
//             MSGCLASS=X,
//             MSGLEVEL=(1,1),
//             USER=IBMUSER,PASSWORD=SYS1
//********************************************************************
//*
//* Desc: Build new NETSOL logon screen: ANSIART
//* Date: 30-04-2022
//* Built using Soldier of FORTRANs ANSi to EBCDiC builder
//*
//* Original ANSi File:   myMVS.ans
//* Original ANSi Date:   20220430
//*
//* Command Line Args: ../playmvs/projects/05_netsol/myMVS.ans --sysgen 
//*
//* After submitting run the following to refresh VTAM in hercules
//* console:
//*
//*     /P TSO
//*     /Z NET,QUICK
//*
//* Then the commands to bring the services back is:
//*
//*     /S NET
//*
//********************************************************************
//*
//* First delete the previous version if it exists
//*
//CLEANUP EXEC PGM=IDCAMS
//SYSPRINT DD  SYSOUT=*
//SYSIN    DD  *
 DELETE SYS1.UMODMAC(ANSIART)
 SET MAXCC=0
 SET LASTCC=0
//*
//* Then we "compress" SYS1.UMODMAC to free up space
//*
//COMP    EXEC COMPRESS,LIB='SYS1.UMODMAC'
//*
//* THEN WE COPY THE ORIGINAL NETSOL SOURCE FROM SYS1.AMACLIB
//* TO SYS1.UMODMAC
//*
//UMODMAC  EXEC PGM=IEBGENER
//SYSIN    DD DUMMY
//SYSPRINT DD SYSOUT=*
//SYSUT1   DD DISP=SHR,DSN=SYS1.AMACLIB(NETSOL)
//SYSUT2   DD DISP=SHR,DSN=SYS1.UMODMAC(NETSOL)
//*
//* THEN WE UPDATE SYS1.UMODMAC(NETSOL) TO DISPLAY OUR CUSTOM 3270
//*
//UPDATE   EXEC PGM=IEBUPDTE
//SYSPRINT DD SYSOUT=*
//SYSUT1   DD DISP=SHR,DSN=SYS1.UMODMAC
//SYSUT2   DD DISP=SHR,DSN=SYS1.UMODMAC
//SYSIN    DD DATA,DLM=$$
./ ADD NAME=ANSIART
* NETSOL screen created by ANSi2EBCDiC.py
         PUSH  PRINT
         PRINT OFF
EGMSG    DS 0C EGMSG
         $WCC  (RESETKBD,MDT)
         $SBA  (1,1)
* (1,1) Normal Display 
         DC    X'280000'
         DC    35C' '
         $SBA  (3,36)
* (3,36) (FG) Red 
         DC    X'2842F2'
         DC    C'__'
         $SBA  (3,38)
* (3,38) (FG) White 
         DC    X'2842F7'
         DC    C'  '
         $SBA  (3,40)
* (3,40) (FG) Red 
         DC    X'2842F2'
         DC    C'____    '
         DC    7C'_'
         $SBA  (3,55)
* (3,55) (FG) White 
         DC    X'2842F7'
         DC    15C' '
         $SBA  (4,16)
* (4,16) Bold/Intense (FG) Yellow 
         DC    X'2841F82842F6'
         DC    C'____'
         $SBA  (4,20)
* (4,20) Normal Display 
         DC    X'280000'
         DC    C' '
         $SBA  (4,21)
* (4,21) Bold/Intense (FG) Yellow 
         DC    X'2841F82842F6'
         DC    C'___'
         $SBA  (4,24)
* (4,24) Normal Display 
         DC    X'280000'
         DC    C'  '
         $SBA  (4,26)
* (4,26) Bold/Intense (FG) Yellow 
         DC    X'2841F82842F6'
         DC    C'__  __'
         $SBA  (4,32)
* (4,32) Normal Display 
         DC    X'280000'
         DC    C'   '
         $SBA  (4,35)
* (4,35) (FG) Red 
         DC    X'2842F2'
         DC    C'/  |/  / |  / / ___/'
         $SBA  (4,55)
* (4,55) (FG) White 
         DC    X'2842F7'
         DC    14C' '
         $SBA  (5,15)
* (5,15) Bold/Intense (FG) Yellow 
         DC    X'2841F82842F6'
         DC    C'/ __ '
         DC    X'79'
         DC    C'__ \/ / / /'
         $SBA  (5,32)
* (5,32) Normal Display 
         DC    X'280000'
         DC    C'  '
         $SBA  (5,34)
* (5,34) (FG) Red 
         DC    X'2842F2'
         DC    C'/ /|_/ /| |'
         $SBA  (5,45)
* (5,45) (FG) White 
         DC    X'2842F7'
         DC    C' '
         $SBA  (5,46)
* (5,46) (FG) Red 
         DC    X'2842F2'
         DC    C'/ /\__ \'
         $SBA  (5,54)
* (5,54) (FG) White 
         DC    X'2842F7'
         DC    13C' '
         $SBA  (6,14)
* (6,14) Bold/Intense (FG) Yellow 
         DC    X'2841F82842F6'
         DC    C'/ / /'
         $SBA  (6,19)
* (6,19) Normal Display 
         DC    X'280000'
         DC    C' '
         $SBA  (6,20)
* (6,20) Bold/Intense (FG) Yellow 
         DC    X'2841F82842F6'
         DC    C'/ / / /_/ /'
         $SBA  (6,31)
* (6,31) Normal Display 
         DC    X'280000'
         DC    C'  '
         $SBA  (6,33)
* (6,33) (FG) Red 
         DC    X'2842F2'
         DC    C'/ /  / /'
         $SBA  (6,41)
* (6,41) (FG) White 
         DC    X'2842F7'
         DC    C' '
         $SBA  (6,42)
* (6,42) (FG) Red 
         DC    X'2842F2'
         DC    C'| |/ /___/ /'
         $SBA  (6,54)
* (6,54) (FG) White 
         DC    X'2842F7'
         DC    12C' '
         $SBA  (7,13)
* (7,13) Bold/Intense (FG) Yellow 
         DC    X'2841F82842F6'
         DC    C'/_/ /_/ /_/\__, /'
         $SBA  (7,30)
* (7,30) Normal Display 
         DC    X'280000'
         DC    C'  '
         $SBA  (7,32)
* (7,32) (FG) Red 
         DC    X'2842F2'
         DC    C'/_/  /_/'
         $SBA  (7,40)
* (7,40) (FG) White 
         DC    X'2842F7'
         DC    C'  '
         $SBA  (7,42)
* (7,42) (FG) Red 
         DC    X'2842F2'
         DC    C'|___//____/'
         $SBA  (7,53)
* (7,53) (FG) White 
         DC    X'2842F7'
         DC    16C' '
         $SBA  (8,17)
* (8,17) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'____'
         $SBA  (8,21)
* (8,21) Normal Display 
         DC    X'280000'
         DC    C'  '
         $SBA  (8,23)
* (8,23) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/'
         $SBA  (8,24)
* (8,24) (FG) Yellow 
         DC    X'2842F6'
         DC    C'/___/'
         $SBA  (8,29)
* (8,29) Normal Display 
         DC    X'280000'
         DC    41C' '
         $SBA  (8,70)
* (8,70) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'__'
         $SBA  (8,72)
* (8,72) Normal Display 
         DC    X'280000'
         DC    15C' '
         $SBA  (9,16)
* (9,16) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/ __ \/ /___ ___'
         $SBA  (9,32)
* (9,32) Normal Display 
         DC    X'280000'
         DC    C'  '
         $SBA  (9,34)
* (9,34) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    6C'_'
         DC    C' '
         DC    10C'_'
         $SBA  (9,51)
* (9,51) Normal Display 
         DC    X'280000'
         DC    C'  '
         $SBA  (9,53)
* (9,53) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'__  '
         DC    6C'_'
         DC    C'  ____/ /'
         $SBA  (9,72)
* (9,72) Normal Display 
         DC    X'280000'
         DC    14C' '
         $SBA  (10,15)
* (10,15) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/ /_/ / / __ '
         DC    X'79'
         DC    C'/ / / / __ '
         DC    X'79'
         DC    C'/ ___/ __ \/ /'
         $SBA  (10,55)
* (10,55) Normal Display 
         DC    X'280000'
         DC    C' '
         $SBA  (10,56)
* (10,56) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/ / __ \/ __'
         $SBA  (10,68)
* (10,68) Normal Display 
         DC    X'280000'
         DC    C'  '
         $SBA  (10,70)
* (10,70) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/'
         $SBA  (10,71)
* (10,71) Normal Display 
         DC    X'280000'
         DC    13C' '
         $SBA  (11,14)
* (11,14) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/ ____/ / /_/ / /_/ / /_/ / /'
         $SBA  (11,43)
* (11,43) Normal Display 
         DC    X'280000'
         DC    C'  '
         $SBA  (11,45)
* (11,45) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/ /_/ / /_/ / / / / /_/'
         $SBA  (11,68)
* (11,68) Normal Display 
         DC    X'280000'
         DC    C' '
         $SBA  (11,69)
* (11,69) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/'
         $SBA  (11,70)
* (11,70) Normal Display 
         DC    X'280000'
         DC    12C' '
         $SBA  (12,13)
* (12,13) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/_/'
         $SBA  (12,16)
* (12,16) Normal Display 
         DC    X'280000'
         DC    C'   '
         $SBA  (12,19)
* (12,19) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/_/\__,_/\__,'
         $SBA  (12,32)
* (12,32) Normal Display 
         DC    X'280000'
         DC    C' '
         $SBA  (12,33)
* (12,33) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/\__, /_/'
         $SBA  (12,42)
* (12,42) Normal Display 
         DC    X'280000'
         DC    C'   '
         $SBA  (12,45)
* (12,45) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'\____/\__,_/_/ /_/\__,_/'
         $SBA  (12,69)
* (12,69) Normal Display 
         DC    X'280000'
         DC    26C' '
         $SBA  (13,27)
* (13,27) Bold/Intense (FG) Blue 
         DC    X'2841F82842F1'
         DC    C'/____//____/'
         $SBA  (13,39)
* (13,39) Normal Display 
         DC    X'280000'
         DC    24C' '
         $SBA  (16,25)
* (16,25) Bold/Intense (FG) Green 
         DC    X'2841F82842F4'
         DC    C'TSO Logon ='
         DC    X'6E'
         $SBA  (16,37)
* (16,37) Normal Display 
         DC    X'280000'
         DC    24C' '
         $SBA  (19,25)
* (19,25) Bold/Intense (FG) Green 
         DC    X'2841F82842F4'
         DC    C'https://github.com/yetacp/playmvs'
         $SBA  (19,58)
* (19,58) Normal Display 
         DC    X'280000'
         DC    32C' '
         $SBA  (21,33)
* (21,33) Bold/Intense (FG) Green 
         DC    X'2841F82842F4'
         DC    C'2022 MIT License'
         $SBA  (21,49)
* (21,49) Normal Display 
         DC    X'280000'
* Insert Cursor and unprotected field
         $SBA  (16,38)
         DC    X'2842F2'  SA COLOR RED
         $SF   (UNPROT,HI)
         $IC
         DC    CL20' '
         DC    X'280000'
         DC    X'1DF8'     SF (PROT,HIGH INTENSITY)
         $SBA  (17,80)
         $SF   (SKIP,HI)
EGMSGLN EQU *-EGMSG
         POP   PRINT
./ CHANGE NAME=NETSOL
         CLI   MSGINDEX,X'0C'                                           23164802
         BNE   EGSKIP                                                   23164804
         LA    R3,EGMSGLN                                               23164808
         L     R4,=A(EGMSG)                                             23164810
*                                                                       23164812
         WRITE RPL=(PTRRPL),                                           X23164814
               OPTCD=(LBT,ERASE),                                      X23164816
               AREA=(R4),                                              X23164818
               RECLEN=(R3),                                            X23164820
               EXIT=WRITEND                                             23164822
*                                                                       23164824
         B EGOK                                                         23164826
*                                                                       23164828
*                                                                       23164830
EGSKIP   DS 0H EGSKIP                                                   23164832
EGOK     DS 0H EGOK                                                     23166010
         COPY ANSIART                     , logon screen copy book      66810010
$$
//*
//* With that done its time to assemble our new screen
//* We assemble SYS1.UMODMAC(NETSOL) with IFOX00
//*
//ASM     EXEC PGM=IFOX00,REGION=1024K
//SYSLIB   DD  DISP=SHR,DSN=SYS1.UMODMAC,DCB=LRECL=32720
//         DD  DISP=SHR,DSN=SYS2.MACLIB
//         DD  DISP=SHR,DSN=SYS1.MACLIB
//         DD  DISP=SHR,DSN=SYS1.AMODGEN
//SYSUT1   DD  UNIT=VIO,SPACE=(1700,(600,100))
//SYSUT2   DD  UNIT=VIO,SPACE=(1700,(300,50))
//SYSUT3   DD  UNIT=VIO,SPACE=(1700,(300,50))
//SYSPRINT DD  SYSOUT=*,DCB=BLKSIZE=1089
//SYSPUNCH DD  DISP=(NEW,PASS,DELETE),
//             UNIT=VIO,SPACE=(TRK,(2,2)),
//             DCB=(BLKSIZE=80,LRECL=80,RECFM=F)
//SYSIN    DD  *
ISTNSC00 CSECT ,
         NETSOL SYSTEM=VS2
         END   ,
//*
//* Then we link it and put it in SYS1.VTAMLIB(ISTNSC00)
//*
//LKED    EXEC PGM=IEWL,PARM='XREF,LIST,LET,NCAL',REGION=1024K
//SYSPRINT DD  SYSOUT=*
//SYSLIN   DD  DISP=(OLD,DELETE,DELETE),DSN=*.ASM.SYSPUNCH
//SYSLMOD  DD  DISP=SHR,DSN=SYS1.VTAMLIB(ISTNSC00)
//SYSUT1   DD  UNIT=VIO,SPACE=(1024,(200,20))
//*
//
