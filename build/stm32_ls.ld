/*Entry Point*/
ENTRY (Reset_Handler)

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
__max_heap_size = 0x200;
__max_stack_size = 0x400;

/* Defining Output Sections */
SECTIONS
{
	.text :
	{
	  . = ALIGN(4);
	  *(.isr_vector_tbl)  /*merge all .isr_vector_tbl sections of input files*/
	  *(.text)             /*merge all .text sections of input files*/
	  *(.rodata)           /*merge all .rodata sections of input files*/
	  . = ALIGN(4);
	 _etext = .;          /*Create a global symbol to hold end of text section*/
	} > FLASH
	    
	.data :
	{
	 . = ALIGN(4);
	_sdata = .;   /*Create a global symbol to hold start of data section*/
	  *(.data)
	 . = ALIGN(4);
	_edata = .;   /*Create a global symbol to hold end of data section*/
	} > SRAM AT> FLASH  /*>(vma) AT> (lma)*/
		
	.bss :
	{
	 . = ALIGN(4);
	_sbss = .;  /*Create a global symbol to hold start of bss section*/
	*(.bss)  /*merge all .bss sections of input files*/
	 . = ALIGN(4);
	_ebss = .;  /*Create a global symbol to hold end of bss section*/
	} > SRAM
}
