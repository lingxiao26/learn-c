** strsub.c - 子字符串替换的实现思路 **  
> 说明:  
> src: 源字符串  
> out: 替换之后存放的内存单元  
> sub: 待替换的子字符串  
> new_sub: 替换之后的子字符串  
```
1. 通过strstr函数在src中查找sub
2. 通过strncat函数将src中符合条件的串追加到out中
　　- 所以这里需要两个不断移动的指针来确定strncat的字节数
　　- 定义head和tail两个指针，初始指向src
3. 通过head和tail的不断移动并把符合条件的串strncat到out中
4. 退出循环的条件:
　　- 当tail=strstr(tail, sub)为空，即没有找到子字符串时，退出循环
　　- \*tail = '\0' 的时候指向了src的最后，退出循环
```