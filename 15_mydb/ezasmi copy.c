#include <string.h>
#include <stdio.h>
#include "ezasmi.h"

/****************/
/*  NOT WORKING */
/****************/

/* Initialize EZASMI */
void ez_begin(void)
{
    /* INSTRUCTION REG, Displacement(Length, Base) */
    asm("WTO   'INITAPI'");

    // clear EZASMI storage
    asm("XC    EZASMTIE(TIELENTH),EZASMTIE");

    //R15 = A(Task storage area)
    //R1 = A(EZASOH03 parm list)
    asm("LA    R15,EZASMTIE");
    asm("LA    R1,T#PARMS-EZASMTIE(R15)");

    // Create a literal 'INIT' and assign to R0
    asm("LA    R0,=C'INIT'");

    //Pt to INIT function ID :: ST R0,0(,R1) => R1[0] = R0
    asm("ST    R0,0(,R1) ");

    //Invoke EZASOH03
    asm("L     R15,=V(EZASOH03) ");
    asm("BALR  R14,R15");
}

/* Terminate EZASMI */
void ez_end(void)
{
    asm("WTO    'TERMAPI'");
    // R15 = A(Task storage area)
    // R1 = A(EZASOH03 parm list)
    asm("LA    R15,EZASMTIE");
    asm("LA    R1,T#PARMS-EZASMTIE(R15)");

    // R0 = A(TERM function ID)
    asm("LA    R0,=C'TERM'");

    // Pt to TERM function ID
    asm("ST    R0,0(,R1)");

    // Pt to working storage
    asm("LA    R0,T#WORK-EZASMTIE(R15)");
    asm("ST    R0,4(,R1)");

    // Invoke EZASOH03
    asm("L     R15,=V(EZASOH03)");
    asm("BALR  R14,R15");
}

/* Try converting hostname/IP addr to network binary format */
Uint32 ez_pton(char *srcaddr, char *dstaddr, Uint32 *retcode)
{
    Uint32 errno = 0;
    Uint32 srclen = strlen(srcaddr);
    asm("WTO   'PTON'");
    asm("LA    R15,EZASMTIE             R15 = A(Task storage area)");
    asm("LA    R1,T#PARMS-EZASMTIE(R15) R1 = A(EZASOH03 parm list)");
    asm("LA    R0,=C'PTON'              Pt to PTON function ID");
    asm("ST    R0,0(,R1)");
    asm("WTO   'PTON1'");
    asm("L     R0,%[errno]              Pt to ERRNO parm value"
        : [errno] "=r"(errno));
    asm("ST    R0,4(,R1)");
    asm("WTO   'PTON2'");
    asm("LA    R0,%[retcode]            Pt to RETCODE parm value"
        : [retcode] "=r"(retcode));
    asm("ST    R0,8(,R1)");
    asm("WTO   'PTON3'");
    asm("LA    R0,=F'02'                Pt to AF parm value");
    asm("ST    R0,12(,R1)");
    asm("WTO   'PTON4'");
    asm("LA    R0,%[srcaddr]            Pt to SRCADDR parm value"
        :
        : [srcaddr] "r"(srcaddr));
    asm("ST    R0,16(,R1)");
    asm("WTO   'PTON5'");
    asm("LA    R0,%[dstaddr]            Pt to DSTADDR parm value"
        :
        : [dstaddr] "r"(dstaddr));
    asm("ST    R0,20(,R1)");
    asm("WTO   'PTON6'");
    asm("L     R0,%[srclen]+2           Pt to SRCLEN parm value"
        :
        : [srclen] "r"(srclen));
    asm("ST    R0,24(,R1)");
    asm("WTO   'PTON7'");
    asm("L     R15,=V(EZASOH03)        Invoke EZASOH03");
    asm("BALR  R14,R15");

    return errno;
}

/* Convert IP address to dotted decimal format */
Uint32 ez_ntop(char *srcaddr, char *dstaddr, Uint32 addrlen, Uint32 *retcode)
{
    Uint32 errno = 0;
    asm("WTO    'NTOP'");
    asm("EZASMI TYPE=NTOP,AF='INET',                                   +\n"
        "\t      SRCADDR=(%[srcaddr]),DSTADDR=(%[dstaddr]),DSTLEN=(%[addrlen]),ERRNO=(%[errno]),RETCODE=(%[retcode])"
        : [errno] "=r"(errno),
          [retcode] "=r"(retcode)
        : [srcaddr] "r"(srcaddr),
          [addrlen] "r"(&addrlen),
          [dstaddr] "r"(dstaddr)
        : "0", "1", "15");
    return errno;
}

/* Resolve IP address to hostname */
Uint32 ez_getha(char *hostaddr, char *hostent, Uint32 *retcode)
{
    asm("WTO    'GETHOSTBYADDR'");
    asm("EZASMI TYPE=GETHOSTBYADDR,                                    +\n"
        "\t      HOSTADR=(%[hostaddr]),HOSTENT=(%[hostent]),RETCODE=(%[retcode])"
        : /* */
        : [hostaddr] "r"(hostaddr),
          [hostent] "r"(hostent),
          [retcode] "r"(retcode)
        : "0", "1", "15");
    return *retcode;
}

/* Resolve hostname to IP address */
Uint32 ez_gethn(char *name, char *hostent, Uint32 *retcode)
{
    Uint32 namelen = strlen(name);
    asm("WTO    'GETHOSTBYNAME'");
    asm("EZASMI TYPE=GETHOSTBYNAME,                                    +\n"
        "\t      NAME=(%[name]),NAMELEN=(%[namelen]),HOSTENT=(%[hostent]),RETCODE=(%[retcode])"
        : /* */
        : [name] "r"(name),
          [namelen] "r"(&namelen),
          [hostent] "r"(hostent),
          [retcode] "r"(retcode)
        : "0", "1", "15");
    return *retcode;
}

/* Create socket */
Uint32 ez_socket(SocketD *socket)
{
    Uint32 errno = 0;
    asm("WTO    'SOCKET'");
    asm("EZASMI TYPE=SOCKET,AF='INET',SOCTYPE='STREAM',                +\n"
        "\t      ERRNO=(%[errno]),RETCODE=(%[socket])"
        :
        : [errno] "r"(errno),
          [socket] "r"(socket)
        : "0", "1", "15");
    return errno;
}

/* Connect */
Uint32 ez_conn(Socket *socket, char *name, Uint32 *retcode)
{
    Uint32 errno = 0;
    asm("WTO    'CONNECT'");
    asm("EZASMI TYPE=CONNECT,                                          +\n"
        "\t      S=(%[socket]),NAME=(%[name]),ERRNO=(%[errno]),RETCODE=(%[retcode])"
        : /* */
        : [socket] "r"(socket),
          [name] "r"(name),
          [errno] "r"(&errno),
          [retcode] "r"(retcode)
        : "0", "1", "15");
    return errno;
}

/* Identify peer server */
Uint32 ez_getpn(Socket *socket, char *name, Uint32 *retcode)
{
    Uint32 errno = 0;
    asm("WTO    'GETPEERNAME'");
    asm("EZASMI TYPE=GETPEERNAME,                                      +\n"
        "\t      S=(%[socket]),NAME=(%[name]),ERRNO=(%[errno]),RETCODE=(%[retcode])"
        : /* */
        : [socket] "r"(socket),
          [name] "r"(name),
          [errno] "r"(&errno),
          [retcode] "r"(retcode)
        : "0", "1", "15");
    return errno;
}

/* Send request */
Uint32 ez_send(Socket *socket, Uint32 nbyte, void *buf, Uint32 *retcode)
{
    Uint32 errno = 0;
    asm("WTO    'SEND'");
    asm("EZASMI TYPE=SEND,MF=(E,TRMPLIST),                             +\n"
        "\t      S=(%[socket]),NBYTE=(%[nbyte]),BUF=(%[buf]),ERRNO=(%[errno]),RETCODE=(%[retcode])"
        : /* */
        : [socket] "r"(socket),
          [nbyte] "r"(&nbyte),
          [buf] "r"(buf),
          [errno] "r"(&errno),
          [retcode] "r"(retcode)
        : "0", "1", "15");
    return errno;
}

/* Receive response */
Uint32 ez_recv(Socket *socket, Uint32 nbyte, void *buf, Uint32 *retcode)
{
    Uint32 errno = 0;
    asm("WTO    'RECV'");
    asm("EZASMI TYPE=RECV,                                             +\n"
        "\t      S=(%[socket]),NBYTE=(%[nbyte]),BUF=(%[buf]),ERRNO=(%[errno]),RETCODE=(%[retcode])"
        : /* */
        : [socket] "r"(socket),
          [nbyte] "r"(&nbyte),
          [buf] "r"(buf),
          [errno] "r"(&errno),
          [retcode] "r"(retcode)
        : "0", "1", "15");
    return errno;
}

/* Close socket */
Uint32 ez_close(Socket *socket, Uint32 *retcode)
{
    Uint32 errno = 0;
    asm("WTO    'CLOSE'");
    asm("EZASMI TYPE=CLOSE,S=(%[socket]),ERRNO=(%[errno]),RETCODE=(%[retcode])"
        : /* */
        : [socket] "r"(socket),
          [errno] "r"(&errno),
          [retcode] "r"(retcode)
        : "0", "1", "15");
    return errno;
}

//***********************
//* Parm list data      *
//***********************
asm("\nTRMPLIST DS    0D");
asm("DS    16F");
//***********************
//* TCP/IP Task Storage *
//***********************
asm("\nEZASMTIE DS    0D");
asm("\nT#PARMS  DS    16F"); // EZASOH03 parm list data
asm("\nT#WORK   DS    0D");  // EZASOH03 Working storage
asm("DS    F");
asm("\nT#END    DS    0D");
asm("\nTIELENTH EQU   T#END-EZASMTIE "); // Length of task storage
asm("YREGS    ,");
