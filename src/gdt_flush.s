.section .text
.global gdt_flush
.type gdt_flush, @function

gdt_flush:
    movl 4(%esp), %eax  # Get the pointer to the GDT, passed as a parameter.
    lgdt (%eax)         # Load the new GDT pointer

    movw $0x10, %ax      # 0x10 is the offset in the GDT to our data segment
    movw %ax, %ds        # Load all data segment selectors with 0x10
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    # The CS register must be loaded using a far jump
    jmp $0x08, $.flush   # 0x08 is the offset to our code segment: Far jump!
.flush:
    ret
