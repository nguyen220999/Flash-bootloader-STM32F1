#ifndef ECU_USERSECTION_H_
#define ECU_USERSECTION_H_

#ifndef _NEW_LINE_
#define _NEW_LINE_ >>
#endif

#define PUT_USER_SEC_HERE(section, object) object.o(.section)

#define USER_ROM_RODATA_SECTION \
*(.rodata) _NEW_LINE_ \
*(.rodata*)

#define USER_ROM_TEXT_SECTION \
*(.text) _NEW_LINE_ \
*(.text*) _NEW_LINE_ \
*(.init) _NEW_LINE_ \
*(.fini)

#define USER_RAM_BSS_SECTION \
*(.bss) _NEW_LINE_ \
*(.bss*) _NEW_LINE_ \
*(COMMON)

#define USER_RAM_DATA_SECTION \
*(.data) _NEW_LINE_ \
*(.data*)


#endif