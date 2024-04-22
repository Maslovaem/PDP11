#pragma once

#include "../headers/mem.h"

enum args {NO_PARAMS, HAS_SS, HAS_DD, HAS_NN = 4, HAS_R = 8};

void do_halt();
void do_add();
void do_mov();
void do_nothing();
void do_sob();

typedef struct {
    word mask;
    word opcode;
    const char * name;
    void (* do_command)(void);
    char params;
} Command;

extern Command command[];
