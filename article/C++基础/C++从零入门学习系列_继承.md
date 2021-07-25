- [一、继承](#一继承)
- [二、访问属性](#二访问属性)
- [三、构造函数的调用顺序](#三构造函数的调用顺序)
- [四、砖石继承](#四砖石继承)
- [五、同名隐藏与赋值兼容规则](#五同名隐藏与赋值兼容规则)
  - [5.1、同名隐藏](#51同名隐藏)
  - [5.2、赋值兼容规则](#52赋值兼容规则)
- [六、说明](#六说明)

## 一、继承

这个机制是面向对象使代码复用的重要手段，在原有类的基础上进行扩展，增加功能；

**继承的出现，应该主要是为了多态性；继承实质是是为了多态做准备。**

## 二、访问属性

1. 有public、protected、private继承，不写的话，默认私有继承；
class d : public B1，B2，B3，在这块，B1是公有继承，B2和B3是默认的，私有继承；

2. class Base{}；sizeof(Base); 空类，计算结果 1 字节；起标识作用

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4RUib0jf0YxbVHlHsf4CEmw55wLCCX4tkxX9XW56m9FobHqicjmTAqicPA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

3. 不管什么继承，子类均不会继承父类的构造方法和析构方法，其余的拷贝一份(包括私有，公有，保护)放到子类，只不过更改相应的修饰符权限。
4. 不论什么继承，子类都不能直接访问父类的私有数据。
5. 从对象和子类内看访问属性：

   - 对象角度：永远只能访问公有方法；
   - 子类内角度：子类永不可能直接访问父类的私有-------->安全性；
   - 子类在公有继承(public)中，父类的(除去私有的)都可以访问;其继承下来的修饰符权限不用改；
   - 子类在保护继承(protected)中，除去父类的私有，都可以访问；
   - 子类在私有继承(private)中，；继承下来的属性都变为私有，原因：成员函数可以访问自己的私有数据；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4nTBzWrJI6vrrjBCrl3rVcicbvXlaObAYybMnG8lE7eXD7nlvmQhWnQw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

6. protected----->只在继承中体现，其它的地方用不到这个；

   - protected/private————>不同之处：影响下一层此的继承；private会阻断继承；

## 三、构造函数的调用顺序

1. 当在继承时创建一个对象，其内部隐藏了先调用其父类的构造函数，先创建了父类的对象，其后创建子类对象；析构函数的调用与此相反;

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs41vib5h51W1zlDcdCVX7qXXahAsXkjZQz9iaTeq0SE6UfoBJDXwvJAicTw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2. **按继承顺序，成员对象创建顺序，调用父类的构造函数，创建父类对象，最后创建自己对象；与参数列表的顺序无关；**

3. 看看有没有虚继承(virtual public B1)；有的话，先调用虚继承的构造函数，在调用普通父类的构造函数，最后调用自己的，一切按顺序来；

## 四、砖石继承

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4esibIo3eNnIkgbib1BWkjqbxDnCbKQduKqsHAia5E7LeNYiaYbzljIIF5A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

继承下来时有2个n，在调用时候会产生二义性；其采用虚继承可以解决：

```cpp
#include<iostream>
using namespace std;
 
class Base{
public:
    int n;
};
 
class D1 : virtual public Base{//加上virtual，表示虚继承
public:     //public virtual Base和上面等同
    int x;
};
 
class D2 : virtual public Base{  //加上virtual，表示虚继承
public:
    int y;
};
 
class S : public D1, public D2{  //此时就只有一个n了;
public:
    int z;
};
 
int main(){
    S c;
    c.n = 10;
 
    cout<<&c.D1::n<<endl;  //因为同一个n,所以地址相同；
    cout<<&c.D2::n<<endl;
    return 0;
}
```

虚继承可以解决这类问题，就只有一个n被继承下来，就可以正确访问n了;

## 五、同名隐藏与赋值兼容规则

### 5.1、同名隐藏

```cpp
#include<iostream>
using namespace std;
  
class Base
{
public:
    void fun()  //父类的无参fun()方法
    {
        cout<<"This is Base fun()"<<endl;
    }
    void fun(int a) //父类的一个参数的fun()方法
    {
        cout<<"This is Base fun(int)"<<endl;
    }
};
  
class D : public Base
{
public:
    void fun()   //子类的fun()方法
    {
        cout<<"This is D fun()"<<endl;
    }
};
  
int main()
{
    D d;
    d.fun();   //肯定调用子类的fun()方法
 // d.fun(1);  此时因为函数名相同，隐藏了父类所有的该方法，子类有没有参数，所以报错
    d.Base::fun(1);//此时调用了父类的fun带参数的方法，刚才只是隐藏了，并没有覆盖！
    return 0;
}
```

**子类在继承父类时，父类中与子类中函数名字相同的所有均被隐藏，(父类中同名的函数不能是虚函数)--->同名隐藏**

### 5.2、赋值兼容规则

```cpp
class Base{};
  
void Cloud(Base *pb){
    pb->fun();  //没写虚函数，将访问父类的此方法；
    pb->show();
}
  
int main(){
    Base b;
    D d;
    Cloud(&d);
    b = d;  //(1)、子类对象可以直接给父类对象赋值
  
    Base *pb = &d; //(2)、子类对象的地址可以赋值给父类对象的指针
    
    Base &rb = d; //(3)、子类对象可以让父类对象所引用
    return 0;
}
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtG9OHxQicvuZ6mqPsFWIWs4yoEnMMRXXaP8b391R3fCosZLPIHMSIAaNdV6coexVFJjpQqOK44Bcw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

以上就是赋值兼容三规则；在多态中将会体现出用处。

## 六、说明

原创文章链接：[C++从零入门学习系列（15）---继承](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483935&idx=1&sn=1fda3f1649a3786654d7394dd54ebdf4&chksm=f94c8822ce3b013416ecb09e7e69e6fc6f1b9d67c354c087512aef1fd842433991b11844167b&scene=21#wechat_redirect)
