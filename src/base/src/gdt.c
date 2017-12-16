#include <system.h>
#include <string.h>
#include <screen.h>
#include <stddef.h>
#include <stdint.h>

struct gdt_entry {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute__((packed)); // packed prevents compiler optimizations

struct gdt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern void gdt_flush();

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, unsigned long base, unsigned long limit,
  unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

/* Should be called by main. This will setup the special GDT
*  pointer, set up the first 3 entries in our GDT, and then
*  finally call gdt_flush() in our assembler file in order
*  to tell the processor where the new GDT is and update the
*  new segment registers */
void gdt_install()
{
  /* Setup the GDT pointer and limit */
  gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
  gp.base = GDTBASE;

  /* Our NULL descriptor */
  gdt_set_gate(0, 0, 0, 0, 0);

  /* The second entry is our Code Segment. The base address
  *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
  *  uses 32-bit opcodes, and is a Code Segment descriptor.
  *  Please check the table above in the tutorial in order
  *  to see exactly what each value means */
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

  /* The third entry is our Data Segment. It's EXACTLY the
  *  same as our code segment, but the descriptor type in
  *  this entry's access byte says it's a Data Segment */
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  /* Flush out the old GDT and install the new changes! */
  memcpy((char *) gp.base, (char *) gdt, gp.limit);

  /* load the gdtr registry */
  asm("lgdtl (gdt)" /*: : "b"(gdt) :*/ );

  /* initiliaz the segments */
	/*asm("movw $0x10, %ax	\n \
        movw %ax, %ds	\n \
        movw %ax, %es	\n \
        movw %ax, %fs	\n \
        movw %ax, %gs	\n \
        jmp $0x08, $next	\n \
        next:		syscall\n");*/
}
