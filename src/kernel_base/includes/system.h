#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stddef.h>
#include <stdint.h>

/*System main*/
extern void* memcpy(void* dest, const void* src, size_t count);
extern void* memset(void* dest, void* val, size_t count);
extern size_t strlen(const char* str);
extern unsigned char inportb(unsigned short _port);
extern void outportb(unsigned short _port, unsigned char _data);

#endif
