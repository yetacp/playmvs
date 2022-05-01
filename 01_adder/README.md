# About Adder

## Requirements
- You **MUST** compile GCCMVS

```bash
sudo apt install gcc-multilib
cd gccmvs
make
```

## How to...
- Passing parameters in JCL to a C program (see PARM in 02_execute.jcl).
- Create CLISTs. See [Jay Moseley TSO Tutorial](http://www.jaymoseley.com/hercules/tso_tutor/tsotutor.htm)
- You can execute from TSO calling ADDER.

## Linux
```bash
$ make # install program in MVS via sockdev
$ make execute # execute adder in background (OP1=3 OP2=4)
3 + 4 = 7)
```
## MVS
```
tso adder 1960 50

 [TSO] OP1=1960 OP2=50
 char * argv[] = ADDER 1960 50
 1960 + 50 = 2010
 ***
```
