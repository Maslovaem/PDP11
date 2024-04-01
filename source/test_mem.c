#include <assert.h>

#include "../headers/test_mem.h"
#include "../headers/mem.h"
#include "../headers/logger.h"

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
