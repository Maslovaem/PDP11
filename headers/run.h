#pragma once

#include "../headers/mem.h"
#include "../headers/command.h"

void run();
struct Argument get_mr(word w);
word read_cmd ();
Command parse_cmd (word w);
void get_type(word w);

