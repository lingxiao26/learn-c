## 线程同步，信号量，进程锁


### 线程同步

     同步：协同步调，按预定的先后次序执行  
     线程同步：一个线程执行一个功能调用，在该功能调用未返回之前，为保证数据一致性，其他的线程不能调用该功能  
       
     **所有“多个控制流共同操作一个共享资源”的情况，都需要同步**  

     共享资源（标准输出）无同步机制的现象 (thrd_shared.c)[thrd_shared.c]

     

#### 互斥量 mutex

     使用互斥量对共享资源的访问进行控制的步骤：  
       
     1. 初始化一个互斥量  
     `pthread_mutex_t mutex;`  
     `pthread_mutex_init(&mutex, NULL);`  

     2. 加锁  
     `pthread_mutex_lock(&mutex);`  

     3. 对共享资源进行操作  
     `do works`  

     4. 解锁  
     `pthread_mutex_unlock(&mutex);`  

     5. 销毁锁  
     `pthead_mutex_destroy(&mutex);` 


#### 死锁

     
