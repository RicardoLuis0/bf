#pragma once

#include <stdint.h>

#define STACKSIZE 128

#define TAPESIZE 0x1FFFE

typedef struct {
    uint32_t pc;
    uint32_t sp;
    uint32_t tp;
    uint32_t len;
    uint32_t stack[STACKSIZE];
    uint8_t tape[TAPESIZE];
    uint8_t data[];
} program_t;

program_t * newProgram(const char * filename);
void deleteProgram(program_t *);

void programStep(program_t *);
