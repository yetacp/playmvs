# My MVS Playground

| ![Logon screen](img/netsol.png "Logon screen") |
| ------ |


## Acknowledgements
```
If I have seen a little further it is by standing on the shoulders of Giants.
Isaac Newton.
```

First and foremost, I would like to thank Volker Bandke (TK3), Juergen Winkelmann (https://wotho.ethz.ch/tk4-/), Jay Moseley (http://www.jaymoseley.com/) and Moshix (https://www.youtube.com/c/moshix/videos).

## About
This is my playground to learn MVS3.8j/TK4- environment and to test C projects using Linux GCCMVS cross-compiler for MVS.

## *Dependencies*

- A MVS3.8j system: 
    - [myMVS](https://github.com/yetacp/mymvs)
    - [TK4-](https://wotho.ethz.ch/tk4-/). 
- [GCC C cross-compiler for MVS](https://github.com/yetacp/gcc_mvs).

Use [MVS sysgen](https://github.com/yetacp/mvs_sysgen) to generate a custom MVS3.8j.

## Projects in progress

- Small programs to demonstrate C programming in MVS.
- A C implementation of VSAM API.
- A web panel editor for FSS API (C Full Screen Interface).
- A LUA port for MVS.

## Project Ideas 
- A database API using TCP/IP interface (EZASMI)
    - Create a client DB API for MVT Cobol, like Jay Moseley's VSAMIOS.
    - A simplified Python script will provide a socket server for database services.

## Components

Except Hercules, I downloaded the software below and I put the installers inside the repository to allow offline installation.

### **Automated MVS3.8j Sysgen** from Jay Moseley site
- Origin: https://github.com/MVS-sysgen/sysgen
- Fork:   https://github.com/moshix/sysgen

### **Hercules**
- Author: Roger Bowler.
- Mantainers: Jay Maynard, Jan Jaeger and others. 
- https://sdl-hercules-390.github.io/html/hercinst.html

Debian / Ubuntu / Mint:
```bash
sudo apt-get -y install git wget time
sudo apt-get -y install build-essential cmake flex gawk m4 autoconf automake libtool-bin libltdl-dev
sudo apt-get -y install libbz2-dev zlib1g-dev
sudo apt-get -y install libcap2-bin
sudo apt-get -y install libregina3-dev 
```

### **GCCMVS**
- Linux C cross compiler for MVS
- Author: Paul Edwards
- Source: http://gccmvs.sourceforge.net/
- Fork: https://github.com/mainframed/gccmvs 

In Ubuntu/Debian install gcc-multilib.

```bash
sudo apt install gcc-multilib
cd gccmvs
make
```

### **PDPCLIB 4.0**
- Public Domain Project C Library
- http://pdos.sourceforge.net/
- Author: Paul Edwards

### **RDRPrep**
- Convert ASCII JCL files to EBCDIC
- Author: James M. Morrison
- Source: https://github.com/mainframed/rdrprep

### **FSS, FSI and Scruples**
- FSS: C Full Screen API
- FSI: Assembly Full Screen API
- Scruples: Panel to FSS Compiler
- Author: Tommy Sprinkle
- Source: http://tommysprinkle.com/mvs

### **PrtSpool**
- Print spooler for MVS3.8j
- Author: Tim Pinkawa
- Source: http://www.timpinkawa.net/hercules

### **BREXX: a MVS 3.8j REXX**
- https://github.com/mvslovers/brexx370

### **RPF (Rob's Programming Facility) 1.92**
- Author: Rob Prins
- Source: http://www.prince-webdesign.nl/rpf

### **RFE (Review Front End) 50.3**
- Author: Greg Price - Prycroft Six
- Source: http://www.prycroft6.com.au/REVIEW/index.html

### **FTPD**
- Authors: Jason Winter (JCC) and Juergen Winkelmann

### **SXMaclib, EZASMI and MVSDDT**
- Author: Shelby Lynne Beach
- Source: http://www.mvsddt.altervista.org/


### [**TODO**] Other contributions 
- I need to reference other authors and contributions.

## Someday, I am going to install

### **Kicks**: A transaction processing system for CMS & TSO
An alternative to CICS for MVS3.8j.
- Author: Mike Noel
- Source: http://www.kicksfortso.com/
- Permissive license to distribute code inside MVS? I don't think so.

### **MvsSplit**
- Print spooler for MVS3.8j
- Source: https://github.com/dasta400/mvssplitspl
- Fork: https://github.com/moshix/mvssplitspl

### **See other interesting MVS projects**
- https://github.com/mainframed/tk4
- https://github.com/mainframed/DOGECICS
- https://github.com/HackerSmacker/Lua370

### Misc
- https://manytools.org/hacker-tools/ascii-banner/
