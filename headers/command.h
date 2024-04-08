#pragma once

#include "../headers/mem.h"

void do_halt();
void do_add();
void do_mov();
void do_nothing();

typedef struct {
    word mask;
    word opcode;
    const char * name;
    void (* do_command)(void);
} Command;

extern Command command[];
