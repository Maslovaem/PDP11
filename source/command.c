#include <stdlib.h>

#include "../headers/command.h"
#include "../headers/logger.h"
#include "../headers/mem.h"

Command command[] = {
    {0170000, 0060000, "add", do_add},
    {0170000, 0010000, "mov", do_mov},
    {0177777, 0000000, "halt", do_halt}
};


void do_halt()
{
    log_(INFO, "THE END!!!\n");
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
