cmake -S . -B ../build/Application -G "MinGW Makefiles"





@echo off
rem uncomment for standalone build
rem cmake -S . -B ../build/Adaption -DCMAKE_CXX_COMPILER_LAUNCHER=C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/Toolchain/ccache-4.8.2-windows-x86_64/ccache.exe -DCMAKE_C_COMPILER_LAUNCHER=C:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/Toolchain/ccache-4.8.2-windows-x86_64/ccache.exe -G "MinGW Makefiles"