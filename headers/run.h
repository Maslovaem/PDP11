#pragma once

#include "../headers/mem.h"
#include "../headers/command.h"

#define cmd_amount 5

void run();
struct Argument get_mr(word w);
word read_cmd ();
Command parse_cmd (word w);
void get_type(word w);

