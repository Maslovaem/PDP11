#pragma once

typedef unsigned char byte;
typedef unsigned int word;
typedef word address;

struct Argument {
    word value;
    address adr;
};

extern struct Argument ss;
extern struct Argument dd;

byte b_read(address adr);
void b_write(address adr, byte value);
word w_read(address adr);
void w_write(address adr, word value);

void mem_dump(address adr, int size);

void reg_dump();

struct Argument get_mr(word w);
