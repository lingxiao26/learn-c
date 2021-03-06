## 进程，进程控制

#### 进程控制块 PCB

```
    本质是一个结构体，常用的成员变量如下：

    1. 进程id：系统中每个进程都有唯一的id，在c语言中用pid_t类型表示，它是一个非负整数。
    2. 进程的状态，有就绪，运行，挂起，停止等状态
        就绪态：等待cpu分配时间片
        运行态：占用cpu进行运算
        挂起  ：等待除cpu以外的其它资源，主动放弃cpu
    3. 进程切换时需要保存和恢复的一些cpu寄存器
    4. 描述虚拟地址空间的信息
    5. 描述控制终端信息
    6. 当前工作目录
    7. umask掩码
    8. 文件描述符表
    9. 和信号相关的信息
    10. 用户id和组id
    11. 会话（session）和进程组（功能相近的进程构成一个进程组）
    12. 进程可以使用的资源上限（Resource Limit）.
```


#### 环境变量

[env_op.c](./env_op.c)


#### 进程控制

```
    fork
    getpid, getppid, getuid, getgid
    execl, execlp （l: list, p: path环境变量）
```

#### 孤儿进程和僵尸进程

```
    孤儿进程：父进程先于子进程退出，子进程成为孤儿进程，子进程的父进程成为init进程（进程孤儿院）
    僵尸进程：子进程终止，父进程尚未回收子进程的残留资源（PCB：存放于内核中），变成僵尸进程

    注意：僵尸进程不能用kill命令清除，因为僵尸进程已经终止，kill命令只是用来终止进程的
    可以通过kill父进程的方法来清除僵尸进程
```

  [zoom.c](./zoom.c)


#### wait函数

```
    wait函数有三个功能：

    1. 阻塞等待子进程退出
    2. 回收子进程残留资源
    3. 获取子进程结束状态（退出原因）

    pid_t wait(int *status);
    return SUCEESS: pid  FAILED: -1
```
[wait.c](./wait.c)

#### waitpid函数

```
    跟wait函数相似，函数原型：

    pid_t waitpid(pid_t pid, int *status, int options);
    返回值：
        SUCCESS：pid
        FAILED： -1（无子进程）
        0     ：参数3为 WNOHANG（非阻塞），且子进程正在运行
    参数pid的不同取值：
        >0  回收指定ID的子进程
        -1  回收任意子进程（相当于wait）
        0   回收和当前调用waitpid一个组的所有子进程
        <-1 回收指定进程组内的任意子进程
```
[waitpid.c](./waitpid.c)

#### 小练习

```
    父进程fork3个子进程，三个子进程
    一个调用ps命令，一个调用自定义程序1（正常），一个调用自定义程序2（会出段错误）
    父进程使用waitpid对子进程进行回收
```
[exercise.c](./exercise.c)
