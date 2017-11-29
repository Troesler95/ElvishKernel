#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stddef.h>
#include <stdint.h>

/*System main*/
extern unsigned char inportb(unsigned short _port);
extern void outportb(unsigned short _port, unsigned char _data);

#endif
