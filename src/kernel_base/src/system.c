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

/** memcpy()
 * Note: The following description was adapted from the memcpy Linux man page
 *
 * Copies count bytes from memory area src into memory area dest
 * The memory areas must not overlap.
 *
 * This function should behave exactly as the c standard library funciton!
 */
void* memcpy(void* dest, const void* src, size_t count)
{
  size_t i;
  /*
   * For optimizations sake, we need to see if we can
   * perform copying on a word-aligned basis or if we are
   * forced to copy byte-by-byte. Word-by-word copying is
   * (obviously) much faster than byte copying.
   *
   * This should be cross platform since we are checking against
   * the size that the compiler thinks that a word is, rather
   * than what we might think it is
   */
  if ((uintptr_t)dest % sizeof(long) == 0 &&
      (uintptr_t)src % sizeof(long) == 0 &&
      count % sizeof(long) == 0)
      {
        long* ld = dest;        // reinterpret as word-aligned pointer
        const long* ls = src;  // reinterpret as word-aligned pointer

        /*Copy the memory from src to dest*/
        for (i = 0; i < count / sizeof(long); ++i)
        {
          ld[i] = ls[i];
        }
      }
      /*If not word-aligned, we are forced to copy byte-by-byte*/
      else
      {
        char *d = dest;       // reinterpret as byte pointer
        const char *s = src; // reinterpret as byte pointer

        /*Copy the memory from src to dest*/
        for (i = 0; i < count; ++i)
        {
          d[i] = s[i];
        }
      }
      /*Return the copy of src*/
      return dest;
}

/** memset()
 *
 */
void* memset(void* dest, void* val, size_t count)
{
  /*treat destination as byte array*/
  unsigned char* p=dest;
  /*for the size of dest, set every byte to the value*/
  while(count--)
    *p++ = (unsigned char)val;
  /*return intialized value*/
  return dest;
}

/** strlen()
 * THIS IS THE GLIBC IMPLEMENTATION OF STRLEN
 * IN NO WAY DO WE OWN THIS INTELLECTUAL PROPERTY AND IT IS PROTECTED UNDER
 * THE GPU LESSER GENERAL PUBLIC LICENSE v2.1.
 *
 * Remarks: I understand it is obnoxious to have 80 lines of code for strlen,
 * but this code is on average four times as fast as checking every character!
 * how does one pass that up? see: http://www.stdlib.net/~colmmacc/2009/03/01/optimising-strlen/
 *
 * TODO: If development of string functions continues, we should consider moving
 *       moving them to their own files! (string.h and string.c)
 */
size_t strlen(const char* str)
{
  const char *char_ptr;
  const unsigned long int *longword_ptr;
  unsigned long int longword, himagic, lomagic;

  /* Handle the first few characters by reading one character at a time.
     Do this until CHAR_PTR is aligned on a longword boundary.  */
  for (char_ptr = str;
      ((unsigned long int) char_ptr & (sizeof (longword) - 1)) != 0;
      ++char_ptr)
  {
          if (*char_ptr == '\0')
            return char_ptr - str;
  }

  /* All these elucidatory comments refer to 4-byte longwords,
     but the theory applies equally well to 8-byte longwords.  */

  longword_ptr = (unsigned long int *) char_ptr;

  /* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
     the "holes."  Note that there is a hole just to the left of
     each byte, with an extra at the end:

     bits:  01111110 11111110 11111110 11111111
     bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD

     The 1-bits make sure that carries propagate to the next 0-bit.
     The 0-bits provide holes for carries to fall into.  */
  himagic = 0x80808080L;
  lomagic = 0x01010101L;
  if (sizeof (longword) > 4)
  {
    /* 64-bit version of the magic.  */
    /* Do the shift in two steps to avoid a warning if long has 32 bits.  */
    himagic = ((himagic << 16) << 16) | himagic;
    lomagic = ((lomagic << 16) << 16) | lomagic;
  }
  if (sizeof (longword) > 8)
    return -1;

  /* Instead of the traditional loop which tests each character,
     we will test a longword at a time.  The tricky part is testing
     if *any of the four* bytes in the longword in question are zero.  */
  for (;;)
  {
    longword = *longword_ptr++;

    if (((longword - lomagic) & ~longword & himagic) != 0)
    {
      /* Which of the bytes was the zero?  If none of them were, it was
        a misfire; continue the search.  */

      const char *cp = (const char *) (longword_ptr - 1);

      if (cp[0] == 0)
        return cp - str;
      if (cp[1] == 0)
        return cp - str + 1;
      if (cp[2] == 0)
        return cp - str + 2;
      if (cp[3] == 0)
        return cp - str + 3;

      if (sizeof (longword) > 4)
      {
        if (cp[4] == 0)
          return cp - str + 4;
        if (cp[5] == 0)
          return cp - str + 5;
        if (cp[6] == 0)
          return cp - str + 6;
        if (cp[7] == 0)
          return cp - str + 7;
      }
    }
  }
}

/*NEEDS EDITING BELOW THIS POINT*/
/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
