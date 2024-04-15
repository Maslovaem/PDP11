#include <stdio.h>
#include <stdlib.h>

#include "../headers/run.h"
#include "../headers/mem.h"
#include "../headers/logger.h"
#include "../headers/command.h"

void run()
{
    pc = 01000;
    word w;

    while(1)
    {
        w = w_read(pc);
        log_(TRACE, "%06o %06o: ", pc, w);
        pc += 2;

        for (int i = 0; i < 4; i++)
        {
            if ( (w & command[i].mask) == command[i].opcode)
            {
                printf("%s\n", command[i].name);
                command[i].do_command();

                break;
            }
        }
    }
}

word read_cmd ()
{
    word w = w_read(pc);
    pc += 2;

    return w;
}

Argument get_mr(word w)
{
    Argument res;

    unsigned int current_reg = w & 7;
    unsigned int mode = (w >> 3) & 7;

    switch (mode)
    {

        case 0:
            ss.adr = current_reg;
            ss.value = reg[current_reg];

            break;

        case 1:
            ss.adr = reg[current_reg];
            ss.value = w_read(ss.adr);

            break;

        case 2:
            ss.adr = reg[current_reg];
            ss.value = w_read(ss.adr);
            pc += 2;

            break;

        default:
            log_(ERROR, "Mode %d not implemented yet!\n", mode);
            exit(1);

    }



    return res;
}

Command parse_cmd (word w)
{
    Command res;

    for (int i = 0; i < 4; i++)
        {
            if ( (w & command[i].mask) == command[i].opcode)
            {
                res = command[i];

                break;
            }
        }



    return res;
}
