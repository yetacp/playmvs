#include "vm.h"

/* 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584 */

int code[] = {
    /* int fib(n): */
    /*   if(n == 0) return 0; */
    /* 0 - load last function argument N */
    LOAD, -3,
    /* 2 - put 0 */
    CONST, 0,
    /* 4 - check equality: N == 0 */
    EQ,
    /* 5 - if they are NOT equal, goto 10 */
    JMPF, 10,
    /* 7 - otherwise put 0 */
    CONST, 0,
    /* 9 - and return it */
    RET,

    /* if(n < 3) return 1; */
    /* 10 - load last function argument N */
    LOAD, -3,
    /* 12 - put 3 */
    CONST, 3,
    /* 14 - check if 3 is less than N */
    LT,
    /* 15 - if 3 is NOT less than N, goto 20 */
    JMPF, 20,
    /* 17 - otherwise put 1 */
    CONST, 1,
    /* 19 - and return it */
    RET,
    /*   else return fib(n-1) + fib(n-2); */
    /* 20 - load last function argument N */
    LOAD, -3,
    /* 22 - put 1 */
    CONST, 1,
    /* 24 - calculate: N-1, result is on the stack */
    SUB,
    /* 25 - call fib function with 1 arg. from the stack */
    CALL, FIB, 1,
    /* 28 - load last function argument N */
    LOAD, -3,
    /* 30 - put 2 */
    CONST, 2,
    /* 32 - calculate: N-2, result is on the stack */
    SUB,
    /* 33 - call fib function with 1 arg. from the stack */
    CALL, FIB, 1,
    /* 36 - since 2 fibs pushed their
    ret values on the stack, just add them */
    ADD,
    /* 37 - return from procedure */
    RET,

    /* main() */
    /* for i = 0 to 100 */
    /* 38 */
    CONST, 0,
    /* 40 */
    GSTORE, 0,
    /* 42 */
    GLOAD, 0,
    /* 44 - call fib(valor) with 1 parameter */
    CALL, FIB, 1,
    PRINT,
    GLOAD, 0,
    CONST, 1,
    ADD,
    DUP,
    GSTORE, 0,
    CONST, 10,
    LT,
    NOT,
    JMPF, 42,
    HALT};
