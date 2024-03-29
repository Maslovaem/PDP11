#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#define prn fprintf(stderr, "str: %d, function: %s\n", __LINE__, __FUNCTION__)

typedef unsigned char byte;
typedef unsigned int word;
typedef word address;

word reg[8];

#define PDP11_MEMSIZE (64*1024)

byte mem[PDP11_MEMSIZE];

byte b_read(address adr);
void b_write(address adr, byte value);
word w_read(address adr);
void w_write(address adr, word value);

void mem_dump(address adr, int size);

enum level {DEBUG, TRACE, INFO, ERROR};
enum level CURRENT_LEVEL = DEBUG;
enum level set_log_level(enum level l);
void log_(enum level l, const char* format, ...);

void do_halt();
void do_add();
void do_mov();
void do_nothing();
void run();

void test_mem()
{
    address a;
    byte b0, b1, bres;
    word w, wres;


    // пишем байт, читаем байт
    log_(TRACE, "Read and write byte\n");
    a = 0;
    b0 = 0x12;
    b_write(a, b0);
    bres = b_read(a);
    log_(TRACE, "a=%06o b0=%hhx bres=%hhx\n", a, b0, bres);
    assert(b0 == bres);


    // пишем слово, читаем слово
    log_(TRACE, "Write and read word\n");
    a = 2;
    w = 0x3456;
    w_write(a, w);
    wres = w_read(a);
    log_(TRACE, "a=%06o w=%04x wres=%04x\n", a, w, wres);
    assert(w == wres);


    // пишем 2 байта, читаем 1 слово
    log_(TRACE, "Write 2 bytes, read word\n");
    a = 4;
    w = 0xa1b2;
    b0 = 0xb2;
    b1 = 0xa1;
    b_write(a, b0);
    b_write(a+1, b1);
    wres = w_read(a);
    log_(TRACE, "a=%06o b1=%02hhx b0=%02hhx wres=%04x\n", a, b1, b0, wres);
    assert(w == wres);

}

void load_data(FILE *stream)
{
    unsigned int a = 0;
    unsigned int n = 0;
    unsigned int temp = 0;
    while (2 == fscanf(stream, "%x%x", &a, &n))
    {
        for (int i = 0; i < n; i++)
        {
            fscanf(stream, "%x", &temp);
            b_write(a + i, (byte)temp);
        }
    }
}

void load_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror(filename);
        exit(1);
    }
    load_data(file);
    fclose(file);
}
void usage(const char *prog)
{
    log_(ERROR, "USAGE: %s file\n file - PDP11 execution fault", prog);
}
int main(int argc, char *argv[])
{
    CURRENT_LEVEL = DEBUG;
    test_mem();
    if (argc - 1 == 0)
    {
        usage(argv[0]);
        exit(0);
    }
    load_file(argv[1]);

    run();

    return 0;
}

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

enum level set_log_level(enum level l)
{
    enum level previous = CURRENT_LEVEL;
    CURRENT_LEVEL = l;
    return previous;
}

void log_(enum level l, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);

    if (l >= CURRENT_LEVEL)
    {
        vprintf(format, ap);
    }

    va_end(ap);

}

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

void do_halt()
{
    log_(INFO, "THE END!!!\n");
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
