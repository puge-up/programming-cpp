- [一、绑定器和取反器](#一绑定器和取反器)
- [二、代码实现](#二代码实现)
- [三、说明](#三说明)

## 一、绑定器和取反器

1. 绑定器：把二元函数对象中一个参数固定，使之转为一元函数，C++标准库中提供了2种预定义的binder适配器，bind1st、bind2nd，分别绑定了第一个/第二个参数；
2. 取反器：翻转的适配器；
3. 一元函数：只针对一个参数，只有一个返回值；二元函数：针对2个参数，只有一个返回值；
4. 绑定器针对的是参数，绑定后其值就不变了，取反器对其进行取反；
5. 可以通过调试工具-g；对源码进行剖析；

## 二、代码实现

关于绑定器和取反器的代码：

```cpp
#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

int main(void){
    int ar[] = {1,3,5,7,9,8,6,4,2,0};
    int n = sizeof(ar) / sizeof(int);
    int nCount = count(ar,ar+n, 4);//求数组中一共有多少个4
    cout<<nCount<<endl;
    //x <= 4;的个数
    nCount = count_if(ar, ar+sizeof(ar)/sizeof(int), bind2nd(greater<int>(), 4));//用的是第二个绑定器进行的绑定;;
    //4 < x
    //nCount = count_if(ar, ar+sizeof(ar)/sizeof(int), bind1st(less<int>(), 4));//用的是第一个绑定器进行的绑定;
    cout<<nCount<<endl;
    //对x < 4;进行取反,也就是x >= 4的个数;
    nCount = count_if(ar, ar+n, not1(bind2nd(less<int>(), 4)));//用的是取反器进行取反;
    cout<<nCount<<endl;


    return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvvNtDy1eOCdeqgelHzxrt6eUBn4ZHoV0SMlSSiaicmb39bOk9csicfibiatg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、说明

原创文章链接：[C++进阶系列之STL（4）---函数适配器](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484008&idx=1&sn=fb97ad8fe76fa88520fa6c2debb507b2&chksm=f94c8855ce3b01436d69e48755d940aa2f415b4b53c4e8ff6258a4a28ef9f05d1303e44dc07e&scene=21#wechat_redirect)
