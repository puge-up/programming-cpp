- [一、string的初始化，遍历，字符串连接](#一string的初始化遍历字符串连接)
- [二、string的查找，替换](#二string的查找替换)
- [三、区间的删除和插入](#三区间的删除和插入)
- [四、string的大小写转换-->函数指针](#四string的大小写转换--函数指针)
- [五、说明](#五说明)

C++ 中 string 的学习使用！

string的初始化，在C++中字符串是一种数据类型；

## 一、string的初始化，遍历，字符串连接

```cpp
#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;

int main(void){  
//string的初始化,在C++中字符串是一种数据类型;
    string s1 = "abcdefg";
    string s2("abcdefg");
    string s3(s2);
    string s4 = s1;  //调用拷贝构造函数;
    string s5(10, 'a');//10个空间中的字符都是'a';
    s5 = s1; 

    cout<<"s3:"<<s3<<endl;
    cout<<"s5:"<<s5<<endl;

//string的遍历,重载了[]操作符;
    //1、数组方式遍历[]
    for(int i = 0; i < s1.length(); i++){
        cout<<s1[i]<<" ";  //出现错误(下标越界),不会向外面剖出异常,引起程序的中断;
    }   
    cout<<endl;
    //2、迭代器
    string::iterator it; 
    for(it = s1.begin(); it != s1.end(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    //3、函数at()遍历
    for(int i = 0; i < s1.length(); i++){
        cout<<s1.at(i)<<" "; //会剖出异常,合理的解决下标越界;
    }
    cout<<endl;

//字符指针和string的转换
    //此时,把s1====>char * 把内存首地址给露出来;
    printf("s1:%s \n", s1.c_str());

    //s1中的内容拷贝到buf中;
    char buf[123] = {0};
    s1.copy(buf, 2, 0);//n, pos;下标从0开始拷贝2个字符到buf中,不会是C风格的,注意自己加上0结束标志;
    cout<<buf<<endl;

//string子符串的连接
    s1 = s1 + s2; //直接+就表：字符串的连接;
    s1 += s2; //+=也是字符串的连接;

    s1.append(s4); //调用方法append()也是字符串的连接;

    cout<<s1<<endl;       

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsoK9c28mOPKUPJ1jvbZ8ganyr3OsKmHlyI4Oo1TQEhzp3hg1ApRZiccF0M7VSNJAHTYXibWiaxpUKCA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、string的查找，替换

```cpp
#include<iostream>
#include<string>
#include<string.h>
using namespace std;

int main(void){
//字符串的查找和替换
    string s1 = "wbm hello wbm 111 wbm 222 wbm 333";

    //1、第一次出现wbm的下标
    int index = s1.find("wbm", 0); 
    cout<<"index :"<<index<<endl;

    //2、求wbm每一次出现的数组下标
    
/*  int offindex = s1.find("wbm", 0);
    while(offindex != -1){
        cout<<"offindex :"<<offindex<<endl;
        offindex += strlen("wbm");
        offindex = s1.find("wbm", offindex);
    }*/

    //3、把小写wbm换成大写
    int offindex = s1.find("wbm", 0); 
    while(offindex != -1){
        cout<<"offindex :"<<offindex<<endl;
        s1.replace(offindex, strlen("wbm"), "WBM"); //从下标offindex开始,删除n个字符,替换为后面的字符;
        offindex += strlen("wbm");
        offindex = s1.find("wbm", offindex);
    }
    cout<<"s1:"<<s1<<endl;

    string s3 = "aaa bbb ccc";
    s3.replace(0, 3, "AAA");  //替换的函数;
    cout<<"s3:"<<s3<<endl;

    return 0;
}

```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsoK9c28mOPKUPJ1jvbZ8gaQBzdpuVyagBLx7OfdL87JHtQuPyhvX0Zx1D2icIUCFgMnwrfSgHSdgg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、区间的删除和插入

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(void){
//区间删除和插入
    string s1 = "hello1 hello2 hell03";
    string::iterator it = find(s1.begin(), s1.end(), 'l');
    if(it != s1.end()){
        s1.erase(it); //删除算法;
    }   
    cout<<"s1 :"<<s1<<endl;

    s1.erase(s1.begin(), s1.end()); //删除从pos开始的n个字符;
    cout<<"s1全部删除:"<<s1<<endl;
    cout<<"s1的长度:"<<s1.length()<<endl;

    string s2 = "BBB";
    s2.insert(0, "AAA");  //头插法
    s2.insert(s2.length(), "CCC");//尾插法
    cout<<s2<<endl;


    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsoK9c28mOPKUPJ1jvbZ8ga2KhZtlgVyl4qEGZLbvhvZ7rWVhgrHbNy1RnJI2bbjQic0yf87QTia3IA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 四、string的大小写转换-->函数指针

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(void){
    string s1 = "AAAbbb";

    transform(s1.begin(), s1.end(), s1.begin(), 0, toupper);//toupper可以是：函数的入口地址,函数对象,
    cout<<s1<<endl;

    string s2 = "AAAbbb";
    transform(s2.begin(), s2.end(), s2.begin(), 0, tolower);
    cout<<s2<<endl;

    return 0;
}
```

## 五、说明

原创文章链接：[C++从零入门学习系列（7）---C++中string数据类型](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483890&idx=1&sn=62b10954523a5a7e37a462715a8b3b0e&chksm=f94c8bcfce3b02d9b28d82511666c610966b9103066fe0233b8061971dd331ef83b3fd4478fd&scene=21#wechat_redirect)
