- [一、引用](#一引用)
- [二、拷贝构造函数](#二拷贝构造函数)
- [三、赋值语句](#三赋值语句)
- [四、函数的优化调用](#四函数的优化调用)
- [五、说明](#五说明)

C++ 方向的学习，一定是痛苦而又漫长的，基础知识必须牢固！

## 一、引用

C++中有一种新的数据类型，对已开辟空间在取一个名字；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgegVdP3dp3MqSPZll5eqyfZQ1To2jT0E0JlI20ibSGrW2YIvurqG1QPOQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(引用空间内存图)</p>

**就是别名，不开辟新的空间，没有空引用；**

```cpp
例：int &b; 错误；
```

交换两个数字用引用实现：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgeiaHVHQS8acMYnKvibL7woqgxt4p01fCJq0sLibJAzFTcWQDcLoT7DuL7A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(交换2数字)</p>

常见的几种引用形式：

1. 对变量引用：int a = 10; int &b = a;
2. 对指针引用：int *p = &a; int *&q = p;
3. 对数组引用：int ar[3] = {1, 2, 3,}; int (&b)[3] = ar;

此外还有以下类型的引用：

1. 常引用 const int x = 100;
   - int &y = x; 错的，非常量的不能引用常量，只有自己也加上const成为常量才可以引用。**常量只能常引用；**

2. int n = 20;
   - const int &m = n;   对的，常量引用非常量可以，因为你可以改变，我要求自己不能改变而已！**变量也可以常引用；**

3. const double d = 12.34;
   - const int &f = d;    对的，此时d和f由于不是同一种数据类型，所以地址不一样，此时f引用的不是真实的d，而是对产生的临时变量的引用(此时会把整数截取)；
4. double d = 12.34;
   - int &f = d;   错的，**临时变量一般都具备常量的性质**，我们往往在类型转换时所产生的中间临时变量具备常量的性质；所以要加const，对常量的引用；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgegAkyfziapJXlJ1ezcS8GvDzjGtPnpwXFEh15ELOhZ1tnB6uPmZDf2zQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**加上const后，常引用对常量，因为中间的临时变量都是常量(在类型转换时会产生中间的临时变量)；只要类型不同，就都会转换；**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgeP0ZeNjyTO8v9UaZdaBJA26vnF4cmoRkJjH6saOmSTpSV9KvWNI33sA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、拷贝构造函数

1、对象初始化对象，调用拷贝构造函数。

```cpp
Test(const Test &t){}
```

因为拷贝构造函数也是构造函数，所以和类名相同。const只是为了保护t不被更改；

&必须加上，因为 Test t(t1);此时相当于t1给t初始化，调用拷贝构造函数，将陷入无穷的递归当中，所以要使用引用；

2、拷贝构造函数系统会有默认的，按其成员进行拷贝！

3、 调用拷贝构造函数的三种场合: 

- 初始化对象时，Test t(t1); 和 Test t = t1;
- 形参实参传递时；
- 返回值为对象时，会创建一个无名的临时变量，(此时相当于对象给对象赋值),返回的是一个新的匿名对象。

## 三、赋值语句

赋值语句系统也有默认的，是各成员之间相互赋值。

```cpp
void operator=(const Test t);
```

赋值语句在对象赋值时调用，可以说是对=的重载；

此时const只是为了保护不被修改，t调用拷贝构造函数(对象给对象初始化赋值)，但是为了时间和空间的效率，此处用引用更好；

```cpp
void operator=(const Test &t);
```

此时不能连等赋值，t = t1 = t2;   这个的本质就是：t.operator=(t1.operator=(t2));所以的有返回值呀。


```cpp
Test& operator=(const Test &t){
  if(this != &t){
   data = t.data;
  }
    
  return *this;   
}
```

因为不是创建临时无名对象，所以可以引用返回；临时的不行，返回时空间就已经析构了。适用场合：Test t;  t = t1 =t2 = t3;(对象已经初始化过了，此时就叫做赋值)；

## 四、函数的优化调用

```cpp
#include<iostream>
using namespace std;
class Test{
public:
    Test(int d = 0) : data(d){
        cout<<"Create Test Object"<<this<<endl;
    }
    Test(const Test &t){
        cout<<"Copy Create Test Object"<<this<<endl;
        data = t.data;
    }
    Test& operator=(const Test &t){
        cout<<"Assign : "<<this<<endl;
        if(this != &t){
            data = t.data;
        }
        return *this;
    }
    ~Test(){
        cout<<"Free Test Object"<<endl;
    }
public:
    int GetData()const{
        return data;
    }
private:
    int data;
};
Test fun(Test x){
    int value = x.GetData();
    Test tmp(value);   //创建临时tmp对象，调用构造函数
    return tmp;        //返回值为对象，调用拷贝构造，借助中间桥梁返回；
}                      //立马先析构tmp和x临时对象，在进行赋值语句，最后析构其他对象；
int main(void){
    Test t1(100);     //创建对象t1，调用构造函数
    Test t2;          //创建对象t2，调用构造函数
    t2 = fun(t1);     //形参，实参传递，调用拷贝构造
    return 0;
}
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcge5kPqNk0Jp3VeGvAgWQPOJibnIfibrNew2v1FV2Hd0Mib0uNB35OjEnoicA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

优化以上的代码，使节省空间和时间：

```cpp
Test fun(Test &x){
    int value = x.GetData();
    return Test(value);  //创建临时无名对象，编译器直接认为：直接就是这个t2对象
}

int main(void){
    Test t1(100);      //创建对象t1
    Test t2 = fun(t1); //不用再调用赋值语句；

    return 0;
}
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgeCVfZPicdn43TTnQhZzjnB5ITE8dRfhnUCxsrewgsIIXTm8CQ973TZng/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

效率最低-->代码的优化。

## 五、说明

原创文章链接：[C++从零入门学习系列（4）---引用，拷贝构造，赋值语句](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483875&idx=1&sn=9e8e73abf129dde7857c5114be4a44b4&chksm=f94c8bdece3b02c8a57dd6af372068806fa1d2599050c06c18641067cc74d252c252015aeb57&scene=21#wechat_redirect)
