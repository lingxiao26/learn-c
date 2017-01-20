### makefile使用小结

目标: 依赖  
    命令(命令前面必须使用一个tab)  

* 目标：要生成的目标文件  
* 依赖：目标文件由哪些文件生成  
* 命令：通过执行该命令由依赖文件生成目标  

#### makefile的变量
```
src = add.c sub.c mul.c main.c
obj = add.o sub.o mul.o main.o

引用变量:
$(var_name)

Example:
main:$(obj)
    gcc -o main $(obj)
```
