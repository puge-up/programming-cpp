- [一、代理模式](#一代理模式)
- [二、具体实现](#二具体实现)
- [三、桥接模式](#三桥接模式)
- [四、具体实现](#四具体实现)
- [五、说明](#五说明)

## 一、代理模式

侧重于逻辑控制!

## 二、具体实现

代码如下：

```cpp
#include<iostream>
using namespace std;

class Subject{   //卖书的接口
    public:
        virtual void sailbook() = 0;
    private:
};

class RealBook : public Subject{  //实体店卖书
    public:
        virtual void sailbook(){
            cout<<"卖书"<<endl;
        }   
    private:
};
//a中包含b类;
//让代理类(Dangdang)包含了一个书店(RealBook),代理和书店都实现了一个协议
class Dangdang : public Subject{  //网上卖书
    public:
        virtual void sailbook(){
            RealBook *rsb = new RealBook;
            rsb->sailbook();
            discount();
        }   
    public:
        void discount(){
            cout<<"双十一打折"<<endl;
        }
    private:
        Subject *m_subject;
};

int main(void){
    Subject *s = new Dangdang;
    s->sailbook();

    delete s;

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvwA7VN8S8XNm7kAETMqiasd5TTJsEnyhI8kYPHNYjGepPg8MDqskKhLJpR4ZeWjYpepxVmx8yq5Hg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、桥接模式

**将抽象部分和实现部分进行分离；**

外观模式：客户要使用N个功能,N个功能又相似,就可以抽象起来；

享元模式：有一个对象可能使用1000次,怎样避免对这些对象进行重复的创建呢?避免对象的大量创建!

## 四、具体实现

代码如下：

```cpp
#include<iostream>
using namespace std;

class Engine{
    public:
        virtual void InstallEngine(){
    
        }   
    private:

};

class Engine4400cc : public Engine{
    public:
        virtual void InstallEngine(){
            cout<<"我是4400 发动机 安装完毕"<<endl;
        }   
    private:
}

class Engine4500cc : public Engine{
    public:
        virtual void InstallEngine(){
            cout<<"我是4500 发动机 安装完毕"<<endl;
        }
    private:
}

class Car{
    public:
        Car(Engine *engine){
            m_engine = engine;
        }
        virtual void installEngine = 0;
    private:
        Engine *m_engine;

};

class BM5{
    public:
        BM5(){

        }
    private:
};    
int main(void){

    return 0;
}
```

组合模式：**想将一大堆不同的事物用同一个类进行表达；**

## 五、说明

原创文章链接：[C++进阶系列之设计模式（5）---代理模式和桥接模式](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484047&idx=1&sn=52cbda810bddfed02c6f180514a118d9&chksm=f94c88b2ce3b01a41f103c5d99422e0e2512018d72fd08308508090aa8132a241f73615849e8&scene=21#wechat_redirect)
