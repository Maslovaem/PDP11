#pragma once

typedef unsigned char byte;
typedef unsigned int word;
typedef word address;

extern word reg[8];

#define pc reg[7]

struct Argument {
    word value;
    address adr;
};


extern struct Argument ss;
extern struct Argument dd;
extern struct Argument nn;
extern struct Argument r;

extern unsigned int is_byte_cmd;

extern unsigned char psw;

byte b_read(address adr);
void b_write(address adr, byte value);
word w_read(address adr);
void w_write(address adr, word value);

void mem_dump(address adr, int size);

void reg_dump();
void reg_clear();

struct Argument get_mr(word w);
