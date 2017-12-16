#ifndef __SYS_SCREEN_H
#define __SYS_SCREEN_H

#include <stddef.h>
#include <string.h>

enum vga_color;

extern void cls();
extern void putch(char c);
extern void puts(char *str);
extern void settextcolor(enum vga_color forecolor, enum vga_color backcolor);
extern void init_video();

#endif
