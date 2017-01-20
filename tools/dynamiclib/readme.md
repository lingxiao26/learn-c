## 创建动态库

#### 动态库 (共享库)

- 机制: 共享代码(不共享数据)
- 优点: 节省内存(共享) 易于更新(动态链接)
- 缺点: 相较于静态库调用速度略慢(延迟绑定机制)

- 重点强调:  
    - 动态库是否加载到内存，取决于程序是否在运行  
    - 动态库加载到内存的位置不固定 (位于堆和栈中间的区域)  

#### 创建步骤

1. 生成链接文件 .o文件  
  gcc -fPIC -c add.c sub.c mul.c (fPIC: 生成“与位置无关”的目标文件*.o)  
2. 生成动态库文件 .so文件  
  gcc -shared -o libmymath.so add.o sub.o mul.o  
3. 生成可执行程序  
  gcc main.c -o main -L库路径 -l库名 -I头文件路径  

- 注意: 此时执行main会提示未找到libmymath.so, 因为动态链接器找不到当前目录下生成的动态库，要让动态链接器找到该库，有以下方法:
  1. export LD_LIBRARY_PATH=\`PWD\`
  2. echo \`pwd\` > /etc/ld.conf.d/mylib.conf

