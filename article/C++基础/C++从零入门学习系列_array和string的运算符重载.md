- [一、array类](#一array类)
- [二、string类](#二string类)
- [三、说明](#三说明)

## 一、array类

```cpp
#include<iostream>
using namespace std;

class Array{
    public:
        Array(int count);
        Array(const Array &t);
        ~Array();
    public:
        void setData(int i, int data);
        int getData(int i);
        int length();
    private:
        int len;
        int *p;
};

Array::Array(int count){
    len = count;
    p = new int[len];
}
//有指针,的进行深拷贝;
Array::Array(const Array &t){
    len = t.len;
    p = new int[len];
    for(int i = 0; i < t.len; i++){
        p[i] = t.p[i];
    }

}
Array::~Array(){
    if(p){
        delete []p;
        p = NULL;
    }

}
void Array::setData(int i, int data){
    p[i] = data;
}
int Array::getData(int i){
    return p[i];
}
int Array::length(){
    return len;
}


int main(void){
    Array array(10);
    int i;

    for(i = 0; i < array.length(); i++){     
        array.setData(i, i);
    }

    for(i = 0; i < array.length(); i++){
        cout<<array.getData(i)<<" ";
    }
    cout<<endl;

    Array array1 = array;
    for(i = 0; i < array1.length(); i++){
        cout<<array1.getData(i)<<" ";
    }
    cout<<endl;


    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsoK9c28mOPKUPJ1jvbZ8gaDwDbInyH9Z5vyjjicPpQKYp5XzdjzEAnqXiacb3tO2df1j2k9j73zYtA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、string类

```cpp
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

class MyString{
    public:
        friend ostream& operator<<(ostream &out, const MyString &s1);
        friend istream& operator>>(istream &in, MyString &s2);
        MyString(int len = 0){ //默认参数看我们是否自己开辟大小的空间;
            if(len != 0){ 
                m_len = len;
                m_p = new char[m_len+1];
                memset(m_p, 0, m_len);
            }else{

                m_len = 0;
                m_p = new char[m_len+1];    
                strcpy(m_p, "");
            }   
        }   
        MyString(const char *p){
            if(p == NULL){
                m_len = 0;
                m_p = new char[m_len+1];    
                strcpy(m_p, "");
            }else{
                m_len = strlen(p);
                m_p = new char[m_len+1];
                strcpy(m_p, p);
            }
        }
        MyString(const MyString &s){
            m_len = s.m_len;
            m_p = new char[m_len+1];
            strcpy(m_p, s.m_p);
        }
        MyString& operator=(const MyString &t){
            if(m_p){
                delete []m_p;
                m_p = NULL;
                m_len = 0;
            }

            m_len = t.m_len;
            m_p = new char[m_len+1];
            strcpy(m_p, t.m_p);

            return *this;
        }
        ~MyString(){
            if(m_p) {
                delete []m_p;         
                m_p = NULL;
                m_len = 0;
            }
        }
    public:
        MyString operator=(const char *p){
            if(m_p){
                delete []m_p;
                m_p = NULL;
                m_len = 0;
            }
            if(p == NULL){
                m_len = 0;
                m_p = new char[m_len+1];
                strcpy(m_p, "");
            }else{
                m_len = strlen(p);
                m_p = new char[m_len+1];
                strcpy(m_p, p);
            }

            return *this;
        }
        char& operator[](int index){
            return m_p[index];
        }     
        bool operator==(const char *p)const{  //判断与字符串是否相等,看长度和里面的内容是否相等!!!
            if(p == NULL){
                if(m_len == 0){
                    return true;
                }else{
                    return false;
                }
            }else{
                if(m_len == strlen(p)){
                    return !strcmp(m_p, p);
                }else{
                    return false;
                }
            }
        }
        bool operator==(const MyString &s)const{
            if(m_len != s.m_len){
                return false;
            }

            return !strcmp(m_p, s.m_p);
        }

        bool operator!=(const char *p)const{
            return !(*this == p);
        }   
        bool operator!=(const MyString &s)const{
            return !(*this == s);
        }
        int operator<(const char *p)const{
            return strcmp(m_p, p);
        }
        int operator<(const MyString &s)const{
            return strcmp(m_p, s.m_p);
        }

        int operator>(const char *p)const{
            return strcmp(p, m_p);
        }
        int operator>(const MyString &s)const{
            return strcmp(s.m_p, m_p);
        }
        //怎么样把类的指针露出来.

    public:
        char *c_str(){     
            return m_p;
        }
        const char *c_str2(){
            return m_p;
        }
        int length(){
            return m_len;
        }
    private:
        int m_len;
        char *m_p;
};


ostream& operator<<(ostream &out, const MyString &s1){
    out<<s1.m_p;

    return out;
}

istream& operator>>(istream &in, MyString &s2){
    in>>s2.m_p;

    return in;
}
int main(void){    
    MyString s1;
    MyString s2("s2");
    MyString s3 = s2;
    MyString s4 = "s444444444444";

    s4 = "s22222222222";

    s4 = s2;

    s4[1] = '3';
    printf("%c\n", s4[1]); //测试[]改变值了吗?
    
    cout<<s4<<endl;

    if(s2 == "s2"){
        cout<<"相等"<<endl;
    }else{
        cout<<"不相等"<<endl;
    }

    s3 = "aaa";
    
    int flag = (s3 < "bbb");
    if(flag < 0){
        cout<<"s3小于bbb"<<endl;  
    }else{
        cout<<"s3大于bbb"<<endl;
    }

    s3 = "adasf";
    strcpy(s3.c_str(), "sga");
    cout<<s3<<endl;

    MyString s9(100);//默认输入要开辟字符串的空间大小;
    cout<<"请输入一个数字 :";
    cin>>s9;
    cout<<s9<<endl;

    return 0;
}
```

运行结果:

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsoK9c28mOPKUPJ1jvbZ8ga2bpqA9858WBqAvqVnwRyn5Ez8rn3GkBDkN31Eo4UtJQ8nteCyXqRpQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、说明

原创文章链接：[C++从零入门学习系列（8）---array和string的运算符重载](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483897&idx=1&sn=8bef60549c28548d57f2893ec89f6107&chksm=f94c8bc4ce3b02d2b854597ccfc47e9fb9150e85e6e5ff9630dd7f80f6b63c746dd04e5c906a&scene=21#wechat_redirect)
