## 创建静态库

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
