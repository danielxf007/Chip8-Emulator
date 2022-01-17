#ifndef __PROCESSOR__
#define __PROCESSOR__
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "type_defs.h"
#include <bitset>
#define UNDEFINED_INSTR "This instruction is undefined"

class Processor{
    private:
        byte V[16], SP, *keys;
        word PC, I, stack[16], op_code;
        RamMem *ram;
        GFXMem *gfx;
        Timers *timers;
        NNNInstr nnn_instr;
        XNNInstr xnn_instr;
        XYInstr xy_instr;
        XYNInstr xyn_instr;
        XInstr x_instr;
    public:
        Processor(RamMem *ram, GFXMem *gfx, Timers *timers, u8 *keys);
        bit getBit(byte b, u8 bit_pos);
        nibble getNibble(word w, u8 nibble_pos);
        byte getByte(word w, u8 byte_pos);
        u8 getDecimalDigit(u8 b, u16 decimal_power);
        void reset();
        void incrementPC();
        void decrementPC();
        void stack_pop(word *buffer);
        void stack_push(word value);
        void cls();
        void ret();
        void jpAddr();
        void callAddr();
        void seVxNN();
        void sneVxNN();
        void seVxVy();
        void ldVxNN();
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
        void rndVxNN();
        void drwVxVyN();
        void skpVx();
        void skpnVx();
        void ldVxDT();
        void ldVxK();
        void ldDTVx();
        void ldSTVx();
        void addIVx();
        void ldFVx();
        void ldBVx();
        void ldMemIVx();
        void ldVxMemI();
        void fetchInstr();
        void processInstr();
        void printRegisters();

};

inline bit Processor::getBit(byte b, u8 bit_pos){
    return ((b & (0x1 << bit_pos)) >> bit_pos);
}

inline nibble Processor::getNibble(word w, u8 nibble_pos){
    return ((w & (0xF << 4*nibble_pos)) >>  (4*nibble_pos));
}

inline byte Processor::getByte(word w, u8 byte_pos){
    return ((w & (0xFF << 8*byte_pos)) >>  (8*byte_pos));
}

inline byte Processor::getDecimalDigit(u8 b, u16 decimal_power){
    return ((b%(decimal_power*10))/decimal_power);
}

inline void Processor::incrementPC(){
    PC += 2;
}

inline void Processor::decrementPC(){
    PC -= 2;
}

inline void Processor::stack_pop(word *buffer){
    *buffer = stack[--SP];
}

inline void Processor::stack_push(word value){
    stack[SP++] = value;
}

inline void Processor::fetchInstr(){
    op_code = (word(ram->mem_ptr[PC]) << 8) | (word(ram->mem_ptr[PC+1]));
    incrementPC();
}
#endif