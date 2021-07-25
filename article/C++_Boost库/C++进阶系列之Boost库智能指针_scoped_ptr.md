- [一、VC和VS](#一vc和vs)
- [二、Boost库](#二boost库)
- [三、scoped_ptr(局部智能指针)](#三scoped_ptr局部智能指针)
  - [3.1、如何使用](#31如何使用)
  - [3.2、理解](#32理解)
- [四、scoped_ptr的内部实现过程](#四scoped_ptr的内部实现过程)
- [五、说明](#五说明)

## 一、VC和VS

VC版并不是标准C++，VS版符合标准C++，其语法相当严格。

**缺点：VC和VS都只能释放一个具体类型空间，不能对数组空间进行释放，还有写时拷贝的问题；**

所以引发了Boost库的出现来解决此类问题。

## 二、Boost库

推荐看一下Boost库完全开发指南。

Boost本身是开源库，在C++中的地位举足轻重，第三章内存管理，智能指针；

C++中也提供了智能指针，但是并不能解决所有问题。

smart_ptr库中：new delete的运用不正确，是C++中造成资源获取/释放问题的根源。

## 三、scoped_ptr(局部智能指针)

### 3.1、如何使用

**scoped_ptr是一个很类似auto_ptr的智能指针，但是scoped_ptr的所有权更加严格，不能转让，一旦scoped_ptr获取了对象的管理权，你就无法再从它那里取回来。**

平常的智能指针加上 memory 头文件，Boost库的搭建，就是拷到相应的目录下；然后编译，出错进去把该注释的都注释上。

```cpp
#include<iostream>
#include<string>
#include<boost/smart_ptr.hpp> //：在include目录下的boost目录下的smart_ptr.hpp;
using namespace std;                    //打开就是其它智能指针的声明；
using namespace boost;  //boost库必须引入的命名空间


int main(void){
    int *p = new int(10);

    scoped_ptr<int> ps(p);
    cout<<*ps<<endl;  //有了指针功能*运算符
    string *px = new string("hello");
    scoped_ptr<string> ps1(px);
    cout<<ps1->size()<<endl;//有了->，指针
}
```

### 3.2、理解

在库的引入下，确实具有智能指针的特性，必须加上。

```cpp
#include<boost/smart_ptr.hpp>  和  using namespace boost;，才具有智能指针的特性。
```

> **对比：VC和VS版的拷贝构造，赋值都没问题。**

> **scoped_ptr(局部智能指针)，对空间的管理权不能交由其它对象，不能进行拷贝构造和赋值。**

## 四、scoped_ptr的内部实现过程

**如何达到拥有权不能转移的目的，拷贝构造和赋值语句声明为私有的，不需要实现。**

模拟源码实现如下：

```cpp
#include<iostream>
using namespace std;                            

template<class T>
class scoped_ptr{
public:
    scoped_ptr(T *p = 0) : px(p){}
    ~scoped_ptr(){
        delete px;
    }
public:
    T& operator*()const{
        return *px;
    }
    T* operator->()const{
        return px;
    }
    T* get()const{
        return px;
    }/*
    void reset(T *p = 0){
        if(p != px && px){
            delete px;
        }
        px = p;
    }*/ //boost库中有一个更好的解决方案
    typedef scoped_ptr<T> this_type;
    void reset(T *p = 0){
        this_type(p).swap(*this); //无名临时对象技术
    }
    void swap(scoped_ptr &b){
        T *tmp = b.px;
        b.px = px;
        px = tmp;
    }
private: //不想让其拥有哪些功能，声明为私有即可。
    scoped_ptr(const scoped_ptr<T> &);//声明为私有，外部就无法进行拷贝构造了
    scoped_ptr& operator=(const scoped_ptr<T> &);//外部就调不动赋值语句了
    void operator==(scoped_ptr const &) const;  //对象不具有比较==
    void operator!=(scoped_ptr const &) const;  //对象不具有比较!=
    T *px;
};

class Test{
public:
    void fun(){
        cout<<"This is Test fun()"<<endl;
    }
};

int main(void){
    int *p = new int(10);

    scoped_ptr<int> ps(p);
    cout<<*ps<<endl;
    int *q = new int(20);
    ps.reset(q); //重新设置函数，将原有空间释放，重新管理一个空间

    
    scoped_ptr<Test> ps1(new Test);
    ps1->fun();
}
```

对reset()函数的理解：this_type(p).swap(*this);模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbuYDzIIAcqN4oK0b0rH5qKKUkLibs5IsVicib8X5bFkgFickib1WeVraFufZep2TrBhHaNME2mPjwZd1vw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

通过新生成的无名临时变量，将新地址与旧地址交换，在最后脱离函数范围，对象消亡，调用析构函数，释放原先空间，达到不内存泄漏，并且对新空间进行管理。

缺点：不能对数组空间进行管理。

## 五、说明

原创文章链接：[C++进阶系列之Boost库智能指针（3）---scoped_ptr](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483953&idx=1&sn=611b9d51b17f398c855fd171166bd627&chksm=f94c880cce3b011ae4939e069d35433e3210eb03b550f37079552925f20ed7fc56dc21613076&scene=21#wechat_redirect)
