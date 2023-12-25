include(./arm_cm3/drivers/STM32F10x_StdPeriph_Driver/STM32F10x_StdPeriph_Driver.cmake)

file (GLOB SOURCE_DRIVERS "arm_cm3/drivers/*.c")
list(REMOVE_ITEM SOURCE_DRIVERS "arm_cm3/drivers/Gpt.c \
                                arm_cm3/drivers/Wdg.c")

set ( DRIVERS_SOURCE 
)