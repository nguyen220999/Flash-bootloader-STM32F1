file (GLOB SOURCE "arm_cm3/drivers/STM32F10x_StdPeriph_Driver/src/*.c")
list(REMOVE_ITEM SOURCE " arm_cm3/drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c \
                          arm_cm3/drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash_swil.c")

set ( STSPERIPH_DRIVER 
    ${SOURCE}
)
