- [一、函数模板](#一函数模板)
- [二、类模板](#二类模板)
- [三、说明](#三说明)

## 一、函数模板

模板就是为了代码的复用，可以把数据类型设计为参数，由我们自定义类型进行传送；

```cpp
#include<iostream>
using namespace std;

template<typename Type>  //模板的声明，老的版本是class替换typename；
Type Max(Type a, Type b){
    return a > b ? a : b;
}

int main(void){ 
    cout<<Max('a', 'b')<<endl;   //求最大值
    cout<<Max(2, 5.45)<<endl;   //这会出错，因为类型不一样，没法转换。不会将double-->int,
                                //不会隐式转换的。
    return 0;
}
```

**模板不支持隐式转换，类型必须明确给出(强制类型转换)；函数模板效率并不高，只是将函数模板-->模板函数；**

上述出错的解决方案：
> cout<<Max(2, (int)5.45)<<endl; 或cout<<Max((double)2, 5.45);
>
> 或cout<<Max<int>(2, 5.45)<<endl; 指定int类型的比较；

```cpp
template<typename Type1, typename Type2>  
Type1 Max(Type1 a, Type2 b){
    return a > b ? a : b;
}
```

这样就可以对应传过去的数据类型；每个参数的类型一一对应，在自己根据情况写出返回值类型。

## 二、类模板

C++中的类一般都是模板类；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvUpicST4hoNdib1OYf3nLyn3mickTwMWcEJgZPNrQpO0Nf8EvKtXQPd6MxboSD5MqicZrdtOibMgybEVA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

模板类要注意的是：

1. 在类上面写上模板，友元函数类的声明，最上面也要写上模板；
2. 在类内声明，在类外实现时要加上模板，并且还得在作用域限定符前面加上数据类型<Type>；

模板的0初始化：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvUpicST4hoNdib1OYf3nLyn3NmT4c00U7J7l8cKbicjPUChQVaczJZRm40tqmkI4Q5b5s57E2lPIibIw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

以上这些可以说明语法是成立的；**Type t = Type();  这个就是模板的初始化，根据不同类型初始化为0；**

## 三、说明

原创文章链接：[C++从零入门学习系列（13）---函数模板、类模板](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483928&idx=1&sn=24737fe4b16873ad064dbfe9a73a3bae&chksm=f94c8825ce3b0133345dfcd47f168e3861f734c9d97227b100c5e07e8c3b1c23e20a8e2f6baf&scene=21#wechat_redirect)
