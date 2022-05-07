# About Debugging application with MVSDDT

## How to...
- Install MVSDDT client software
- Install MVSDDT service in MVS Sysgen
- Change SVC number to 241 from 233 in SYS2.MACLIB(DDTBRK) and SYSGEN.DDT.MACLIB(DDTBRK) 
    - &DDTSVC# SETA  241     DDT SVC number

## Linux
```bash
$ make # install program in MVS via sockdev
$ make execute # execute adder with MVSDDT
```

## Install MVSDDT in MVS Sysgen

List of APFs in SYS1.PARMLIB(IEAAPF00)
- SYS1.VTAMLIB MVSRES,  // REQUIRED BY MVS
- SYS1.INDMAC MVSRES,   // REQUIRED BY MVS
- SYS2.LINKLIB MVS000,  // USER BATCH LINKLIB
- SYSC.LINKLIB SYSCPK   // COMPILER/TOOLS VOLUME 

See https://h390-mvs.yahoogroups.narkive.com/UG0EFPQN/clpa-issue-with-jay-moseley-style-mvs3-8j-and-mvsddt

```
First down load MVSDDT and install it on your PC where it will create directories containing the PC (client) and the MVS (server) code. 

The Server directory contains the JCL to load a tape on to MVS. The MVSDDT manual in the client directory contains all the steps needed to get the right thing in the right place. 

The one thing we Moseley MVS users have to do is rename the SVC program from IGC0023C to a SVC defined on our system. I have gone for SVC 241 which means, due to SVC naming conventions, the new name is IGC0024A. 

Copy this module into SYS1.LPALIB and restart MVS. 

At the very first message issue Reply R 00,CLPA which should pull in the new MVSDDT SVC. 

Now you can start the client side connection to MVS and run a test job.

There is an addition to be added to the Hercules configuration file which defines the CTC device additions. All this is described in the MVSDDT manual under the Server installation section.
```
