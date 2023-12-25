rem build cmake
@Echo off

cd ../
if not exist build ( mkdir build)

if not exist .ccache ( mkdir .ccache)

xcopy /s /y C:\Users\tgr6hc\Desktop\Embedded_full\GatewayECU_git\FlashBootLoader\builder\ccache.conf C:\Users\tgr6hc\Desktop\Embedded_full\GatewayECU_git\FlashBootLoader\.ccache

SET LOGFILE= build/LogFile.log
cd builder

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
echo ==============Gen Cmake Application======================
@echo on
cd ../Application
call Standalone_build.bat

echo ================Gen Cmake MCAL========================
@echo on
cd ../MCAL
call Standalone_build.bat


cd ../builder
@echo off
echo ================Run Makefiles=========================
echo ******************************************************
echo ******************************************************
echo ******************************************************
@echo on

@echo off
echo ==============Run Makefiles Application==================
@echo on
cd ../build/Application
call mingw32-make
cd ../../builder

@echo off
echo ================Run Makefiles MCAL====================
@echo on
cd ../build/MCAL
call mingw32-make
cd ../../builder



@echo off
echo ======================Linker==========================
@echo on

call gen_linker_script.bat

@echo off
echo ===================Start Linker=======================
@echo on
rem -nostartfiles
rem C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU/build/startup.o

set "LINKER_SCRIPT =C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/build/generated_linkerscript_fn.ld" 
set "LIBRARY = C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/build/Arccore_BSW/libarccore_bsw_lib.a C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/build/Trampoline_Os/libtrampoline_os_lib.a C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/build/RTE_develop/libRTE_develop_lib.a C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/build/MCAL/libMCAL_lib.a C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/build/Adaption/libadaption_lib.a"
rem C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU/Toolchain/ccache-4.8.2-windows-x86_64/ccache --config-path C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/builder/ccache.conf
rem PATH C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/builder/ccache.conf 
C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU/Toolchain/ccache-4.8.2-windows-x86_64/ccache cache_dir=C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/.ccache arm-none-eabi-gcc -Wl,-Map,../build/software_fbl.map -Os --specs=nosys.specs -TC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/build/generated_linkerscript_fn.ld C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/build/Application/libapplication_lib.a C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/build/MCAL/libMCAL_lib.a C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU/adaption/main/main.c -o ../build/software_fbl.elf
objcopy -O ihex ../build/software_fbl.elf ../build/software_fbl.hex
objcopy -O binary ../build/software_fbl.elf ../build/software_fbl.bin
)