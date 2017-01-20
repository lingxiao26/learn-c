## 创建静态库

静态库需要跟源代码链接一起编译生成可执行程序，每一个需要用到该静态库的程序都会包含该库的一份完整拷贝
如果有多个程序会使用这个静态库，会占用大量内存

```
1. 汇编 - 生成链接文件
    gcc -c add.c sub.c mul.c
2. 生成静态库
    ar rs libmymath.a add.o sub.o mul.o 
3. 链接
    gcc main.c -o main -I ./ -L ./ -l mymath

    -I 指定头文件目录
    -L 指定静态库所在目录
    -l 指定静态库的名字
```
