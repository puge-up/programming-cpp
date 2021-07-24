- [一、C++ 默认函数](#一c-默认函数)
- [二、深拷贝与浅拷贝](#二深拷贝与浅拷贝)
- [三、说明](#三说明)

这篇文章是 C++ 面试高频知识点，必须熟悉默认函数、深浅拷贝、赋值！

## 一、C++ 默认函数

**C++中什么都不写，就有6个默认函数，由系统自动提供：**
***构造函数，拷贝构造函数，赋值语句，析构函数，对一般对象的取地址符，对常对象的取地址重载；***

对&运算符的重载：

```cpp
Test t3;

Test *pt = &t3;

Test* operator&(){

    return this;
}
```

对常对象的取地址重载：

```cpp
const Test t4;

const Test *pt1 = &t4;



const Test* operator&()const{

    return this;
}
```

## 二、深拷贝与浅拷贝

```cpp
#include<iostream>
#include<string.h>
#include<malloc.h>
using namespace std;

class String{
public:
    String(const char *str = ""){
        if(str == NULL){
            data = new char;
            data[0] = 0;
        }else{
            data = new char[strlen(str) + 1];
            strcpy(data, str);
        }
    }
    ~String(){
        delete []data;
    }
private:
    char *data;
};

int main(void){
    String t1("abcdef");
    String t2 = t1;
    String t3("hello");
    t3 = t1;

    return 0;
}
```

运行结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgec73A8YtxWLtMRFY8UyVknBrJxAONPAN7PQHGEeFvXgibjjPx7teHlaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

可以知道，程序崩了，我们用的是系统默认的拷贝构造函数和赋值语句，此时只是各成员之间的赋值。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgeqhoE8NtPqmAnL2libRDbBUhmYIfy4njIP5cAbscOqxhefayELELUPew/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**两个对象通过默认的拷贝构造，成员data之间相互赋值，使得data不同，data的值相同，指向了同一空间；**

**此时在最后调用析构函数时，形成了对同一空间的多次释放，是错误操作！！！，这就是浅拷贝。**

**两个对象通过默认的赋值语句，成员data之间相互赋值，使得data不同，data的值相同，指向了同一空间，浅赋值。**

解决方案，此时应给自己写拷贝构造和赋值语句，达成深拷贝：

```cpp
String(const String &s){
    data = new char[strlen(s.data) + 1];
    strcpy(data, s.data);
}
String& operator=(const String &s){
    if(this != &s){
        delete []data;
        data = new char[strlen(s.data) + 1];
        strcpy(data, s.data);
    }

    return *this;
}
```

深拷贝和深赋值的意思：**就是重新申请空间，各自保存自己的，最后在自己释放自己的，保证了对内存访问的安全性；**

深赋值应当注意以下四步：

1. 判断自己是否给自己赋值；
2. **释放原有空间  //有可能在构造对象时，已经指向了某一空间，此时就得先释放，不然就内存泄漏；**
3. 申请空间进行赋值；
4. 返回引用空间。

## 三、说明

原创文章链接：[C++从零入门学习系列（5）---默认函数，深拷贝与浅拷贝，深赋值与浅赋值](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483882&idx=1&sn=b32b37caedfd49614907fda2ba12476b&chksm=f94c8bd7ce3b02c108f42e685ddc248deebdc6c6a6d0b40c03b7b48c7e88ab141e466a590c18&scene=21#wechat_redirect)
