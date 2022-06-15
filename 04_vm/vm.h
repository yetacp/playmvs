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
    I_NEG,
    I_ADD,
    I_SUB,
    I_MUL,
    I_DIV,
    I_MOD,
    I_SHL,
    I_SHR,
    /* Arithmetic double floating point operators */
    F_NEG,
    F_ADD,
    F_SUB,
    F_MUL,
    F_DIV,
    F_MOD,
    /* Arithmetic decimal operators */
    D_NEG,
    D_ADD,
    D_SUB,
    D_MUL,
    D_DIV,
    /* I/O functions */
    OPEN,
    CLOSE,
    READ,
    WRITE,
    /* Dynamic Memory */
    ALLOC,
    FREE,
    MEMSET,
    MEMCMP
};

extern int code[];
