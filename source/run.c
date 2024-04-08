#include <stdio.h>

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

        for (int i = 0; i < 3; i++)
        {
            if ( (w & command[i].mask) == command[i].opcode)
            {
                printf("%s\n", command[i].name);
                command[i].do_command();
            }
        }
    }
}
