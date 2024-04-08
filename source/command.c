#include <stdlib.h>

#include "../headers/command.h"
#include "../headers/logger.h"
#include "../headers/mem.h"

void do_halt()
{
    log_(INFO, "THE END!!!\n");
    reg_dump();
    exit(0);
}

void do_add()
{

}

void do_mov()
{

}

void do_nothing()
{

}
