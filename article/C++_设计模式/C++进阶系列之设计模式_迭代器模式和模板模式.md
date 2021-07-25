- [一、迭代器模式](#一迭代器模式)
- [二、具体实现](#二具体实现)
- [三、模板模式](#三模板模式)
- [四、具体实现](#四具体实现)
- [五、其余设计模式](#五其余设计模式)
- [六、说明](#六说明)

## 一、迭代器模式

**里面有一个对集合的引用；**

**这个迭代器是对谁创建的，这个迭代器就持有谁(这个集合)的引用!**

## 二、具体实现

代码如下：

```cpp
#include<iostream>
using namespace std;

#define SIZE    5

class MyIterator{ //抽象的迭代器
    public:
        virtual void First() = 0;
        virtual void Next() = 0;
        virtual bool isDone() = 0;
        virtual int CurrentItem() = 0;
    private:
};
 
class Abstract{  //抽象的集合类
    public:  
        virtual MyIterator *createIterator() = 0;
        virtual int getItem(int index) = 0;
        virtual int getSize() = 0;
    protected:
};

class ConIterator : public MyIterator{ // 具体的迭代器
    public:
        ConIterator(Abstract *ag){
            p = ag;
            currentIndex = 0;
        }
        virtual void First(){
            currentIndex = 0;   //让当前游标回到位置0;
        }
        virtual void Next(){
            if(currentIndex < p->getSize())
            currentIndex++;
        }
        virtual bool isDone(){

            return currentIndex == p->getSize();
        }
        virtual int CurrentItem(){
            return p->getItem(currentIndex);
        }
    private:
        int currentIndex;
        Abstract *p;
};

class Jh : public Abstract{
    public:
        Jh(){    
            for(int i = 0; i < SIZE; i++){
                arr[i] = i+100;
            }
        }
        virtual MyIterator *createIterator(){
            return new ConIterator(this);   //让迭代器持有一个集合的引用!!!
        }
        virtual int getItem(int index){
            return arr[index];
        }
        virtual int getSize(){
            return SIZE;
        }
    private:
        int arr[SIZE];
};


int main(void){
    Abstract *ag = new Jh;
    MyIterator *it = ag->createIterator();

    for(; !(it->isDone()); it->Next()){
        cout<<it->CurrentItem()<<" ";
    }
    cout<<endl;     
    delete ag;
    delete it;

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbuC6JddpdsB1wjibwh7TYnySX59fcpek60Rtib4CfYFqhUiacDKL9GQrdlKQjgZCkrKzchnibXFhyOWHw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、模板模式

**提前将业务逻辑做好了，就是同一种模板；**

## 四、具体实现

代码实现：

```cpp
#include<iostream>
using namespace std;

class MakeCar{
    public:
        virtual void MakeHead() = 0;
        virtual void MakeBody() = 0;
        virtual void MakeTail() = 0;
    public:
        void Make(){  //模版函数：提前将业务逻辑做好了;
            MakeTail();
            MakeBody();
            MakeHead();
        }
    private:
};

class Jeep : public MakeCar{
    public:
        virtual void MakeHead(){
            cout<<"Jeep head"<<endl;
        }   
        virtual void MakeBody(){
            cout<<"Jeep Body"<<endl;
        }   
        virtual void MakeTail(){
            cout<<"Jeep Tail"<<endl;
        }
    private:
};


class Bus : public MakeCar{
    public:
        virtual void MakeHead(){
            cout<<"Bus head"<<endl;
        }
        virtual void MakeBody(){
            cout<<"Bus Body"<<endl;
        }
        virtual void MakeTail(){
            cout<<"Bus Tail"<<endl;
        }
    private:
};
int main(void){
    MakeCar *car = new Bus;
    car->Make();
    delete car;

    MakeCar *car1 = new Jeep;
    car1->Make();
    delete car1;    

    return 0;
}
```

## 五、其余设计模式

1. 责任链模式：执行完一个任务以后,自动的执行下一个任务;
2. 观察者模式：定义对象间多种的依赖关系,使得每一个对象改变状态,则所有依赖的对象都会得到通知；一对多的关系!!!
3. 访问者模式：将对象的数据和行为进行分离!!!
主要作用于数据结构：将数据结构与数据结构上的具体操作进行分离!!!
不同对象对同一个事务的不同操作!
4. 解释模式：根据用户的输入：程序自动解释为不同的动作!!!

## 六、说明

原创文章链接：[C++进阶系列之设计模式（9）---迭代器模式和模板模式](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484074&idx=1&sn=25295d9e5cb870302c73f0af2f98cc5f&chksm=f94c8897ce3b0181cc2aeab3e0603f3527f9244bee2dfbc05162254eb7104b8862929fdc1a01&scene=21#wechat_redirect)
