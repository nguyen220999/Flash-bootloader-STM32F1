rem build cmake
@Echo off


echo off
set request=%1
echo -------
echo !request!
echo -------
if "%request%" == "clear" (
    cd ../
    rmdir "build" /S /Q
    cd builder
) else (

rem call :Logit >> %LOGFILE% 
rem :Logit

@echo off
echo ****************Build Project*************************
echo ==============Gen Cmake SWIL======================
@echo on

rem call Standalone_build.bat


@echo off
echo ================Run Makefiles=========================
echo ******************************************************
echo ******************************************************
echo ******************************************************
@echo on

@echo off
echo ==============Run Makefiles SWIL==================
@echo on
cd ../../build/swil
rem call mingw32-make
cd ../../builder/swil


@echo off
echo ======================Linker==========================
@echo on

rem call gen_linker_script.bat

@echo off
echo ===================Start Linker=======================
@echo on
rem -nostartfiles
rem C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU/build/startup.o

rem C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU/Toolchain/ccache-4.8.2-windows-x86_64/ccache --config-path C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/builder/ccache.conf
rem PATH C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/builder/ccache.conf 
arm-none-eabi-gcc -Wl,-Map,../../build/swil/software.map -nostdlib -Os -IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/MCAL/arm_cm3/drivers/STM32F10x_StdPeriph_Driver/inc -IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/MCAL/arm_cm3/kernel -TC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/builder/builder_swil/swil_linkerscript.ld C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/MCAL/arm_cm3/drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash_swil.c -o ../../build/swil/software_swil.elf
objcopy -O ihex ../../build/swil/software_swil.elf ../../build/swil/software_swil.hex
objcopy -O binary ../../build/swil/software_swil.elf ../../build/swil/software_swil.bin
cd ../../builder/builder_swil
)