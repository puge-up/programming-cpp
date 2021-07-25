- [一、设计模式思想](#一设计模式思想)
- [二、简单工厂模式](#二简单工厂模式)
- [三、说明](#三说明)

## 一、设计模式思想

我实现设计模式是基于C++语言的：

1. **设计模式：主要是研究类与类之间的关系；**
2. **设计模式的基石：利用C++中的多态技术；**
3. **开闭原则：通过添加代码，而不是修改代码，完成功能的修改与扩展；**
4. **依赖倒置原则：产品和框架都向抽象层靠拢；**
5. **简单工产模式：不属于23种设计模式,将产品的创建都放到一个类(具体的工厂类)中去生产；**
6. **设计模式就是一种规定的形式，是一种套路，关键是理解思想；**

## 二、简单工厂模式

简单工厂模式：创建型模式/静态工厂方法模式，不属于23种设计模式，
就是实实在在的构造一个工厂类(高內聚，新增添的话，必须修改原有代码，而不是扩充原有代码)，不易扩充；

**作用：用一个类去创建其它类，但都有一个接口(面向抽象类编程)；**

代码实现：

```cpp
#include<iostream>
#include<string.h>
using namespace std;

class Fruit{
    public:
        virtual void getFruit() = 0;
    private:
};

class Banana : public Fruit{
    public:
        virtual void getFruit(){
            cout<<"我是香蕉......"<<endl;
        }   

    private:
};

class Apple : public Fruit{
    public:
        virtual void getFruit(){
            cout<<"我是苹果......"<<endl;
        }

    private:
};

class Factory{
    public:
        Fruit *create(const char *p){
            if(strcmp(p, "banana") == 0){
                return new Banana;
            }else if(strcmp(p, "apple") == 0){
                return new Apple;
            }else{
                cout<<"不支持"<<endl;
            }
        }
    private:
};
int main(void){
    Factory *f = new Factory;
    Fruit *fruit = NULL;

    //工厂生产香蕉
    fruit = f->create("banana");
    fruit->getFruit();  

    //工厂生产苹果
    fruit = f->create("apple");
    fruit->getFruit();

    delete f;

    return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7fbrKHXcgWtSSHuvCjkPYf59wwhKYmiblk95xoqUcsg0LOpVPibX9fZJSGVzPUXCsPnCvwk2aMpOg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、说明

原创文章链接：[C++进阶系列之设计模式的核心思想](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484021&idx=1&sn=3987107ee65d4bdb37d83adae2c9a737&chksm=f94c8848ce3b015e5a26a381910c2b748341d304f20505558f8f736faff70a6795b37c6bfd65&scene=21#wechat_redirect)
