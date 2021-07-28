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
    cout<<"请输入一个数字 : ";
    cin>>s9;
    cout<<s9<<endl;
 
    return 0;
}
