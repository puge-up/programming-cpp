- [一、对于 register 关键字](#一对于-register-关键字)
- [二、变量可以重复定义](#二变量可以重复定义)
- [三、对于函数的返回值和函数的参数](#三对于函数的返回值和函数的参数)
- [四、三目运算符](#四三目运算符)
- [五、对于C语言中的const](#五对于c语言中的const)
- [六、说明](#六说明)

编程的学习，绝非一朝一夕，只有日积月累，长久的坚持学习，去编程，对我们的影响将是潜移默化的，最终技术的提升是水到渠成，让我们一起开启 Linux C/C++ 之旅.

## 一、对于 register 关键字

1、C 程序

```c
#include<stdio.h>

int main(void){
   register int a = 10;

   printf("&a = %p\n", &a);
   return 0;
}
```

运行结果:

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjm9Lb7wJT0fXjFHCfp0PnxrDx1mQoY5e3QtiaiaibeM9YSicgcJh4iaTJibww/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2、C++程序

```cpp
#include<iostream>
#include<stdio.h>
using namespace std;

int main(void){
   register int a = 10;

   printf("&a = %p\n", &a);
   return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOj9hKe5cjbPVR2vvPwBzScic1w73IsibDiajfibav74RIo89INLxVYpgHbKw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**C语言中register(寄存器存储变量)，不能对这个所修饰的变量进行取地址。**

**C++中可以对register修饰的变量进行取地址，因为C++编译器内部做好了优化处理。**

## 二、变量可以重复定义

代码如下

```c
#include<stdio.h>

int g_a;   //在这里变量都已经定义了
int g_a = 100;
int main(void){
   printf("%d\n", g_a);
   return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjqaJNhKI8w1khVZ05ZY9WD6b5SgQy8Mrq9R4eJaibAON8Yh6V2F2LN4g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**C编译器检查不严格，可以这样重复定义变量。**

## 三、对于函数的返回值和函数的参数

代码如下

```c
#include<stdio.h>

//C++编译器是非常严格的
f(i){  
   printf("%d\n", i);
}

g(){    //C语言的编译器是不严格的(存在默认类型);
   return 5;
}

int main(void){
   f('A');

   printf("%d\n", g(1, 2, 3, 4, 5, 6));
   return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjRDPxtgFXOhqVADs4sLgk5bWSXFB8s5iafyZNBzv3NNIkThiahhLvXcaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**C语言对于函数的参数和返回值的要求不是那么的严格意义上的。**

## 四、三目运算符

代码如下

```c
#include<stdio.h>

int main(void){
   int a = 10;
   int b = 20;
   //在C语言中,表达式的结果,存放在寄存器
   //在C语言中,表达式返回的是变量的值
   //(a < b ? a : b)  (里面返回的是常量,常量不能&)  = 30;
   //10 = 30;
   //返回的是一段连续的空间即可,即一段内存的首地址;
   *(a < b ? &a : &b) = 30;   //C++编译器对C++语言的优化,内部就是这样实现的;

   printf("a = %d, b = %d\n", a, b);
   return 0;

}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjciaehhRJiauvkZTZ9hW1Fibrw17ScukDmeicFsULzvZngIS9RpUGCFaWFQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**在C语言中，三目运算符的返回时一个值，不是一段连续的内存空间，所以对其不能进行赋值操作。**

## 五、对于C语言中的const

1、代码如下

```c
#include<stdio.h>

typedef int* TYPE;

int main(void){
   //TYPE const a;
   const TYPE a;
   int b = 10;
   int c = 20;

   a = &b;
   a = &c;

   return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjNKPD2vgTTicicU13x1icaZDnNkEABw0Ctpibherntz72O9GnRt8P7icGwXg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

原因分析：类比法，const int a; <===>  int const a;  Type的数据类型是：int *

**此时的情况是：const Type a; <===> Type const a;  此时可以说明的是：const修饰的是指针变量的值，是常量，不能更改，而这个指针所指向空间的值是可以改变的。**

2、代码如下

```c
#include<stdio.h>

int main(void){

   //C语言中的const是一个冒牌货
   const int a = 10;//只读变量,在内存中分配空间
   int *p = (int *)&a;

   *p = 20; //间接赋值
   printf("a = %d\n", a);
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjYrPGUyBOHibDH9r0Kic31msHAg9iaUACuqw1826xgtj8I8e8233kbCKvg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**在C语言中，const修饰的是一个冒牌货，叫做只读变量，不是真正意义上的常量，可以通过指针间接赋值对其修改。**

在C++中的情况，代码如下

```c++
#include<stdio.h>
#include<iostream>
using namespace std;

int main(void){
   const int a = 10; //符号表,键值对的存储
   int *p = (int *)&a;//&,此时另外分配了内存空间,时机:编译器在编译期间;
   
   //C++语言中const是一个真正的常量
   *p = 20; //间接赋值
   printf("a = %d\n", a);
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvhrjWQErOj3WlZBykHmnOjXdLD397mabudiaVWvDaNfEic6mmiaovKeFVu6s610gCXQw9H0V5ojfQFw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**C++中的const所修饰的是真正的常量，在对其进行&运算时，将会开辟另外的内存空间。**

## 六、说明

原创文章链接：[C 语言中的一些不足](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483665&idx=1&sn=d0f838ba51686bbdde5a9c9c51c54a76&chksm=f94c8b2cce3b023a1a4d2c879d54f762752f9d4979db704d4c93ba860f0df78aef771ef93565&scene=21#wechat_redirect)
