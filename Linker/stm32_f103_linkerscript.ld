/* Linker script */


#include "ECU_UserSections.h"
#include "ECU_PlatformSections.h"

#define SECTION_CFG(mem_name, section_name, subsection, vml) \
.section_name(current_add_##mem_name##): _NEW_LINE_ \
{ _NEW_LINE_ \
	. = ALIGN(4); _NEW_LINE_ \
	_start_##mem_name##_##section_name## = .; _NEW_LINE_ \
\
	subsection _NEW_LINE_ \
	. = ALIGN(4); _NEW_LINE_ \
	_end_##mem_name##_##section_name##   = .; _NEW_LINE_ \
	\
\
} > vml _NEW_LINE_ \
current_add_##mem_name## = . ; _NEW_LINE_

ENTRY(startup_hadler)
/*STARTUP(startup.o)*/

#undef MEMORY
#define MEMORY(mem_name, start_add, size, attr, intBlock) \
mem_name (attr) : ORIGIN = start_add, LENGTH = size _NEW_LINE_

MEMORY
{
	ECU_BLOCK_CFG
}

#undef MEMORY
#define MEMORY(mem_name, start_add, size, attr, intBlock) \
current_add_##mem_name = start_add ; _NEW_LINE_ \
intBlock

SECTIONS
{
	ECU_BLOCK_CFG
}

