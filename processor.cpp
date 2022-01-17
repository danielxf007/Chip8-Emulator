#include "processor.h"

Processor::Processor(RamMem *ram, GFXMem *gfx, Timers *timers, u8 *keys){
    SP = 0;
    I = 0;
    PC = 0x200;
    this->ram = ram;
    this->gfx = gfx;
    this->timers = timers;
    this->keys = keys;
    std::memset(V, 0, 16);
}

void Processor::reset(){
    SP = 0;
    I = 0;
    PC = 0x200;
    std::memset(V, 0, 16);
}

void Processor::cls(){
    std::memset(gfx->mem_ptr, 0, gfx->sz);
}

void Processor::ret(){
    stack_pop(&PC);
}

void Processor::jpAddr(){
    PC = nnn_instr.nnn;
}

void Processor::callAddr(){
    stack_push(PC);
    PC = nnn_instr.nnn;
}

void Processor::seVxNN(){
    if(V[xnn_instr.x] == xnn_instr.nn){
        incrementPC();
    }
}

void Processor::sneVxNN(){
    if(V[xnn_instr.x] != xnn_instr.nn){
        incrementPC();
    }
}

void Processor::seVxVy(){
    if(V[xy_instr.x] == V[xy_instr.y]){
        incrementPC();
    }
}

void Processor::ldVxNN(){
    V[xnn_instr.x] = xnn_instr.nn;
}

void Processor::addVxNN(){
    V[xnn_instr.x] += xnn_instr.nn;
}

void Processor::ldVxVy(){
    V[xy_instr.x] = V[xy_instr.y];
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
        incrementPC();
    }
}

void Processor::ldIAddr(){
    I = nnn_instr.nnn;
}

void Processor::jpV0Addr(){
    PC = nnn_instr.nnn + V[0x0];
}

void Processor::rndVxNN(){
    V[xnn_instr.x] = (rand() % 0xFF) & xnn_instr.nn;
}

void Processor::drwVxVyN(){
    u16 k;
    byte sprite_row;
    V[0xF] = 0;
    for(u8 i = 0; i < xyn_instr.n; i++){
        sprite_row = ram->mem_ptr[I+i];
        for(u8 j = 0; j < 8; j++){
            if(sprite_row & (0x80 >> j)){
                k = (gfx->m_cols*(V[xyn_instr.y]+i) + (V[xyn_instr.x] + j))%gfx->sz;
                if(gfx->mem_ptr[k]){
                    V[0xF] = 1;
                }
                gfx->mem_ptr[k] ^= 0x01;
            }
        }
    }
}

void Processor::skpVx(){
    if(keys[x_instr.x]){
        incrementPC();
    }
}

void Processor::skpnVx(){
    if(!keys[x_instr.x]){
        incrementPC();
    }
}

void Processor::ldVxDT(){
    V[x_instr.x] = timers->DT;
}

void Processor::ldVxK(){
    decrementPC();
    for(u8 i = 0; i < 16; i++){
        if(keys[i]){
            V[x_instr.x] = i;
            incrementPC();
            break;
        }
    }
}

void Processor::ldDTVx(){
    timers->DT = V[x_instr.x];
}

void Processor::ldSTVx(){
    timers->ST = V[x_instr.x];
}

void Processor::addIVx(){
    I += V[x_instr.x];
}

void Processor::ldFVx(){
    I = V[x_instr.x]*5;
}

void Processor::ldBVx(){
    ram->mem_ptr[I] = getDecimalDigit(V[x_instr.x], 100);
    ram->mem_ptr[I+1] = getDecimalDigit(V[x_instr.x], 10);
    ram->mem_ptr[I+2] = getDecimalDigit(V[x_instr.x], 1);
}

void Processor::ldMemIVx(){
    for(word addr = I; addr < I+x_instr.x+1; addr++){
        ram->mem_ptr[addr] = V[addr - I];
    }
}

void Processor::ldVxMemI(){
    for(word addr = I; addr < I+x_instr.x+1; addr++){
        V[addr - I] = ram->mem_ptr[addr];
    }
}

void Processor::processInstr(){
    fetchInstr();
    switch(getNibble(op_code, 3)){
            case 0x0:
                if((op_code & 0xFFF) == 0x0E0){
                    cls();
                }else if((op_code & 0xFFF) == 0x0EE){
                    ret();
                }else{
                    std::cout << std::hex << int(op_code) << UNDEFINED_INSTR << std::endl;
                }
                break;
            case 0x1:
                nnn_instr.val = op_code;
                jpAddr();
                break;
            case 0x2:
                nnn_instr.val = op_code;
                callAddr();
                break;
            case 0x3:
                xnn_instr.val = op_code;
                seVxNN();
                break;
            case 0x4:
                xnn_instr.val = op_code;
                sneVxNN();
                break;
            case 0x5:
                xy_instr.val = op_code;
                seVxVy();
                break;
            case 0x6:
                xnn_instr.val = op_code;
                ldVxNN();
                break;
            case 0x7:
                xnn_instr.val = op_code;
                addVxNN();
                break;
            case 0x8:
                xy_instr.val = op_code;
                switch(getNibble(op_code, 0)){
                    case 0x0:
                        ldVxVy();
                        break;
                    case 0x1:
                        orVxVy();
                        break;
                    case 0x2:
                        andVxVy();
                        break;
                    case 0x3:
                        xorVxVy();
                        break;
                    case 0x4:
                        addVxVy();
                        break;
                    case 0x5:
                        subVxVy();
                        break;
                    case 0x6:
                        shrVx();
                        break;
                    case 0x7:
                        subnVxVy();
                        break;
                    case 0xE:
                        shlVx();
                        break;
                    default:
                        std::cout << std::hex << int(op_code) << UNDEFINED_INSTR << std::endl;
                }
                break;
            case 0x9:
                xy_instr.val = op_code;
                sneVxVy();
                break;
            case 0xA:
                nnn_instr.val = op_code;
                ldIAddr();
                break;
            case 0xB:
                nnn_instr.val = op_code;
                jpV0Addr();
                break;
            case 0xC:
                xnn_instr.val = op_code;
                rndVxNN();
                break;
            case 0xD:
                xyn_instr.val = op_code;
                drwVxVyN();
                break;
            case 0xE:
                x_instr.val = op_code;
                if(getByte(op_code, 0) == 0x9E){
                    skpVx();
                }else if(getByte(op_code, 0) == 0xA1){
                    skpnVx();
                }else{
                    std::cout << std::hex << int(op_code) << UNDEFINED_INSTR << std::endl;
                }
                break;
            case 0xF:
                x_instr.val = op_code;
                switch(getByte(op_code, 0)){
                case 0x07:
                    ldVxDT();
                    break;
                case 0x0A:
                    ldVxK();
                    break;
                case 0x15:
                    ldDTVx();
                    break;
                case 0x18:
                    ldSTVx();
                    break;
                case 0x1E:
                    addIVx();
                    break;
                case 0x29:
                    ldFVx();
                    break;
                case 0x33:
                    ldBVx();
                    break;
                case 0x55:
                    ldMemIVx();
                    break;
                case 0x65:
                    ldVxMemI();
                    break;
                default:
                    std::cout << std::hex << int(op_code) << UNDEFINED_INSTR << std::endl;
                }
                break;
            default:
                std::cout << std::hex << int(op_code) << UNDEFINED_INSTR << std::endl;
        }
}

void Processor::printRegisters(){
    std::cout << "######" << std::endl;
    for(u8 i = 0; i < 16; i++){
        std::cout << "V" << std::hex << int(i) << " : " << std::hex << int(V[i]) << std::endl;
    }
    std::cout << "PC: " << std::hex << int(PC)  << std::endl;
    std::cout << "Instr: " << std::hex << int(op_code) << std::endl;
    std::cout << "DT: " << std::hex << int(timers->DT)  << std::endl;
    std::cout << "ST: " << std::hex << int(timers->ST)  << std::endl;
    std::cout << "I: " << std::hex << int(I) << std::endl;
    std::cout << "SP: " << std::hex << int(SP) << std::endl;
    for(u8 i = 0; i < 16; i++){
        std::cout << "Stack[" << std::hex << int(i) << "]: " << std::hex << int(stack[i]) << std::endl;
    }
}