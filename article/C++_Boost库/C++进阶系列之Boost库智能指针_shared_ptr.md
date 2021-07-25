- [一、shared_ptr中的px出现原因](#一shared_ptr中的px出现原因)
- [二、解决析构函数](#二解决析构函数)
- [三、拷贝构造和赋值语句](#三拷贝构造和赋值语句)
- [四、shared_ptr的模拟部分](#四shared_ptr的模拟部分)
- [五、删除器](#五删除器)
- [六、说明](#六说明)

## 一、shared_ptr中的px出现原因

方便对其数据空间的管理，取值和获取地址将极大的方便我们的操作。

## 二、解决析构函数

避免内存空间的泄漏。new出来的空间都没有释放掉！

释放拥有全靠的是引用计数。

```cpp
~shared_count(){ 
    if(pi){  //判断所指父类是否为空
        pi->release(); //释放new出来的对象和外部new出来的空间
    }
}
////////////////////////////////////////////////////////////////////////
public:
    virtual void dispose() = 0; //纯虚函数
    void release(){  //在sp_counted_base中
        if(--use_count_ == 0){ //判断use_count是否为0
            dispose();  //因为虚函数，所以子类中实现
            delete this; //先调用析构函数，在释放this指向的空间
        }    
    }
///////////////////////////////////////////////////////////////////////
public:
    void dispose(){
        delete px_; //释放外部new出来的空间
    }
```

因为要级联释放空间，所以sp_counted_base的析构函数必须是虚函数，才能先调用子类的析构，最后调用自己的析构函数。

结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcysyY6BMerY1v7ia1p7ODgzGIJ7rOFOUX02oK2zB4to1rlV8S0brK8PA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

use_count和unique函数的实现比较简单

## 三、拷贝构造和赋值语句

此时应当相当于浅拷贝，use_count加1即可！模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcgmML8oGib6Ria4GUN5fZibhHic7DqZzsicRekqztRUibm3rZe8obKn6keicbQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

此时应在shared_ptr和shared_count进行浅拷贝，并在shared_count中加入方法。

```cpp
    shared_count(shared_count const &r) : pi(r.pi){
        if(pi){
            pi->add_ref_copy(); //在父类中实现这个方法，只要让++use_count_即可！
        }
    }
```

赋值语句，关键调用swap函数，的认真思考，画画图就好理解多了(前面已经写过这个了)。

**这个赋值语句写的真的很好，既让use_count_加1，又可以让原先的空间符合情况的释放。**

```cpp
    shared_ptr<T>& operator=(shared_ptr<T> const &r){
        if(this != &r){
            this_type(r).swap(*this);//调用拷贝构造，先创建一个无名临时的对象，
        }                         //因为调用了拷贝构造，所以在shared_count中调用方法,
        return *this;             //会让use_count_加1的。
    }
//////////////////////////////////////////////////////////////////////////////////////
    void swap(shared_ptr<T> &other){
        std::swap(px, other.px); //指针的交换
        pn.swap(other.pn);
    }
```

## 四、shared_ptr的模拟部分

```cpp
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include<iostream>
using namespace std;

//#define DISPLAY

#endif
////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHARED_PTR_H_
#define _SHARED_PTR_H_

#include"shared_count.h"

template<class T>
class shared_ptr{
    typedef shared_ptr<T> this_type;
public:
    shared_ptr(T *p = 0) : px(p), pn(p){
#ifdef DISPLAY
        cout<<"Create shared_ptr object!"<<endl;
#endif
    }
    shared_ptr(shared_ptr<T> const &r) : px(r.px), pn(r.pn){}
    shared_ptr<T>& operator=(shared_ptr<T> const &r){
        if(this != &r){
            this_type(r).swap(*this);//调用拷贝构造，先创建一个无名临时的对象
        }
        return *this;
    }
    ~shared_ptr(){
#ifdef DISPLAY
        cout<<"Free shared_ptr object"<<endl;
#endif
    }
public:
    T& operator*()const{
        return *(get());
    }
    T* operator->()const{
        return get();
    }
    T* get()const{
        return px;
    }
public:
    long use_count()const{
        return pn.use_count();
    }
    bool unique()const{
        return pn.unique();
    }
    void reset(T *p){
        this_type(p).swap(*this);
    }
    void swap(shared_ptr<T> &other){
        std::swap(px, other.px); //指针的交换
        pn.swap(other.pn);
    }
private:
    T *px;
    shared_count pn;
};

#endif
////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHARED_COUNT_H_
#define _SHARED_COUNT_H_

#include"config.h"
#include"sp_counted_base.h"
#include"sp_counted_impl_xx.h"

class shared_count{
public:
    template<class T>  //此时类型不定，写模板函数
        shared_count(T *p) : pi(new sp_counted_impl_xx<T>(p)){
#ifdef DISPLAY
        cout<<"Create shared_cout object!"<<endl;
#endif
    }
    shared_count(shared_count const &r) : pi(r.pi){
        if(pi){
            pi->add_ref_copy();
        }
    }
    ~shared_count(){
#ifdef DISPLAY
        cout<<"Free shared_count object"<<endl;
#endif
        if(pi){
            pi->release();
        }
    }
public:
    long use_count()const{
        return pi != 0 ? pi->use_count() : 0;
    }
    bool unique()const{
        return use_count() == 1;
    }
    void swap(shared_count &r){
        sp_counted_base *tmp = r.pi;
        r.pi = pi;
        pi = tmp;
    }
private:
    sp_counted_base *pi;
};

#endif
//////////////////////////////////////////////////////////////////////////////
#ifndef SP_COUNTED_BASE_H_
#define SP_COUNTED_BASE_H_

#include"config.h"

class sp_counted_base{  //抽象类
public:
    sp_counted_base() : use_count_(1){
#ifdef DISPLAY
        cout<<"Create sp_counted_base object"<<endl;
#endif
    }
    virtual ~sp_counted_base(){
#ifdef DISPLAY
        cout<<"Free sp_counted_base object"<<endl;
#endif
    }
public:
    virtual void dispose() = 0; //纯虚函数
    void release(){
        if(--use_count_ == 0){
            dispose();
            delete this;
        }    
    }
public:
    long use_count()const{
        return use_count_;
    }
    void add_ref_copy(){
        ++use_count_;
    }
private:
    long use_count_;
};

#endif
/////////////////////////////////////////////////////////////////////////////////////
#ifndef SP_COUNTED_IMPL_XX_H_
#define SP_COUNTED_IMPL_XX_H_

#include"sp_counted_base.h"

template<class T>
class sp_counted_impl_xx : public sp_counted_base{
public:
    sp_counted_impl_xx(T *p) : px_(p){
#ifdef DISPLAY
        cout<<"Create sp_counted_impl_xx object"<<endl;
#endif
    }
    ~sp_counted_impl_xx(){
#ifdef DISPLAY
        cout<<"Free sp_counted_impl_xx object"<<endl;
#endif
    }
public:
    void dispose(){
        delete px_;
    }
private:
    T *px_;
};

#endif
////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include"shared_ptr.h"
using namespace std;

int main(void){
    int *p = new int(10);
    shared_ptr<int> ps(p);

    cout<<ps.use_count()<<endl;
    cout<<ps.unique()<<endl;

    shared_ptr<int> ps1 = ps;
    cout<<ps.use_count()<<endl;
    cout<<ps.unique()<<endl;
    shared_ptr<int> ps2;
    ps2 = ps;
    cout<<ps.use_count()<<endl;
    cout<<ps.unique()<<endl;

    //cout<<*ps<<endl;
    
}

```

以上就是对shared_ptr的部分源码剖析的理解了。

## 五、删除器

删除器d可以是一个函数对象(是一个对象，但是使用起来像函数)，也可以是一个函数指针；

可以根据自己定义的方式去管理(释放)内存空间。有2个特性：函数对象 operator()进行了重载。

删除器的使用，调用系统的：

```cpp
#include<iostream>
#include<boost/smart_ptr.hpp>
using namespace std;
using namespace boost;

void My_Deleter(int *p){ //删除器
    cout<<"HaHa:"<<endl;
    delete p;
}
//靠删除器来管理空间，而不再向之前的调用析构函数。
int main(void){
    int *p = new int(10); //假设p是特殊的资源
    shared_ptr<int> ps(p, My_Deleter);
}
```

回过头来，对自己的空间进行释放，定义自定义的删除器。不采用默认方式释放，而是采用自己的方式释放！

删除器自己模拟部分代码：

```cpp
public:
    template<class Y, class D>
        shared_ptr(Y *p, D d) : px(p), pn(p, d){}//支持传递删除器
/////////////////////////////////////////////////////////////////////////////
    template<class Y, class D>
    shared_count(Y *p, D d) : pi(0){
        typedef Y* P;
        pi = new sp_counted_impl_pd<P, D>(p, d);
    }
///////////////////////////////////////////////////////////////////////////
template<class P, class D>
class sp_counted_impl_pd : public sp_counted_base{
public:
    sp_counted_impl_pd(P p, D d) : ptr(p), del(d){}
public:
    void dispose(){
        delete ptr;
    }
private:
    P ptr;
    D del;
};
//////////////////////////////////////////////////////////////////////////
#include<iostream>
#include"shared_ptr.h"
using namespace std;


void My_Deleter(int *p){ //删除器
    cout<<"HaHa:"<<endl;
    delete p;
}

int main(void){
    int *p = new int(10); 
    shared_ptr<int> ps(p, My_Deleter);
}

```

以上就是删除器实现的主要代码，是在shared_ptr中实现的。

## 六、说明

原创文章链接：[C++进阶系列之Boost库智能指针（6）---shared_ptr(下)](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483975&idx=1&sn=2fa59f6a75fdbefb18a156ecec16f4c1&chksm=f94c887ace3b016c45755dd29908c3ede957ecfdd1cc44863e2892f1c4a93b178cfd5882b926&scene=21#wechat_redirect)
