
global gdt_load_and_set

section .text

SEGSEL_KERNEL_CS equ 0x08
SEGSEL_KERNEL_DS equ 0x10

gdt_load_and_set:
    mov eax, [esp + 4]
    lgdt [eax]

    ; Load the new segments
jmp     SEGSEL_KERNEL_CS:.reload_segments

.reload_segments:
    ; we only use one segment for data
    mov     ax, SEGSEL_KERNEL_DS
    mov     ds, ax
    mov     ss, ax
    mov     es, ax
    mov     gs, ax
    mov     fs, ax
    ret