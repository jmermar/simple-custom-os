ENTRY(loader)
SECTIONS {
	. = 0x00100000;
	
	.text ALIGN(4K):
	{
		*(.text)
	}

	/* Read-only data. */
	.rodata ALIGN(4K):
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data ALIGN(4K):
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss ALIGN(4K):
	{
		*(COMMON)
		*(.bss)
	}
}
