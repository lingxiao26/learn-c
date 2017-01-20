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

#### 自动变量
```
$@: 在命令中表示规则中的目标
$<: 在命令中表示规则中的第一个条件
$^: 在命令中表示规则中的所有条件，组成一个列表，以空格隔开，如果有重复的项则去除重复项

Example:
main: $(obj)
    gcc -o $@ $^
add.o: add.c
    gcc -c $< -o $@
```

#### makefile函数
```
/* wildcard:函数名   *.c:参数 */
src = $(wildcard *.c)       # 找到当前目录下所有后缀为.c的文件，赋值给src
obj = $(patsubst %.c, %.o, $(src))      # 把src变量里所有"xxx.c"的文件替换成"xxx.o", "xxx"必须严格匹配

Example:
src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))

main: $(obj)
    gcc $^ -o $@
%.o: %.c
    gcc -c $< -o $@
clean:
    rm -rf main $(obj)
```
