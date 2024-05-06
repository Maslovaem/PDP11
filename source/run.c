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

        Command cmd = parse_cmd(w);

        cmd.do_command();
        log_(TRACE, "\n");
        reg_dump();
        log_(TRACE, "\n");

    }
}

word read_cmd ()
{
    word w = w_read(pc);

    log_(TRACE, "%06o %06o: ", pc, w);

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

            res.adr = current_reg;
            res.value = reg[current_reg];

            log_(TRACE, "R%d ", current_reg);

            break;

        case 1:
            res.adr = reg[current_reg];
            res.value = w_read(res.adr);

            log_(TRACE, "(R%d) ", current_reg);

            break;

        case 2:
            //log_(TRACE, "%06o #R%d", w_read(pc), current_reg);

            res.adr = reg[current_reg];
            res.value = w_read(res.adr);

            get_type(w);

            if (!is_byte_cmd || current_reg >= 6)
            {
                reg[current_reg] += 2;
            }
            else
            {
                reg[current_reg] += 1;
            }

            if (current_reg == 7)
                log_(TRACE, "#%o ", res.value);
            else
                log_(TRACE, "(R%d)+ ", current_reg);

            break;

        case 3:

            res.adr = w_read(reg[current_reg]);
            res.value = w_read(res.adr);
            reg[current_reg] += 2;

            if (current_reg == 7)
                log_(TRACE, "#%o ", res.value);
            else
                log_(TRACE, "(R%d)+ ", current_reg);

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

    for (int i = 0; i < cmd_amount; i++)
        {
            if ( (w & command[i].mask) == command[i].opcode)
            {
                res = command[i];
                log_(TRACE, "%s ", res.name);

                break;
            }
        }

    if ( (res.params) & HAS_SS)
    {
        ss = get_mr(w >> 6);
    }
    if ( (res.params) & HAS_DD)
    {
        dd = get_mr(w);
    }
    if ( (res.params) & HAS_NN)
    {
        nn.value = w & 0000077;
        log_(TRACE, " NN = %d ", nn.value);
    }
    if ( (res.params) & HAS_R)
    {
        r.adr = (w >> 6) & 0000007;
        log_(TRACE, " R%d ", r.adr);
    }

    return res;
}

void get_type(word w)
{
    if ( (w >> 15) & 7)
    {
        is_byte_cmd = 1;
    }
    else
    {
        is_byte_cmd = 0;
    }
}
