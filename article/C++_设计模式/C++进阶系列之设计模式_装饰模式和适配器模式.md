- [一、装饰模式](#一装饰模式)
- [二、具体实现](#二具体实现)
- [三、适配器模式](#三适配器模式)
- [四、具体实现](#四具体实现)
- [五、说明](#五说明)

## 一、装饰模式

**动态的给一个对象添加一些额外的职责；侧重于功能的扩展：对其功能可以自由的增加或者减少；**

## 二、具体实现

代码实现：

```cpp
#include<iostream>
using namespace std;

class Car{
    public:
        virtual void show() = 0;
    private:

};

class RunCar : public Car{
    public:
        virtual void show(){
            cout<<"可以跑"<<endl;
        }   
    private:
};

class SwimCarDriver : public Car{
    public:
        SwimCarDriver(Car *car){
            m_car = car;
        }   
        virtual void show(){
            m_car->show();
            cout<<"可以游泳"<<endl;
        }
    private:
        Car *m_car;

};

class FlyCarDriver : public Car{
    public:
        FlyCarDriver(Car *car){{
            m_car = car;
        }
        virtual void show(){
            m_car->show();
            cout<<"可以飞"<<endl;
        }
    private:
        Car *m_car;

};

//功能可以自由自在的组合,功能很强大!!!
int main(void){
    Car *mycar = NULL;
    mycar = new RunCar;

    mycar->show();

    cout<<"--------------------------------"<<endl;
    FlyCarDriver *flycar = new FlyCarDriver(mycar);
    flycar->show();
    cout<<"--------------------------------"<<endl;
    SwimCarDriver *swimcar = new SwimCarDriver(flycar);
    swimcar->show();

    return 0;
}
```

## 三、适配器模式

**适配器是将2个不同的对象进行连接和组合！将一个类的接口转换成客户希望的另外一个接口。**

## 四、具体实现

代码如下：

```cpp
#include<iostream>
using namespace std;

class Current18{
    public:
        virtual void useCurrent18() = 0;
    private:
};

class Current220{
    public:
        void useCurrent220(){
            cout<<"我是220V,欢迎使用"<<endl;
        }   

    private:
};

class Adapter : public Current18 { //适配器,要满足客户的需求;
    public:
        Adapter(Current220 *current){
            m_current = current;
        }   
        virtual void useCurrent18(){
            cout<<"适配器 适配220V"<<endl;
            m_current->useCurrent220();
        }
    private:
        Current220 *m_current;
};

int main(void){
    Current220 *current220 = new Current220;

    Adapter *adapter = new Adapter(current220);

    adapter->useCurrent18();
    delete current220;

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbszQiaoEd7hiaNdbKcsI3YjYS0lGNa8ia8GntuDsBib0Jb1ylJPG1GICQ4a2SB91D6h15Y6ibpn1ibsDQdQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 五、说明

原创文章链接：[C++进阶系列之设计模式（6）---装饰模式和适配器模式](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484052&idx=1&sn=65ed18fe7bbd008910495032f88464a9&chksm=f94c88a9ce3b01bfa7cf6457a2ea4eb0c079fe64923d59e7aec535c4a7cf9f9319d8ad6c44b2&scene=21#wechat_redirect)
