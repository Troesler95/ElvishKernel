#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>
#include <stdint.h>

extern void* memcpy(void* dest, const void* src, size_t count);
extern void* memset(void* dest, void* val, size_t count);
extern size_t strlen(const char* str);

#endif
