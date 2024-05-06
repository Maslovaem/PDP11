#include <stdlib.h>

#include "../headers/command.h"
#include "../headers/logger.h"
#include "../headers/mem.h"

Command command[] = {
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
    {0077000, 0077000, "sob", do_sob, HAS_NN | HAS_R},
    {0000000, 0000000, "unknown", do_nothing, NO_PARAMS} //has to be the last command
};


void do_halt()
{
    log_(INFO, "\nTHE END!!!\n");
    reg_dump();
    exit(0);
}

void do_add()
{
    w_write(dd.adr, ss.value + dd.value);
}

void do_mov()
{
    w_write(dd.adr, ss.value);
}

void do_nothing()
{

}

void do_sob()
{
    if (--reg[r.adr] != 0)
    {
        pc = pc - 2*nn.value;
    }
}
