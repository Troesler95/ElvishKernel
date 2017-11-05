#include <system.h>
#include <stddef.h>
#include <stdint.h>

/** TODO:
 *  1. If optimization is of great concern in the future, consideration should
 *     be given to the generic void* used in these functions.
 *     The use of C++ templates is more optimized for this purpose.
 *     See: attractivechaos.wordpress.com/2008/10/02/using-void-in-generic-c-programming-may-be-inefficient/
 *     See also: https://stackoverflow.com/questions/339880/disadvantages-of-using-void-pointers-in-c
 *
 *  2. move the below implementations to a separate system.c file!
 */

/*INLINE ASSEMBLY
* Inline assembly in C allows us to exeute assembly instructions using C variables
* and funcitons.
* Syntax:
* asm (assembler templates
*      : output operands [opt]
*      : input operands [opt]
*      : clobbered registers list [opt]
*     )
*
* The assembler template is just GAS-compatible. % is a special character,
* so registers need to start with two '%' (i.e. %%eax). You can make use of
* C variables in inline assembly by the use of %n where n is the # of the variable
* in the C namespace starting at 0 (i.e. %0, %1, ...)
*
* The output operands is used to tell the compiler/assembler how to handle C variables
* used to store some output from the ASM code. The ouptut ops is a list of pairs
* each consisting of a string constraint and the C variable the constraint maps to
*
* i.e. asm( "movl $0, %0" : "=a" (out) says "using EAX (without caring about the
* initial value because of the '='), take the integer literal '0', move it into
* EAX, then set the C variable to what is currently in EAX" and therefore sets
* the value of the c variable "out" to 0.
*
* The input operands allow us to parameterize the ASM code.
* i.e. asm("movl %0, %%eax" : : "b" (someInt) : %%eax ) says "take the value of
* someInt (from the C code) and move it into the EAX register using the EBX
* register and be sure that the EAX register doesn't contain anything we care
* about before we do this"
*
* The clobber list tells the assembler to make sure all of the registers we list
* do not contain information we care about
*/
// OUTPUT TO PORT functions
static inline uint8_t inb(uint16_t port)
{
  uint8_t ret = 0;
  asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

static inline uint16_t inw(uint16_t port)
{
  uint16_t ret = 0;
  asm volatile( "inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
