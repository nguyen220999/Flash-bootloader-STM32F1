if exist cmake_install.cmake del cmake_install.cmake

if exist CMakeFiles\ (del /s /q CMakeFiles\* rmdir /s /q CMakeFiles\ )
if exist CMakeCache.txt del CMakeCache.txt
if exist Makefile del Makefile
if exist *.a del *.a