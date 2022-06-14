#include "vm.h"

int main(int argc, char **argv)
{
    int *tmp;
    int debug;    // print the executed instructions
    int assembly; // print out the assembly and source

    int *pc, *bp, *sp, ax, cycle; // virtual machine registers

    int poolsize;

    int *text,     // text segment
        *stack;    // stack
    int *old_text; // for dump text segment
    char *data;    // data segment
    int *idmain;

    poolsize = 256 * 1024; // arbitrary size

    // allocate memory
    if (!(text = malloc(poolsize)))
    {
        printf("could not malloc(%d) for text area\n", poolsize);
        return -1;
    }
    if (!(data = malloc(poolsize)))
    {
        printf("could not malloc(%d) for data area\n", poolsize);
        return -1;
    }
    if (!(stack = malloc(poolsize)))
    {
        printf("could not malloc(%d) for stack area\n", poolsize);
        return -1;
    }

    memset(text, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);

    old_text = text;

    if (!(pc = (int *)idmain[Value]))
    {
        printf("main() not defined\n");
        return -1;
    }

    sp = (int *)((int)stack + poolsize);
    *--sp = EXIT; // call exit if main returns
    *--sp = PUSH;
    tmp = sp;
    *--sp = argc;
    *--sp = (int)argv;
    *--sp = (int)tmp;

    int op, *tmp;
    cycle = 0;
    while (1)
    {
        cycle++;
        op = *pc++; // get next operation code

        // print debug info
        if (debug)
        {
            printf("%d> %.4s", cycle,
                   &"LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,"
                    "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
                    "OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT"[op * 5]);
            if (op <= ADJ)
                printf(" %d\n", *pc);
            else
                printf("\n");
        }
        if (op == IMM)
        {
            ax = *pc++;
        } // load immediate value to ax
        else if (op == LC)
        {
            ax = *(char *)ax;
        } // load character to ax, address in ax
        else if (op == LI)
        {
            ax = *(int *)ax;
        } // load integer to ax, address in ax
        else if (op == SC)
        {
            ax = *(char *)*sp++ = ax;
        } // save character to address, value in ax, address on stack
        else if (op == SI)
        {
            *(int *)*sp++ = ax;
        } // save integer to address, value in ax, address on stack
        else if (op == PUSH)
        {
            *--sp = ax;
        } // push the value of ax onto the stack
        else if (op == JMP)
        {
            pc = (int *)*pc;
        } // jump to the address
        else if (op == JZ)
        {
            pc = ax ? pc + 1 : (int *)*pc;
        } // jump if ax is zero
        else if (op == JNZ)
        {
            pc = ax ? (int *)*pc : pc + 1;
        } // jump if ax is not zero
        else if (op == CALL)
        {
            *--sp = (int)(pc + 1);
            pc = (int *)*pc;
        } // call subroutine
        //else if (op == RET)  {pc = (int *)*sp++;}                              // return from subroutine;
        else if (op == ENT)
        {
            *--sp = (int)bp;
            bp = sp;
            sp = sp - *pc++;
        } // make new stack frame
        else if (op == ADJ)
        {
            sp = sp + *pc++;
        } // add esp, <size>
        else if (op == LEV)
        {
            sp = bp;
            bp = (int *)*sp++;
            pc = (int *)*sp++;
        } // restore call frame and PC
        else if (op == LEA)
        {
            ax = (int)(bp + *pc++);
        } // load address for arguments.

        else if (op == OR)
            ax = *sp++ | ax;
        else if (op == XOR)
            ax = *sp++ ^ ax;
        else if (op == AND)
            ax = *sp++ & ax;
        else if (op == EQ)
            ax = *sp++ == ax;
        else if (op == NE)
            ax = *sp++ != ax;
        else if (op == LT)
            ax = *sp++ < ax;
        else if (op == LE)
            ax = *sp++ <= ax;
        else if (op == GT)
            ax = *sp++ > ax;
        else if (op == GE)
            ax = *sp++ >= ax;
        else if (op == SHL)
            ax = *sp++ << ax;
        else if (op == SHR)
            ax = *sp++ >> ax;
        else if (op == ADD)
            ax = *sp++ + ax;
        else if (op == SUB)
            ax = *sp++ - ax;
        else if (op == MUL)
            ax = *sp++ * ax;
        else if (op == DIV)
            ax = *sp++ / ax;
        else if (op == MOD)
            ax = *sp++ % ax;

        else if (op == EXIT)
        {
            printf("exit(%d)", *sp);
            return *sp;
        }
        else if (op == OPEN)
        {
            ax = open((char *)sp[1], sp[0]);
        }
        else if (op == CLOS)
        {
            ax = close(*sp);
        }
        else if (op == READ)
        {
            ax = read(sp[2], (char *)sp[1], *sp);
        }
        else if (op == PRTF)
        {
            tmp = sp + pc[1];
            ax = printf((char *)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]);
        }
        else if (op == MALC)
        {
            ax = (int)malloc(*sp);
        }
        else if (op == MSET)
        {
            ax = (int)memset((char *)sp[2], sp[1], *sp);
        }
        else if (op == MCMP)
        {
            ax = memcmp((char *)sp[2], (char *)sp[1], *sp);
        }
        else
        {
            printf("unknown instruction:%d\n", op);
            return -1;
        }
    }
}