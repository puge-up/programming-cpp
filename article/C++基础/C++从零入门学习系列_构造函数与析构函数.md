- [一、构造函数](#一构造函数)
- [二、构造函数的3个作用](#二构造函数的3个作用)
- [三、析构函数](#三析构函数)
- [四、说明](#四说明)

对于 C++ 的学习，先把基础概念弄明白，理解熟悉常见语法。

## 一、构造函数

在我们定义一个类后，对其实例化，值都是随机的，然后我们自己在写函数对其赋值，感觉是多余的，Ｃ++就提供了在实例化时就初始化的过程，就叫做构造函数。

构造函数是特殊的公有成员函数，有一下特点:

1. 构造函数与类名相同；
2. 构造函数不写返回值；
3. 在实例化对象时，自动 必须 一次调用；
4. 可以重载(人生而不平等，这样理解)；
5. 构造函数可以在类内定义，也可以在类外定义(通过作用域限定符::)
6. C++会自动的给出默认的构造函数，要是自己写了，就不会再提供默认的构造函数了；

```cpp
class Test{
public:
  Test(int d = 0) : data(d){}
```

这就是一个缺省的构造函数，存在时，不能再有无参的构造函数(不然是初始化为随机值还是默认值0)。

## 二、构造函数的3个作用

1. 构造对象，自动调用构造函数；
2. 初始化对象；
3. **类型转换。**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFIm1QWGicNtdl2jD3DwufxSuoT7C6ZpVxFZ3MVYLvBajx6iaTlk0ZwV3AQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

分析:t1是Test类型的，100是×××的；不同类型怎么能赋值呢?

**C C++都是强类型语言，如果类型不一样，从某种角度上说不许赋值；**

```cpp
int a;
double d = 12.34;

a = d;
```

**类型不一样，不可能直接赋值，的借助中间临时变量来赋值；**

现在来看 t = 100;

**100 必须的找到中间桥梁Test类型的，才能给Test类型的t赋值，里面是对应成员一一赋值；刚好有个构造函数，并且有一个参数，通过构造函数，把×××100转化为Test类型，此时实例化了一个对象，刚好转换为类型一致，可以赋值。**

此时还存在一个这样的问题：关键字 explicit  显示的，作用:

1. **预防构造函数被隐式调用；**
2. **只能在构造函数前使用此关键字；**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFI6MWLLw0vUe8MnWxElmDLf0ftz2Hj2x2vmEf1QYaiauRoTdwP6LMoHPw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

此时隐式赋值，不能调用显示构造函数，所以出错；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFIpI9ryctBbRKja2TQ7ALgXjY60XxiayBcwQib5PEdQKibhkCjJkxNt682Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

Test t = (Test)100;强制类型转换就是显示调用，explicit修饰的构造函数方可被调用！

现在看下面的问题：Test类型能否给int类型赋值？

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFIpI9ryctBbRKja2TQ7ALgXjY60XxiayBcwQib5PEdQKibhkCjJkxNt682Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

两边类型不一致，并且在类的内部没有找到转换相同类型Test->int类型的函数(也就是说没有找到中间桥梁)；所以出错！

必须的用到运算符重载(添加方法)，下面这个叫做类型转换，————>不能有返回值；

添加在类内一个方法：

```cpp
public:
    operator int(){
        return data;
    }
```

将Test类型转换为int，(有了这个方法就可以实现)，从而找到桥梁，类型一致便可赋值；**原理: 借助了中间的无名变量空间(充当桥梁)。**

结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtFCWgDY6bIreRADaib0FuFIEVvupvz5QVVaFmWlWkYp6ibVIu0HBv6hNZ8fYtGB6lIUTCPiaZmEZOIQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、析构函数

```cpp
~Test(){}
```

析构函数就是释放对象占用的空间，对任何函数死亡都是一样的，所以任何对象的析构只能用相同的方式进行。

**析构函数无重载，无参，无返回，只有一个(死是平等的)。**

特点：

1. 析构函数与类名相同，但在前面加上'~'，如：~Test(){}
2. **对象释放时，系统自动调用析构函数(可以是默认的)。**

## 四、说明

原创文章链接：[C++从零入门学习系列（3）---构造函数与析构函数](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483868&idx=1&sn=4e755a6a7bf9afc6590fcc49e8016c00&chksm=f94c8be1ce3b02f7bc0a9e599ce51996608d245f59bc9e9383fa9ac92ceecdb4fc681e3617f0&scene=21#wechat_redirect)
