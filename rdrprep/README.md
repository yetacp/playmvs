# RDRPREP

This file, and the remaining contents of the archive containing it
(as detailed below) are Copyright 2001-2002, James M. Morrison. 
Rdrprep is released under the QPL.
```bash
rdrprep command
```

Version 00.02 December 2, 2002


## Overview
--------

This program prepares a deck for submission to a virtual card reader,
translating (where necessary) from ASCII input to EBCDIC output, 
producing an EBCDIC output deck.

It provides a rudimentary "include" facility which can be used to
cause additional decks to be embedded into the resulting (combined)
output deck. Includes are only recognized in ASCII input files, but
included decks may include other decks up to a maximum level 
(nested includes) specified by the FILE_DEPTH definition (10).

The main input deck (specified on command line) is assumed to be 
encoded in ASCII.

The output deck will be in EBCDIC, fixed length (lrecl) records.
Currently, the only supported lrecl is 80.

Input lines longer than lrecl will be truncated, shorter lines
padded out to lrecl length.

ASCII input files are assumed to be of variable line length,
EBCDIC input files are assumed to be of fixed (lrecl) length.


## Sample Help
------------------------------------------

Copyright 2001-2002, James M. Morrison
Version 00.02

This program prepares an ASCII file for submission to a Hercules virtual
card reader. It reads the input file, and provides a mechanism to include
other (ASCII or EBCDIC) files. Files are included by specifying an 'include'
statement (beginning in column 1) whose format is:
::C [path]filename
where:
:: are the include escape characters
C either E (EBCDIC) or A (ASCII) for the included file's
 character set. The case of E or A is not significant.
[path]filename specifies the filename and optional path of the file
 to be included.

The main input file (specified on the command line) is assumed to be in
ASCII. ASCII files are assumed to be of variable line lengths, EBCDIC
files are assumed to be of fixed length. All input lines are translated
to EBCDIC (if necessary), and blank padded or truncated to 80 characters.
Include statements are only recognized in ASCII input files.


## Syntax
```bash
rdrprep [options...] input [output]
input input filename
output output filename (default reader.jcl)

Default options on/yes(+) off/no(-) HELP (default: not displayed)
------------------------------------------- ------------------------------
-list echo output (translated to ASCII) -about copyright & version
+trunc truncate long ASCII lines (80) -help general help
 -syntax syntax help
 ```
 
## Sample execution
----------------
```bash
bash-2.04# cat test.jcl
//TEST JOB CLASS=A,MSGLEVEL=(1,1)
//UPDTE EXEC PGM=IEBUPDTE
//SYSPRINT DD SYSOUT=A
//SYSUT1 DD DISP=OLD,DSN=SYS2.LOCAL.ASM
//SYSUT2 DD DISP=OLD,DSN=SYS2.LOCAL.ASM
//SYSIN DD *
./ ADD NAME=JUNK
::a first.include.txt
./ ADD NAME=IEFBR14
::a iefbr14.asm
//LINK EXEC PGM=IEWL,PARM='MAP'
//SYSPRINT DD SYSOUT=*
//SYSLMOD DD DISP=SHR,DSN=SYS2.LOCAL.LINKLIB(IEFBR14)
//SYSUT1 DD UNIT=SYSDA,SPACE=(TRK,(5,5))
//SYSLIN DD *
::e iefbr14.obj
//IEFBR14 EXEC PGM=IEFBR14
//STEPLIB DD DSN=SYS2.LOCAL.LINKLIB,DISP=SHR
// 

bash-2.04# rdrprep +list test.jcl
//TEST JOB CLASS=A,MSGLEVEL=(1,1)
//UPDTE EXEC PGM=IEBUPDTE
//SYSPRINT DD SYSOUT=A
//SYSUT1 DD DISP=OLD,DSN=SYS2.LOCAL.ASM
//SYSUT2 DD DISP=OLD,DSN=SYS2.LOCAL.ASM
//SYSIN DD *
./ ADD NAME=JUNK
First Include Text Line 1
First Include Text Line 2
Second Include Text Line 1
Second Include Text Line 2
Second Include Text Final Line
First Include Text Final Line
./ ADD NAME=IEFBR14
IEFBR14 CSECT ,
SLR 15,15
BR 14
END IEFBR14
//LINK EXEC PGM=IEWL,PARM='MAP'
//SYSPRINT DD SYSOUT=*
//SYSLMOD DD DISP=SHR,DSN=SYS2.LOCAL.LINKLIB(IEFBR14)
//SYSUT1 DD UNIT=SYSDA,SPACE=(TRK,(5,5))
//SYSLIN DD *
ESD IEFBR14 00000001
TXT 00000002
END 1X390ASM 210001038 00000003
//IEFBR14 EXEC PGM=IEFBR14
//STEPLIB DD DSN=SYS2.LOCAL.LINKLIB,DISP=SHR
// 
```

## Archive contents
----------------
rdrprep-xxxx.zip
first.include.txt 
iefbr14.asm
iefbr14.obj
makefile
rdrprep.c 
reader.jcl 
readme.txt 
second.include.txt 
test.jcl

## Version history
---------------

Version 00.00 February 7, 2001

Base release

Version 00.01 April 7, 2001

Ignores zero length ASCII input records

Version 00.02 December 2, 2002

Incorporate Mike Rayborn's fix for long ASCII lines,
as reported in the Yahoo turnkey-mvs group.

Added trunc option; -trunc will wrap long ASCII lines
(for example HTML files); similar to old behavior.
Default is +trunc (truncate ASCII input at 80 bytes).

Best regards,
Jim
