/* Entry Point */
ENTRY(Reset_Handler)

/* Available Memory */
MEMORY
{
	FLASH(rx):ORIGIN =0x08000000,LENGTH =512K
	SRAM(rwx):ORIGIN =0x20000000,LENGTH =128K
}

/*
 * Setting the stack pointer to the end of SRAM
 * Ensures that it starts at the maximum available address
 */
_estack = ORIGIN(SRAM)+LENGTH(SRAM);
 
/*
 * Specifying the necessary heap and stack sizes
 */
_Min_Stack_Size = 0x400; /* 1024 bytes */
_Min_Heap_Size = 0x200;  /* 512 bytes */

/* Defining Output Sections */
SECTIONS
{ 	
	.text :
	{
		. = ALIGN(4);
		
		/* Merge all .isr_vector_tbl sections of input files */
		*(.isr_vector_tbl)

		/* Merge all .text and .text.* sections of input files */
		*(.text)
		*(.text.*)
		
		/* Merge all .rodata and .rodata.* sections of input files */
		*(.rodata)				
		*(.rodata.*)

		. = ALIGN(4);
		
		/* Create a global symbol to hold end of text section */
		_etext = .;
	
	} > FLASH

	/* Flash address (LMA) of .data init values */
	_sidata = LOADADDR(.data);		
	
	.data :
	{
		. = ALIGN(4);
		
		/* Create a global symbol to hold start of data section */
		_sdata = .;				
		
		/* Merge all .data and .data.* sections of input files */
		*(.data)				
		*(.data.*)

		. = ALIGN(4);
		
		/* Create a global symbol to hold end of data section */
		_edata = .;

	} > SRAM AT> FLASH /* >(VMA) AT> (LMA) */
		
	.bss :
	{
		. = ALIGN(4);
		
		/* Create a global symbol to hold start of bss section */
		_sbss = .;		
		__bss_start__ = _sbss;
		
		/* Merge all .bss and .bss.* sections of input files */
		*(.bss)			
		*(.bss.*)

		. = ALIGN(4);
	
		/* Create a global symbol to hold end of bss section */
		_ebss = .;
		__bss_end__ = _ebss;
	
	} > SRAM

	_end = .;
}
