#include "graphics.h"

Graphicator::Graphicator(u32 screen_w, u32 screen_h, GFXMem *gfx, const char *window_title){
    this->window_flags = 0;
    this->screen_w = screen_w;
    this->screen_h = screen_h;
    this->gfx = gfx;
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << "Couldn't initialize SDL";
		exit(1);
	}
    this->window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
     screen_w, screen_h, this->window_flags);
    SDL_SetSurfaceRLE(SDL_GetWindowSurface(window), 1);
}

Graphicator::~Graphicator(){
    SDL_DestroyWindow(window);
}

void Graphicator::renderScreen(){
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_LockSurface(surface);
    SDL_memset(surface->pixels, 0xFFFFFFFF, screen_h*(surface->pitch));
    u32 *screen = (u32*) surface->pixels;
    for(u32 n_row = 0; n_row < screen_h; n_row++){
        for(u32 m_col = 0; m_col < screen_w; m_col++)
            screen[screen_w*n_row + m_col] = gfx->mem_ptr[(n_row/10)*64 + m_col/10]? 0xFFFFFFFF: 0;
    }
    SDL_UnlockSurface(surface);
    SDL_UpdateWindowSurface(window);
}