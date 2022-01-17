#ifndef __TYPE_DEFINITIONS__
#define __TYPE_DEFINITIONS__
#include <stdint.h>
typedef enum {STARTED, RUNNING, LOADING, PAUSED, RESETED, FINISHED} EMU_STATES;
typedef uint8_t bit;
typedef uint8_t nibble;
typedef uint8_t byte;
typedef uint16_t word;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef struct{
    u8 *mem_ptr;
    u16 sz;
}RamMem;

typedef struct{
    u8 *mem_ptr, n_rows, m_cols;
    u16 sz;
}GFXMem;

typedef struct{
    u8 DT, ST, dt_timer_counter, st_timer_counter;
}Timers;

//z# don't care

typedef union {
    word val;
    struct{
        word nnn:12;
    };
}NNNInstr;

typedef union {
    word val;
    struct{
        byte nn, x:4;
    };
}XNNInstr;

typedef union {
    word val;
    struct{
        byte z0:4, y:4, x:4;
    };
}XYInstr;

typedef union {
    word val;
    struct{
        byte n:4, y:4, x:4;
    };
}XYNInstr;

typedef union {
    word val;
    struct{
        byte z0:4, z1:4, x:4;
    };
}XInstr;
#endif