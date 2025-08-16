/*Entry Point*/
ENTRY(Reset_Handler)

/* Available Memory*/
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
 
/*Specifying the necessary heap and stack sizes*/
_Min_Stack_Size = 0x400; /* 1024 bytes */
_Min_Heap_Size = 0x200;  /* 512 bytes */

/* Defining Output Sections */
SECTIONS
{
	.text :
	{
		. = ALIGN(4);
		*(.isr_vector_tbl)	/* Merge all .isr_vector_tbl sections of input files */
		*(.text)		/* Merge all .text sections of input files */
		*(.rodata)      	/* Merge all .rodata sections of input files */
		
		. = ALIGN(4);
		_etext = .; 		/* Create a global symbol to hold end of text section */
	} > FLASH
	
	_sidata = LOADADDR(.data);	/* Flash address (LMA) of .data init values */	
	
	.data :
	{
		. = ALIGN(4);
		_sdata = .; 		/*Create a global symbol to hold start of data section*/
		
		*(.data) 		/* Merge all .data sections of input files */
	
		. = ALIGN(4);
		_edata = .;   		/*Create a global symbol to hold end of data section*/
	} > SRAM AT> FLASH  		/*>(VMA) AT> (LMA)*/
		
	.bss :
	{
		. = ALIGN(4);
		_sbss = .; 		/*Create a global symbol to hold start of bss section*/
		__bss_start__ = _sbss;

		*(.bss) 		/*Merge all .bss sections of input files*/

		. = ALIGN(4);
		_ebss = .;  		/*Create a global symbol to hold end of bss section*/
		__bss_end__ = _ebss;
	} > SRAM

	_end = .;
}
