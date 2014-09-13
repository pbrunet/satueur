.macro irq num
.global irq\num
.type irq\num, @function
irq\num:
    push $0
    push $\num
    jmp irq_common_stub
.endm

.macro isr_noerrorcode num
.global isr\num
.type isr\num, @function
isr\num:
    push $0
    push $\num
    jmp isr_common_stub
.endm

.macro isr_errorcode num
.global isr\num
.type isr\num, @function
isr\num:
    push $\num
    jmp isr_common_stub
.endm


.section .text
.extern isr_handler
.extern irq_handler
isr_noerrorcode 0
isr_noerrorcode 1
isr_noerrorcode 2
isr_noerrorcode 3
isr_noerrorcode 4
isr_noerrorcode 5
isr_noerrorcode 6
isr_noerrorcode 7
isr_errorcode 8
isr_noerrorcode 9
isr_errorcode 10
isr_errorcode 11
isr_errorcode 12
isr_errorcode 13
isr_errorcode 14
isr_noerrorcode 15
isr_noerrorcode 16
isr_noerrorcode 17
isr_noerrorcode 18
isr_noerrorcode 19
isr_noerrorcode 20
isr_noerrorcode 21
isr_noerrorcode 22
isr_noerrorcode 23
isr_noerrorcode 24
isr_noerrorcode 25
isr_noerrorcode 26
isr_noerrorcode 27
isr_noerrorcode 28
isr_noerrorcode 29
isr_noerrorcode 30
isr_noerrorcode 31
irq 32
irq 33
irq 34
irq 35
irq 36
irq 37
irq 38
irq 39
irq 40
irq 41
irq 42
irq 43
irq 44
irq 45
irq 46
irq 47

.global isr_common_stub
.type isr_common_stub, @function
isr_common_stub:
    # This is our common ISR stub. It saves the processor state, sets
    # up for kernel mode segments, calls the C-level fault handler,
    # and finally restores the stack frame.
    pusha            # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    pushw %ds        # Push all segments
    pushw %es
    pushw %fs
    pushw %gs

    movw $0x10, %ax  # load the kernel data segment descriptor
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    pushl %esp

    call isr_handler

    addl $4, %esp    # Cleans up the register_t pointer pushed as parameter

    popw %gs         # Restore segments values
    popw %fs
    popw %es
    popw %ds

    popa              # Pops edi,esi,ebp...
    addl $8, %esp     # Cleans up the pushed error code and pushed ISR number
    iret              # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

.global irq_common_stub
.type irq_common_stub, @function
irq_common_stub:
    # This is our common IRQ stub. It saves the processor state, sets
    # up for kernel mode segments, calls the C-level fault handler,
    # and finally restores the stack frame.
    pusha            # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    pushw %ds        # Push all segments
    pushw %es
    pushw %fs
    pushw %gs

    movw $0x10, %ax  # load the kernel data segment descriptor
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    pushl %esp

    call irq_handler

    addl $4, %esp    # Cleans up the register_t pointer pushed as parameter

    popw %gs         # Restore segments values
    popw %fs
    popw %es
    popw %ds

    popa              # Pops edi,esi,ebp...
    addl $8, %esp     # Cleans up the pushed error code and pushed ISR number
    iret              # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
