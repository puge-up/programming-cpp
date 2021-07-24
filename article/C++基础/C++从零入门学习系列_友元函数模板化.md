- [一、构造函数的一种使用](#一构造函数的一种使用)
- [二、构造与赋值语句](#二构造与赋值语句)
- [三、构造函数的执行顺序](#三构造函数的执行顺序)
- [四、new和delete](#四new和delete)
- [五、static](#五static)
- [六、赋值语句](#六赋值语句)
- [七、继承中的字节大小](#七继承中的字节大小)
- [八、函数模板](#八函数模板)
- [九、友元函数的模板化](#九友元函数的模板化)
- [十、说明](#十说明)

## 一、构造函数的一种使用

```cpp
int main(void){
    //Test t1 = 10;// 在构造函数中寻找只有一个参数的
    
    //手动的调用构造函数;
    Test t2 = Test(1, 2);  //直接调用构造函数--->匿名对象;
    //直接调用Test的有参构造函数,初始化t2对象;  只会调用一次构造函数(直接把匿名对象转成t2);
    
}
```

## 二、构造与赋值语句

```cpp
Test g(){
    
    //返回为对象,我就给你返回一个新的对象(匿名对象);
}

int main(void){
    Test t1(1, 2); 
    Test t2; 

    Test t3 = t1; //用t1初始化t3,调用拷贝构造函数;
    Test t3(t1);
    t2 = t1; //利用t1给t2赋值,调用赋值语句;

    Test m = g(); //函数的返回值为对象,用匿名对象初始化m,此时C++编译器将直接把匿名对象转化为有名对象m;
    m = g();//此时匿名对象将没有用,赋值完成,没有转正,将被析构

}

//在定义类时,只要你写了构造函数,则必须要用你自己写的,此时C++编译器将不会给你提供默认的构造和拷贝构造函
数
```

## 三、构造函数的执行顺序

执行顺序：先执行被组合对象的构造函数，如果有多个，按定义顺序执行，而不是按初始化列表的顺序执行；

析构函数的调用顺序相反；初始化列表用来给const属性赋值；

代码如下：

```cpp
#include<iostream>
using namespace std;

class A{
    public:
        A(int a){ 
            m = a;
        }   
    private:
        int m;
};
    //在构造中调用构造函数是一种危险的行为,里面是一个匿名对象;用完立即调用析构,
    //参数列表也可以在拷贝构造函数上面使用;
class B{
    public:  //构造函数的初始化列表：解决,在B类中,组合了A类对象,
            //根据构造函数的规则,写了A类的构造函数,必须要用;
        B(int q, int a, int b, int c) : a1(b), a2(c), c(0){
            x = q;
            y = a;
        }   
    //执行顺序：先执行被组合对象的构造函数,如果有多个,按定义顺序执行,而不是按初始化列表的顺序执行;
    //析构函数的调用顺序相反;
    //构造调用顺序：a1、a2、b
    //初始化列表用来给const属性赋值;
    private:
        int x;
        int y;
        A a1;
        A a2;
        const int c;  //常量c必须初始化(通过参数列表)
};

int main(void){
    B b(1, 2, 3, 4);
}
```

## 四、new和delete

**new能执行类的构造函数,delete能行类的析构函数；**

**malloc free new delete可以互换使用，只不过new先开辟空间-->调用构造；delete--->先析构，在释放空间；**

## 五、static

**静态成员不占这个类的字节的大小;------->不属于这个实例的，相当于全局变量；**

代码如下：

```cpp
#include<iostream>
using namespace std;

class A{
    public:
        A(){}
        int getD(){
            return d;
        }
        void Add(){
            d++;
        }   
        static void getC(){ //静态成员函数;
            //静态方法只能调用静态的成员、函数;
            cout<<"d:"<<d<<endl;

        }   
    private:
        int a;
        int b;
        int c;
        static int d;  //静态成员变量
};

int A::d = 10; 

int main(void){
    A a;
    cout<<a.getD()<<endl;
    A::getC();

    cout<<sizeof(a)<<endl; //静态成员不占这个类的字节的大小;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwUNZADM9WpRbjyS6zVZWY2OSsfCas3Uwl9fvebRlzmXGQW8jTEz61pw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 六、赋值语句

重载=运算符难点：

1. 先把旧的内存释放掉；
2. 返回一个引用；为了支持连等；
3. 根据大小分配内存；

## 七、继承中的字节大小

**子类继承父类，在访问上有所限制，但是在内存空间上对属性成员是全部的继承了下来；静态变量在全局区，所以对静态变量不计入字节大小的计算；**

**class M{};//空的类，占一个标示，1字节；**

## 八、函数模板

- **普通函数的调用：可以进行隐式的类型转换；**
- **函数模版的调用：将严格按照类型进行匹配，不会进行自动类型转换；**

## 九、友元函数的模板化

**对友元函数实现<<运算符重载。**

代码如下：

```cpp
#include<iostream>
using namespace std;


//结论：友元函数的类模版比较复杂;

template<typename Type>
class Complex; //类的前置声明
template<typename Type>
ostream& operator<<(ostream &out, const Complex<Type> &c);//友元函数的前置声明


template<typename Type>
class Complex{
    public:
        friend ostream& operator<<<Type>(ostream &out, const Complex<Type> &c); //对<<的后面加上<Type>
;进行友元函数的模版化;
        Complex(Type a, Type b); 
        Complex(const Complex &c){}
        Complex& operator=(const Complex &c){}
        ~Complex(){}
    public:
        void printComplex();
        Complex operator+(const Complex &c);
    private:
        Type a;
        Type b;
};

//成员函数实现 +
template<typename Type>
Complex<Type>::Complex(Type a, Type b){
    this->a = a;
    this->b = b;
}
template<typename Type>
void Complex<Type>::printComplex(){
    cout<<"a:"<<a<<" b:"<<b<<endl;

}
template<typename Type>
Complex<Type> Complex<Type>::operator+(const Complex<Type> &c){
    return Complex(a+c.a, b+c.b);
}

//友元函数实现<<运算符重载
template<typename Type>
ostream& operator<<(ostream &out, const Complex<Type> &c){
    out<<"("<<c.a<<", "<<c.b<<")";

    return out;   
}
int main(void){
    Complex<int> c1(1, 2);
    Complex<int> c2(3, 4);
    Complex<int> c3 = c1 + c2;
    cout<<c3<<endl;
    c3.printComplex();

    return 0;
}
```

运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJw3fpLbWW6XDl01Fv5WKtCtlOj9Kib7X1nYxIJLpJhCIQlZOH4UvnhRwQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 十、说明

原创文章链接：[C++从零入门学习系列（10）---友元函数<<的模板化](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483907&idx=1&sn=ef209eaaf00904f3c219fd1f05d75471&chksm=f94c883ece3b012812cc03558b6fba879c3124ee73401a8aa56a4f69c6df548420657dbb6184&scene=21#wechat_redirect)
