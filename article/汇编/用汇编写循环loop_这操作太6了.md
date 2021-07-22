- [一、常用符号](#一常用符号)
- [二、loop](#二loop)
- [三、loop s](#三loop-s)
- [四、loop总结](#四loop总结)
- [五、段前缀](#五段前缀)
- [六、一段安全的空间](#六一段安全的空间)
- [七、说明](#七说明)

用汇编写循环语句，真的太 6 了！说句实在的，这没多少人能手写出来，关键还是在于底层知识的掌握！

**推荐王爽老师的：《汇编语言》这本书好好看看，吸收一下！**

## 一、常用符号

- ()：取内容的意思,在描述中使用,编程中不能使用()；
- mov ax, [bx]    <===>   (ax) = ((ds)*16 + (bx))
- mov [bx], ax    <===>    ((ds)*16 + (bx)) = (ax)
- idata: 表示常量；

## 二、loop

1. loop和cx是紧密结合的；
2. 判断cx中的值,不为0则跳转至标号处执行,如果为0则向下执行;此时,cx中的值影响着loop指令的执行结果。
3. 通常,loop指令来实现循环功能,cx中存放循环的次数。

## 三、loop s

CPU执行loop s的时候，需要进行两步操作：

1. (cx) = (cx) - 1;
2. 判断cx中的值，不为0则跳转至标号s所标识的地址处执行，如果为0则执行下一条指令；

原题：计算2^12的结果：

示例代码(没有汇编的，只能以C语言格式上传)：

```c
assume cs:code
code segment

start: mov ax, 2
    mov cx, 11
s:  add ax, ax
    loop s
    
    mov ax, 4c00h
    int 21h
    
code ends
end start
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbt7uoObwchgUDrGctAh2S7QNzARuz3rJmshvyic3I1MQ5iaXXr2hFHc8D9P5WjRTq3ew8PCGeQEQWMw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbt7uoObwchgUDrGctAh2S7QPADjvdV7ZBDXWfqSw8YL6fG2I8nCZVZ37fco1lmdrv0LJ7ONicIMDLg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

因为debug模式下面都是16进制数，最终计算结果1000H, 也就是4096。

## 四、loop总结

1. **cx中存放循环次数(规定好的)；[bx]中存放偏移地址；**
2. loop指令中的标号所标识的地址要在前面;
3. 循环执行的程序段,要写在标号和loop指令的中间；

循环框架：

```c
  mov cx, 循环次数
s:
  循环执行的程序段
  loop s
```

**debug下面针对循环,循环次数很多的情况下,先用u来查看一下程序的地址,g 偏移地址，直接就会跳过去，到这个地址执行相应的代码段;将g指令看作是断点；**

**循环次数很多的情况下,按p指令,直接就把循环执行完了,到了程序的最后；**

## 五、段前缀

用于显示的指明内存单元的段地址的 ds: cs: ss: es:，在汇编语言中称为段前缀；

mov ax, cs:[0]

## 六、一段安全的空间

在8086模式中,随意向一段内存空间写入内容是很危险的,因为这段空间中可能存放着重要的系统数据或代码。

**在一般的PC机中,DOS方式下,一般都不会使用0:200-0:2FF,(0:200h-0:2FFh)的256个字节的空间，所以这段空间是安全的。**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbt7uoObwchgUDrGctAh2S7Q3lK1UExldhzSKUazj90w7ibIDPSAc8xDI1Uv3maERGicKl6TmX7Jj8kA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

通过 debug 可以看出，这段空间确实没有数据,我们可以放心使用。我们在向内存中写入数据时，可以使用这段空间。

## 七、说明

原创文章链接：[用汇编写循环（loop），这操作太6了！](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483823&idx=1&sn=a8de6764d087c12a0c89168ac9b4f32a&chksm=f94c8b92ce3b0284ee5aeebebf852a0adfbf529e7115cd22704ecde839a1fbae027f824c71bc&scene=21#wechat_redirect)
