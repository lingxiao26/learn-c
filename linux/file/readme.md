#### C标准库文件IO函数
```
fopen, fclose, fread, fwrite
fputc, fgetc, fputs, fgets
fseek, ftell, frewind
...
```

#### linux系统函数
```
头文件:
    unistd.h, fcntl.h
函数
    open, close, read, write
open函数常用参数:
    头文件: fcntl.h
    O_RDONLY, O_WRONLY, O_RDWR
    O_CREAT, O_TRUNC
错误处理函数
    错误号: errno 定义在头文件 errno.h中
    perror函数:   void perror(const char *s);
    strerror函数: char *strerror(int errnum);
```

#### 阻塞，非阻塞
> 读常规文件是不会阻塞的，不管读多少字节，read一定会在有限的时间内返回。从终端设备或网络读则不一定
> 阻塞和非阻塞是对于文件而言的。而不是read，write的属性。read终端，默认阻塞读.

- 阻塞读终端  
    [block_readtty.c](./block_readtty.c)  

- 非阻塞读终端  
> 错误代码: EAGAIN 当使用不可阻断I/O 时（O_NONBLOCK），若无数据可读取则返回此值.   
    [nonblock_readtty.c](./nonblock_readtty.c)  

- 非阻塞读终端和等待超时   
    [nonblock_timeout.c](./nonblock_timeout.c)  

- read函数返回值总结：  
    - 返回非零值: 实际read到的字节数  
    - 返回-1:  
        - errno == EAGAIN(或==EWOULDBLOCK)设置了非阻塞读，并且没有数据到达  
        - error != EAGAIN(或!=EWOULDBLOCK) read 出错  
    - 返回0：读到文件末尾  
