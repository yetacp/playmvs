         COPY  PDPTOP
         CSECT

         DS    0F
* Program text area
@@LC0    EQU   *
         DS    0F
         COPY  PDPMAIN

* X-FUNC main PROLOGUE
MAIN     PDPPRLG CINDEX=0,FRAME=96,BASER=12,ENTRY=YES
         B     @@FEN0
         LTORG
@@FEN0   EQU   *
         DROP  12
         BALR  12,0
         USING *,12
@@PG0    EQU   *
         LR    11,1
         L     10,=A(@@PGT0)

* FUNCTION main CODE

* Initialize EZASMI interface
         WTO   'Initialize EZASM API'
         XC    EZASMTIE(TIELENTH),EZASMTIE     clear EZASMI storage
         EZASMI TYPE=INITAPI,MAXSNO=MAXSNO,ERRNO=ERRCD,RETCODE=RETCD

* Try converting hostname/IP addr to network binary format using PTON
         WTO   'Try convert hostname/ip to binary format'
         EZASMI TYPE=PTON,AF='INET',SRCADDR=HOSTIN,SRCLEN=NAMELEN+2,   +
               DSTADDR=IPADDR,ERRNO=ERRCD,RETCODE=RETCD
         CLC   RETCD,=X'FFFFFFFF' conversion successful?
         BE    GETHBN             no, go treat input as a hostname
         LH    R6,NAMELEN+2       get length
         STH   R6,ADDRLEN         remember for display
         BCTR  R6,0               decrement for EXecute
         LA    R3,HOSTIN          address of IP address
         EX    R6,GETIP           copy IP address

* Resolve IP address to hostname using GETHOSTBYADDR
         WTO   'Resolve IP to hostname'
         EZASMI TYPE=GETHOSTBYADDR,HOSTADR=IPADDR,HOSTENT=HOSTENT,     +
               RETCODE=RETCD
         L     R3,HOSTENT         get hostname address ..
         L     R3,0(,R3)          .. from HOSTENT
         LR    R6,R3              \
CHKLEN   EQU   *
         CLI   0(R6),X'00'         \
         BE    HOSTEND              \ compute length
         LA    R6,1(,R6)            / of hostname
         B     CHKLEN              /
HOSTEND  EQU   *
         SR    R6,R3              /
         ST    R6,NAMELEN         remember length
         BCTR  R6,0               decrement for EXecute
         EX    R6,GETHOST         copy hostname
         B     SOCKET             create socket

* Resolve hostname to IP address using GETHOSTBYNAME
GETHBN   EQU   *
         L     R6,NAMELEN         get length
         BCTR  R6,0               decrement for EXecute
         LA    R3,HOSTIN          hostname address
         EX    R6,GETHOST         copy hostname
         WTO   'Resolve hostname to IP'
         EZASMI TYPE=GETHOSTBYNAME,NAMELEN=NAMELEN,NAME=HOSTNAME,      +
               HOSTENT=HOSTENT,RETCODE=RETCD
         L     R3,HOSTENT         \
         L     R3,16(,R3)          \
         L     R3,0(,R3)            > get first IP address from HOSTENT
         L     R3,0(,R3)           /
         ST    R3,IPADDR          /

* Convert IP address to dotted decimal format using NTOP
         WTO   'Convert IP to dotted decimal format'
         EZASMI TYPE=NTOP,AF='INET',SRCADDR=IPADDR,DSTADDR=ADDR,       +
               DSTLEN=ADDRLEN,ERRNO=ERRCD,RETCODE=RETCD

* Create socket
SOCKET   EQU   *
         WTO   'Create socket'
         EZASMI TYPE=SOCKET,AF='INET',SOCTYPE='STREAM',                +
               ERRNO=ERRCD,RETCODE=SOCKDESC
         LT    R3,SOCKDESC        socket created?
         BNL   CONNECT            yes -> continue

         WTO   'Socket not created'
         TPUT  MSGSOCK,L'MSGSOCK  \ no -> tell user..
         B     RETNSOCK           /                  .. and exit

* Connect info
CONNECT  EQU   *
         WTO   'Socket created'
         CLC   IPADDR,=XL4'00000000' address zero?
         BNE   ADDROK             no -> continue

         WTO   'Default address = 127.0.0.1'
         MVC   IPADDR,=XL4'7F000001'  \
         MVC   ADDR,=CL9'127.0.0.1'    \
         MVC   HOSTNAME,=CL9'localhost' \ yes -> connect to
         LA    R6,9                     /        localhost (127.0.0.1)
         STH   R6,ADDRLEN              /
         ST    R6,NAMELEN             /

* Connect server (client socket)
ADDROK   EQU   *
         WTO   'Connect server (client socket)'
         EZASMI TYPE=CONNECT,S=SOCKDESC+2,NAME=SOCKADDR,               +
               ERRNO=ERRCD,RETCODE=RETCD
         LT    R3,RETCD           socket connected?
         BNL   CONECTED           yes -> continue

         WTO   'Not connected'
         TPUT  MSGCONN,L'MSGCONN   no -> tell user..
         B     RETURN             exit

* Identify peer server
CONECTED EQU   *
         WTO   'Identify peer server'
         EZASMI TYPE=GETPEERNAME,S=SOCKDESC+2,NAME=SOCKADDR,           +
               ERRNO=ERRCD,RETCODE=RETCD
         LT    R3,RETCD           GETPEERNAME successful?
         BNL   GOTPEER            yes -> continue
         TPUT  MSGPEER,L'MSGPEER   no -> tell user..
         B     RETURN             exit

* Resolve peer server IP address to hostname using GETHOSTBYADDR
GOTPEER  EQU   *
         WTO   'Resolve peer server IP to hostname'
         EZASMI TYPE=GETHOSTBYADDR,HOSTADR=IPADDR,HOSTENT=HOSTENT,     +
               RETCODE=RETCD
         L     R3,HOSTENT         get hostname address ..
         L     R3,0(,R3)            .. from HOSTENT
         LR    R6,R3              \
CHKLENP  EQU   *
         CLI   0(R6),X'00'         \
         BE    HOSTENDP             \ compute length
         LA    R6,1(,R6)            / of hostname
         B     CHKLENP             /
HOSTENDP EQU   *
         SR    R6,R3              /
         ST    R6,NAMELEN         remember length
         BCTR  R6,0               decrement for EXecute
         EX    R6,GETHOST         copy hostname

* Convert peer IP address to dotted decimal format using NTOP
         LA    R6,L'ADDR          reinitialize length ..
         STH    R6,ADDRLEN

         WTO   'Convert peer IP to dotted decimal'  .. of IP address
         EZASMI TYPE=NTOP,AF='INET',SRCADDR=IPADDR,DSTADDR=ADDR,       +
               DSTLEN=ADDRLEN,ERRNO=ERRCD,RETCODE=RETCD

* Display connection message
         LH    R6,ADDRLEN         length of dotted decimal IP address
         L     R5,NAMELEN         length of hostname
         LA    R4,MFROM           indicate server mode
         LA    R3,L'MFROM         length of server mode message
         LT    R2,NEWSOCK         did we get a new socket?
         BNL   *+12               yes -> continue
         LA    R4,MTO             indicate client mode
         LA    R3,L'MTO           length of client mode message
         STRING ((R4),(R3)),(HOSTNAME,(R5)),' (',(ADDR,(R6)),')',      +
               ' port ',(PORT,H,L),INTO=PRTDATA format message
* Display connected to <hostname> (<ip>) port <port>
         TPUT  PRTDATA,L'PRTDATA

* Get storage for SEND/RECV buffer
         GETMAIN R,LV=SENDSIZE    R1 = get send buffer
         ST    R1,SENDBUFA        remember address
         GETMAIN R,LV=RECVSIZE    R1 = get recv buffer
         ST    R1,RECVBUFA        remember address

* Initialize SENDBUFA
         MVC   SENDBUFA(HTTPLEN),HTTP001
         MVC   NETLENS,HTTPLEN

* Use linefeed character matching the installation's conversion tables
         LA    R3,1                        convert ASCII linefeed ..
         ST    R3,NETLENR                  .. to EBCDIC (LF or NL) ..
         CALL  EZACIC05,(LF1+4,NETLENR),VL .. and put it into ..
         MVC   LF2+1(1),LF1+4

SENDIT   EQU   *
         WTO   'Convert to ASCII'
         LA    R3,1(,R1)          increment length for newline
         ST    R3,NETLENS         store length for use by EZACIC04/SEND
         LA    R2,0(R1,R9)        send
LF2      MVI   0(R2),*-*          insert linefeed character
         L     R4,SENDBUFA        address data
         CALL  EZACIC04,((R4),NETLENS),VL convert to ASCII

         WTO   'Send request'
         EZASMI TYPE=SEND,S=SOCKDESC+2,NBYTE=NETLENS,BUF=*SENDBUFA,    +
               ERRNO=ERRCDS,RETCODE=RETCDS,MF=(E,TRMPLIST)

         LT    R3,RETCDS          successfully sent?
         BNL   RETURN             yes -> check for dialog type

         MVI   RUNNING,X'01'
* While RUNNING is X'01' and no RECV error occurs:
* Read recv from peer and display it on terminal

READNET  EQU   *
         CLI   RUNNING,X'01'      dialog running?
         BNE   RETURN             no -> exit
         MVC   NETLENR,RECVBUFS   yes -> get length of network buffer

         WTO   'Await response'
         EZASMI TYPE=RECV,S=SOCKDESC+2,NBYTE=NETLENR,BUF=*RECVBUFA,    +
               ERRNO=ERRCD,RETCODE=RETCD

         WTO   'Successfully received?'
         LT    R3,RETCD           successfully received?
         BNL   RECVOK             yes -> continue

         WTO   'Socket already closed?'
         CLFHSI ERRCD,ENOTSOCK    no -> socket already closed?
         BE    RETNSOCK           yes -> exit without error msg

         WTO   'RECV cancelled?'
         CLFHSI ERRCD,ECANCELD    no -> RECV cancelled?
         BE    RETNSOCK           yes -> exit without msg

         TPUT  MSGRECV,L'MSGRECV  no -> tell user..
         B     RETURN             exit

RECVOK   EQU   *
         WTO   'RECV Ok'
         BH    CONVERT            convert if at least one byte received

         WTO   'Nothing received'
         TPUT  EOD,L'EOD          nothing received: Tell user ..
         B     RETURN             .. and exit

CONVERT  EQU   *
         WTO   'Convert to EBCDIC'
         ST    R3,NETLENR         store length for use by EZACIC05
         L     R4,RECVBUFA        address data
         CALL  EZACIC05,((R4),NETLENR),VL convert to EBCDIC
         CLI   0(R4),55           EOT character received?
         BNE   DISPLAY            no -> check for dialog type

         WTO   'EOT received'
         TPUT  EOT,L'EOT          yes -> Tell user ..
         B     RETURN             .. and exit

* Split data at LF or CRLF and display line by line on terminal
DISPLAY  EQU   *
         LR    R5,R4              initialize compare pointer
         SR    R8,R8              initialize to zero for CLIJ
NEXTCHAR EQU   *
         IC    R8,0(,R5)          load character to check
LF1      EQU   *
         CLIJE R8,X'0A',DISPLINE  if linefeed -> display line
         LA    R5,1(,R5)          else -> point to next character
         B     NEXTCHAR           check next character

DISPLINE EQU   *
         MVI   0(R5),X'15'        replace linefeed with newline
         LR    R7,R4              remember begin of current output line
         LA    R6,1(,R5)          remember begin of next output line
         BCTR  R5,0               last character of output line
         IC    R8,0(,R5)          load character to check
         CLIJNE R8,X'0D',LASTCHAR if not CR -> go ahead
         BCTR  R5,0                    else -> decrement

LASTCHAR EQU   *
         LA    R5,1(,R5)          compute ...
         SR    R5,R4              ... length of output line
         TPUT  (R7),(R5)          display on terminal
         LR    R5,R6              compute ..
         SR    R5,R7              .. residual ..
         SR    R3,R5              .. count
         LR    R4,R6              initialize ..
         LR    R5,R6              .. next line
         BNZ   NEXTCHAR           more data -> check it
         TPUT  NEWLINE,1,ASIS     else -> newline ..

         B     READNET            continue reading socket

* Exit processing
RETURN   EQU   *
         WTO   'Closing socket'
         EZASMI TYPE=CLOSE,S=SOCKDESC+2,ERRNO=ERRCD,RETCODE=RETCD

RETNSOCK EQU   *
         WTO   'Terminate API'
         MVI   RUNNING,X'02'        terminate terminal task
         STIMER WAIT,BINTVL=WAIT50  wait half a second
         EZASMI TYPE=TERMAPI        terminate API
         CLI   RUNNING,X'00'        never running?
         BE    RELSEND              yes -> just exit
         STIMER WAIT,BINTVL=WAIT50  wait half a second
         CLI   RUNNING,X'FF'        terminal already terminated?
         BE    RELSEND              yes -> we are done
         STIMER WAIT,BINTVL=WAIT50  no -> wait half a second and exit

* Release RECV buffer
RELSEND  EQU   *
         WTO   'Release send buffer'
         ICM   R1,B'1111',SENDBUFA     send buffer address
         BZ    RELRECV                 skip release if never allocated
         FREEMAIN R,LV=SENDSIZE,A=(R1) release send buffer

RELRECV  EQU *
         WTO   'Release recv buffer'
         ICM   R1,B'1111',RECVBUFA     receive buffer address
         BZ    ALLDONE                 skip release if never allocated
         FREEMAIN R,LV=RECVSIZE,A=(R1) release receive buffer

* That's all folks!
ALLDONE  EQU   *
         WTO   'Returning'
         SLR   15,15

* FUNCTION main EPILOGUE
         PDPEPIL

* EXecuted instructions
GETHOST  MVC   HOSTNAME(*-*),0(R3) copy hostname
GETIP    MVC   ADDR(*-*),0(R3)     copy IP address
MOVEPRTR MVC   0(*-*,R6),0(R4)     right justify port number
MOVEHOST MVC   HOSTIN(*-*),0(R4)   get hostname/IP from command line

* FUNCTION main LITERAL POOL
         DS    0F
         LTORG

         YREGS ,                  register equates

SENDSIZE EQU   4096               size of send buffer
RECVSIZE EQU   81920              size of network receive buffer
ENOTSOCK EQU   38                 socket already closed on RECV
EADDINUS EQU   48                 address already in use
ECANCELD EQU   1009               RECV cancelled, EIBMCANCELLED

* FUNCTION main PAGE TABLE
         DS    0F
@@PGT0   EQU   *
         DC    A(@@PG0)
* Program data area
ERRCD    DC    A(*-*)             error code main task
ERRCDS   DC    A(*-*)             error code terminal input task
RETCD    DC    A(*-*)             return code main task
RETCDS   DC    A(*-*)             return code terminal input task
MAXSNO   DC    A(*-*)               highest socket number assigned

SOCKDESC DC    F'-1'              socket descriptor
SOCKADDR DS    0F                 sockaddr structure
AF@INET  DC    H'2'               address family
PORT     DC    H'3000'            port to connect to or listen at
IPADDR   DC    F'0'               INET address (netid)
         DC    XL8'00'            Reserved area not used
NEWSOCK  DC    F'-1'              new socket descriptor from ACCEPT
HOSTENT  DC    F'0'               address of HOSTENT structure
PORTD    DC    D'0'               decimal port number

MSGSOCK  DC    C'SOCKET failed'
MSGCLOS  DC    C'CLOSE failed'
MSGCONN  DC    C'CONNECT failed'
MSGPEER  DC    C'GETPEERNAME failed'
MNOSEND  DC    C'SEND failed'
MSGRECV  DC    C'RECV failed'
MFROM    DC    C'Connection from '
MTO      DC    C'Connected to '
EOD      DC    C'Terminating at EOD'
EOT      DC    C'Terminating at EOT'

HTTP001  DC    C'GET / HTTP/1.0'
         DC    X'25'              Linefeed in EBCDIC
         DC    C'Host: 127.0.0.1'
         DC    X'25'
         DC    X'25'
         DC    X'25'
HTTPLEN  EQU   *-HTTP001

NEWLINE  DC    X'15'              EBCDIC newline character

RUNNING  DC    X'00'              status indicator

ADDR     DC    CL15' '            dotted decimal IP address
ADDRLEN  DC    Y(L'ADDR)          length of dotted decimal IP address
HOSTNAME DC    CL256' '           Hostname
HOSTIN   DC    CL50' '            hostname or IP addr from command line

WAIT25   DC    F'25'              quarter of a second
WAIT50   DC    F'50'              half a second
WAIT1000 DC    F'1000'            ten seconds

NAMELEN  DC    F'0'               length of hostname
PORTLEN  DC    F'0'               length of port number
NETLENR  DS    F                  number of bytes for RECV/EZACIC05
NETLENS  DS    F                  number of bytes for SEND/EZACIC04
PORTRPCK DC    CL5' '             port right justified for PACK
PORTR    DC    CL5' '             port right justified
PRTDATA  DC    CL78' '            formatted result

SENDBUFA DC    F'0'               address of send buffer
SENDBUFS DC    A(SENDSIZE)        size of send buffer

RECVBUFA DC    F'0'               address of recv buffer
RECVBUFS DC    A(RECVSIZE)        size of recv buffer

TRMPLIST EZASMI MF=L            EZASMI parameter list for terminal task
         EZASMI TYPE=TASK,STORAGE=CSECT EZASMI task storage

         STRING GENERATE          STRING storage goes here

         END   @@MAIN
