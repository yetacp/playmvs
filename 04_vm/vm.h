#include <stdio.h>
#define FIB 0
#define ZERO 0
#define MINUSONE -1
#define INVALID_OPCODE 100
#define STACK_UNDERFLOW 101
#define STACK_OVERFLOW 102
#define STACK_MAX 500

enum
{
    HALT = 0,
    /* Stack */
    CONST,
    GLOAD,
    GSTOR,
    LOAD,
    STORE,
    DROP,
    SWAP,
    DUP,
    /* Branch */
    JMP,
    JMPF,
    CALL,
    RET,
    /* Boolean operators */
    NOT,
    AND,
    OR,
    XOR,
    /* Relational operators */
    EQ,
    NE,
    LT,
    LE,
    GT,
    GE,
    /* Arithmetic integer operators */
    INEG,
    IADD,
    ISUB,
    IMUL,
    IDIV,
    IMOD,
    ISHL,
    ISHR,
    /* Arithmetic double floating point operators */
    FNEG,
    FADD,
    FSUB,
    FMUL,
    FDIV,
    FMOD,
    /* Arithmetic decimal operators */
    DNEG,
    DADD,
    DSUB,
    DMUL,
    DDIV,
    /* I/O functions */
    OPEN,
    CLOSE,
    READ,
    WRITE,
    /* Dynamic Memory */
    ALLOC,
    FREE,
    MSET,
    MCMP
};

extern int code[];
