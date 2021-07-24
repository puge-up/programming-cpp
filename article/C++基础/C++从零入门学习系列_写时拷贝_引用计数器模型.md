- [一、深浅拷贝的使用时机](#一深浅拷贝的使用时机)
- [二、引用计数器模型](#二引用计数器模型)
- [三、写时拷贝](#三写时拷贝)
- [四、说明](#四说明)

## 一、深浅拷贝的使用时机

- 浅拷贝：对只读数据共用一份空间，且只释放一次空间；
- 深拷贝：数据的修改，的不同空间；

## 二、引用计数器模型

- 使用变量use_count，来记载初始化对象个数；
- static模型(此处只用浅拷贝与浅赋值)。

```cpp
#include<iostream>
#include<string.h>
#include<malloc.h>
using namespace std;

class String{
public:
    String(const char *str = ""){
        if(str == NULL){
            data = new char;
            data[0] = 0;
        }else{
            data = new char[strlen(str) + 1];
            strcpy(data,str);
        }
        use_count++;     //每新创建一个对象，对引用计数器++；
    }
    String(const String &s){
        data = s.data;
        use_count++;      //创建出新的对象，use_count++；
    }
 //此处先不写赋值语句
    ~String(){
        if(--use_count == 0){  //当引用计数器减为0时，就是每次行析构对象时，都对它减一次，直到为0才释放空间，
            delete []data;
            data = NULL;
        }
    }
public:
    char* GetString()const{
        return data;
    }
private:
    char *data;
    static int use_count;   //此处use_count只有一份，负责记载创建了多少个对象；
};

int String::use_count = 0;  //C++中的静态变量全局只有一份，可以再类外进行初始化；

int main(void)
{
    String s1("hello");
    cout<<s1.GetString()<<endl;
    String s2;
    s2 = s1;  //浅赋值，调用默认的；
    cout<<s2.GetString()<<endl;
    String s3("xyz"); //创建t3对象，要出问题了；(对其就只创建出来，不在进行赋值语句等操作)；此时的情况是：已经有两个对象，其成员data指向同一空间，此时又有一个data指向另一个空
                      //间，但是use_count为0才释放空间，只释放一份，所以肯定有内存泄漏！！！
    return 0;
}
```

上面的static浅拷贝其实存在很大的问题，当t3对象创建时，use_count会加1；

当调用析构函数时，每次减1，为0时，释放空间。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgefjMrqfJ31OO1GYxHYlKrH5NJoF5oS16X2FhqU3djmu6a2uYFlydw8Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、写时拷贝

浅拷贝与深拷贝联合使用，看实际需求对其编写，此时我希望，对数据读时共用一份数据，需要修改时，在单独开辟空间进行修改，在进行改写，并且对象(初始化)应该有自己的data和use_count，赋值语句时共用一份就行，此时就需要句柄了，这就是写时拷贝；

具体完整代码如下：

```cpp
#include<iostream>
#include<malloc.h>
#include<string.h>
using namespace std;
class String;
class String_rep{        // 这个类是封装在内部供我们程序员自己使用的。
    friend class String;  //友元类，可以访问私有数据。
public:
    String_rep(const char *str = ""):use_count(0){  //构造函数的初始化
        if(str == NULL){
            data = new char[1];
            data[0] = 0;
        }else{
            data = new char[strlen(str)+1];
            strcpy(data,str);
        }
    }
    String_rep(const String_rep &rep);
    String_rep& operator=(const String_rep &rep);
    ~String_rep(){
        delete []data;
        data = NULL;
    }
public:
    void increment(){  
        use_count++;
    }
    void decrement(){   //这个函数至关重要，写了一个释放空间的函数，要在其后赋值语句中使用；
        if(--use_count == 0)
            delete this;
    }
    int use_count_()const{
        return use_count;
    }
public:
    char *getdata()const{
        return data;
    }
private:
    char *data;
    int use_count;
};
class String{
public:
    String(const char *str = ""):rep(new String_rep(str)){
        rep->increment();
    }
    String(const String &s){
        rep = s.rep;
        rep->increment();
    }
    String& operator=(const String &s){
        if(this != &s){
            rep->decrement();
            rep = s.rep;
            rep->increment();
        }
        return *this;
    }
    ~String(){
        rep->decrement();
    }
public:
    int use_count()const{
        return rep->use_count_();
    }
    void print()const{
        cout<<rep->data<<endl;
    }
    void toupper(){      //这个函数提供的意义：对其要改的对象重新申请空间，进行改写，使相互之间不影响。
        if(rep->use_count_() > 1){ //对象个数大于1才进行拷贝出来重新写，只有一个就直接在其上进行修改。
            String_rep *new_rep = new String_rep(rep->data);
            this->rep->decrement();
            rep = new_rep;
            rep->increment();
        }
        char *pch = rep->data;
        while(*pch){
            *pch -= 32;
            pch++;
        }
    }
private:
    String_rep *rep; // 句柄
};
int main(){
    String s1("hello");
    String s2 = s1;
    String s3("xyz");
    s3 = s2;
    s1.toupper();
    s1.print();
    cout<<"s1 count = "<<s1.use_count()<<endl;
    s2.print();
    cout<<"s2 count = "<<s2.use_count()<<endl;
    s3.print();
    cout<<"s3 count = "<<s3.use_count()<<endl;
    return 0;
}
```

以上的代码就可以达到目的，每次创建对象都有自己的data和use_count(调用构造函数),在赋值语句时先释放原有空间，在进行浅拷贝，构造函数时也是浅拷贝，对其进行了各自空间的管理与释放，并且在修改数据时拷贝出来一份即可。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcgenEw1pWicgISD9iaZeMoMGsPB38StN5nsxnLQ1t2wvcvtx6PccEEH7icibQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

分析如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbum1f6qibzGf6qH49DGNlcge5OzqoPicTDJyL6Hz2R10wGw4uhwagA5XY2BRwYeADnqgUJCAJYfGtUA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

关于以上还有个问题：

```cpp
void decrement(){   
  if(--use_count == 0)
   delete this;
}
```

为什么不在String类的析构函数中写delete呢？

**原因：析构函数只有在对象释放是才调用，而在此时，通过赋值语句要释放空间，析构函数此时就不能及时释放原有空间，会造成内存泄漏，所以写一个释放空间的函数，内部有delete，会先调用析构函数，达到了及时释放空间的目的！**

以上只是对写时拷贝的粗浅理解。

## 四、说明

原创文章链接：[C++从零入门学习系列（6）---写时拷贝，引用计数器模型](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483883&idx=1&sn=0fbb190f803b577d0a91fa596d3812e6&chksm=f94c8bd6ce3b02c010313567eb28744033dc72ab666b3989570a1dcf1692986d3229780835d5&scene=21#wechat_redirect)
