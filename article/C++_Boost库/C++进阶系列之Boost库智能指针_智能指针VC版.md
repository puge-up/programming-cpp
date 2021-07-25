- [一、智能指针](#一智能指针)
- [二、VC版的智能指针->auto_ptr](#二vc版的智能指针-auto_ptr)
- [三、总结](#三总结)
- [四、说明](#四说明)

## 一、智能指针

- VC版 Linux下的 STL 2 种智能指针。
- boost库下的：scoped_ptr、scoped_array、shared_ptr、shared_array、weak_ptr、instrusive_ptr 6种智能指针；

boost库下是极大的充裕了标准C++下的内存管理问题，尤其是数组，写时拷贝等得到了极大的补充；

那么智能指针的含义是什么呢？

**智能：将所申请到的空间交由一个对象去管理，预防程序中出现异常或者由于自己忘记释放所申请的空间，造成内存泄漏的问题。**

**指针：通过对*和->的重载，使其对象具有指针的特性；**

## 二、VC版的智能指针->auto_ptr

1、通过引入头文件 memory

```cpp
#include<iostream>
#include<stdio.h>
#include<memory>  //在VC下调用智能指针管理空间所必须的头文件;
using namespace std;

int main(){
    int *p = new int(10);
    auto_ptr<int> pa(p);//新开辟空间的地址交由pa对象去管理,在对象消亡时，调用析构函数释放空间;将不会发生内存泄漏;
    return 0;           //因为将开辟出来的空间交由对象去管理，在最后析构时其内部必有delete，去释放空间;
}
```

auto_ptr的内部具体实现过程是怎样的呢？

其私有数据的成员有：

```cpp
class auto_ptr{
public:
    ......  //构造函数在此都一一赋值了；
private:
    bool _Owns;  //空间所有权的管理者，为1释放空间;
    _Ty *_Ptr;   //保存所开辟空间的地址;
};
int main(){
    int *p = new int(10); //通过new开辟一个×××空间;
    auto_ptr<int> pa(p);  //将空间的地址交由pa对象来管理;
    cout<<*pa<<endl;
}
```

此时的模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbuYDzIIAcqN4oK0b0rH5qKKbTTFbGdlTga576XHMUHAHV86AV3klGHT7nFb9D9OChe0jq6CkZv7JA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

其后就是根据源码写的智能指针的整个过程并进行剖析：

```cpp
#include<iostream>
using namespace std;

template<class _Ty>   //所管理的空间类型不定，所以用模板
class auto_ptr{       //VC下的空间管理交由auto_ptr这种类进行处理
public:
    auto_ptr(_Ty *_P=0) : _Owns(_P!=0),_Ptr(_P){}  //构造函数，当申请空间成功时，_Owns为1，_ptr也指向那个空间；
    auto_ptr(const auto_ptr<_Ty> &_Y):_Owns(_Y._Owns),_Ptr(_Y.release()){}//拷贝构造函数，进行了拥有权的转移；
    auto_ptr<_Ty>& operator=(const auto_ptr<_Ty> &_Y){  //赋值语句是关键,抓住那4步：
        if(this != &_Y){  //1、判断自己是否给自己赋值
            if(_Ptr != _Y._Ptr){  //赋值的地址不相等
                if(_Owns)   //要赋的先判断是否为1
                    delete _Ptr;  //释放原先空间
            }
            _Owns = _Y._Owns;    
            _Ptr = _Y.release(); //拥有权的转移；
        }
        return *this;
    }
    ~auto_ptr(){
        if(_Owns)
            delete _Ptr;
    }
public:
    _Ty& operator*(){ //对*进行了运算符重载,
        return *_Ptr;  //返回其空间中的内容
    }
    _Ty* operator->(){ //对->进行了运算符重载,
        return _Ptr;   ////返回其空间的地址
    }
    //_Ty* release(const auto_ptr<_Ty> *const this)  //其改写后的函数本质
    _Ty* release()const{   //这个函数时进行拥有权的转移；
        ((auto_ptr<_Ty>*)this)->_Owns = false; //因为const常量，不能更改，所以通过强制类型转换对其进行更改；
        //_Owns = false;
        return _Ptr;  //返回这个地址
    }
private:
    //mutable bool _Owns;
    bool _Owns;
    _Ty *_Ptr;
};

int main(){
    int *p = new int(10); //开辟了一个×××空间，交给了p;
    auto_ptr<int> pa(p);  //将开辟出的空间地址交给了pa对象来管理；
    cout<<*pa<<endl;

    auto_ptr<int> pa1(pa); //此时拥有权的转移;空间交由pa1去管理，不关pa什么事了；

    auto_ptr<int> pa2;
    pa2 = pa1;  //拥有权在次转移给pa2对象，此时与前面的pa,pa1应该没有什么关系了；

    return 0;
}
```

对赋值语句的两种模型进行画图解释：

```cpp
_Ptr != _Y._Ptr;  //这种是空间不同下对象的管理赋值情况：
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbuYDzIIAcqN4oK0b0rH5qKK9I5ibaLejlicGPaiazCwWz9EzokT7iauo2uovhGGGibFw6YwibhCmvDzO2ug/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

```cpp
_Ptr == _Y._Ptr;//此时，只要进行拥有权的交换即可；

```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbuYDzIIAcqN4oK0b0rH5qKKUGtUqj3Lv2b6jgBVp9RtOMEeMfeoh6LEhZyRKfyRbibzh8ZL6DNcEyQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、总结

> **auto_ptr  本质：对象，但是用起来像指针(\* ->的重载)。**

> **RAII：将自动调用构造函数，在对象消亡时在自动的调用析构函数，只有这样才为智能指针的出现提供了可能。**

> **VC版的实现：拥有权的转移，_Owns(此成员起的作用)。**

> **缺点：在_Owns为1/0时(这个牵扯到释放空间)，\*pa对象都可访问，就是那个地址还保留着，转移的不彻底，存在安全隐患！！！**

以上就是我对VC下auto_ptr智能指针的认识了。

## 四、说明

原创文章链接：[C++进阶系列之Boost库智能指针（1）---智能指针VC版](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483945&idx=1&sn=87aa6b084c5272f62112e8c59590333a&chksm=f94c8814ce3b01023f0c7b8948c44fcd779ff213c966da491be94e6f763202b869c09b4d360c&scene=21#wechat_redirect)
