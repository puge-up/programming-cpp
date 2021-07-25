- [一、建造者模式](#一建造者模式)
- [二、具体实现](#二具体实现)
- [三、抽象工厂](#三抽象工厂)
- [四、具体实现](#四具体实现)
- [五、说明](#五说明)

## 一、建造者模式

**一个对象的构建比较复杂，将一个对象的构建和对象的表示进行分离!!!**

## 二、具体实现

代码如下：

```cpp
#include<iostream>
#include<string>
using namespace std;

class House{
    public:
        void setDoor(string door){
            this->m_door = door;
        }   
        void setWall(string wall){
            this->m_wall = wall;
        }   
        void setWindow(string window){
            this->m_window = window;
        }   
    public:
        string getDoor(){
            return m_door;
        }   
        string getWall(){
            return m_wall;
        }   
        string getWindow(){
            return m_window;
        }
    private:
        string m_door;
        string m_wall;
        string m_window;
};

//请工程队来建造房子
class Build{
    public:
        House *setHouse(){

        }
    private:
};
int main(void){
    //这样写不好,是客户直接造房子;
    House *house = new House;
    house->setDoor("门");
    house->setWall("墙面");
    house->setWindow("窗口");

    delete house;

    return 0;     
}
```

## 三、抽象工厂

只能生产一个产品；

## 四、具体实现

代码如下：

```cpp
#include<iostream>
using namespace std;

class Fruit;
class AbstractFactory{
    public:           
        virtual Fruit *CreateBanana() = 0;
        virtual Fruit *CreateApple() = 0;
    private:
};

class Fruit{
    public:
        virtual void sayname() = 0;
    private:
};

class NorthBanana : public Fruit{
    public:
        virtual void sayname(){
            cout<<"我是北方香蕉"<<endl;
        }   
};
class NorthApple : public Fruit{
    public:
        virtual void sayname(){
            cout<<"我是北方苹果"<<endl;
        }
};

class SouthBanana : public Fruit{
    public:
        virtual void sayname(){
            cout<<"我是南方香蕉"<<endl;
        }
};

class SouthApple : public Fruit{
    public:
        virtual void sayname(){
            cout<<"我是南方苹果"<<endl;
        }
};

class NorthFactory : public AbstractFactory{
    public:
        virtual Fruit *CreateBanana(){
            return new NorthBanana;
        }
        virtual Fruit *CreateApple(){
            return new NorthApple;
        }
    private:
};

class SouthFactory : public AbstractFactory{
    public:
        virtual Fruit *CreateBanana(){
            return new SouthBanana;
        }
        virtual Fruit *CreateApple(){
            return new SouthApple;
        }
    private:
};
int main(void){
    Fruit *fruit = NULL;
    AbstractFactory *af = NULL;
    //---------------------------
    af = new SouthFactory;
    fruit = af->CreateApple();
    fruit->sayname();
    fruit = af->CreateBanana();
    fruit->sayname();
    //---------------------------
    af = new NorthFactory;      
    fruit = af->CreateApple();
    fruit->sayname();
    fruit = af->CreateBanana();
    fruit->sayname();

    delete af;

    return 0;      
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvwA7VN8S8XNm7kAETMqiasduwiaRX7lxGB3NPPnyQUuicKpNfkS8QBawxkuS4Ltx3GajFLqWg5FGsLg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

抽象模式

- 缺点：抽象工厂的产品线都被写死了;只能生产这2种产品;

## 五、说明

原创文章链接：[C++进阶系列之设计模式（4）---建造者模式和抽象工厂模式](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484044&idx=1&sn=03cb324588b0567a6b7c69819d93e0f8&chksm=f94c88b1ce3b01a7d9e1d90aca8ebddcbeee1cefc1c751673eff94ae201b4917392c359f629f&scene=21#wechat_redirect)
