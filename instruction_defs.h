#ifndef __INSTRUCTION_DEFS__
#define __INSTRUCTION_DEFS__
#include "type_definitions.h"

//z# don't care

typedef union {
    word val;
    struct{
        word nnn:12;
    };
}NNNInstr;

typedef union {
    word val;
    struct{
        byte nn, x:4;
    };
}XNNInstr;

typedef union {
    word val;
    struct{
        byte z0:4, y:4, x:4;
    };
}XYInstr;

typedef union {
    word val;
    struct{
        byte n:4, y:4, x:4;
    };
}XYNInstr;

typedef union {
    word val;
    struct{
        byte z0:4, z1:4, x:4;
    };
}XInstr;

#endif