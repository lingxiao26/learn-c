#### 进程组

   进程组也叫作业，代表一个或多个进程的集合。  
   进程组ID == 第一个进程ID（组长ID）  
   可以使用kill -9 -pgid（负的）来杀死整个进程组内的进程  

   ```
       进程组操作函数：
       
       
       pid_t getpgrp(void);                 /* 获取当前进程组ID           */
       pid_t getpgid(pid_t pid);            /* 获取指定进程ID所属进程组ID */
       int setpgid(pid_t pid, pid_t pgid);  /* 设置指定进程ID的进程组ID   */
   ```


#### 会话

   一个或多个`进程组`的集合  
   开始于`用户登录`  
   结束于`用户退出`  

   ```
     会话操作函数：

     pid_t getsid(pid_t pid);               /* 获取指定进程所属的session ID，pid为0时获取当前进程所属的session ID */
     pid_t setsid(void);                    /* 为当前进程创建一个新会话（当前进程不能为进程组组长）               */ 
   ```


#### 守护进程

   Daemon进程，是linux中的后台服务进程，通常独立于控制终端周期性的执行某种任务或等待处理某些发生的事件，一般采用以d结尾的名字  

###### 创建守护进程模型

1. 创建子进程，父进程退出
