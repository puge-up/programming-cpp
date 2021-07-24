- [一、C++中的const](#一c中的const)
- [二、引用的本质](#二引用的本质)
- [三、C++的内联函数](#三c的内联函数)
- [四、 C++中的默认参数](#四-c中的默认参数)
- [五、占位参数和默认参数](#五占位参数和默认参数)
- [六、说明](#六说明)

## 一、C++中的const

1、**C++中的const是真正的常量，可以进行数组大小的定义；**

代码如下：

```cpp
#include<iostream>
using namespace std;

#define A 10

int main(void){
    int a = 10; 
    int array[a]; //Linux内核支持这样定义数组,其他的编译器不支持

    const int a = 10;  //这里是常量,所以可以进行下面的数组大小的确定；
    int array[a]; //任何平台都是对的,const编译时,执行;

    return 0;
}
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwWBcnqMzQXqPbRdaQwiaDGbUiaCKsDhYWtcdpMibyZCRwNqntDW6fNypRg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2、**C++中常引用时，必定开辟了新的内存空间；**

代码如下：

```cpp
#include<iostream>
using namespace std;

int main(void){
    //int &b = 10; //普通引用,引用一个常量,常量没有内存地址,引用就是给内存取多个别名;

    const int &b = 10; //C++编译器会为其分配内存空间;
}
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwQBPWmKXufewFGJFZVS4J7ETHYZvhoTpRzFYAVLynibnOUH8uJTtEiclw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

3、const在函数后面修饰的本质：void fun(int a) const;

本质：void fun(const Teacher * const this, int a){}，**就是修饰的是*this；**

## 二、引用的本质

引用的本质：**引用在C++中的内部实现是一个常指针;C++编译器帮我们程序员取了一个地址；**

```cpp
Type &name <===> Type * const name; 
```

代码如下：

```cpp
#include<iostream>
using namespace std;

struct Teacher{
    char name[64];
    int age;
    int &a; //很像指针所占用的内存空间大小;
    int &b; 
};
//普通引用占内存空间,和指针所占空间大小是一样的;

//引用的本质:引用在C++中的内部实现是一个常指针;C++编译器帮我们程序员取了一个地址;
//          Type &name <===> Type * const name;
int main(void){
    cout<<sizeof(Teacher)<<endl;

    return 0;
}
//一般int返回,返回的是变量的值;
//一般int &,引用返回的是变量本身;函数可放左边/右边;
//用引用作为返回值的话,其返回的空间不能是临时空间;
//g2() = 100;  可以作为左值,因为引用返回的是一段连续的存储空间,是变量;
//函数作左值,必须返回一个引用;
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwjQ8OXQmvbCppY9ScCwGOGxBPJ1cdo15yChJrcqmzpicx1wiaFWOWdWag/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**原因：因为我用的是64位的，所以指针8字节，还有字节对齐，是其中最大基础数据类型字节的整数倍，此处应该为8的整数倍；**

## 三、C++的内联函数

1. 内联函数必须和函数体的实现写在一块;
2. 内联函数直接将函数体插入在函数调用的地方;
3. 内联函数速度更快,没有压栈,调转,返回等额外开销;
4. 内联函数中不能有循环语句,不能存在过多的条件判断语句;
5. 内联函数只是一种请求,C++编译器不一定允许这种请求;

代码如下：

```cpp
#include<iostream>
using namespace std;

inline void printA(){   //内联函数让C++做特殊处理;
    int a = 10; 
    cout<<"a = "<<a<<endl;
}

//内联函数替代宏代码片段; inline
int main(void){
    printA();

    return 0;
}

```

## 四、 C++中的默认参数

代码如下

```cpp
#include<iostream>
using namespace std;

//没传参数,就使用默认参数;
int printfA(int a = 1){ 
    cout<<a<<endl;
}
int printfA_1(int a, int b, int c = 1){}

//C++中允许函数有默认参数
//默认参数规则：从左边开始,如果默认参数出现,那么接下来的(右边)都必须是默认参数;
int printA_2(int a = 1, int b = 2, int c){}

int main(void){
    printfA();

    return 0;
}

```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwuibZBoKtJOnujSn9FOxibK6sMeGxlxgfGWCzNWYbTqQ7CzJcJy0I61nw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**默认参数规则：从左边开始,如果默认参数出现,那么接下来的(右边)都必须是默认参数，否则报错！！**

## 五、占位参数和默认参数

代码如下：

```cpp
#include<iostream>
using namespace std;

//函数占位参数：函数调用时,必须写够参数;
void func1(int a, int b, int){
    cout<<"a "<<a<<" b "<<b<<endl;
    
}

//默认参数和占位参数
//目的：为以后的程序留下扩展;

void func2(int a, int b, int = 0){  //这个函数既是默认参数，也是占位参数;
    cout<<"a "<<a<<" b "<<b<<endl;
}

int main(void){
    //func1(1, 2); 占位参数此时必须为3个,所以错误;
    //func1(1, 2, 3); 对
    func2(1, 2); //占位和默认参数，2/3个参数都是可以的;
    func2(1, 2, 3);//此时第3个参数没有什么意思,不能使用;

    return 0;
}
```

## 六、说明

原创文章链接：[C++从零入门学习系列（11）---const,引用本质,内联,默认/占位参数](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483911&idx=1&sn=2405efc5ca74a85fcd0cedca98019332&chksm=f94c883ace3b012cb6a9df7e1b3c6982260bc6a4cc70eb3b3f53c98efdefc3dde2089bea317b&scene=21#wechat_redirect)
