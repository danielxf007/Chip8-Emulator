#ifndef __INPUT__
#define __INPUT__
#include <iostream>
#include <SDL2/SDL.h>
#include "type_defs.h"
class InputHandler{
    private:
        u8 *keys;
        u8 *emu_state;
    public:
        InputHandler(u8 *keys, u8 *emu_state);
        u16 mapKey(u8 key);
        void doKeyDown(SDL_KeyboardEvent *event);
        void doKeyUp(SDL_KeyboardEvent *event);
        void doInput();
        void printKeys();
};
#endif