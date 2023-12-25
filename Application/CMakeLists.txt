cmake_minimum_required(VERSION 3.5)

SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)

set ( INCLUDE 
	" \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/MCAL \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/MCAL/arm_cm3 \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/MCAL/arm_cm3/kernel \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/MCAL/arm_cm3/drivers/STM32F10x_StdPeriph_Driver/inc \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/MCAL/ConfigTypes \
	\
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/Crc \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/Diag_com \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/ECU_Cfg \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/Flashing_Hdl \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/main \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/main/hardware_handle \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/main/main_state_machine \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/NvM_Hdl \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/Service_Hdl \
	-IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/SWIL_Hdl"

)

#[[-DUSE_WDGIF]]
set(CMAKE_MAKE_PROGRAM mingw32-make CACHE FILEPATH "" FORCE)
set(CMAKE_C_FLAGS "-fmax-errors=100 -std=c99 -c -mcpu=cortex-m4 -mthumb --specs=nosys.specs -DUSE_MCU  -DUSE_KERNEL_EXTRA ${INCLUDE}" CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_FLAGS "-fmax-errors=100 -std=gnu11 -c -mcpu=cortex-m4 -mthumb ${INCLUDE}" CACHE FILEPATH "" FORCE)
set(CMAKE_C_COMPILER   arm-none-eabi-gcc CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER arm-none-eabi-gcc CACHE FILEPATH "" FORCE)

project(application_lib)

include(application.cmake)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library( ${PROJECT_NAME}

	STATIC ${APPLICATION_SOURCE}

)