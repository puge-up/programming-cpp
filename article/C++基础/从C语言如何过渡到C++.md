- [一、C++ 编译](#一c-编译)
- [二、C和C++的关系](#二c和c的关系)
- [三、C和C++的简单区别](#三c和c的简单区别)
- [四、C和C++的编译](#四c和c的编译)
- [五、C和C++的编程思想](#五c和c的编程思想)
- [六、在C++中对于多个完全相同函数](#六在c中对于多个完全相同函数)
  - [6.1、利用条件宏](#61利用条件宏)
  - [6.2、利用命名空间加以解决](#62利用命名空间加以解决)
- [七、说明](#七说明)

C 语言是面向过程（函数式编程），C++ 是面向对象（对象式编程），如何从面向过程的思维转化为面向对象的思维呢，从以下几点可以看出端倪！

## 一、C++ 编译

在C++中，一个程序通过g++的编译器的进行四步：

- 预处理  g++ tect.cpp -o test.i  -E
- 编译     g++ test.i -o test.s      -S
- 汇编     g++ test.s -o test.o     -c
- 链接     g++ test.o -o test
- 其后执行语句: ./test

## 二、C和C++的关系

学习任何一门新的语言都必须对已学过的进行思考，找出异同点，方便学习新语言的特性。

C++的意思：C plus plus。

C++是完全兼容C语言的，其中很多特性都能体现出来。

C：.c stdio.h printf scanf 函数无重载，且结构体不能为空 过程。

C++：.cpp iostream(引入命名空间) cout cin 有重载，且类可以为空 强调的是对象。

C程序：

```c
#include<stdio.h>                 

void main(void)
{
    int i = 10;
    printf("i = %d\n", i);
}

```

C++程序：

```cpp
#include<iostream>
using namespace std;

int main(void)
{
    int i = 10;
    cout<<i<<endl;
}
```

C++的输出不强调输出的格式，由编译器自动识别，以endl回车换行。

## 三、C和C++的简单区别

1. 建立的文件类型不一样，C语言为.c, C++为.cpp
2. 引入的头文件不一样
3. C++有命名空间
4. 输入输出的语句不一样
5. C语言不允许重载，C++可以进行重载
6. 自定义类型不一样，C语言使用struct，C++使用class
7. C++语言有逻辑数据类型bool

## 四、C和C++的编译

- C语言的变量必须放到：所有有效语句之前；
- C++语言在何时用到变量，在定义，比较符合人文化。

## 五、C和C++的编程思想

C function 函数 + 算法：**编程强调的是实现的过程。**

C++ 因为其完全兼容C，其定义变量并不像java一样，全部都是对象，int i;这只是普通的变量，所以C++是一门**基于面向对象**的语言。

对象+对象+.................+算法

**谈C++一切都要用对象，编程强调的是对象怎么了，一切围绕对象；**

## 六、在C++中对于多个完全相同函数

### 6.1、利用条件宏

```c
#define   AAA

#ifdef    AAA
    void fun(){}
#else
    void fun(){}
#endif
```

### 6.2、利用命名空间加以解决

```c
#include<iostream>
using namespace std;
namespace MySpace{
  void fun(){
   cout<<"This MySpace"<<endl;
  }
};
namespace YouSpace{
  void fun(){
   cout<<"This YouSpace"<<endl;
  }
};

using namespace MySpace;
int main(void){
  fun();
  return 0;
}
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvFZPwZ0oTuE1nrUGZXoiaCY1VuAicR8QAhQqsDxFPxibCzZe9DXCUBRCXyKmkFIvfcVbkhrEic3yGhaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(左神算法课程)</p>

这就是通过命名空间解决了函数一样的调用问题，当然，命名空间的本质及用法对自己刚接触Ｃ++，还不是很清楚。

**如果在文件iostream中没有引入命名空间，就得由我们自己手工写std;**

```cpp
std::cout<<"namespace std"<<std::endl;
```

## 七、说明

原创文章链接：[从C语言如何过渡到C++](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483838&idx=1&sn=b064d0f842e28bf67c06b785aa4b958e&chksm=f94c8b83ce3b0295c9db6a14af2a7a9fce58869c343b82da7270545c9c2387f70c091bc35661&scene=21#wechat_redirect)
