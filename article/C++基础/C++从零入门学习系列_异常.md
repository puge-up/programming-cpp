- [一、异常处理机制](#一异常处理机制)
- [二、异常规范](#二异常规范)
- [三、自定义异常](#三自定义异常)
- [四、C++标准库的异常类](#四c标准库的异常类)
- [五、说明](#五说明)

## 一、异常处理机制

1、异常处理就是挽救错误的一个概念；

**异不异常只有编程人员才能知道，因为每种场合下是不一样的。**

关键三步:

- try  有可能发生异常的地方；
- throw  抛出变量/自定义类的对象
- catch  捕获异常类进行处理(按数据类型进行捕获)

2、抛出时为无名临时对象，此时异常在捕获时用引用接收，其生存域：到catch捕获块结束之后才释放；例：catch(类 &e)

3、没有异常处理，发生错误，由操作系统处理，操作系统的处理手段：直接把程序结束掉。

**写了异常处理，错误不会交给操作系统处理，而是由我们自己处理错误。**

可以把异常处理看作是操作系统下面的一个二级机构，对发生的异常自己进行处理，不会报告操作系统。

一个例子如下，用异常解决的：

```cpp
#include<iostream>
using namespace std;

//异常规范，就是明确了抛出的数据类型，
class Test{};
double Div(int a, int b)throw(int, double, short, Test)//能抛出哪些类型的 throw(),将不能抛出异常
{ 
    if(b == 0){
        throw b; //抛出异常，其后代码将不会执行，
    }            //直接进行到捕获的地方
    return a/b; 
}

int main(){
    int a = 10;
    int b = 0;
    double result = 0.0;
    try{  //试试看是否发生异常
        result = Div(a, b);
    }
    catch(int){  //按类型进行捕获
        cout<<"Div Error(int), b==0"<<endl;
    }
    catch(short){
        cout<<"Div Error(short), b==0"<<endl;
    }
    catch(...){  //捕获的是所有的异常
                 //这个只能作为最后的捕获分支，上面没捕获到，交给它处理。
    }
    cout<<result<<endl;
    //异常的发生，程序正常的结束！
}
```

## 二、异常规范

**也叫运行时异常，在编译时期完全正确，运行的话就会发生段错误；**

异常从函数的右端出口：

- throw()，不能抛出任何类型的异常；
- 不写，可以抛出一切类型的异常；
- throw(int, char, double......)，只能抛出你规定数据类型的异常。

## 三、自定义异常

处理栈的问题进行理解自定义异常，模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwxrp2X5aeVoNSEIMaGSuS55Y1mbB5mSWyGzVIH6mH20uQNzTkiaqlDqw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

相关的自定义异常处理栈代码如下：

```cpp
#include<iostream>
#include<string>
using namespace std;

#define STACK_SIZE    8

//编写相关的异常类，来处理入栈满
template<typename Type>
class pushOnStackFull{
public:
    pushOnStackFull(const char *s, int val) : str(s), value(val){} 
    ~pushOnStackFull(){}
public:
    void What(){  //明确异常发生了什么，并且相应的解决
        cout<<str<<endl; //这里只是打印信息。
        cout<<value<<" not push stack!"<<endl;
    }
private:
    Type value;
    string str;
};

template<typename Type>
class Stack{
public:
    Stack(int sz = STACK_SIZE){
        capacity = sz > STACK_SIZE ? sz : STACK_SIZE;
        data = new Type[capacity];
        top = 0;
    }
    ~Stack(){
        delete []data;
        data = NULL;
        capacity = top = 0;
    }
public:
    bool isFull()const{
        return top >= capacity;
    }
    bool push(const Type &x){
        if(isFull()){
            throw pushOnStackFull<Type>("栈已满，不能入栈!", x);
        }
        data[top++] = x;
        return true;
    }
public:
    void showStack()const{
        for(int i = top-1; i >=0; --i){
            cout<<data[i]<<endl;
        }
    }
private:
    Type *data;
    size_t capacity;
    size_t top;
};

int main(void){
    Stack<int> st;
    try{
        for(int i = 0; i <= 8; i++){
            st.push(i);
        }
    }
    catch(pushOnStackFull<int> &e){
        e.What();
    }
    st.showStack();
}
```

## 四、C++标准库的异常类

已经提供了常用的异常类，逻辑异常、运行时异常、其他异常库中都实现了，可以直接借助系统的异常类抛出。

在Linux下面，系统内的异常类在头文件<stdexcept>中；

**其系统内有what()方法，只不过这个方法是虚函数，的我们自己重写，然后直接调用即可。**

## 五、说明

原创文章链接：[C++从零入门学习系列（17）---异常](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483940&idx=1&sn=5ca954345b01886b01053d7c38c1b740&chksm=f94c8819ce3b010f2acf7f14b95a011f074472bfd836ff4820dc6ca5af46dc04945a1d7d0c45&scene=21#wechat_redirect)
