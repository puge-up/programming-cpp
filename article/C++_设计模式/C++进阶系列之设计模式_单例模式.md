- [一、单例模式](#一单例模式)
- [二、实现单例的步骤](#二实现单例的步骤)
- [三、单例模式->懒汉式](#三单例模式-懒汉式)
  - [3.1、懒汉式](#31懒汉式)
  - [3.2、懒汉式存在的一个问题](#32懒汉式存在的一个问题)
- [四、单例模式->饿汉式](#四单例模式-饿汉式)
- [五、说明](#五说明)

## 一、单例模式

单例模式：**一个类只能创建一个对象。**

为什么使用单例模式？

*在多个线程之间，初始化一次socket资源，对资源进行共享。*

## 二、实现单例的步骤

1. 构造函数私有化
2. 提供一个全局的静态方法
3. 在类中定义一个静态指针,指向本类的变量的静态指针变量！！！

## 三、单例模式->懒汉式

代码实现：

```cpp
#include<iostream>
using namespace std;

class Singelton{
    private:
        Singelton(){
            cout<<"Singelton 构造函数执行"<<endl;
        }   
    public:
        static Singelton *getInstance(){
            if(m_psl == NULL){
                m_psl = new Singelton;  //申请了一个对象的入口地址;
            }   
            return m_psl;
        }   
        static void freeInstance(){
            if(m_psl){
                cout<<"释放对象空间"<<endl;
                delete m_psl;
                m_psl = NULL;
            }
        }
    private:
        static Singelton *m_psl; //静态变量,必须在类外进行初始化,此时才会分配内存空间!!!
};

Singelton *Singelton::m_psl = NULL;

int main(void){
    Singelton *p1 = Singelton::getInstance();
    Singelton *p2 = Singelton::getInstance();

    if(p1 == p2){
        cout<<"是同一个对象"<<endl;
    }else{
        cout<<"不是同一个对象"<<endl;
    }

    Singelton::freeInstance();
    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7fbrKHXcgWtSSHuvCjkPYJMHqhGfGAx96sndpg7M7WrvKcibCIEZfTRtA4kOJiaZ4aH085JYS0ZdQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

### 3.1、懒汉式

- 懒汉式：只有在调用相应的方法时，才会构造对象!!!
- 缺点：每次都要进行判断,程序进行慢!

### 3.2、懒汉式存在的一个问题

1. **懒汉式遇上多线程，此时就不能保证是单例模式了,可能会创建多个对象,解决方案：同步加锁、解锁机制！**

2. **构造函数不是线程安全函数!--->进行线程同步,保证只有一个线程去调用构造函数.其它的线程都要等待,才能保证只构造一个对象！**

## 四、单例模式->饿汉式

代码实现：

```cpp
#include<iostream>
using namespace std;

class Singelton{
    private:
        Singelton(){
            cout<<"Singelton 构造函数执行"<<endl;
        }   
    public:
        static Singelton *getInstance(){
            return m_psl;
        }   
        static void freeInstance(){
            if(m_psl){
                cout<<"释放对象空间"<<endl;
                delete m_psl;
                m_psl = NULL;
            }   
        }   
    private:
        static Singelton *m_psl; //此时C++编译器并没有分配内存!!!
};

Singelton *Singelton::m_psl = new Singelton;

int main(void){
    cout<<"*********************"<<endl;  //执行顺序：先执行静态变量的初始化(此时也就是构造函数),在执>
行主函数中的代码!!!
    Singelton *p1 = Singelton::getInstance();
    Singelton *p2 = Singelton::getInstance();

    if(p1 == p2){
        cout<<"是同一个对象"<<endl;
    }else{
        cout<<"不是同一个对象"<<endl;
    }

    Singelton::freeInstance();
    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7fbrKHXcgWtSSHuvCjkPY476udNrGa8uQqTRlLQiat5uMTcZ3aWTEaKcf81xqQwgMCE0JBovttFw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

饿汉式：

- **饿汉式：不管需不需要对象空间，都先提前布局好对象空间；**
- **缺点：可能存在内存空间的浪费!**

还有个懒汉式多线程的代码没有实现，那是解决单例中同步问题的方法。

## 五、说明

原创文章链接：[C++进阶系列之设计模式（2）---单例模式](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484025&idx=1&sn=c443bef2bc9dfc8be898554c0a7d992b&chksm=f94c8844ce3b0152cec43ba44112f62623a8a472e87bf49c163b08ab9243910ef26f1d25cb52&scene=21#wechat_redirect)
