- [一、为什么要用Makefile进行多个.C文件的编译](#一为什么要用makefile进行多个c文件的编译)
- [二、Makefile的使用规则](#二makefile的使用规则)
- [三、头文件的一点知识](#三头文件的一点知识)
- [四、gdb的使用](#四gdb的使用)
  - [1、命令](#1命令)
  - [2、设断点](#2设断点)
  - [3、一些输出](#3一些输出)
- [五、说明](#五说明)

## 一、为什么要用Makefile进行多个.C文件的编译

1. 一般我们在进行项目开发的时候，会建立工程，下面有许多目录，不同目录下又有许多.C文件，这事就需要联合编译了。
2. 我们自己手动编译的话，多个程序文件交织在一起，会出现不同文件资源之间的依赖与被依赖关系。那么在编译的时候就会出现问题：必须先解决被依赖项，在解决依赖项。
3. 在这种情况下，我们进行手动编译的话，将会变得异常困难，首先我们必须记住依赖关系，才能知道编译顺序，其次每一次都要执行非常多的gcc编译命令才能完成最终的编译目标(gcc中还带有许多参数呢)。
4. 这时就得用Makefile，Makefile是工程管理的有效工具，用脚本语言进行编写。

## 二、Makefile的使用规则

- 使用命令：make test
- ./test (test就是你最终生成的目标文件)
- make：只修改你新改动的文件

Makefile中的书写规则：目标... : [依赖项...]、[[@]命令]

1. []中为可写可不写的内容。
2. @符号:命令在终端上出现的关闭符号。
3. 命令前必须有一个tab符号。

Makefile中可以定义变量，好处：减少书写规则；变量的使用格式：${变量名称}。

自动变量：

命令|解释
|:--|:--
$@|代表规则里的目标文件
$^|代表规则里所有依赖文件
$<|代表规则里第一个依赖文件
%.o : %.c|所有的.o文件均一一对应依赖与其后的.c文件(模式规则)

注意：

1. Makefile当中出现.PHONY:clean 意思是，当前目录下也有clean文件时,执行Makefile中的命令clean。
2. 当其中有确定规则时，执行确定规则的命令。

这个是没有使用变量前的Makefile：
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu6QgnD46eLM41Gm4LiaicEBGraiaibTSqX4rm6f2ibg9Lh2lZmHKic6cJRHeAfBOGjh1ODKMfYYK68nyQA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(未使用变量的Makefile)</p>

这个是使用变量后的精简Makefile：
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu6QgnD46eLM41Gm4LiaicEBGyaSzHfPKZjSe5vt2icasDux76Vp9EENicpNuUhFVsolcsl8VaVN6O21w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(使用变量的Makefile)</p>

## 三、头文件的一点知识

< >和" "的区别：

- < >，在系统的指定目录下去找，一般情况下在/usr/include/xxx.h
- " "，在当前目录下找

头文件的格式：

- #ifndef _TEST_H_
- #define _TEST_H_

- ......

- #endif

条件预编译目的：防止头文件的重复包含。

## 四、gdb的使用

### 1、命令

- gcc -g test.c -o test   （-g是调试程序必须用的参数）
- gdb -q test      (-q跳过提示，直接调试) (test要调试的目标文件)
- start    进入调试
- s和n: s表示遇到函数，进入函数，跳转到函数进行调试；n表示不进入函数，继续往下调试。

### 2、设断点

- b  行数
- run : 此时将跳转到该行执行
- 删除断点   d  n(n不是行数，表示将第几个断点删除)
- 查看断点   info  b

### 3、一些输出

- 打印/格式  相应的量
- p/x str    p/c *str   p/d str ......可以查看相应的地址，值，字符...
- 离开gdb调试：q

## 五、说明

原创文章链接：[Makefile和gdb的简单使用](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483804&idx=1&sn=4394bb776f52228c56a090c4c472ed3c&chksm=f94c8ba1ce3b02b7534d46375fa70092fad7318622841f17c581e1e9e55e9d44fdf6d6c912f8&scene=21#wechat_redirect)
