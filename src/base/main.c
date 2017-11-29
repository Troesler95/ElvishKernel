#include <screen.h>
#include <system.h>
#include <string.h>

/* This is a very simple main() function. All it does is sit in an
*  infinite loop. This will be like our 'idle' loop */
void kernel_main()
{
    /* You would add commands after here */
    init_video();
    puts("Hello world!\n");
}
