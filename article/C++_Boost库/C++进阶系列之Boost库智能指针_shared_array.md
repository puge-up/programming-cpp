- [一、上次写的删除器有些问题](#一上次写的删除器有些问题)
- [二、shared_array](#二shared_array)
- [三、如何使用shared_array](#三如何使用shared_array)
- [四、shared_array](#四shared_array)
- [五、说明](#五说明)

## 一、上次写的删除器有些问题

```cpp
template<class P, class D>
class sp_counted_impl_pd : public sp_counted_base{
public:
    sp_counted_impl_pd(P p, D d) : ptr(p), del(d){}
public:
    void dispose(){
        del(ptr);  //就是这里，将对象用作函数！！！
    }
private:
    P ptr;
    D del;
};
```

**del(ptr)  -> del.operator()(ptr);重载了()的类使用起来就是函数对象。**

**删除器：函数对象和函数都可以充当。**

## 二、shared_array

它和shared_ptr类似，它包装了new[]操作符在堆上分配的动态数组，也是采用了引用计数的机制。

shared_array的接口和功能与shared_ptr几乎是相同的，主要区别：

1. 接受指针p必须是new []的结果
2. 提供operator[]的重载，可以使用下标
3. 系统没有提供*、->的重载
4. 析构函数使用delete  [];

## 三、如何使用shared_array

系统调用：

```cpp
#include<iostream>
#include<boost/smart_ptr.hpp>
using namespace std;
using namespace boost;

int main(void){
    int *p = new int[10];
    shared_array<int> pa(p);  //共享数组

    for(int i = 0; i < 10; i++){
        pa[i] = i+1;  //系统内进行了[]的重载
    }
    for(i = 0; i < 10; i++){
        cout<<pa[i]<<" ";
    }
    cout<<endl;

}
```

## 四、shared_array

模仿的源码如下：

```cpp
#ifndef _SHARED_ARRAY_H_
#define _SHARED_ARRAY_H_

#include"checked_delete.h"

template<class T>
class shared_array{
public:
    typedef checked_array_deleter<T> deleter;
    shared_array(T *p = 0) : px(p), pn(p, deleter()){} //无名对象
    ~shared_array(){
        
    }
public:
    T& operator[](int i)const{
        return px[i];
    }
private:
    T *px;
    shared_count pn;  //必须用到引用计数器对象
};

#endif
///////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CHECKED_DELETE_H_
#define _CHECKED_DELETE_H_

template<class T>
void checked_array_delete(T *x){
    delete []x;
}

template<class T>
struct checked_array_deleter{
public:
    void operator()(T *x)const{
        checked_array_delete(x);        
    }
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include"shared_ptr.h"
#include"shared_array.h"
using namespace std;
/*
template<class T>
void checked_array_delete(T *x){
    delete []x;
}

template<class T>
struct checked_array_deleter{
public:
    void operator()(T *x)const{
        checked_array_delete(x);
    }
};
写好()的重载之后，就是在shared_counted.h中释放空间时将用到。
del(ptr)  -> del.operator()(ptr);重载了()的类使用起来就是函数对象
删除器：函数对象和函数都可以充当。
*/
int main(void){
    int *p = new int[10];
    shared_array<int> pa(p);

    for(int i = 0; i < 10; i++){
        pa[i] = i+1;
    }
    for(i = 0; i < 10; i++){
        cout<<pa[i]<<" ";
    }
    cout<<endl;
}

```

缺点：

1. 重载使用[]时要小心，shared_array不提供数组的索引范围检查
2. 所管理的空间是死的，不能够自动增长。

## 五、说明

原创文章链接：[C++进阶系列之Boost库智能指针（7）---shared_array](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483976&idx=1&sn=003e92e049245a52413eed20380bef52&chksm=f94c8875ce3b016367baf90693e267cb82d844ed0273d03f1338b2efe9544f08402f0ece84dd&scene=21#wechat_redirect)
