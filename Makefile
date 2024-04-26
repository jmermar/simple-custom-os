CC := i686-elf-gcc
AS := nasm

PROJDIRS := src

SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "*.s")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")

OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) $(patsubst %.s,%.o,$(ASMFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

.PHONY: all clean


WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wconversion -Wstrict-prototypes
CFLAGS :=  -ffreestanding -O2 -Wall -Wextra $(WARNINGS)


all: myOS.iso

myOS.iso: myOS.bin
	mkdir -p isodir/boot/grub
	cp myOS.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myOS.iso isodir

myOS.bin: $(OBJFILES) src/link.ld
	$(CC) -T src/link.ld -o $@ -ffreestanding -O2 -nostdlib $(OBJFILES) -lgcc

clean:
	-@$(RM) -rf $(wildcard $(OBJFILES) myOS.bin myOS.iso isodir)

-include $(DEPFILES)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%.o: %.s Makefile
	$(AS) -f elf32 $< -o $@
