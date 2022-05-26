# Intercomm Setup

In order to get Intercomm set up on MVS Sysgen System, you will need to take next steps:

1. Attach DASD image to Hercules, by entering **ATTACH 181 3380 int001.181.cckd** at Hercules command line.

2. Vary it online to MVS: **/V 181,ONLINE** on MVS console.

3. Mount volume on MVS: **/M 181,VOL=(SL,INT001),USE=PRIVATE** on MVS console.

4. In RFE, option 3.4 enter volume **INT001**

5. Add it to **SYS1.PARMLIB(VATLST00)** so it gets mounted that way on subsequent IPLs.

```
MVSRES,0,2,3350    ,Y        SYSTEM RESIDENCE (PRIVATE)
MVS000,0,2,3350    ,Y        SYSTEM DATASETS (PRIVATE)
PAGE00,0,2,3350    ,Y        PAGE DATASETS (PRIVATE)
PUB000,1,2,3380    ,N        PUBLIC DATASETS (PRIVATE)
PUB001,1,2,3390    ,N        PUBLIC DATASETS (PRIVATE)
SMP000,1,2,3350    ,N        DISTRIBUTION LIBRARIES (PRIVATE)
SORTW1,1,1,2314    ,N        SORT WORK (PUBLIC)
SORTW2,1,1,2314    ,N        SORT WORK (PUBLIC)
SORTW3,1,1,2314    ,N        SORT WORK (PUBLIC)
SORTW4,1,1,2314    ,N        SORT WORK (PUBLIC)
SORTW5,1,1,2314    ,N        SORT WORK (PUBLIC)
SORTW6,1,1,2314    ,N        SORT WORK (PUBLIC)
SPOOL1,0,2,3350    ,Y        JES2 QUEUES (PRIVATE)
SYSCPK,1,2,3350    ,N        COMPILER/TOOLS (PRIVATE)
WORK00,1,0,3350    ,N        WORK PACK (STORAGE)
WORK01,1,0,3350    ,N        WORK PACK (STORAGE)
INT000,1,2,3380    ,N        INTERCOMM (PRIVATE)
```

6. Connect user catalog to MVS master catalog and define the INT high-level qualifier alias. Run job  **INT.JCL.CNTL(IMPCAT)** to do this. It should complete with a condition code 0. If you have datasets named INT.* on your system already, you will need to uncatalog them before running this job and recatalog them afterward.

```
//IMPCAT   JOB (5161A020,1A11),'CATALOG',CLASS=A,MSGCLASS=A,
//             MSGLEVEL=(1,1),NOTIFY=HMVS01
//IDCAMS   EXEC PGM=IDCAMS
//SYSPRINT DD SYSOUT=*
//SYSIN    DD *
IMPORT OBJECTS((SYS1.UCAT.ICOM VOLUME(INT001) -
                                 DEVICETYPE(3380))) CONNECT
DEFINE ALIAS (NAME(INT) RELATE(SYS1.UCAT.ICOM))
//  
```

7. **SYS2.PROCLIB** dataset needs 10 directory blocks to store INTERCOMM procedures. For MVSYSGEN, it is no necessary to expand SYS2.PROCLIB.

8. Copy the Intercomm-supplied procs to SYS2.PROCLIB. Intercomm supplies several procs for application building and system maintenance. Run the job **INT.JCL.CNTL(COPYPROX)** to copy them.

9. Define VTAM application major node. Intercomm, like all VTAM applications, uses a definition in **SYS1.VTAMLST**. For consistency, and ease of maintenance, this is defined in its own major node (PDS member). Run the job **INT.JCL.CNTL(VTAMLST)** to create this member. After doing so, issue the command **/V NET,ACT,ID=AICOM** on the system console to activate the new definition. You may add a line in the VTAM configuration list in **SYS1.VTAMLST(ATCCON01)** naming the AICOM major node to cause it to be automatically activated at VTAM startup.

```
APPLTSO,                                             TSO APPLS         X
LCL400,                                              LOCAL 3270S       X
AICOM                                                INTERCOMM          
```

10. Copy **ICOMEXEC** procedure to SYS2.PROCLIB. This is the procedure that is used to run Intercomm. Run the job **INT.ICOMGEN(ICMGEN90)** to install the procedure.

11. Edit **SYS1.VTAMSRC(LOGTAB01)** and add lines for
INTERCOM application ID.

```
***********************************************************************
*  VTAM LOGON INTERPRET TABLE                                         *
***********************************************************************
LOGTAB01 INTAB
         LOGCHAR APPLID=(APPLICID,INTERCOM),SEQNCE='INTERCOM'
         LOGCHAR APPLID=(APPLICID,INTERCOM),SEQNCE='intercom'
         LOGCHAR APPLID=(APPLICID,TSO),SEQNCE='LOGON'
         LOGCHAR APPLID=(APPLICID,TSO),SEQNCE='logon'
         LOGCHAR APPLID=(APPLICID,TSO)
         ENDINTAB
         END
```

12. With the new LOGTAB01 in place, assemble and link it with a job such as **HMVS01.SOURCE(CLOGTAB)**
```
//LOGTAB   JOB 1,'REBUILD LOGTAB',CLASS=A,MSGCLASS=A
//ASMLKED    EXEC ASMFCL,PARM.ASM='OBJ,NODECK'
//ASM.SYSIN    DD DISP=SHR,DSN=SYS1.VTAMSRC(LOGTAB01)
//LKED.SYSLMOD DD DISP=SHR,DSN=SYS1.VTAMLIB(LOGTAB01)
```
13. Restart VTAM. Log out of TSO, then at MVS console:

```
/P TSO
/Z NET,QUICK
/S NET
```

14. Edit **INT.SYMUSR(VTTK4)**, which are the tables customized for the TK4- system. Our terminals are at CUU400-CUU407 (as opposed to the TK4- system which are at CUU0C0-CUU0C7). At lines 113-116, see the **VTIDTAB** macros under heading *3) THE VTAM INTERCOMM SYNONYM TABLE*. In the VTAMIDS, change **CUU0C0** to **CUU400**,
**CUU0C1** to **CUU401**, etc. Do *not* change the ICOMIDS (LU0C0, LU0C1, etc) unless you also changed their names earlier in the table (in the LUNIT macros).

```
*   3)   THE VTAM - INTERCOMM SYNONYM TABLE                             
*                                                                       
         VTIDTAB VTAMIDS=(CUU400,CUU401,CUU402,CUU403,CUU404,CUU405),  *
               ICOMIDS=(LU0C0,LU0C1,LU0C2,LU0C3,LU0C4,LU0C5)            
         VTIDTAB VTAMIDS=(CUU406,CUU407),                              *
               ICOMIDS=(LU0C6,LU0C7)                                    
```

15. Rebuild tables. Run job **INT.ICOMGEN(ICMGEN36)**. Then run job **INT.ICOMGEN(ICMGEN85)**, but we **NEED** to change **SYS1.COBLIB** and **SYS1.PL1LIB** in the **LKED.SYSLIB** concatenation to **SYSC.COBLIB** and **SYSC.PL1LIB**, which is where they live on our system.

```
//ICMGEN85 JOB (5161A020,1A11),'INTERCOMMGEN MAYNARD',CLASS=A, 
//             MSGCLASS=A,MSGLEVEL=(1,1),NOTIFY=HMVS01         
//*                                                            
//* LINKEDIT THE ON-LINE INTERCOMM SYSTEM                      
//*                                                            
//S10  EXEC  LKEDP,P='INT',Q=USR,LMOD=ICOMCR,REGION.LKED=1024K,
//           PARM.LKED='XREF,LIST,LET,NCAL,SIZE=(512K,256K)'   
//LKED.SYSLIB  DD                                              
//             DD                                              
//             DD                                              
//             DD                                              
//             DD  DSN=SYSC.COBLIB,DISP=SHR                    
//             DD  DSN=SYSC.PL1LIB,DISP=SHR                    
//LKED.SYSPRINT DD SYSOUT=*                                    
//LKED.SYSIN   DD  DSN=INT.SYMINCL(ILINKCR),DISP=SHR           
//*                                                            
//* COMPRESS MODUSR BECAUSE THE INTERCOMM LOAD MODULE IS HUGE  
//*                                                            
//COMPRESS EXEC PGM=IEBCOPY                                    
//SYSPRINT DD SYSOUT=*                                         
//SYSUT1   DD DISP=SHR,DSN=INT.MODUSR                          
//SYSUT2   DD DISP=SHR,DSN=INT.MODUSR                          
//SYSIN    DD DUMMY                                            
//                                                             
```

16. The job to start INTERCOMM is set to use CLASS=C. By default we don't have an initiator started that processes class C jobs. At your MVS console, enter **/$SI4** to start initiator 4.

17. Assuming you restarted VTAM, and
added the AICOM entry to your **SYS1.VTAMLST(ATCCON00)** list, you can start INTERCOMM with the **INT.JCL.CNTL(RUNICOM)** job and then from your network solicitor screen, just type **INTERCOM** to log on.
