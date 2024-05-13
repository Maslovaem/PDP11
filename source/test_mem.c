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
    a = 16;
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
    a = 24;
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

    //проверка моды 1
    test_mode1_toreg();

    //проверка моды 2
    test_mode2();

    //проверка разбора аргументов для sob
    test_parse_sob();

    test_sob();

    test_mode3();

    //байтовый или нет тип команды
    test_get_type();

    test_set_NZ();

    test_set_C();

    reg_clear();//в конце тестов
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

void test_mode1_toreg()
{
    log_(TRACE, __FUNCTION__);

    reg[3] = 12;    // dd
    reg[5] = 0200;  // ss
    w_write(0200, 34);


    Command cmd = parse_cmd(0011503);


    assert(ss.value == 34);
    assert(ss.adr == 0200);
    assert(dd.value == 12);
    assert(dd.adr == 3);


    cmd.do_command();


    assert(reg[3] = 34);
    assert(reg[5] = 0200); //the number of the reg did not change


    log_(TRACE, " ... OK\n");
}

void test_mode2()
{
    log_(TRACE, __FUNCTION__);

    reg[3] = 12;    // dd
    reg[5] = 0200;  // ss
    w_write(0200, 34);


    Command cmd = parse_cmd(0012503);


    assert(ss.value == 34);
    assert(ss.adr == 0200);
    assert(dd.value == 12);
    assert(dd.adr == 3);
    assert(reg[5] == 0202);


    cmd.do_command();


    assert(reg[3] = 34);
    assert(reg[5] = 0202); //the number of the reg did not change


    log_(TRACE, " ... OK\n");
}

void test_parse_sob()
{
    log_(TRACE, __FUNCTION__);

    Command cmd = parse_cmd(0077105);

    assert(r.adr == 1);
    assert(nn.value == 5);

    log_(TRACE, " ... OK\n");
}

void test_sob()
{
    log_(TRACE, __FUNCTION__);
    reg[3] = 1;    // r
    pc = 01200;    //
    Command cmd = parse_cmd(0077306);
    cmd.do_command();
    assert(reg[3] == 0);
    assert(pc == 01200);

    reg[3] = 4;    // r
    pc = 01006;    //
    cmd = parse_cmd(0077303);
    cmd.do_command();
    assert(reg[3] == 3);
    assert(pc == 01000);

    log_(TRACE, " ... OK\n");

}

void test_mode3()
{
    log_(TRACE, __FUNCTION__);

    reg[3] = 12;    // dd
    reg[5] = 0200;  // ss
    w_write(0200, 0204);
    w_write(0204, 34);

    Command cmd = parse_cmd(0013503);

    assert(ss.value == 34);
    assert(ss.adr == 0204);
    assert(dd.value == 12);
    assert(dd.adr == 3);
    assert(reg[5] == 0202);

    cmd.do_command();

    assert(reg[3] = 34);
    assert(reg[5] = 0202); //the number of the reg did not change

    log_(TRACE, " ... OK\n");
}

void test_get_type()
{
    get_type(0112203);
    log_(TRACE, __FUNCTION__);

    assert(is_byte_cmd);

    get_type(0012203);
    assert(!is_byte_cmd);

    log_(TRACE, " ... OK\n");
}

void test_set_NZ()
{
    log_(TRACE, __FUNCTION__);

    set_NZ(5);
    assert( !(psw >> 3) );
    assert( !( (psw >> 1) & 1) );

    set_NZ(0);
    assert( !(psw >> 3) );
    assert( (psw >> 1) & 1 );

    set_NZ(-5);
    assert(psw >> 3);
    assert( !( (psw >> 1) & 1) );

    log_(TRACE, " ... OK\n");
}

void test_set_C()
{
    log_(TRACE, __FUNCTION__);

    set_C(0xFFFF + 0xFFFF);
    assert(psw & 1);

    set_C(0x1 + 0x1);
    assert( !(psw & 1) );

    log_(TRACE, " ... OK\n");
}
