#include "emulator.h"

Emulator::Emulator(){
    keys = new u8[N_KEYS];
    std::memset(keys, 0, N_KEYS);
    emu_state = STARTED;
    ram = new RamMem;
    ram->mem_ptr = new u8[RAM_SZ];
    std::memset(ram->mem_ptr, 0, RAM_SZ);
    std::memcpy(ram->mem_ptr, font, FONT_DATA_SZ);
    ram->sz = RAM_SZ;
    gfx = new GFXMem;
    gfx->mem_ptr = new u8[GFX_SZ];
    std::memset(gfx->mem_ptr, 0, GFX_SZ);
    gfx->sz = GFX_SZ;
    gfx->n_rows = 32;
    gfx->m_cols = 64;
    timers = new Timers;
    std::memset(timers, 0, sizeof(Timers));
    processor = new Processor(ram, gfx, timers, keys);
    input_handler = new InputHandler(keys, &emu_state);
    graphicator = new Graphicator(SCREEN_W, SCREEN_H, gfx, name);
}

Emulator::~Emulator(){
    delete ram->mem_ptr;
    delete ram;
    delete gfx->mem_ptr;
    delete gfx;
    delete timers;
    delete processor;
    delete input_handler;
    delete graphicator;
}

void Emulator::getRomPath(){
    std::cout << "Enter Rom Path: ";
    std::cin >> buffer;
}

void Emulator::loadRom(){
    std::FILE *file;
    file = std::fopen(buffer, "rb");
    if(!file){
        std::cout << "File not found" << std::endl;
        exit(1);
    }
    std::fread(ram->mem_ptr + FONT_DATA_SZ, 1, RAM_SZ-FONT_DATA_SZ, file);
    std::fclose(file);
}

void Emulator::printRom(u16 n_bytes){
    for(u16 i = 0x200; i < 0x200+n_bytes; i+=2){
        std::cout << "Memory Addr: " << std::hex << int(i) << " Value: " << std::hex << (((int(ram->mem_ptr[i]))<<8) | int(ram->mem_ptr[i+1])) << std::endl;
    }
}

void Emulator::emulate(){
    while(emu_state != FINISHED){
        switch (emu_state){
        case STARTED:
            emu_state = LOADING;
            break;
        case LOADING:
            reset();
            getRomPath();
            loadRom();
            emu_state = RUNNING;
            break;
        case RUNNING:
            input_handler->doInput();
            processor->processInstr();
            decrementTimers();
            graphicator->renderScreen();
            break;
        case  PAUSED:
            input_handler->doInput();
            break;
        }
    }
}

void Emulator::decrementTimers(){
    if(timers->DT > 0x0 && timers->dt_timer_counter == 60){
        --(timers->DT);
        timers->dt_timer_counter = 0;
    }else if(timers->DT > 0x0 && timers->dt_timer_counter < 60){
        ++(timers->dt_timer_counter);
    }
    if(timers->ST > 0x0 && timers->st_timer_counter == 60){
        --(timers->ST);
        timers->st_timer_counter = 0;
    }else if(timers->ST > 0x0 && timers->st_timer_counter < 60){
        ++(timers->st_timer_counter);
    }
}

void Emulator::reset(){
    std::memset(keys, 0, N_KEYS);
    std::memset(ram->mem_ptr+FONT_DATA_SZ, 0, RAM_SZ-FONT_DATA_SZ);
    std::memset(gfx->mem_ptr, 0, gfx->sz);
    std::memset(timers, 0, sizeof(Timers));
    processor->reset();
}
