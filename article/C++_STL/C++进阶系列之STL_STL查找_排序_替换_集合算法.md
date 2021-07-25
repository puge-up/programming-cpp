- [一、STL查找算法](#一stl查找算法)
- [二、STL排序算法](#二stl排序算法)
- [三、STL拷贝替换](#三stl拷贝替换)
- [四、STL集合算法](#四stl集合算法)
- [五、说明](#五说明)

## 一、STL查找算法

代码如下：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


//查找算法！！！
void main_adjacent_find(){
    vector<int> v1; 

    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(5);

    //查找第一个元素重复的位置;
    vector<int>::iterator it; 
    it = adjacent_find(v1.begin(), v1.end()); //查找第一个重复出现的数字;
    if(it == v1.end()){
        cout<<"没有找到重复的元素"<<endl;
    }else{
        cout<<*it<<endl;
    }   

    int index = distance(v1.begin(), it); //从头开始,的知当前迭代器的指针所在的数组下标处;
    cout<<"index:"<<index<<endl;
}

void main_binary_search(){
    vector<int> v1;

    //0 1 2 3 4 5.......n-1
    //二分法,10次就可以找到了;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(9);

    bool b = binary_search(v1.begin(), v1.end(), 7);
    if(b == true){
        cout<<"找到了"<<endl;
    }else{
        cout<<"没找到"<<endl;
    }
}

void main_count(){
    vector<int> v1;

    v1.push_back(1);
    v1.push_back(3);   
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(7);
    v1.push_back(9);
    v1.push_back(7);

    int num = count(v1.begin(), v1.end(), 7);

    cout<<"num:"<<num<<endl;
}

bool GreatThree(int num){
    if(num > 3){
        return true;
    }
    return false;
}

void main_count_if(){
    vector<int> v1;     

    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(9);

    int num = count_if(v1.begin(), v1.end(), GreatThree);
    cout<<"num:"<<num<<endl;
}

void main_find(){
    vector<int> v1;

    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(9);

    vector<int>::iterator it;
    it = find(v1.begin(), v1.end(), 5);
    cout<<*it<<endl;
}    
void main_find_if(){
    vector<int> v1;

    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);
    v1.push_back(9);

    vector<int>::iterator it;
    it = find_if(v1.begin(), v1.end(), GreatThree); //返回的是第一个回调函数所指向的迭代器;
    cout<<*it<<endl;
}
int main(void){
    main_adjacent_find();   //查找第一个重复的元素;
    main_binary_search();  //二分法查找某一个元素;
    main_count();  //查找某一个元素出现的次数; 针对基础数据类型
    main_count_if(); //用一个一元谓词,可以查找大于某一个数字的个数; 针对自定义的数据类型
    main_find();  //查找某一数据，通过迭代器指出; 针对基础数据类型
    main_find_if();  //查找某一数据，通过迭代器指出; 针对自定义数据类型;

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvOGVxMcraBNDyZ288KttxsPtcvc6fk6K06hAWy30fQ9UJD3RiaR0eApg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、STL排序算法

代码如下：

```cpp
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

//排序算法
void printV(vector<int> &v){
    vector<int>::iterator it; 

    for(it = v.begin(); it != v.end(); it++){
        cout<<*it<<" ";
    }   
    cout<<endl;
}

void main_merge(){
    vector<int> v1; 
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    vector<int> v2; 
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(6);

    vector<int> v3;
    v3.resize(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

    printV(v3);
}

class Student{
    public:
        Student(string name, int id){
            m_name = name;
            m_id = id;
        }
    public:
        string m_name;
        int m_id;
};

bool Compare(Student s1, Student s2){
    return (s1.m_id < s2.m_id);
}

void main_sort(){
    Student s1("老大", 1);
    Student s2("老二", 2);    
    Student s3("老三", 3);
    Student s4("老四", 4);

    vector<Student> v1;
    v1.push_back(s4);
    v1.push_back(s1);
    v1.push_back(s3);
    v1.push_back(s2);

    vector<Student>::iterator it;
    for(it = v1.begin(); it != v1.end(); it++){
        cout<<it->m_id<<"\t"<<it->m_name<<endl;
    }

    //sort()要对自定义的数据类型进行排序,就的进行自定义数据类型的排序;
    sort(v1.begin(), v1.end(), Compare); //Compare就是谓词,谓词就是函数名称,返回值为bool类型;

    for(it = v1.begin(); it != v1.end(); it++){
        cout<<it->m_id<<"\t"<<it->m_name<<endl;
    }
}

void main_random_shuffle(){
    vector<int> v1;    
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);

    //对动态数组进行随机打乱
    random_shuffle(v1.begin(), v1.end());

    printV(v1);

    //对字符串随机的打乱顺序;
    string str = "abcdefg";
    random_shuffle(str.begin(), str.end());;
    cout<<"str:"<<str<<endl;
}

void main_reverse(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);

    reverse(v1.begin(), v1.end());
    printV(v1);  
}

int main(void){
    main_merge(); //归并排序
    main_sort();
    main_random_shuffle();
    main_reverse();

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvDNy6aryFTH097BmzCcZOUiaaGHbAMpzYvdxfCwNSpJiciasoumxha4Amw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、STL拷贝替换

代码如下：

```cpp
#include<iostream>
#include<numeric> //accumulate()函数的头文件;
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

//拷贝替换

void printV(vector<int> &v){
    vector<int>::iterator it;

    for(it = v.begin(); it != v.end(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}

void main_copy(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    vector<int> v2; 
    v2.resize(v1.size());  //调整容器大小的函数;

    copy(v1.begin(), v1.end(), v2.begin());  //拷贝容器函数;

    printV(v2);

}

void main_replace(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(3);
    v1.push_back(3);
    v1.push_back(5);

    replace(v1.begin(), v1.end(), 3, 8);  //替换函数,将前面的数据都用后面的数据替换;
    printV(v1);
}

bool great_equal(int &n){
    if(n >= 5){
        return true;
    }else{
        return false;
    }
}    
void main_replace_if(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(8);
    v1.push_back(8);
    v1.push_back(8);
    v1.push_back(5);

    replace_if(v1.begin(), v1.end(), great_equal, 1);   //这里就是可以替换范围内的数据,通过谓词进行控>
制!!,将great_equal范围内的数字(返回值为真的)进行替换!!!
    printV(v1);
}

void main_swap(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    vector<int> v2;
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(6);

    swap(v1, v2);  //交换了v1、v2容器中的内容!!!
    printV(v1);
}

void main_accumulate(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    int tmp = accumulate(v1.begin(), v1.end(), 100);  //求和函数,加上一个初始值100;
    cout<<tmp<<endl;

}

void main_fill(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    fill(v1.begin(), v1.end(), 8);  //将容器中的数值全都改为8;
    printV(v1);
}
int main(void){
    main_copy();  //拷贝
    main_replace();  //替换 基础数据类型
    main_replace_if();  //替换范围 自定义数据类型
    main_swap();  //交换容器中的内容
    main_accumulate(); //求和函数
    main_fill();


    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvrFwZtlEpRYuDh4AwRibUXIolRFRme0j4SEKYmsiclV7ZvcXm466WdbGQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 四、STL集合算法

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
using namespace std;

void printV(vector<int> &v){
    vector<int>::iterator it; 

    for(it = v.begin(); it != v.end(); it++){
        cout<<*it<<" ";
    }   
    cout<<endl;
}
//集合
int main(void){
    vector<int> v1; 
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    vector<int> v2; 
    v2.push_back(1);
    v2.push_back(1);
    v2.push_back(1);
    vector<int> v3; 
    v3.resize(v1.size() + v2.size());
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin()); //集合中取并集;没有填满的空间默，认为0;
    printV(v3);

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8Ewvx02uhrVZVS7INNgqh6sKKdceVohUzXbFzyUaUQiboZtRuCLTb3KjXTg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 五、说明

原创文章链接：[C++进阶系列之STL（10）---STL查找、排序、替换、集合算法](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484014&idx=1&sn=13eae32f965cd1cdbf6d590b9e05aa43&chksm=f94c8853ce3b0145188f0b4d516b83b2ff5a887fc840b123de29a6cd5bef70633eb6bced1c56&scene=21#wechat_redirect)
