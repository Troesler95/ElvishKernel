#include <screen.h>
#include <stddef.h>
#include <stdint.h>
#include <system.h>


/*TODO: implement kernel textmode from tutorial_kernel.c here as well! */
/* This is a very simple main() function. All it does is sit in an
*  infinite loop. This will be like our 'idle' loop */
void kernel_main()
{
    /* You would add commands after here */
    init_video();
    puts("Hello world!\n");
}
