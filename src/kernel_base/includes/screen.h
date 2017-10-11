#ifndef __SYS_SCREEN_H
#define __SYS_SCREEN_H

enum vga_color;

extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void settextcolor(enum vga_color forecolor, enum vga_color backcolor);
extern void init_video();

#endif
