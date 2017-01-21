# 不同场景下的makefile

#### 多个源文件生成一个可执行文件的makefile
```
src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = main

ALL:$(target)

$(target): $(obj)
    gcc $^ -o $@
$(obj):%.o:%.c
    gcc -c $< -o $@         # 静态模式规则：只有$(obj)定义的目标才使用改模式规则

clean:
    rm -rf $(target) $(obj)

.PHONY: clean
```

#### 不同的源文件生成各自对应的可执行文件
```
src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = $(patsubst %.c, %, $(src))

ALL: $(target)

$(target): %: %.o
    gcc $< -o $@

$(obj):%.o:%.c
    gcc -c $< -o $@

clean:
    rm -rf $(target) $(obj)

.PHONY: clean
```
