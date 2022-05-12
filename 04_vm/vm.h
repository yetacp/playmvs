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
    CONST = 1,
    GLOAD,
    LOAD,
    GSTORE,
    STORE,
    DROP,
    SWAP,
    DUP,
    HALT,
    JMP,
    JMPF,
    CALL,
    RET,
    NEG,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NOT,
    AND,
    OR,
    LT,
    EQ,
    PRINT
};

extern int code[];
