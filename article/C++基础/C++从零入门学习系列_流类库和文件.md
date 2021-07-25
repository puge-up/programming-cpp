- [一、流类库](#一流类库)
- [二、格式控制](#二格式控制)
- [三、文件](#三文件)
- [四、二进制读写](#四二进制读写)
- [五、文件随机访问](#五文件随机访问)
- [六、文件与对象](#六文件与对象)
- [七、说明](#七说明)

## 一、流类库

1、C++中没有输入输出，标准库中包含一个I/O流类库。

C语言中printf 和scanf 称为函数； 输出到屏幕；C++中cout和cin称为对象；输入是键盘，其中iostream是虚继承；cout<<int/char/double--->是因为重载了<<。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwsf5KjB85f4OTWZ1kmB9CuAPGnYDPU2lQFg2DiaLCfm3ucszofhesYFg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2、C++流类库中定义4个全局流对象，cin、cout、cerr、clog

- cin 标准输入流对象，键盘
- cout标准输出流，屏幕
- cerr和clog标准错误输出流， 屏幕

其中cin、cout、clog是带缓冲区的，缓冲区由streambuf类对象来管理，cerr非缓冲区，一旦错误发生立即显示。

```cpp
#include<iostream>
using namespace std;

int main(void){
    cerr<<"Error"<<endl; //错误直接输出
    cout<<"Hello"<<endl; //先放到缓冲区中
}
```

## 二、格式控制

会用，知道怎么查就行了，没必要记这些；

cout.flags(ios::hex); //hex这些在ios类中，以16进制输出；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsEiacQY79zE79O4zYiaOpAJwcGic4t5E9icic6yx8xJYibd0jpyM6PERoV4icsOTBBJHzHKwY0KUwTIramA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

0000 0000 0000 0000  有多少个1，就有什么功能；

ios::hex | ios::showbase hex和showbase都是在ios类中定义的枚举，1-16各占一位；

## 三、文件

1. 先定义一个文件对象流
2. 打开某个文件
3. 进行文件的读写
4. 关闭文件

ASCII字符节文件：

- fprintf(fd, "", );    :写入文件
- fscanf(fd, "", );    :从文件读出

文本文件的操作，写入文件：

```cpp
#include<iostream>
#include<fstream>//文件输出流头文件
#include<stdlib.h>
using namespace std;

int main(void){
    int ar[] = {1, 3, 5, 6, 7, 9,};
    //1、
    //ofstream ofile("Test1.txt", ios::out);与下2步等价
    ofstream ofile;
    //2、
    ofile.open("Test1.txt", ios::out);
    if(!ofile){
        cerr<<"Open File Fail!"<<endl;
        exit(1);
    }
    for(int i = 0; i < sizeof(ar)/sizeof(int); i++){
        ofile<<ar[i]<<" ";
    }

    ofile.close();
}
```

在文件中读出：

```cpp
#include<iostream>
#include<fstream>//文件输出流头文件
#include<stdlib.h>
using namespace std;

int main(void){
    int ar[10];
    ifstream ifile;
    ifile.open("Test1.txt", ios::in);
    if(!ifile){
        cerr<<"Open File Fail"<<endl;
        exit(1);
    }
    for(int i = 0; i < 4; i++){
        ifile>>ar[i];
    }

    ifile.close();
}
```

## 四、二进制读写

写入文件：

```cpp
#include<iostream>
#include<fstream>//文件输出流头文件
#include<stdlib.h>
using namespace std;

int main(void){
    int ar[] = {1, 3, 5, 6, 7, 9,};
    //1、
    //ofstream ofile("Test1.txt", ios::out);与下2步等价
    ofstream ofile;
    //2、
    ofile.open("Test1.txt", ios::out | ios::binary);
    if(!ofile){
        cerr<<"Open File Fail!"<<endl;
        exit(1);
    }
    ofile.write((char *)ar, sizeof(ar));//这样就不用循环了，一次性解决

    ofile.close();
}

```

从文件读出：

```cpp
#include<iostream>
#include<fstream>//文件输出流头文件
#include<stdlib.h>
using namespace std;

int main(void){
    int ar[] = {1, 3, 5, 6, 7, 9,};
    //1、
    //ifstream ofile("Test1.txt", ios::out);
    ifstream ifile;
    //2、
    ifile.open("Test1.txt", ios::out | ios::binary);
    if(!ifile){
        cerr<<"Open File Fail!"<<endl;
        exit(1);
    }
    ifile.read((char *)ar, sizeof(ar));//这样就不用循环了,一次性全部读出

    ifile.close();
}

```

## 五、文件随机访问

随机读写关键靠文件指针；

**文件指针，开始指向第一个，读写就靠这个文件读写指针，会自动指向下一个；**

```cpp
#include<iostream>
#include<fstream>//文件输出流头文件
#include<stdlib.h>
using namespace std;

int main(void){
    ifstream ifile;

    ifile.open("Test1.txt", ios::in);
    if(!ifile){
        cerr<<"Open File Fail!"<<endl;
        exit(1);
    }
    int pos;
    int value;
    while(1){
        cout<<"请输入位置: ";
        cin>>pos;
        //beg  cur  end
        ifile.seekg(pos, ios::beg);//定位函数，pos,相对于什么地方开始
        ifile>>value; //将定位处的值放入value；
        cout<<"value = "<<value<<endl;
    }
    ifile.close();
}
```

**文件可以定位读出，最好用二进制解决，每个数字都是4字节；就不用考虑每个数字跨几个字节，所以为pos*4；**

**文本文件在其中每个数字(0-9)占用1个字节，不好定位一个完整数字占用几个字节；**

## 六、文件与对象

**在C++程序设计中，文件应该在构造函数中打开，并创建对象，而在析构函数中保存和关闭文件，并撤销对象；**

**对文件而言，释放资源的同时包括将对象中的信息再次存入磁盘文件，在程序运行过程中，应将信息适时保存到相应的磁盘文件，以免数据意外丢失。**

文件与对象的有机结合(关键在构造和析构函数)，以下就是一个相应的例子：

```cpp
#include<iostream>
#include<fstream>
using namespace std;

class Complex;
ostream& operator<<(ostream &out, const Complex &t);

class Complex{
    friend ostream& operator<<(ostream &out, const Complex &t);
public:
    Complex() : real(0), p_w_picpath(0){
        ifstream ifile;
        ifile.open("Test.txt", ios::in);
        if(!ifile){
            cerr<<"Open File Fail"<<endl;
            exit(1);
        }
        ifile>>real>>p_w_picpath;
        ifile.close();
    }
    Complex(int rea, int imag) : real(rea), p_w_picpath(imag){}
    ~Complex(){
        ofstream ofile;
        ofile.open("Test.txt", ios::out);
        if(!ofile){
            cerr<<"Open File Fail"<<endl;
            exit(1);
        }
        ofile<<real<<" "<<p_w_picpath;
        ofile.close();
    }
public:
    void setComplex(int real, int p_w_picpath){
        this->real = real;
        this->p_w_picpath = p_w_picpath;
    }
private:
    int real;
    int p_w_picpath;
};

ostream& operator<<(ostream &out, const Complex &t){
    out<<"("<<t.real<<","<<t.p_w_picpath<<")";
    return out;
}
int main(void){
    Complex c;
    cout<<c<<endl;
    c.setComplex(100, 200);//模拟了在下一次实例化时把上一次读取出来。
//    cout<<c<<endl;//写进文件，保存设置。
}

```

## 七、说明

原创文章链接：[C++从零入门学习系列（18）---流类库和文件](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483941&idx=1&sn=5fee369e2576a1fe19ce72862b6aaf24&chksm=f94c8818ce3b010efaf1ac69314e488fd24120d1fed811b6a26c8a6a2dc80596c1d9e763749d&scene=21#wechat_redirect)
