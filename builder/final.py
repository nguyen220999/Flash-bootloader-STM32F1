f_final= open("../build/generated_linkerscript_fn.ld","w")
f_write_read= open("../build/generated_linkerscript.ld","r")    

lines_gen = f_write_read.readlines()       
add_start = "_start_ram_bss"
add_end   = "_end_ram_bss"

#temporary solution about library
add_end_head = "_end_ram_bss"

for line_gen in lines_gen:
    if add_start in line_gen:
        f_final.write(line_gen)
        f_final.write('\n')
        f_final.write(' __bss_start__ = _start_ram_bss;')
        f_final.write('\n')  
    elif add_end in line_gen:
        f_final.write(line_gen)
        f_final.write('\n')
        f_final.write(' __bss_end__ = _end_ram_bss;')
        f_final.write('\n')
        f_final.write(' end = _end_ram_bss;')
        f_final.write('\n')
    else:
        f_final.write(line_gen)