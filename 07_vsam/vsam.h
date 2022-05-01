
#ifndef __VSAM_H__
#define __VSAM_H__

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;

typedef union
{
    Uint8 u24[4];
    Uint32 u32;
} C32to24;

Uint32 to24(Uint32 from);

#define EXLSTID 0x81
#define EXLSVSAM 0x10
#define EXLLEN 20
#define EXIT_SPECIFIED 0x80
#define EXIT_ACTIVE 0x40

typedef struct ExitList
{
    Uint8 id;      //  0  DC X'81'         EXLIST IDENTIFICATION                                                                                                                    PAGE    9
    Uint8 subtype; //  1  DC AL1(0)        EXLST SUBTYPE
    Uint16 len;    //  2  DC H'20'         EXLST LIST LENGTH
    Uint8 flags;   //  4  DC X'00'         EXLST FLAGS
    Uint8 eodad;   //  5  DC AL1(192)      EODAD ENTRY DESCRIPTION
    void *p_eodad; //  6  DC AL4(VSEOF)    POINTER TO EODAD EXIT
    Uint8 synad;   // 10  DC AL1(192)      SYNAD ENTRY DESCRIPTION
    void *p_synad; // 11  DC AL4(VSERROR)  POINTER TO SYNAD EXIT
    Uint8 lerad;   // 15  DC AL1(192)      LERAD ENTRY DESCRIPTION
    void *p_lerad; // 16  DC AL4(VSERROR)  POINTER TO LERAD EXIT
} __attribute__((packed)) ExitList;

#define ACBDORGA 0x08 /* ACB INDICATOR */
#define ACBIDVAL 0xA0 /* IDENTIFIER VALUE */
#define ACBSVSAM 0x10 /* VSAM SUBTYPE */

#define ACBADR 0x40 /* ADDRESSED PROCESSING WITHOUT INDEX */
#define ACBCNV 0x20 /* PROCESSING BY CONTROL INTERVAL */
#define ACBDIR 0x08 /* DIRECT PROCESSING */
#define ACBKEY 0x80 /* KEYED PROCESSING VIA INDEX */
#define ACBSEQ 0x10 /* SEQUENTIAL PROCESSING */

#define ACBIN 0x04  /* INPUT PROCESSING USING GET OR READ */
#define ACBOUT 0x02 /* OUTPUT PROCESSING USING PUT OR WRITE */

#define VSAMLEN 76

#define DDNAME_LEN 8

#define ACBEXFG 0x02
/* USER EXIT FLAG
 SET TO 0 BY AN I/O SUPPORT WHEN A USER EXIT TAKEN;
 SET TO 1 ON RETURN
*/
typedef struct AccessMethodControlBlock
{
    Uint8 id;           //  0 DC X'A0'       ACB IDENTIFICATION
    Uint8 subtype;      //  1 DC AL1(16)     ACB SUBTYPE
    Uint16 len;         //  2 DC AL2(76+0)   ACB LENGTH
    Uint32 p_amblst;    //  4 DC A(0)        AMB LIST POINTER
    Uint32 p_interf;    //  8 DC A(0)        INTERFACE ROUTINE POINTER
    Uint8 macrf1;       // 12 DC B'10010100' MACRF(1)
    Uint8 macrf2;       // 13 DC B'00000000' MACRF(2)
    Uint8 num_conc;     // 14 DC AL1(0)      NO OF CONCURRENT STRINGS FOR AIX PATH
    Uint8 num_str;      // 15 DC AL1(1)      NUMBER OF STRINGS
    Uint16 num_dat;     // 16 DC AL2(0)      NUMBER OF DATA BUFFERS
    Uint16 num_index;   // 18 DC AL2(0)      NUMBER OF INDEX BUFFERS
    Uint8 macrf3;       // 20 DC B'00000000' MACRF(3)
    Uint8 macrf4;       // 21 DC B'00000000' MACRF(4)
    Uint16 jes_pool;    // 22 DC AL2(0)      JES BUFFER POOL/NUMBER OF JOURNAL BUFFERS
    Uint8 recfm;        // 24 DC X'80'       RECFM=A
    Uint8 cct;          // 25 DC B'00000000' CONTROL CHARACTER TYPE
    Uint16 dsorg;       // 26 DC X'0008'     DSORG=ACB
    Uint32 p_filler;    // 28 DC A(0)
    Uint32 p_passwd;    // 32 DC A(0)        PASSWORD POINTER
    ExitList *p_exitls; // 36 DC A(MSTEXL)   EXIT LIST POINTER
    char ddname[8];     // 40 DC CL8'VSIN'   DDNAME
    Uint8 oflgs;        // 48 DC X'02'       OFLAGS
    Uint8 erflgs;       // 49 DC AL1(0)      ERFLAGS
    Uint8 inflgs1;      // 50 DC B'00000000' INFLGS(1)
    Uint8 inflgs2;      // 51 DC B'00000000' INFLGS(2)
    Uint32 p_ojfcb;     // 52 DC A(0)        OPENJ JFCB POINTER
    Uint32 bufspace;    // 56 DC A(0)        BUFFER SPACE
    Uint16 blksize;     // 60 DC AL2(0)      BLOCK SIZE
    Uint16 recsize;     // 62 DC AL2(0)      RECORD SIZE
    Uint32 p_usrwka;    // 64 DC A(0)        USER WORKAREA POINTER
    Uint32 p_cblkm;     // 68 DC A(0)        CONTROL BLOCK MANIPULATION WORKAREA POINTER
    Uint32 p_appnam;    // 72 DC A(0)        PTR TO APPLICATION NAME
} __attribute__((packed)) AccessMethodControlBlock;

#define RPLIDD 0
#define RPLSVSAM 0x10
#define RPLLEN 76
#define RPLNOERR 0

typedef struct RequestParameterList
{
    Uint8 id;                        // 0 DC AL1(0)      RPL IDENTIFICATION
    Uint8 subtype;                   // 1 DC AL1(16)     RPL SUBTYPE
    Uint8 reqtype;                   // 2 DC AL1(0)      RPL REQUEST TYPE
    Uint8 len;                       // 3 DC AL1(76)     RPL LENGTH
    Uint32 p_plhold;                 // 4 DC A(0)        POINTER TO PLACEHOLDER
    Uint32 ecb;                      // 8 DC A(0)        ECB                                                                                                                                      PAGE   10
    Uint8 status;                    // 12 DC BL1'0'      STATUS BYTE
    Uint8 retcode;                   // 13 DC AL1(0)     RPLRTNCD - RPL RETURN CODE
    Uint8 condition;                 // 14 DC AL1'0'     RPLCNDCD - RPL CONDITION
    Uint8 errcode;                   // 15 DC AL1'0'     RPLERRCD - ERROR CODE
    Uint16 keylen;                   // 16 DC AL2(6)      KEY LENGTH
    Uint16 transid;                  // 18 DC AL2(0)      TRANSID
    Uint32 p_chrctr;                 // 20 DC A(0)        POINTER TO CONTROL CHARACTER
    AccessMethodControlBlock *p_acb; // 24 DC A(VSAMFILE) POINTER TO ACB
    Uint32 p_tcb;                    // DC A(0)        POINTER TO TCB
    char *p_recare;                  // DC A(INREC)    POINTER TO RECORD AREA
    char *p_arg;                     // DC A(USERKEY)  POINTER TO ARGUMENT
    Uint8 optcd[4];                  // DC B'00100000' OPTCD BYTEs 0,1,2,3
    Uint32 p_nxtrpl;                 // DC A(0)        POINTER TO NEXT RPL
    Uint32 logrecl;                  // DC A(0)        RESERVED FOR LOGICAL REC LEN
    Uint32 buflen;                  // DC A(118)      BUFFER LENGTH OPTCD BYTES 5-8
    Uint8 byte5;                     // DC B'00000000' BYTE 5
    Uint8 byte6;                     // DC B'00000000' BYTE 6
    Uint8 byte7;                     // DC B'00000000' BYTE 7
    Uint8 byte8;                     // DC B'00000000' BYTE 8
    Uint8 rba[8];                    // DC XL8'0'      RBA
    Uint8 exitdef;                    // DC B'01000000'
    Uint8 actind;                    // DC AL1(0)      ACTIVE INDICATOR
    Uint16 mxerrlen;                 // DC AL2(0)      MAXIMUM ERROR MSG LENGTH
    Uint32 p_msgare;                 // DC A(0)        RESERVED FOR MESSAGE AREA PTR
} __attribute__((packed)) RequestParameterList;

typedef struct VSAMDataset
{
    ExitList exitList;
    AccessMethodControlBlock acb;
    RequestParameterList rpl;
} VSAMDataset;

// ORGANIZATION
#define ORG_INDEXED 1
#define ORG_SEQUENTIAL 2
#define ORG_RELATIVE 3

// ACCESS
#define ACCESS_SEQUENTIAL 1
#define ACCESS_RANDOM 2
#define ACCESS_DYNAMIC 3

// MODE
#define INPUT 1
#define OUTPUT 2

// RPLOPT1
#define RPLLOC 0x80   /* LOCATE MODE */
#define RPLDIR 0x40   /* DIRECT SEARCH ACCESS */
#define RPLSEQ 0x20   /* SEQUENTIAL ACCESS */
#define RPLSKP 0x10   /* SKIP SEQ ACCESS */
#define RPLASY 0x08   /* ASYNCHRONOUS REQUEST */
#define RPLKGE 0x04   /* SEARCH KEY GT/EQ */
#define RPLGEN 0x02   /* GENERIC KEY REQUEST */
#define RPLECBSW 0x01 /* EXTERNAL ECB */

// RPLOPT2
#define RPLKEY   0x80   /* KEYED ACCESS         */
#define RPLADR   0x40   /* ACCESS BY LOCATION   */
#define RPLCNV   0x20   /* CINV ACCESS (BY RBA) */
#define RPLBWD   0x10   /* FWD=0/BWD=1  @X04SVHS*/
#define RPLLRD   0x08   /* ARD=0/LRD=1  @X04SVHS*/
#define RPLWAITX 0x04 /* SYNCH  PROCESSING WAIT EXIT */
#define RPLUPD   0x02   /* UPDATE IF ON         */
#define RPLNSP   0x01   /* NOTE STRING POSITION */

// RPLOPT3
#define RPLEODS 0x80  /* END OF USER SYSOUT   */
#define RPLSFORM 0x40 /* SPECIAL FORM ON REMOTE PRINTER */
#define RPLBLK 0x20   /* BLOCK=1,UNBLOCKED=0 FIXED BLOCK PROCESSING */
#define RPLVFY 0x10   /* UCS/FCB VERIFY=1 */
#define RPLFLD 0x08   /* UCS FOLD=1 */
#define RPLFMT_UCSLOAD 0x00 /* 00=UCS LOAD     */
#define RPLFMT_FCBLOAD 0x04 /* 01=FCB LOAD     */
#define RPLFMT_3800 0x02    /* 10=3800 PRINTER */
#define RPLALIGN 0x01       /* 0=DO NOT ALIGN FCB 1=ALIGN BUFFER AND NOTIFY OPERATOR      */

// RPLEXTDS
#define RPLEXSCH 0x80 /* EXIT SCHEDULED X03004*/
#define RPLNEXIT 0x40 /* NO EXIT SPECIFIED */
#define RPLEXIT 0x20  /* ASYNCH EXIT */
#define RPLTCRYP 0x08 /* IF ON, ENCRYPTION FEATURE REQ*/
#define RPLNIB 0x04   /* ARG HAS NIB POINTER IF ON*/
#define RPLBRANC 0x02 /* BRANCH ENTRY TO MACRO IF ON*/

void V_open2(VSAMDataset *record,
             void *inrec,
             int organization,
             int access,
             int mode,
             void (*p_eodad)(void),
             void (*p_synad)(void),
             void (*p_lerad)(void));

void V_key(VSAMDataset *record,
           void *key,
           int len);

void v_el(ExitList *el,
          void (*p_eodad)(void),
          void (*p_synad)(void),
          void (*p_lerad)(void));

void v_acb(AccessMethodControlBlock *acb,
           ExitList *p_exitls);

void v_rpl(RequestParameterList *rpl,
           AccessMethodControlBlock *acb,
           void *inrec,
           void *userkey);

int v_open(AccessMethodControlBlock *acb, int mode);

int v_close(AccessMethodControlBlock *acb, int mode);

int v_get(RequestParameterList *rpl);

#endif
