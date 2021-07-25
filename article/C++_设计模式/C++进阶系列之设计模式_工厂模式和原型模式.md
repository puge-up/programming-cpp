- [一、工厂模式](#一工厂模式)
- [二、具体实现](#二具体实现)
- [三、原型模式](#三原型模式)
- [四、具体实现](#四具体实现)
- [五、说明](#五说明)

## 一、工厂模式

面向抽象类编程，底下可以接N多个生产某种的具体工厂；

**简单工厂模式：专门定义一个类来负责创建其它类的实例，被创建的实例通常都具有共同的父类；**

## 二、具体实现

代码如下

```cpp
#include<iostream>
using namespace std;

class Fruit{
    public:
        virtual void sayname() = 0;
    private:

};

class Banana : public Fruit{
    public:
        void sayname(){
            cout<<"我是香蕉"<<endl;
        }   
    private:
};

class Apple : public Fruit{
    public:
        void sayname(){
            cout<<"我是苹果"<<endl;
        }   
    private:
};
class AbFactory{
    public:
        virtual Fruit *CreateProduct() = 0;
    private:

};

class BananaFactory : public AbFactory{
    public:
        virtual Fruit *CreateProduct(){
            return new Banana;
        }

    private:
};

class AppleFactory : public AbFactory{
    public:
        virtual Fruit *CreateProduct(){
            return new Apple;
        }

    private:
};
//添加新的产品
class Pear : public Fruit{
    public:
        void sayname(){
            cout<<"我是 pear"<<endl;
        }
    private:
};

class PearFactory : public AbFactory{
    public:
        Fruit *CreateProduct(){
            return new Pear;
        }
    private:
};


int main(void){
    AbFactory *factory = NULL;
    Fruit *fruit = NULL;
    //吃香蕉
    factory = new BananaFactory;
    fruit = factory->CreateProduct();
    fruit->sayname();

    //吃梨
    factory = new PearFactory;
    fruit = factory->CreateProduct();
    fruit->sayname();
    delete factory;

    return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvwA7VN8S8XNm7kAETMqiasdYNymW0iaIXjmWSfa8SdfVs8zd3UPRPdoB9o2ZbMvXKjZvuTMRoevo1Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

工厂模式：扩展性不好；

## 三、原型模式

提供一个clone()接口，让普通对象拥有自我复制的功能!

相当于拷贝构造函数的编写；(当有成员为指针时)这个牵扯深拷贝和浅拷贝的问题；

## 四、具体实现

代码如下

```cpp
#include<iostream>
#include<string>
using namespace std;

class Person{
    public:
        virtual Person *clone() = 0;
        virtual void printT() = 0;
    private:
};

class Cplus : public Person{
    public:
        Cplus(){
            m_name = ""; 
            m_age = 0;
        }   
        Cplus(string name, int age){
            m_name = name;
            m_age = age;
        }   
        virtual void printT(){
            cout<<"m_name:"<<m_name<<" "<<"m_age:"<<m_age<<endl;
        }   
        virtual Person *clone(){
            Cplus *tmp = new Cplus;
            *tmp = *this;

            return tmp;
        }
    private:
        string m_name;
        int m_age;
        char *p;   //此时就会牵扯深拷贝的问题

};

int main(void){
    Cplus *c1 = new Cplus("张三", 32);
    c1->printT();

    Person *c2 = c1->clone();
    c2->printT();

    return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvwA7VN8S8XNm7kAETMqiasdfcSsfBboePXRhmuibFo2cRibpUs3D1GV25yAVXBG27jvhCSmnMcYJu4w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 五、说明

原创文章链接：[C++进阶系列之设计模式（3）---工厂模式和原型模式](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484037&idx=1&sn=7ef11c9eda70c1c89e96fc517131ddd9&chksm=f94c88b8ce3b01aeea48adef75432e1c0fa50f1c9c35fd5390a8a1b8789f70d4304f89b6a046&scene=21#wechat_redirect)
