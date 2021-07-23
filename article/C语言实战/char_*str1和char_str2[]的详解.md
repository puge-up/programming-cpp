- [一、内存管理](#一内存管理)
- [二、指针变量](#二指针变量)
- [三、对char *str1 = "hello world"的深刻理解](#三对char-str1--hello-world的深刻理解)
- [四、说明](#四说明)

学 C 不易，请坚持下去

C 语言的一个知识点：

```c
char *str1 = "hello world" 和 char str2[] = "hello world"; //其区别：
```

## 一、内存管理

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbuzR6kYOicR77TNBmibnq7UXqamU05bFIKMI1vARmQz55Zqft6reMS74c6lwZXkRXSV3o87Ulpy6REg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(内存映像图)</p>

如上图所示：只读代码段一般存放的是编写好的程序；

**内存分为了：只读代码段，只读数据段，BSS，堆，栈五个不同区域。**

- 只读数据段放的是常量(字符串常量，数组名称，函数名称)，**只读区域不能更改；**
- BSS 区域存放的是全局变量和 static 静态类变量，又分为未初始化，值都为0，和已初始化区域；
- 堆中存放的是 malloc()，calloc()……申请的空间，不由操作系统回收，必须靠程序员自己通过 free() 回收空间，不然就是内存泄漏；
- 栈中存放的是局部变量，形参变量，栈中空间可被任何函数使用，是数据的可靠性很低；

## 二、指针变量

str1 是指针变量，str1++; right,指针加减整型，结果还是指针。

对于 str2 而言：

```c
char str2[] = "hello world"; <=> char str2[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'}。
```

这是对字符数组初始化，所以 str2 是数组名称(指针常量)，str2++；false，常量不能赋值。

**"hello world"字符串本身就是以 0 结尾的字符数组。**

"hello world"字符串常量在只读数据段，值本身内容不能被更改。

- str1 为指针变量，*str1 = 't'; false,更改的是只读数据段中的区域；
- str2 为数组名称，其空间在栈中申请，*str2 = 't'; true，栈中的数据可以被更改；

## 三、对char *str1 = "hello world"的深刻理解

- strlen(str1);    11
- strlen(str2);    11
- sizeof(str2);    12   数组名称，求字节数，是数组所申请的空间的字节数，在上0结束标志  
- sizeof(str1);    4/8  与平台有关，32位系统下，指针 4 字节，64 位，指针8字节；
- sizeof(*str1);   1    *str1 就是'h'，占用一个字
- sizeof("hello world");   12   字符串常量所占空间；

strlen();   求得是字符串长度，不算那个 0；sizeof()；关键字，单目运算符，求字节数，算字符串的结束标志 0，这就是区别。

数组[]中的值，由初值个数决定。

## 四、说明

原创文章链接：[char *str1 和 char str2[]的详解](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483673&idx=1&sn=af2d886143a8a9c96e063f550d3f1f14&chksm=f94c8b24ce3b0232b6a3f0ca50b0ad89dbd9f9f74ba157d42361e6bea2bc3e27cb9c10938307&scene=21#wechat_redirect)
