# Playground projects

This folder contains some programs to test C programming in MVS.
 
These programs are compiled inside **Linux** using GCCMVS to generate source code in assembly.

I use jobs to send these source code to MVS through Hercules sockdevs (3505 card readers).

Assembling (IFOX00) and linkediting (IEWL) are executed inside **MVS**.

## ADDER

C program to receive 2 numbers from JCL and add them.

## Fileio

C program to read and print a dataset declared in DD JCL.

## FSS projects
Make full screen MVS programs using amazing Tommy Sprinkle's "C Full Screen API" .

- Source: http://tommysprinkle.com/mvs/fss/using.html
- FSS_01_hello - Another ye olde Hello World.
- FSS_02_hello - Yet another ye olde Hello World with colors.
- FSS_03_login - Read a username and password.
- FSS_04_panel - Use Scruples editor to create a complex panel.
- FSS_05_menu  - A menu example using a panel.

## Libs (Auxiliary libraries for projects)
FSS libraries (only 'svc' version for GCCMVS)

## LUA (It is not working)
Yet another not working MVS port of Lua 5.4.
- You can find a working port in https://github.com/HackerSmacker/Lua370

## Multiple (compile and link multiple C programs)

- I cross-compile two C programs in **Linux** to assembly source code.
- Generated assembly code is compiled using IFOX00 in **MVS**.
- After, modules are linked using IEWL in **MVS**.

## Panel Editor

A web panel editor for FSS API.
- Author: myself
- Yet not working.

## PDPCLIB
- Sample programs using PDPCLIB.
- Not tested.

## VM

A tiny toy virtual machine written in C.
A Fibonnaci algorithm is hard coded in vmcode.c file.

## VSAM 

A C implementation of VSAM API
- Author: myself
- Only KSKDS works