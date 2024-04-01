#include "../headers/mem.h"
#include "../headers/logger.h"

#define PDP11_MEMSIZE (64*1024)

static byte mem[PDP11_MEMSIZE];
word reg[8];

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
