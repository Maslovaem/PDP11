#pragma once

#include "../headers/mem.h"

enum args {NO_PARAMS = 0, HAS_SS = 1, HAS_DD = 2, HAS_NN = 4, HAS_R = 8};

void do_halt();
void do_add();
void do_mov();
void do_nothing();
void do_sob();
void do_movb();
void clr();

typedef struct {
    word mask;
    word opcode;
    const char * name;
    void (* do_command)(void);
    char params;
} Command;

extern Command command[];
