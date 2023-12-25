f_diag = open("../build/preprocess_linkerscript.ld","r")
f_write= open("../build/generated_linkerscript.ld","w")

lines = f_diag.readlines()
day_find = ">>"
for line in lines:
    if day_find in line:
        #line.replace('>>','\n')
        x= line.split(">>")
        for y in x:           
            f_write.write(y)
            f_write.write('\n')
    else:
        f_write.write(line)

