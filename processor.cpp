#include "processor.h"

inline bit Processor::getBit(byte b, byte bit_pos){
    return (b & (0x1 << bit_pos)) >> bit_pos;
}

inline void Processor::incrementPc(){
    PC += 2;
}

inline void Processor::stack_pop(word *buffer){
    *buffer = stack[SP--];
}

inline void Processor::stack_push(word value){
    stack[SP++] = value;
}

void Processor::cls(){

}

void Processor::ret(){
    stack_pop(&PC);
}

void Processor::callAddr(){
    stack_push(PC);
    PC = nnn_instr.nnn;
}

void Processor::jpAddr(){
    PC = nnn_instr.nnn;
}

void Processor::ldVxN(){
    V[xnn_instr.x] = xnn_instr.nn;
}

void Processor::addVxNN(){
    V[xnn_instr.x] += xnn_instr.nn;
}

void Processor::ldVxVy(){
    V[xy_instr.x] = xy_instr.y;
}

void Processor::orVxVy(){
    V[xy_instr.x] |= V[xy_instr.y];
}

void Processor::andVxVy(){
    V[xy_instr.x] &= V[xy_instr.y];
}

void Processor::xorVxVy(){
    V[xy_instr.x] ^= V[xy_instr.y];
}

void Processor::addVxVy(){
    word result = V[xy_instr.x] + V[xy_instr.y];
    V[0xF] = result > 0xFF? 1 : 0;
    V[xy_instr.x] = result;
}

void Processor::subVxVy(){
    V[0xF] = V[xy_instr.x] > V[xy_instr.y]? 1 : 0;
    V[xy_instr.x] -= V[xy_instr.y];
}

void Processor::shrVx(){
    V[0xF] = getBit(V[xy_instr.x], 0);
    V[xy_instr.x] >>= 1;
}

void Processor::subnVxVy(){
    V[0xF] = V[xy_instr.y] > V[xy_instr.x]? 1 : 0;
    V[xy_instr.x] = V[xy_instr.y] - V[xy_instr.x];
}

void Processor::shlVx(){
    V[0xF] = getBit(V[xy_instr.x], 7);
    V[xy_instr.x] <<= 1;
}

void Processor::sneVxVy(){
    if(V[xy_instr.x] != V[xy_instr.y]){
        incrementPc();
    }
}

void Processor::ldIAddr(){
    I = nnn_instr.nnn;
}

void Processor::jpV0Addr(){
    PC = nnn_instr.nnn + V[0x0];
}