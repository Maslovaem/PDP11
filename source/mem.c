#include "../headers/mem.h"
#include "../headers/logger.h"
#include <stdio.h>
#include <stdlib.h>

#define PDP11_MEMSIZE (64*1024)

static byte mem[PDP11_MEMSIZE];
word reg[8];

struct Argument ss;
struct Argument dd;
struct Argument nn;
struct Argument r;

unsigned int is_byte_cmd = 0;

unsigned char psw = 0;

void b_write(address adr, byte value)
{
    if (adr < 8)
    {
        if( (value >> 7) == 1)
        {
            reg[adr] = (value | 0xFF00);
        }
        else
        {
            reg[adr] = value;
        }
    }
    else
    {
        mem[adr] = value;
    }
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
    if (adr < 8) {
        // считаем первые 8 адресов номерами регистров
        reg[adr] = val & 0xFFFF;
    }
    else {
        mem[adr] = val;
        mem[adr + 1] = val >> 8;
    }
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

void reg_clear()
{
    for (int i = 0; i < 8; i++)
    {
        reg[i] = 0;
    }
}

