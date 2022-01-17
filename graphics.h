#ifndef __GRAPHICS__
#define __GRAPHICS__
#include <iostream>
#include <SDL2/SDL.h>
#include "type_defs.h"


class Graphicator{
    private:
        u32 window_flags, screen_w, screen_h;
        GFXMem *gfx;
        SDL_Window *window;
    public:
        Graphicator(u32 screen_w, u32 screen_h, GFXMem *gfx, const char *window_title);
        ~Graphicator();
        void renderScreen();
};

#endif