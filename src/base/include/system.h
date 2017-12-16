#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stddef.h>
#include <stdint.h>

#define GDTBASE	0x00000800
#define GDTSIZE 3

/*System main*/
extern unsigned char inportb(unsigned short _port);
extern void outportb(unsigned short _port, unsigned char _data);

void gdt_set_gate(int num, unsigned long base, unsigned long limit,
  unsigned char access, unsigned char gran);
void gdt_install();
extern void gdt_flush();

#endif
