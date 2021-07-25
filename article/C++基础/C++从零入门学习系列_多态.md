- [一、内存模型](#一内存模型)
- [二、虚函数](#二虚函数)
- [三、多态](#三多态)
- [四、虚函数剖析](#四虚函数剖析)
- [五、多态的原理](#五多态的原理)
- [六、多继承中虚表的画法](#六多继承中虚表的画法)
- [七、纯虚函数与抽象类](#七纯虚函数与抽象类)
- [八、说明](#八说明)

## 一、内存模型

当定义一个子类对象时，该子类就会有相应的内存情况，此时就是内存模型；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4B4u60niaopmL4NxbOrhS0zRQ8UgDJq5TB3Bqwicf5FsfmCnVpTz1V6BA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、虚函数

虚函数是一个类的成员函数，其定义格式如下：virtual 返回值类型 函数名(参数表)；

关键字virtual指明该成员函数为虚函数。

```cpp
class Test{
public：
    virtual void fun(){}   //虚函数
}；
```

## 三、多态

1. **必须在继承体系中；**
2. **父类中存在的成员函数为虚函数的(virtual)；**
3. **子类必须达到三同(返回值 函数名 参数列表)**
4. **必须通过父类型的指针/引用来调用；**
5. **两个类外；**

1、父类的成员函数返回值为 Base*

子类的成员函数返回值为 D* 此时，打破三同，仍为覆盖！！！

2、**父类的析构函数一般都要加上(virtual)，就可以利用多态性级联的调用析构函数，此时先调用子类的，在调用父类的；(以免发生内存泄漏)！！！**

## 四、虚函数剖析

1、当在类中出现一个(virtual)，虚方法时，对象中第一个成员将是：_vptr;

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4h4kDG2rsJriaH6ibgvNKT3k8LibllM9CllesZPHbJTfF5zwEDfdPnf9DA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

此时只有一个成员，应该为4B，但是其因为**有虚函数的存在，内部的第一个成员就一定为虚表指针；**

指针32位下为4字节，所以此时一共为8字节；**(不管内部有多少个虚函数，但是虚表指针只有一个)；**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4cLVYicicyhnrG1Dib6ZpQQGcAdPXhiauwHcdia6R09cI88n1huT4cAAG89w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2、虚函数将在继承体系中，一直为虚(覆盖时); 此时的virtual可以省略不写；

3、多态：就是对虚方法的重写；

4、**虚表：装虚函数的表，其本质是地址的覆盖；**

## 五、多态的原理

这是没有覆盖的虚表：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4oib691SVgO5IohqkbH5MH9v3ictC0QO8sngPyCs4djm8OG6KxHSztdicg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

假如子类有一个方法与父类的虚方法三同，此时覆盖；但是通过父类的指针/引用永远只能访问父类对象的部分；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4rYiaAEIgIY82icFfMSUFkwsw4C2dXAIuB9ibLic8SCyHoNxJg8w7eAS4pw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

如何取得虚表中的函数呢？

```cpp
Base b;
cout<<&b<<endl;   //对象的地址
printf("%p\n", *(int *)(&b));  //虚表中虚表指针的值(指针4字节)，所以转换×××指针，也就是虚表指针的地址；
((Fun)*((int*)*(int*)(&b) + 0))();  //Fun是函数指针，将获得虚表中的第一个函数;
((Fun)*((int*)*(int*)(&b) + 1))();  //Fun是函数指针，将获得虚表中的第二个函数;
((Fun)*((int*)*(int*)(&b) + 2))();  //Fun是函数指针，将获得虚表中的第三个函数;
```

## 六、多继承中虚表的画法

父类均为虚函数，子类中也有虚函数，且没有进行覆盖，**则将子类的放到第一个虚表的最后，其余的父类虚表就不用放了；**

因为就是放了，通过父类的指针/引用也访问不了，浪费内存空间；要是有覆盖的，则每个虚表都得画出；其余情况类似分析就行。

## 七、纯虚函数与抽象类

```cpp
#include<iostream>
using namespace std;

class Test{
public:
    virtual void fun() = 0;  //这种形式就是存虚函数，赋值为0；
    virtual void fun1() = 0;
    virtual void fun2() = 0;
    virtual void fun3() = 0;
};

int main(void){
    return 0;
}
```

以上的类中都为纯虚函数的类叫做抽象类; 抽象类不能实例化；也就是不能定义对象；

**继承抽象类的，必须实现其所有方法，不然自己继承下来依旧是抽象类，不能实例化对象。**

## 八、说明

原创文章链接：[C++从零入门学习系列（16）---多态](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483939&idx=1&sn=5ecc943e9d7abe424d87ecaac5af783e&chksm=f94c881ece3b010819958f429a43a22335185e680a61fd66c0df593643addcce1a6b2352f127&scene=21#wechat_redirect)
