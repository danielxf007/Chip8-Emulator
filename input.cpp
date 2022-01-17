#include "input.h"

InputHandler::InputHandler(u8 *keys, u8 *emu_state){
    this->emu_state = emu_state;
    this->keys = keys;
}

u16 InputHandler::mapKey(u8 key){
    switch(key){
        case SDLK_1:
            return 0x1;
        case SDLK_2:
            return 0x2;
        case SDLK_3:
            return 0x3;
        case SDLK_4:
            return 0xC;
        case SDLK_q:
            return 0x4;
        case SDLK_w:
            return 0x5;
        case SDLK_e:
            return 0x6;
        case SDLK_r:
            return 0xD;
        case SDLK_a:
            return 0x7;
        case SDLK_s:
            return 0x8;
        case SDLK_d:
            return 0x9;
        case SDLK_f:
            return 0xE;
        case SDLK_z:
            return 0xA;
        case SDLK_x:
            return 0x0;
        case SDLK_c:
            return 0xB;
        case SDLK_v:
            return 0xF;
        case SDLK_ESCAPE:
            return 0x10;
        case SDLK_l:
            return 0x11;
        case SDLK_SPACE:
            return 0x12;
    }
    return 0x13;
}

void InputHandler::doKeyDown(SDL_KeyboardEvent *event){
    u16 k_code;
    if (event->repeat == 0){
        k_code = mapKey(event->keysym.sym);
        switch(k_code){
            case 0x10:
                *emu_state = FINISHED;
                break;
            case 0x11:
                *emu_state = LOADING;
                break;
            case 0x12:
                if(*emu_state == RUNNING)
                    *emu_state = PAUSED;
                else if(*emu_state == PAUSED)
                    *emu_state = RUNNING;
            case 0x13:
                break;
            default:
                keys[k_code]= 1;
        }
    }
}

void InputHandler::doKeyUp(SDL_KeyboardEvent *event){
    u16 k_code;
    if (event->repeat == 0){
        k_code = mapKey(event->keysym.sym);
        keys[k_code] = 0;
    }
}

void InputHandler::doInput(){
   SDL_Event event;
   while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_KEYDOWN:
            doKeyDown(&event.key);
            break;
        case SDL_KEYUP:
            doKeyUp(&event.key);
            break;
        }
   }   
}

void InputHandler::printKeys(){
    for(int i = 0; i<16; i++){
        if(keys[i])
            std::cout << "Key: " << i << " Pressed: " << bool(keys[i]) <<std::endl;
    }
}