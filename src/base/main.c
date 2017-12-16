#include <screen.h>
#include <system.h>
#include <string.h>

/* This is a very simple main() function. All it does is sit in an
*  infinite loop. This will be like our 'idle' loop */
void kernel_main()
{
    // install our custom global descriptor table
    gdt_install();
    // initialize terminal to black background w/ white text
    init_video();
    puts("Hello world!\n");
}
