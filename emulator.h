#ifndef __EMULATOR__
#define __EMULATOR__
#include "type_defs.h"
#include "processor.h"
#include "input.h"
#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include<iostream>
#define N_KEYS 16
#define FONT_DATA_SZ 0x200
#define SCREEN_W 640
#define SCREEN_H 320
#define RAM_SZ 4096
#define GFX_SZ 2048


class Emulator{
    private:
        const u8 FPS = 60;
        const u16 FRAME_DELAY = 1000/FPS;
        u32 frame_start, frame_time;
        char buffer[128];
        u8 emu_state, *keys;
        RamMem *ram;
        GFXMem *gfx;
        Timers *timers;
        Processor *processor;
        InputHandler *input_handler;
        Graphicator *graphicator;
        const char *name = "Chip8 Emulator";
        const u8 font[FONT_DATA_SZ] ={
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };
    public:
        Emulator();
        ~Emulator();
        void getRomPath();
        void loadRom();
        void printRom(u16 n_bytes);
        void emulate();
        void decrementTimers();
        void reset();
};
#endif