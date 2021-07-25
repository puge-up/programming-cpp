- [一、共享性智能指针(shared_ptr)](#一共享性智能指针shared_ptr)
- [二、怎么使用shared_ptr](#二怎么使用shared_ptr)
- [三、框架的搭建](#三框架的搭建)
- [四、说明](#四说明)

## 一、共享性智能指针(shared_ptr)

引用计数型指针：shared_ptr是一个最像指针的“智能指针”，是boost.smart_ptr库中最有价值，最重要，也是最有用的。

**shared_ptr实现的是引用技术型的智能指针，可以被拷贝和赋值，在任意地方共享它，当没有代码使用(此时引用计数为0)它才删除被动态分配的对象。shared_ptr也可以被安全的放到标准容器中；**

## 二、怎么使用shared_ptr

举一个操作的例子：

```cpp
#include<iostream>
#include<boost/smart_ptr.hpp>
using namespace std;
using namespace boost;

int main(void){
    int *p = new int(10);
    shared_ptr<int> ps(p);
//    cout<<*ps<<endl;

    cout<<ps.unique()<<endl; //判断对空间是否唯一，
    cout<<ps.use_count()<<endl;
    shared_ptr<int> ps1 = ps;
    cout<<ps.unique()<<endl; //此时有两个对空间有共享，所以不唯一，是0
    cout<<ps.use_count()<<endl;
    shared_ptr<int> ps2;
    ps2 = ps1;
    cout<<ps.use_count()<<endl;
}
```

关键在shared_ptr中存在共享引用计数。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcjZWU5kP4ricts1BxZPq1eGSZDC4KtONqx88czpaoI5RuicsFIM1G0BIA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、框架的搭建

阅读源代码：

shared_ptr 中的私有数据成员：

```cpp
private:
    T *px;
    shared_count pn; //对象成员，肯定先调这个对象的构造函数；
```

**之前的引用计数通过一个指针，现在的引用计数通过一个对象，pn
构造函数的调用顺序：先虚基类，父类，对象成员，最后构造自己；**

此时的模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcv343JN8D8xibrfYOQ8dfwqicjZINXtJkdHPSly9zPGmejRaKYuwj7Llw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

其后调用对象成员的构造函数：

shared_counted中的私有数据成员：

```cpp
private:
    sp_counted_base *pi; //有一个指向引用计数器父类的指针；
```

此时就得先写：sp_counted_base类了；

sp_counted_base类中的私有数据成员：

```cpp
private:
    long use_count_;
```

然后看到在shared_counted的构造函数：

```cpp
public:
    template<class T>  //此时类型不定，写模板函数
        shared_count(T *p) : pi(new sp_counted_impl_xx(p)){ //特别重要，这个构造函数
```

此时就得写sp_counted_impl_xx类了：这是继承sp_counted_base类

其内部数据时成员：

```cpp
private:
    T *px_;
```

此时整体的建构体系就已经形成：

我认为是这样的：

1. 先实现了shared_ptr类，因为有对象成员，其后调用构造函数；
2. 实现了shared_count; 其数据成员有sp_counted_base；
3. 因为编译器的顺序，先类名，在数据成员，最后函数，所以此时先实现sp_counted_base;
4. 因为shared_counted中的构造函数要在堆上开辟sp_counted_impl_xx空间，最后实现是sp_counted_impl_xx，它有继承sp_counted_base,所以构造函数的调用顺序就很清楚了。

构造函数的调用顺序：sp_counted_base、sp_counted_impl_xx、shared_count、shared_ptr。

此时的具体实现代码如下：

```cpp
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include<iostream>
using namespace std;

#endif
////////////////////////////////////////////////////////////////////////////
#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_

#include"shared_count.h"

template<class T>
class shared_ptr{
public:
    shared_ptr(T *p = 0) : px(p), pn(p){
        cout<<"Create shared_ptr object!"<<endl;
    }
    ~shared_ptr(){
        cout<<"Free shared_ptr object"<<endl;
    }
private:
    T *px;
    shared_count pn;
};

#endif
///////////////////////////////////////////////////////////////////////////////
#ifndef _SHARED_COUNT_H_
#define _SHARED_COUNT_H_

#include"config.h"
#include"sp_counted_base.h"
#include"sp_counted_impl_xx.h"

class shared_count{
public:
    template<class T>  //此时类型不定，写模板函数
        shared_count(T *p) : pi(new sp_counted_impl_xx<T>(p)){
        cout<<"Create shared_cout object!"<<endl;
    }
    ~shared_count(){
        cout<<"Free shared_count object"<<endl;
    }
private:
    sp_counted_base *pi;
};


#endif
///////////////////////////////////////////////////////////////////////////////
#ifndef SP_COUNTED_BASE_H_
#define SP_COUNTED_BASE_H_

#include"config.h"

class sp_counted_base{
public:
    sp_counted_base() : use_count_(1){
        cout<<"Create sp_counted_base object"<<endl;
    }
    ~sp_counted_base(){
        cout<<"Free sp_counted_base object"<<endl;
    }
private:
    long use_count_;
};

#endif
//////////////////////////////////////////////////////////////////////////////////////
#ifndef SP_COUNTED_IMPL_XX_H_
#define SP_COUNTED_IMPL_XX_H_

#include"sp_counted_base.h"

template<class T>
class sp_counted_impl_xx : public sp_counted_base{
public:
    sp_counted_impl_xx(T *p) : px_(p){
        cout<<"Create sp_counted_impl_xx object"<<endl;
    }
    ~sp_counted_impl_xx(){
        cout<<"Free sp_counted_impl_xx object"<<endl;
    }
private:
    T *px_;
};

#endif
//////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include"shared_ptr.h"
using namespace std;

int main(void){
    int *p = new int(10);
    shared_ptr<int> ps(p);   
}

```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTc8UtrIjpUZvia97YdBpZJBKhmVU6yRrt4Ix8nzib7xYvPgnuzIVFsBD9A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

以上就是只搭好了大致的框架，并没有考虑内存泄漏、析构的具体写法和其它函数的实现；

那么整个模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcaR9HiabG7Tic28LsPbJbmH7a2UQY2DRsFCxiaaqC5ibxTia2BOics35gtqiaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 四、说明

原创文章链接：[C++进阶系列之Boost库智能指针（5）---shared_ptr(上)](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483974&idx=1&sn=5ad0fa72c605e2c48511008bda167972&chksm=f94c887bce3b016da4a02880f3e28f31d0f0f23bc3869e5ed5a64c41ac4b2e410bd634759065&scene=21#wechat_redirect)
