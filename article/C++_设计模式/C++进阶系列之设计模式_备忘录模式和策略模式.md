- [一、备忘录模式](#一备忘录模式)
- [二、具体实现](#二具体实现)
- [三、策略模式](#三策略模式)
- [四、具体实现](#四具体实现)
- [五、说明](#五说明)

## 一、备忘录模式

**保存对象的状态,在需要的时候在恢复出来即可!!!**

## 二、具体实现

代码实现：

```cpp
#include<iostream>
#include<string>
using namespace std;

class Mem{ //备忘录类
    public:
        Mem(string name, int age){
            m_name = name;
            m_age = age;
        }   
        string getName(){
            return m_name;
        }   
        int getAge(){
            return m_age;
        }   
        void setName(string name){
            m_name = name;
        }   
        void setAge(int age){
            m_age = age;
        }   

    private:
        string m_name;
        int m_age;
};

class Person{
    public:
        Person(string name, int age){
            m_name = name;
            m_age = age;
        }
        string getName(){
            return m_name;
        }
        int getAge(){
            return m_age;
        }
        void setName(string name){
            m_name = name;
        }
        void setAge(int age){
            m_age = age;
        }

        //保存
        Mem *createMem(){
            return new Mem(m_name, m_age);
        }        
        //还原
        void setMem(Mem *mem){
            this->m_age = mem->getAge();
            this->m_name = mem->getName();
        }
        void printT(){
            cout<<"m_name: "<<m_name<<"m_age: "<<m_age<<endl;
        }
    private:
        string m_name;
        int m_age;
};

//增加一个备忘录的管理者!!!
class Manager{
    public:
        Manager(Mem *m){
            this->m = m;
        }
        Mem *getMem(){
            return m;
        }
        void setMem(Mem *m){
            this->m = m;        
        }
    private:
        Mem *m; //持有一个备忘录的引用!!!
};

int main(void){
    /*
    Mem *m = NULL;
    Person *p = new Person("张三",32);
    p->printT();
    //创建Person对象的一个状态
    cout<<"---------------------------"<<endl;
    m = p->createMem();
    p->setAge(42);
    p->printT();

    cout<<"还原旧的状态"<<endl;
    p->setMem(m);
    p->printT();

    delete p;
    */

    Manager *m1;      
    Person *p = new Person("张三",32);
    p->printT();
    //创建Person对象的一个状态
    cout<<"---------------------------"<<endl;
    m1 = new Manager(p->createMem());
    p->setAge(42);
    p->printT();

    cout<<"还原旧的状态"<<endl;
    p->setMem(m1->getMem());
    p->printT();

    delete p;

    return 0;
}
```

结果如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu5vxlY0H3o2fbjFCiaRsziaGTYqtD0quziaHibEUZ8KibBGXURUu6Ryx6ibgJaya6srGv57SFv1opvYD5w/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、策略模式

**准备一组算法,并将每一个算法封装起来,使得它们可以互换；**

## 四、具体实现

代码如下：

```cpp
#include<iostream>
using namespace std;

//策略模式：准备一组算法,并将每一个算法封装起来,使得它们可以互换;
 
class Strategy{
    public:
        virtual void crypt() = 0;
    private:
};

class AES : public Strategy{
    public:
        virtual void crypt(){
            cout<<"AES加密算法"<<endl;
        }   
    private:

}; 

class DES : public Strategy{
    public:
        virtual void crypt(){
            cout<<"DES加密算法"<<endl;
        }   
    private:

};

class Context{  //组合算法的抽象类
    public:
        void setStrategy(Strategy *strategy){
            this->strategy = strategy;
        }
        void myoperator(){
            strategy->crypt();
        }

    private:
        Strategy *strategy;
};
int main(void){
    //1、直接调用的方法;
    /*
    DES *des = new DES;
    des->crypt();
    delete des;
    */

    //2、客户端可以自由的进行策略的更换;
    //Strategy *des = new DES;
    Strategy *des = new AES;    
    Context *context = new Context;
    context->setStrategy(des);
    context->myoperator();

    delete des;
    delete context;

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu5vxlY0H3o2fbjFCiaRsziaGHATB3e8K3zU6jFtN0zvmrnM4FWzZ5eoBaich57HYAmJq3ebLbqsBu5g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 五、说明

原创文章链接：[C++进阶系列之设计模式（7）---备忘录模式和策略模式](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484056&idx=1&sn=d66c8730bd798424c525bdfe05fc08b3&chksm=f94c88a5ce3b01b38461496bd18aae81bba5a55e980de1df527ea318845565e4a091a948809a&scene=21#wechat_redirect)
