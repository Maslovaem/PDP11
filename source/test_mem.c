#include <assert.h>
#include <string.h>

#include "../headers/test_mem.h"
#include "../headers/mem.h"
#include "../headers/logger.h"
#include "../headers/command.h"
#include "../headers/run.h"


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
    a = 8;
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

    //проверка распознавания mov
    test_parse_mov();

    //проверка разбора аргументов для моды 0
    test_mode0();

    //проверка работы mov
    test_mov();

}

void test_parse_mov()
{
    log_(TRACE, __FUNCTION__);
    Command cmd = parse_cmd(0012700);
    assert(strcmp(cmd.name, "mov") == 0);
    log_(TRACE, " ... OK\n");
}

void test_mode0()
{
    log_(TRACE, __FUNCTION__);
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503);
    assert(ss.value == 34);
    assert(ss.adr == 5);
    assert(dd.value == 12);
    assert(dd.adr == 3);
    log_(TRACE, " ... OK\n");
}

void test_mov()
{
    log_(TRACE, __FUNCTION__);
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503);
    cmd.do_command();
    assert(reg[3] = 34);
    assert(reg[5] = 34);
    log_(TRACE, " ... OK\n");
}
