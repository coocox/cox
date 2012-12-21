//*****************************************************************************
//
//! \file main.c
//! \brief Test main.
//! \version 1.0
//! \date 5/17/2011
//! \author CooCox
//! \copy
//!
//! Copyright (c) 2009-2011 CooCox.  All rights reserved.
//
//*****************************************************************************

#include "test.h"

#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"
#pragma section = "CodeRelocate"
#pragma section = "CodeRelocateRam" 

void
common_startup(void)
{
//    extern char __DATA_ROM[];
//    extern char __DATA_RAM[];
//    extern char __DATA_END[];
  
    /* Declare a counter we'll use in all of the copy loops */
    unsigned long n;
 
 
    /* Addresses for VECTOR_TABLE and VECTOR_RAM come from the linker file */  
    extern unsigned long __VECTOR_TABLE[];
    extern unsigned long __VECTOR_RAM[];

    /* Copy the vector table to RAM */
    if (__VECTOR_RAM != __VECTOR_TABLE)
    {
        for (n = 0; n < 0x410; n++)
            __VECTOR_RAM[n] = __VECTOR_TABLE[n];
    }
    /* Point the VTOR to the new copy of the vector table */
    xHWREG(0xE000ED08) = ((unsigned long)__VECTOR_RAM);    
    
    /* Get the addresses for the .data section (initialized data section) */
    unsigned char* data_ram = __section_begin(".data");
    unsigned char* data_rom = __section_begin(".data_init");
    unsigned char* data_rom_end = __section_end(".data_init");
    
    /* Copy initialized data from ROM to RAM */
    n = data_rom_end - data_rom;
    while (n--)
      *data_ram++ = *data_rom++;
 
 
    /* Get the addresses for the .bss section (zero-initialized data) */
    unsigned char* bss_start = __section_begin(".bss");
    unsigned char* bss_end = __section_end(".bss");
    
    /* Clear the zero-initialized data section */
    n = bss_end - bss_start;
    while(n--)
      *bss_start++ = 0;    
    
    /* Get addresses for any code sections that need to be copied from ROM to RAM.
     * The IAR tools have a predefined keyword that can be used to mark individual
     * functions for execution from RAM. Add "__ramfunc" before the return type in
     * the function prototype for any routines you need to execute from RAM instead 
     * of ROM. ex: __ramfunc void foo(void);
     */
    unsigned char* code_relocate_ram = __section_begin("CodeRelocateRam");
    unsigned char* code_relocate = __section_begin("CodeRelocate");
    unsigned char* code_relocate_end = __section_end("CodeRelocate");
    
    /* Copy functions from ROM to RAM */
    n = code_relocate_end - code_relocate;
    while (n--)
      *code_relocate_ram++ = *code_relocate++;
}

int main(void)
{
    //
    // Do the main test
    //
    (*((volatile unsigned long *)(0x40048100))) = 0x00;
    common_startup();
    TestMain();

    while(1)
    {
      //xHWREG(SIM_SRVCOP) = 0x55;
      //xHWREG(SIM_SRVCOP) = 0xAA;
    }
}
