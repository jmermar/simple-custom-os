global loader; 
extern main;
MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER; define the magic number constant
; multiboot flags
; calculate the checksum
; (magic number + checksum + flags should equal 0)

KERNEL_STACK_SIZE equ 4096; size of stack in bytes

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE;


section .text:

align 4
	dd MAGIC_NUMBER
	dd FLAGS; start of the text (code) section
	dd CHECKSUM;
loader:
	cli
	mov esp, kernel_stack + KERNEL_STACK_SIZE
	call main
.loop:
	jmp .loop
; the code must be 4 byte aligned
; write the magi
