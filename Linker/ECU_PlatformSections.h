#ifndef ECU_PLATFORMSECTION_H_
#define ECU_PLATFORMSECTION_H_

#ifndef _NEW_LINE_
#define _NEW_LINE_ >>
#endif

#define VECTOR_TABLE_SECTION \
KEEP(*(.isr_vector))



#define ROM_BLOCK(nameBlock) \
SECTION_CFG(nameBlock, isr_vector, VECTOR_TABLE_SECTION, rom) \
SECTION_CFG(nameBlock, text, USER_ROM_TEXT_SECTION, rom) \
SECTION_CFG(nameBlock, rodata, USER_ROM_RODATA_SECTION, rom) \

#define ROM_MEMORY MEMORY(rom, 0x08000000, 32K, rx, ROM_BLOCK(rom))
#define RAM_MEMORY MEMORY(ram, 0x20000000, 20K, rwx, RAM_BLOCK(ram))

#define RAM_BLOCK(nameBlock) \
SECTION_CFG(nameBlock, data, USER_RAM_DATA_SECTION, ram)\
SECTION_CFG(nameBlock, bss, USER_RAM_BSS_SECTION, ram) 
 

#define ECU_BLOCK_CFG \
ROM_MEMORY \
RAM_MEMORY 

#endif
