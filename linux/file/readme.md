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
    open, close
常用参数:
    头文件: fcntl.h
    O_RDONLY, O_WRONLY, O_RDWR
    O_CREAT, O_TRUNC
错误:
    记录在 "errno(一个整数)" 中，需添加头文件 errno.h
```
