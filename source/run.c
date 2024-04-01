#include "../headers/run.h"
#include "../headers/mem.h"
#include "../headers/logger.h"
#include "../headers/command.h"

void run()
{
    address pc = 01000;
    word w;

    while(1)
    {
        w = w_read(pc);
        log_(TRACE, "%06o %06o: ", pc, w);
        pc += 2;

        if ( (w & 0170000) == 0060000)
        {
            log_(TRACE, "add\n");
            do_add();
        }
        else if ( (w & 0170000) == 0010000)
        {
            log_(TRACE, "mov\n");
            do_mov();
        }
        else if ( (w & 0177777) == 0000000)
        {
            log_(TRACE, "halt\n");
            do_halt();
        }
        else
        {
            log_(TRACE, "unknown\n");
            do_nothing();
        }



    }
}
