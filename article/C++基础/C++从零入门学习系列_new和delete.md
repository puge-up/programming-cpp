- [一、内存分配](#一内存分配)
- [二、new和delete](#二new和delete)
- [三、delete](#三delete)
- [四、new的三种形式](#四new的三种形式)
  - [4.1、new operator](#41new-operator)
  - [4.2、operator new](#42operator-new)
  - [4.3、placement new](#43placement-new)
- [五、说明](#五说明)

## 一、内存分配

我们定义对象时，Test t;  这是静态存储分配，由系统在栈空间给我们分配好了；

有些情况要求运行时分配，这就是动态存储分配，在堆中进行；

## 二、new和delete

在C++中用new和delete来对空间进行管理。

**new开辟空间返回值是一个指针。**

1. C语言中通过malloc来申请空间，不管变量还是数组都一样，通过字节来计算申请空间的大小。

```cpp
Ｃ++中的new不同；
int *a = new int;(变量)        
int *a = new int[10];(数组)  new开辟空间不考虑字节个数。
```

2. C++中申请空间时还能初始化。  int *a = new int(10);   但不能对申请数组空间进行初始化，所以必须有默认的构造函数；

3. 释放空间
   
```cpp
delete a;
delete []a;  //释放空间；[]中的数字可以不写，就是写多少都不影响。
```

原因如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvUpicST4hoNdib1OYf3nLyn31hwJ9jSy0yuwVLesjnicUKRN6X7eClkhJRYkw4B7DjChn4ZAeadXrOA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**在C++中申请的是数组空间，在释放时必须写上[], 不然delete a; 将会发生内存泄漏！！！**

4. C++中在进行new开辟空间时，做两件事，先申请空间，在调用构造函数。

delete也做两件事：先调用析构函数，在释放其所指向的空间。

## 三、delete

void *ps= new String("abc");

---
> delete ps;   如何评价？

> void，指针所指向的类型不定，所以在delete时，不调用析构函数，此时，将发生内存泄漏；

>只有指针所指向的空间类型定了，delete时才调用析构函数。  

>String *ps= new String("abc");

---

delete ps;   如何评价？

**此时整个过程：先开辟空间 -->再调构造函数.....调析构函数--->释放ps所指向的空间.**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvUpicST4hoNdib1OYf3nLyn3zpFickVD6EpeA6MiboC35X7qWl3vSVtRetLSAvuMMXLPfH5OezjmURsQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 四、new的三种形式

### 4.1、new operator

```cpp
operator new Constructor //先申请空间，在调用构造函数。(缺一不可)

delete operator：先调用析构函数，在释放其所指向的空间；(缺一不可)
```

### 4.2、operator new

我们可以改变如何分配内存，也就是开辟空间的过程。

new的重载：

1. 返回值必须为void*类型；
2. 第一个参数必须为size_t；

```cpp
    void* operator new(size_t sz){
        void *p = malloc(sz);
        return p;
    }
    void* operator new[](size_t sz){
        void *p = malloc(sz);   //重载，对数组申请空间
        return p;
    }
    ...........
    void operator delete(void *p){
        free(p);
    }
    void operator delete[](void *p){
        free(p);               //重载，对数组释放空间
    }
```

**重载了new，就必须重载delete，因为malloc开辟空间和free释放空间必须一一对应。**

**operator new只负责开辟空间，要是函数中有，调用离自己最近的(类内->全局->系统)。**

### 4.3、placement new

定位new  不开辟新的空间，对已有的空间进行赋值；

```cpp
new(p)int(10);   //p是一个地址，默认下标是0，10是要赋的值。
```

```cpp
#include<iostream>
using namespace std;

void* operator new(size_t sz, int *d, int pos){ //operator new 的重载
    return &d[pos];  //d + pos;
}

int main(void){
    int ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,};
    new(ar, 1)int(10); //定位new，不开辟新的空间。
                       //将10放到下标为0的地方；
    cout<<ar[1]<<endl;
    return 0;
}
```

结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvUpicST4hoNdib1OYf3nLyn36vq6bh5HjYFQlTvyVRpKkEEEZO3CrbHpol9icE9uqY1V3KRE0lA3THw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 五、说明

原创文章链接：[C++从零入门学习系列（14）---new和delete](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483929&idx=1&sn=81e84d9267d2d730b3a543dbf43b6640&chksm=f94c8824ce3b0132161f9f24944ea2eb2b816c4005cec1b1208384209542de52ffaf2d1452d8&scene=21#wechat_redirect)
