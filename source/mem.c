#include "../headers/mem.h"
#include "../headers/logger.h"
#include <stdio.h>
#include <stdlib.h>

#define PDP11_MEMSIZE (64*1024)

static byte mem[PDP11_MEMSIZE];
word reg[8];

struct Argument ss;
struct Argument dd;

void b_write(address adr, byte value)
{
    mem[adr] = value;
}

byte b_read(address adr)
{
    return mem[adr];
}

word w_read (address adr)
{
    byte b0 = mem[adr];
    byte b1 = mem[adr + 1];

    word w = b1;
    w = w << 8;
    w = w |(b0 & 0xFF);
    return w;
}

void w_write (address adr, word val)
{
    mem[adr] = val;
    mem[adr + 1] = val >> 8;
}

void mem_dump(address adr, int size)
{

    for (address i = adr; i < adr + size; i += 2)
    {
        log_(INFO, "%06o: %06o %04x\n", i, w_read(i), w_read(i));
    }
}

void reg_dump()
{
    for (int i = 0; i < 8; i++)
    {
        printf("r%d:%o ", i, reg[i]);
    }
}

struct Argument get_mr(word w)
{
    Argument res;

    int r = w & 7;
    int m = (w >> 3) & 7;

    switch (m)
    {
        case 0:
            res.adr = r;
            res.value = reg[r];
            log_(TRACE, "R%d ", r);
            break;


        case 1:
            res.adr = reg[r];
            res.value = w_read(res.adr);
            log_(TRACE, "(R%d) ", r);
            break;

        case 2:
            res.adr = reg[r];
            res.value = w_read(res.adr);
            reg[r] += 2;
            if (r == 7)
                log_(TRACE, "#%o ", res.value);
            else
                log_(TRACE, "(R%d)+ ", r);
            break;

        default:
            log_(ERROR, "Mode %d not implemented yet!\n", m);
            exit(1);
    }

    return res;
}

