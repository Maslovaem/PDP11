#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef unsigned char byte;
typedef unsigned int word;
typedef word address;

#define PDP11_MEMSIZE (64*1024)

byte mem[PDP11_MEMSIZE];

byte b_read(address adr);
void b_write(address adr, byte value);
word w_read(address adr);
void w_write(address adr, word value);

void test_mem()
{
    address a;
    byte b0, b1, bres;
    word w, wres;


    // пишем байт, читаем байт
    fprintf(stderr, "Read and write byte\n");
    a = 0;
    b0 = 0x12;
    b_write(a, b0);
    bres = b_read(a);
    fprintf(stderr, "a=%06o b0=%hhx bres=%hhx\n", a, b0, bres);
    assert(b0 == bres);


    // пишем слово, читаем слово
    fprintf(stderr, "Write and read word\n");
    a = 2;
    w = 0x3456;
    w_write(a, w);
    wres = w_read(a);
    fprintf(stderr, "a=%06o w=%04x wres=%04x\n", a, w, wres);
    assert(w == wres);


    // пишем 2 байта, читаем 1 слово
    fprintf(stderr, "Write 2 bytes, read word\n");
    a = 4;
    w = 0xa1b2;
    b0 = 0xb2;
    b1 = 0xa1;
    b_write(a, b0);
    b_write(a+1, b1);
    wres = w_read(a);
    fprintf(stderr, "a=%06o b1=%02hhx b0=%02hhx wres=%04x\n", a, b1, b0, wres);
    assert(w == wres);

}

void load_data(FILE *stream)
{
    address a;
    int n;
    while (2==fscanf(stream, "%x%x", &a, &n))
    {
        /*for ()
        {
        }*/
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
    printf("USAGE: %s file\n file - PDP11 execution fault", prog);
}
int main(int argc, char *argv[])
{
    test_mem();
    return 0;
    if (argc - 1 == 0)
    {
        usage(argv[0]);
        exit(0);
    }
    load_data(stdin);
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
