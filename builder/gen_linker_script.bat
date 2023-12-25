cd ../
if exist build (
	cd build 
	if exist *.ld del *.ld 
	cd ../ )

cd builder
arm-none-eabi-gcc -E -P -x c -Wno-error -IC:/Users/tgr6hc/Desktop/Embedded_full/GatewayECU_git/FlashBootLoader/Application/linker ../Linker/stm32_f103_linkerscript.ld >>../build/preprocess_linkerscript.ld

python gen_linker_script.py
python final.py

