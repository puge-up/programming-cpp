- [一、VC版智能指针](#一vc版智能指针)
  - [1.1、赋值语句](#11赋值语句)
  - [1.2、release()函数](#12release函数)
- [二、标准的VS或Linux下的标准库](#二标准的vs或linux下的标准库)
- [三、说明](#三说明)

## 一、VC版智能指针

上次的对其auto_ptr内部结构的实现有些问题：

### 1.1、赋值语句

```cpp
 auto_ptr<_Ty>& operator=(const auto_ptr<_Ty> &_Y){
        if(this != &_Y){
            if(_Ptr != _Y._Ptr){
                if(_Owns)
                    delete _Ptr;
                _Owns = _Y._Owns;
            }
            else if(_Y._Owns){   //这个地方上次写错了,自己考虑的不周到，
                                 //应该判断其是否为真，真的赋值，假的话，不能，
                _Owns = _Y._Owns; //因为此时万一是下面主函数所写的，就会发生
            }                   //内存空间没人管理，内存泄漏！！！
            _Ptr = _Y.release();
        }
        return *this;
    }

    int main(void){
        int *p = new int(10);
        
        auto_ptr<int> pa(p);
        auto_ptr<int> pa1(pa);
        pa1 = pa;    //上面赋值语句防的就是这种情况，担心同一空间没人管理，导致没法释放！！！
    }
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbuYDzIIAcqN4oK0b0rH5qKKRibW8BC3rrhyoHsYiaiaZDfQiaQkuiabuHd7h8WLJkC3T9ou0fBC4VBPcDg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

### 1.2、release()函数

就是VC版的在release()函数中也可以转移彻底，程序如下：

```cpp
 _Ty* release()const{
         _Ty *tmp = _Ptr;  //先保留原有空间的地址
        ((auto_ptr<_Ty>*)this)->_Owns = false;
        ((auto_ptr<_Ty>*)this)->_Ptr = 0;  //此时拥有权已经转移的便不再对原有空间的访问。
        return tmp；
}
```

**上面是对自己上次写VC版auto_ptr的赋值语句的修改，上次考虑的情况不周，导致有可能发生内存泄漏！！！**

## 二、标准的VS或Linux下的标准库

1、库里面的函数主要是：reset、release、get、->、 * 、析构、多个赋值 拷贝构造。

**在这个里面对VC进行了改进，没有了所谓的拥有权，其转移的更彻底，消除了安全隐患。**

在VS下面不存在拥有权的管理问题，而只是只有一个私有数据：

```cpp
private：
    _Ty *_ptr;  //就是这一个指针进行管理其空间；
```

其加上头文件 #include memory ,在内部就已经实现好了之间的所有的操作；

```cpp
#include<iostream>
#include<memory>  //有这个头文件在，智能指针内部都已经实现好了对象之间的拷贝构造，
using namespace std;  //赋值语句，而不会造成内存空间的泄漏！！！

int main(void){
    int *p = new int(10);
    auto_ptr<int> pa(pa);
    
    auto_ptr<int> pa1 = pa; //其实现过程在头文件#include<memory>中均已实现；
}

```

2、模拟的部分源码如下：

```cpp
#include<iostream>
using namespace std;

template<class _Ty>
class auto_ptr{
public:
    auto_ptr(_Ty *p = 0) : _ptr(p){}
    auto_ptr(auto_ptr &t) : _ptr(t.release()){} //此时不能加const，因为要对其原有的指向赋值为空
    auto_ptr<_Ty>& operator=(auto_ptr<_Ty> &t){
        if(this != &t){
            reset(t.release());  //先释放自己，在设置其他的对象。
        }
        return *this;
    }
    ~auto_ptr(){
        if(_ptr){
            delete _ptr;
        }
    }
public:
    _Ty& operator*()const{
        return *(get());
    }
    _Ty* operator->()const{
        return get();
    }
    _Ty* get()const{
        return (_ptr);
    }
    _Ty* release(){ //没有拥有权，但是同时也可以达到对对象的控制，
        _Ty *tmp = _ptr; //通过对原先的指针赋空，将其交了出去，自己
        _ptr = 0; //便不再有所控制权了；
        return tmp;//此时释放函数彻底抛弃了拥有权。
    }
    void reset(_Ty *p = 0){
        if(p != _ptr && _ptr){  //这个判断至关重要，看是不是自己设置自己！
            delete _ptr;
        }   //这是重新设置的空间
        _ptr = p;
    }
private:
    _Ty *_ptr; //没有转移权，直接切断联系，断了安全隐患！
};

int main(void){
    int *p = new int(10);
    auto_ptr<int> pa(p);

    cout<<*pa<<endl;
    auto_ptr<int> pa1 = pa;
    auto_ptr<int> pa2;
    pa2 = pa1;
    return 0;
}

/*
int main(void){
    int *p = new int(10);
    auto_ptr<int> pa(p);
    pa.reset(pa);  //自己给自己设置，此时，若没有判断语句，自己把自己将干掉，
    在重新赋值没有任何作用。何来后续的访问呢？
    pa.reset(); //此时释放自己原有空间，并且赋值为空！

    上面get()函数还有其他的用法：
    从智能指针中要回自己的地址，
    int *x = pa.get();
    pa.release(); 此时，-ptr将为空，必须手动释放内存空间；

    delete x;
}
*/
```

3、没有拥有权如何管理，靠释放函数把指针赋空，为了编写赋值语句，用了一种更好的方案，重新设置的方案。

在源码中还有其他的函数，是为了解决：

```cpp
pa1 = auto_ptr<int>(new int(100));  //这种问题，临时对象只能是常对象，所以通过其他的方法解决const的问题。
```

在以后有机会会更深入的剖析，将其他函数一一弄清楚。

## 三、说明

原创文章链接：[C++进阶系列之Boost库智能指针（2）---VS/Linux版的auto_ptr](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483952&idx=1&sn=4ee7af37b02d33765d926d8e136dec37&chksm=f94c880dce3b011b11b922c1c9f63e6dec44245d7dcb92f12cb4d2cd974eee59a4fd5396e59a&scene=21#wechat_redirect)
