#include "vm.h"

/* local scoped data */
int locals[STACK_MAX];
/* virtual stack */
int stack[STACK_MAX];

int run()
{
    /* program counter */
    register int pc = 38;
    /* stack pointer */
    register int sp = MINUSONE;
    /* frame pointer (for local scope) */
    register int fp = ZERO;
    register int tmpA;
    register int tmpB;
    register int opcode;
    register int addr;
    register int offset;
    register int rval;
    register int argc;

    do
    {
        opcode = code[pc];
        pc++;

        switch (opcode)
        {

        case HALT:
            /* stop the program */
            tmpA = stack[sp];
            printf("\nHALT stack[%d]=%d\n", sp, tmpA);
            return tmpA;

        case CONST:
            /* get next value from code and
            move it on top of the stack */
            tmpA = code[pc];
            pc++;
            sp++;
            if (sp >= STACK_MAX)
            {
                return STACK_OVERFLOW;
            }
            stack[sp] = tmpA;
            break;

        case GLOAD:
            addr = code[pc];
            pc++;
            tmpA = locals[addr];
            sp++;
            if (sp >= STACK_MAX)
            {
                return STACK_OVERFLOW;
            }
            stack[sp] = tmpA;
            break;

        case GSTOR:
            tmpA = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            addr = code[pc];
            pc++;
            locals[addr] = tmpA;
            break;

        case LOAD:
            offset = code[pc];
            pc++;
            sp++;
            if (sp >= STACK_MAX)
            {
                return STACK_OVERFLOW;
            }
            stack[sp] = stack[fp + offset];
            break;

        case STORE:
            tmpA = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            offset = code[pc];
            pc++;
            locals[fp + offset] = tmpA;
            break;

        case DROP:
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            break;

        case SWAP:
            /* ( n1 n2 - n2 n1) */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = tmpB;
            sp++;
            if (sp >= STACK_MAX)
            {
                return STACK_OVERFLOW;
            }
            stack[sp] = tmpA;
            break;

        case DUP:
            tmpA = stack[sp];
            sp++;
            if (sp >= STACK_MAX)
            {
                return STACK_OVERFLOW;
            }
            stack[sp] = tmpA;
            break;

        case JMP:
            /* Jump */
            pc = code[pc];
            pc++;
            break;

        case JMPF:
            /* Jump if false */
            addr = code[pc];
            pc++;
            if (!stack[sp])
            {
                pc = addr;
            }
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            break;

        case CALL:
            /* we expect all args to be on the stack */
            /* get next instruction as address of procedure jump */
            addr = code[pc];
            pc++;
            /* and next one as number of arguments to load */
            argc = code[pc];
            pc++;
            sp++;
            if (sp >= STACK_MAX)
            {
                return STACK_OVERFLOW;
            }
            /* save num args */
            stack[sp] = argc;
            sp++;
            if (sp >= STACK_MAX)
            {
                return STACK_OVERFLOW;
            }
            /* save function pointer */
            stack[sp] = fp;
            sp++;
            if (sp >= STACK_MAX)
            {
                return STACK_OVERFLOW;
            }
            /* save instruction pointer */
            stack[sp] = pc;
            /* set new frame pointer */
            fp = sp;
            /* move instruction pointer to target proc address */
            pc = addr;
            break;

        case RET:
            /* pop return value from top of the stack */
            rval = stack[sp];
            /* return from procedure address */
            sp = fp;
            /*  restore instruction pointer  */
            pc = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            /*  restore framepointer  */
            fp = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            /*  hom many args procedure has  */
            argc = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            /*  discard all of the args left  */
            sp -= argc;
            ++sp;
            /*  leave return value on top of the stack */
            stack[sp] = rval;
            break;

        case INEG:
            /* ( n1 - -n1  )  */
            stack[sp] = -stack[sp];
            break;

        case IADD:
            /* ( n1 n2 - n1+n2 )  */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = tmpA + tmpB;
            break;

        case ISUB:
            /* ( n1 n2 - n1-n2 )  */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = tmpA - tmpB;
            break;

        case IMUL:
            /* ( n1 n2 - n1*n2 )  */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = tmpA * tmpB;
            break;

        case IDIV:
            /* ( n1 n2 - n1/n2 )  */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = tmpA / tmpB;
            break;

        case IMOD:
            /* ( n1 n2 - n1 mod n2 )  */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = tmpA % tmpB;
            break;

        case NOT:
            /* ( n1 - !n1  )  */
            stack[sp] = !stack[sp];
            break;

        case AND:
            /* ( n1 n2 - n1 && n2 )  */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = tmpA && tmpB;
            break;

        case OR:
            /* ( n1 n2 - n1 || n2 )  */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = tmpA || tmpB;
            break;

        case EQ: /* EQ NOT ::= NE (n1 !== n2) */
            /* ( n1 n2 - n1 == n2 ? ) */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = ((tmpA == tmpB) ? 1 : 0);
            break;

        case LT:
            /* ( n1 n2 ) LT( n1 < n2 ?) */
            /* ( n1 n2 ) LT NOT( n1 >= n2 ?) */
            /* ( n1 n2 ) SWAP LT( n2 < n1 -> n1 > n2 ?) */
            /* ( n1 n2 ) SWAP LT NOT( n2 >= n1 -> n1 <= n2 ?) */
            tmpB = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            tmpA = stack[sp];
            stack[sp] = ((tmpA < tmpB) ? 1 : 0);
            break;

        case WRITE:
            tmpA = stack[sp];
            sp--;
            if (sp < -1)
            {
                return STACK_UNDERFLOW;
            }
            printf("%d ", tmpA);
            break;

        default:
            printf("Invalid opcode\n");
            return INVALID_OPCODE;
        }
    } while (1);
    return 0;
}

int main(int argc, char *argv[])
{
    run();
}