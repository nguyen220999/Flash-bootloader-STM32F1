/* ENTRY(startup_hadler) */
MEMORY
{
 rom (rx) : ORIGIN = 0x08000000, LENGTH = 64K 
 ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K 

}
SECTIONS
{
 current_add_ram = 0x20000000 ; 
 .isr_vector(current_add_ram): 
 { 
 . = ALIGN(4); 
 _start_rom_isr_vector = .; 
 KEEP(*(.isr_vector)) 
 . = ALIGN(4); 
 _end_rom_isr_vector = .; 
 } > ram AT>ram 
 
 current_add_ram = . ; 
 .text(current_add_ram): 
 { 
 . = ALIGN(4); 
 _start_ram_text = .; 
 *(.text) 
 *(.text*) 
 *(.init) 
 *(.fini) 
 . = ALIGN(4); 
 _end_rom_text = .; 
 } > ram AT>ram 
 
 current_add_ram = . ; 
 .rodata(current_add_ram): 
 { 
 . = ALIGN(4); 
 _start_rom_rodata = .; 
 *(.rodata) 
 *(.rodata*) 
 . = ALIGN(4); 
 _end_rom_rodata = .; 
 } > ram AT>ram 
 
 current_add_ram = . ; 

 .data(current_add_ram): 
 { 
 . = ALIGN(4); 
 _start_ram_data = .; 
 *(.data) 
 *(.data*) 
 . = ALIGN(4); 
 _end_ram_data = .; 
 } > ram AT>ram 
 
 current_add_ram = . ; 
.bss(current_add_ram): 
 { 
 . = ALIGN(4); 
 _start_ram_bss = .; 

 __bss_start__ = _start_ram_bss;
 *(.bss) 
 *(.bss*) 
 *(COMMON) 
 . = ALIGN(4); 
 _end_ram_bss = .; 

 __bss_end__ = _end_ram_bss;
 end = _end_ram_bss;
 } > ram AT>ram 
 current_add_ram = . ; 


}
