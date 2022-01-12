#ifndef __PROCESSOR__
#define __PROCESSOR__
#include <iostream>
#include "type_defs.h"
#include "instruction_defs.h"
#define RAM_SZ 4096

class Processor{
    private:
        byte V[16], ram[RAM_SZ], SP;
        word PC, I, stack[16];
        NNNInstr nnn_instr;
        XNNInstr xnn_instr;
        XYInstr xy_instr;
        XYNInstr xyn_instr;
        XYNInstr x_instr;
    public:
        bit getBit(byte b, byte bit_pos);
        void incrementPc();
        void stack_pop(word *buffer);
        void stack_push(word value);
        void cls();
        void ret();
        void jpAddr();
        void callAddr();
        void seVxNN();
        void sneVxNN();
        void seVxVy();
        void ldVxN();
        void addVxNN();
        void ldVxVy();
        void orVxVy();
        void andVxVy();
        void xorVxVy();
        void addVxVy();
        void subVxVy();
        void shrVx();
        void subnVxVy();
        void shlVx();
        void sneVxVy();
        void ldIAddr();
        void jpV0Addr();

};

#endif