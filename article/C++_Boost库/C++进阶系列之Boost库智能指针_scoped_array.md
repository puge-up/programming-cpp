- [一、scoped_array](#一scoped_array)
- [二、此类特点如下](#二此类特点如下)
- [三、怎么使用scoped_array](#三怎么使用scoped_array)
- [四、scoped_array源码的实现](#四scoped_array源码的实现)
- [五、说明](#五说明)

## 一、scoped_array

是专门对数组空间进行管理的。包装了new[]在堆上分配的动态数组；

scoped_array弥补了标准库中没有指向数组的智能指针的缺憾。

## 二、此类特点如下

1. 构造函数接受的指针p必须是new[]的结果，不能是new；
2. 没有*、->操作符的重载(库中不提供这些的重载，但是我们可以自己写)，因为scoped_array所持有的不是一个普通的指针；
3. **析构则必须用delete [];**
4. **提供operator[]的重载，可以像普通数组一样进行下标访问元素；**
5. 没有begin()、end()等类似容器的迭代器操作函数；

**scoped_array与scoped_ptr有相同的设计思想，也是局部智能指针，不能拷贝和赋值；**

## 三、怎么使用scoped_array

```cpp
#include<iostream>
#include<boost/smart_ptr.hpp> //内部实现好的，直接调用系统的。
using namespace std;
using namespace boost;  //这个命名空间必须要有。

int main(void){
    int *p = new int[10];  //申请数组空间
    scoped_array<int> ps(p); //交与智能指针管理

    for(int i = 0; i < 10; i++){
        ps[i] = i+1;  //可以进行下标操作
    }
    for(i = 0; i < 10; i++){
        cout<<ps[i]<<" ";
    }
    cout<<endl;
}
//拷贝构造和赋值都不可以。
```

## 四、scoped_array源码的实现

```cpp
#include<iostream>
using namespace std;

template<class T>
class scoped_array{
public:
    explicit scoped_array(T *p = 0) : px(p){} //预防隐式调用
    ~scoped_array(){
        delete []px;
    }
public:
    typedef scoped_array<T> this_type;
    void reset(T *p = 0){ //重置方法
        this_type.swap(*this);//无名临时对象
    }
    void swap(scoped_array &b){
        T *tmp = b.px;
        b.px = px;
        px = tmp;
    }
    T* get()const{
        return px;
    }
    T& operator[](int i)const{ //下标越界没有检测
        //return *(px+i);
        return px[i];
    }
    T& operator*()const{
        return px[0];
    }
    T* operator+(int i)const{
        return px+i;
    }

private:
    T *px;
    scoped_array(scoped_array const &);//放到私有中，外界无法调用
    scoped_array& operator=(scoped_array const &);
    
    void operator==(scoped_array const &)const;
    void operator!=(scoped_array const &)const;
};

int main(void){
    int *p = new int[10];
    scoped_array<int> ps(p);

    *ps = 2;

    for(int i = 0; i < 10; i++){
        ps[i] = i+1;
    }
    *(ps + 3) = 100; //利用 + ，*的运算符的重载即可以实现。
    for(i = 0; i < 10; i++){
        cout<<ps[i]<<" ";
    }
    cout<<endl;
}
```

库中没有提供*和+的重载。

scoped_array缺点：不能动态增长，没有迭代器支持，不能搭配STL算法，是纯粹的裸接口，不推荐使用。

## 五、说明

原创文章链接：[C++进阶系列之Boost库智能指针（4）---scoped_array](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483959&idx=1&sn=ecd9a65f52641fcac8f14bdfbfac463d&chksm=f94c880ace3b011c06ffef20951b914d98baa783525e34e82401e158a80c9288b985ead9e752&scene=21#wechat_redirect)
