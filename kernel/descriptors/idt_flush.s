.section .text
.global idt_flush
.type idt_flush, @function

idt_flush:
    movl 4(%esp), %eax  # Get the pointer to the GDT, passed as a parameter.
    lidt (%eax)        # Load the new GDT pointer
    ret
