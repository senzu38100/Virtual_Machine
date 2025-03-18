/* SenzuVM.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <birchutils.h>
#pragma GCC diagnostic ignored "-Wstringop-truncation"
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wformat-truncation="
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"


#define ErrMem 0x01
#define NoArgs	 { 0x00, 0x00 }


typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

#define $1 (int8 *)
#define $2 (int16)
#define $3 (int32)
#define $4 (int64)
#define $c (char *)
#define $i (int)

typedef unsigned short int Reg;

struct s_registers {
	Reg ax;
	Reg bx;
	Reg cx;
	Reg dx;
	Reg sp;
	Reg ip;

};
typedef struct s_registers Registers;


struct s_cpu {
	Registers r;
};
typedef struct s_cpu CPU;


enum e_opcode {
	mov = 0x01,
	nop = 0x02
};
typedef enum e_opcode Opcode;

struct s_instrmap {
	Opcode o;
	int8 s;
};
typedef struct s_instrmap IM;

typedef int8 Args;

struct s_instruction { // An instruction is a command to the cpu

	Opcode o; 
	Args a[]; //variable lenght of argument 0-2 bytes

};
typedef struct s_instruction Instruction;

typedef int8 Memory[((unsigned int)(-1))]; // Memory space, sequence of 8 bit characters. -1 because we want 0xffff and it's the same as -1.
typedef int8 Program; // by definition a program is a sequence of instrutions, so it will be also an array


struct s_vm {

	CPU c;
	Memory m;
	Program *p;
};
typedef struct s_vm VM;

typedef Memory *Stack;

static Opcode opc;

static IM instrmap[] = {
	{ mov, 0x03},
	{ nop, 0x01}
};
#define IMs (sizeof(instrmap) / sizeof(struct s_instrmap))



Program *exampleprogram(VM*);
int8 map(Opcode);
VM *virtualmachine(void);
int main(int,char**);
