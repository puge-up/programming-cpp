- [一、C++实例化对象](#一c实例化对象)
- [二、this指针使用时机](#二this指针使用时机)
- [三、this指向当前对象的本质](#三this指向当前对象的本质)
- [四、说明](#四说明)

this 指针可以看出 C++ 底层的特性。

## 一、C++实例化对象

C++中在实例化对象之后

```cpp
class Test{};
```

用sizeof(Test)计算类的大小，可以知道只有数据成员的大小，并没有方法的大小，因为其数据各自保存，而成员方法共用一份。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtEtnf3S39BaUE4mT673tuEPlCdgVN7R3wXf8tZdCQB0dWrFExSlaVEuU9SibTWqPIh9dkZ0MKHriaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

那么每个对象在调用方法是怎么会知道是自己的数据成员呢？

## 二、this指针使用时机

this指针是由编译器所造，真实的隐藏在内部。

```cpp
#include<iostream>
using namespace std;

class Test{
public:
    void setData(int x){
        data = x;
    }
    int getData(){
        return data;
    }
private:
    int data;
};
int main(void){
    Test t1;
    int value;
    
    t1.setData(3);
    value = t1.getData();
    cout<<value<<endl;
    
    return 0;
}
```

以上的这个程序，其实内部就隐藏了this指针，万一函数如下呢：

```cpp
void setData(int data){
    data = data;
}
```

解决方案：

```cpp
void setData(int data){
    this->data = data;
}
```

此时this->data指的就是当前对象的data。

**this的使用时机：当参数名字和要赋值的数据成员同名时；使用this。**

## 三、this指向当前对象的本质

Ｃ++中编译器对类的编译顺序：

- 先识别类名；
- 在识别所有的数据成员(包括私有、公有、保护)；
- 识别方法，并且重写方法。

```cpp
void setData(int data){
    this->data = data;
}
...........

t1.setData(3);
```

上面的代码本质，有个隐藏的参数传递，其编译器改写的函数如下：

```cpp
t1.setData(3)---->  setData(&t1, 3);
void setData(Test *this, int data){}
```

相当于函数有一个隐式参数，但是程序不能那样写，必须写其对象调用的形式(知道本质，却不能写本质形式)，否则会报错。

**C++中就是通过这个this指向当前对象，从而区分了不同对象的数据成员；**

但问题远没有这么简单，再看下面的代码：

```cpp
void setData(int data){
  this = NULL;
  this->data = x;
}
```

此时代码将出现问题，万一不小心给this = NULL；此时将会报错，编译根本无法通过，但是，发明Ｃ++的人，不会让你给this赋值，这就的对this本质在此剖析：

怎样才能不更改this的值呢？改写函数：

```cpp
t1.setData(3)---->  setData(&t1, 3);
void setData(Test * const this, int data){}
```

**这才是this的本质，其const修饰，为常量的，不可更改！**

**只要对象调用方法(普通方法)，必然会有隐式的函数改写，其this的本质一目了然！**

## 四、说明

原创文章链接：[C++从零入门学习系列（2）---this指针](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483850&idx=1&sn=bf51741e739b852f46702aa2e0b8079a&chksm=f94c8bf7ce3b02e14e4f5a5999928718d99b6744a982ad9166e15e977726fdfc00280582d380&scene=21#wechat_redirect)
