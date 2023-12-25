ENTRY(startup_hadler)
MEMORY
{
 rom (rx) : ORIGIN = 0x08000000, LENGTH = 32K >> ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K >>
}
SECTIONS
{
 current_add_rom = 0x08000000 ; >> .isr_vector(current_add_rom): >> { >> . = ALIGN(4); >> _start_rom_isr_vector = .; >> KEEP(*(.isr_vector)) >> . = ALIGN(4); >> _end_rom_isr_vector = .; >> } > rom >> current_add_rom = . ; >> .text(current_add_rom): >> { >> . = ALIGN(4); >> _start_rom_text = .; >> *(.text) >> *(.text*) >> *(.init) >> *(.fini) >> . = ALIGN(4); >> _end_rom_text = .; >> } > rom >> current_add_rom = . ; >> .rodata(current_add_rom): >> { >> . = ALIGN(4); >> _start_rom_rodata = .; >> *(.rodata) >> *(.rodata*) >> . = ALIGN(4); >> _end_rom_rodata = .; >> } > rom >> current_add_rom = . ; >> current_add_ram = 0x20000000 ; >> .data(current_add_ram): >> { >> . = ALIGN(4); >> _start_ram_data = .; >> *(.data) >> *(.data*) >> . = ALIGN(4); >> _end_ram_data = .; >> } > ram >> current_add_ram = . ; >>.bss(current_add_ram): >> { >> . = ALIGN(4); >> _start_ram_bss = .; >> *(.bss) >> *(.bss*) >> *(COMMON) >> . = ALIGN(4); >> _end_ram_bss = .; >> } > ram >> current_add_ram = . ; >>
}
