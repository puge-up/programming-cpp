- [一、set的基本操作](#一set的基本操作)
  - [1.1、set的删除、插入操作](#11set的删除插入操作)
  - [1.2、set的排序](#12set的排序)
  - [1.3、set中为复杂数据类型时的排序](#13set中为复杂数据类型时的排序)
  - [1.4、set中迭代器的使用](#14set中迭代器的使用)
- [二、multiset的基本操作](#二multiset的基本操作)
- [三、map的基本操作](#三map的基本操作)
  - [3.1、map元素的添加、遍历、删除](#31map元素的添加遍历删除)
  - [3.2、map中4种初始化的分析](#32map中4种初始化的分析)
  - [3.3、map查找](#33map查找)
- [四、multimap的基本操作](#四multimap的基本操作)
- [五、说明](#五说明)

## 一、set的基本操作

### 1.1、set的删除、插入操作

代码如下：

```cpp
#include<iostream>
#include<set>
using namespace std;

//set底层是红黑树,其所包含的元素是唯一的,集合中的元素按一定的顺序排列,元素插入过程是按排序规则插入,所>
以不能指定插入位置;
int main(void){
    //set 集合 元素唯一 自动排序(默认情况下是从小到大) 不能按照[]方式插入元素 底层红黑树
    
    set<int> set1;

    for(int i = 0; i < 5; i++){
        set1.insert(34);
        set1.insert(24);
        set1.insert(14);
        set1.insert(84);
        set1.insert(-4);
    }   
    //插入重复的元素
    set1.insert(100);
    set1.insert(100);
    set1.insert(100);
    set1.insert(100);

    set<int>::iterator it; 
    for(it = set1.begin(); it != set1.end(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;

    //删除集合中的元素
    while(!set1.empty()){
        set<int>::iterator it = set1.begin();
        cout<<*it<<" ";
        set1.erase(set1.begin());
    }
    cout<<endl;
    return 0;
}
```

### 1.2、set的排序

代码如下：

```cpp
#include<iostream>
#include<set>
using namespace std;

//对于基础数据可以进行排序,复杂数据类型的排序是怎么回事?------>仿函数解决
int main(void){
    set<int> set1; //默认排序从小到大
    set<int, less<int> > set2; //集合是从小到大
    set<int, greater<int> > set3; //集合从大到小的输出;

    for(int i = 0; i < 5; i++){
        set3.insert(11);
        set3.insert(45);
        set3.insert(99);
        set3.insert(77);
        set3.insert(66);
    }   

    //从大到小的排序
    set<int, greater<int> >::iterator it; 
    for(it = set3.begin(); it != set3.end(); it++){
        cout<<*it<<" ";
    }   
    cout<<endl;

    return 0;
}
```

### 1.3、set中为复杂数据类型时的排序

代码如下：

```cpp
#include<iostream>
#include<string.h>
#include<set>
using namespace std;

class Student{
    public:
        Student(const char *name, int age){
            strcpy(this->name, name);
            this->age = age;
        }
    public:
        char name[32];
        int age;

};

//仿函数：重载了(),
struct FunStudent{
    bool operator()(const Student &left, const Student &right){
        if(left.age < right.age){ //左边的小,就返回为真!!从小到大进行排序
            return true;
        }else{
            return false;
        }
    }
};
int main(void){
/*
    Student s1("s1", 31);
    Student s2("s2", 22);
    Student s3("s3", 55);
    Student s4("s4", 11);
    Student s5("s5", 31); //如果2个31岁,能插入成功吗?
    //如何知道插入的结果,看函数的返回值
    
    set<Student, FunStudent> set1; //集合中插入的是学生类型(复杂数据类型),会调用这个仿函数
    set1.insert(s1);
    set1.insert(s2);
    set1.insert(s3);
    set1.insert(s4);
    set1.insert(s5);

    set<Student, FunStudent>::iterator it;
    for(it = set1.begin(); it != set1.end(); it++){
        cout<<it->age<<" "<<it->name<<endl;
    }
*/
    //如何判断set1.insert()函数的返回值
    Student s1("s1", 31);
    Student s2("s2", 22);
    Student s3("s3", 55);
    Student s4("s4", 11);
    Student s5("s5", 31); //此时,由于比较的是age,所以将会插入失败,因为仿函数中用的是age做的键值;
    
    set<Student, FunStudent> set1; //集合中插入的是学生类型(复杂数据类型),会调用这个仿函数
    pair<set<Student, FunStudent>::iterator, bool> pair1 = set1.insert(s1);
    if(pair1.second == true){ //insert()的返回值是pair(对组)类型;
        cout<<"插入s1成功"<<endl;
    }else{
        cout<<"插入s1失败"<<endl;
    }
    set1.insert(s2);
    set1.insert(s3);
    set1.insert(s4);
    pair<set<Student, FunStudent>::iterator, bool> pair5 = set1.insert(s5);
    if(pair5.second == true){
        cout<<"插入s1成功"<<endl;
    }else{
        cout<<"插入s1失败"<<endl;
    }

    set<Student, FunStudent>::iterator it;
    for(it = set1.begin(); it != set1.end(); it++){
        cout<<it->age<<" "<<it->name<<endl;
    }

    return 0;
}
```

### 1.4、set中迭代器的使用

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;


//返回值为pair的类型要学会使用;
int main(void){
    set<int> set1;

    for(int i = 0; i < 10; i++){
        set1.insert(i+1);
    }   

    set<int>::iterator it; 
    for(it = set1.begin(); it != set1.end(); it++){
        cout<<*it<<" "; 
    }   
    cout<<endl;

    set<int>::iterator it0 = set1.find(5);
    cout<<"it0:"<<*it0<<endl;

    int num1 = set1.count(5);
    cout<<"num1:"<<num1<<endl;

    set<int>::iterator it1 = set1.lower_bound(5);  //大于等于5的元素的迭代器的位置
    cout<<"it1:"<<*it1<<endl;

    set1.erase(5);  //删除容器中值为5的所有元素
    pair<set<int>::iterator, set<int>::iterator> mypair = set1.equal_range(5); //函数的返回值为对组
    cout<<*mypair.first<<endl; //迭代器中第一个找的是大于等于5的
    cout<<*mypair.second<<endl;  //代器中的第二个找的是大于5的

    return 0;
}
```

## 二、multiset的基本操作

代码如下：

```cpp
#include<iostream>
#include<set>
using namespace std;

int main(void){
    multiset<int> set1;
    int tmp = 0;

    cout<<"请输入multiset集合中的值:";
    cin>>tmp;

    while(tmp != 0){ 
        set1.insert(tmp);
        cout<<"请输入multiset集合中的值:";
        cin>>tmp;
    }   

    multiset<int>::iterator it; 
    for(it = set1.begin(); it != set1.end(); it++){
        cout<<*it<<" ";
    }   
    cout<<endl;

    while(!set1.empty()){
        multiset<int>::iterator it = set1.begin();
        cout<<*it<<" ";
        set1.erase(it);
    }
    cout<<endl;

    return 0;
}
```

## 三、map的基本操作

### 3.1、map元素的添加、遍历、删除

代码如下：

```cpp
#include<iostream>
#include<string>
#include<map>
using namespace std;

//map元素的添加、遍历、删除
int main(void){
    map<int, string> map1;
    //因为map是key-value结构,所以可以做成pair(对组)
    //初始化map:
    //方法1、
    map1.insert(pair<int, string>(1, "teacher01"));
    map1.insert(pair<int, string>(2, "teacher02"));
    //方法2、
    map1.insert(make_pair(3, "teacher03"));
    map1.insert(make_pair(4, "teacher04"));
    //方法3、
    map1.insert(map<int, string>::value_type(5, "teacher05"));
    map1.insert(map<int, string>::value_type(6, "teacher06"));
    //方法4、
    map1[7] = "teacher07";
    map1[8] = "teacher08";


    //容器的遍历
    map<int, string>::iterator it; 
    for(it = map1.begin(); it != map1.end(); it++){
        cout<<it->first<<" "<<it->second<<endl;   //map的遍历,跟pair(对组)一样,first表示第一个(键key),
second表示第二个(值value)；
    }
    cout<<"遍历结束"<<endl;

    //容器的删除
    while(!map1.empty()){
        map<int, string>::iterator it = map1.begin();
        cout<<it->first<<" "<<it->second<<endl;
        map1.erase(it);
    }

    return 0;
}
```

### 3.2、map中4种初始化的分析

代码如下：

```cpp
#include<iostream>
#include<map>
using namespace std;

//前三种初始化方法的返回值都为：pair(iterator, bool)
//插入四中方法的异同
//结论：前三种方法,若key已经存在,此时在进行插入,将会报错;
//方法4、若key已经存在,则修改;
int main(void){
    map<int, string> map1;
    //方法1、
    pair<map<int, string>::iterator, bool>  mypair1 = map1.insert(pair<int, string>(1, "teacher01"));
    map1.insert(pair<int, string>(2, "teacher02"));
    //方法2、
    pair<map<int, string>::iterator, bool>  mypair3 = map1.insert(make_pair(3, "teacher03"));
    map1.insert(make_pair(4, "teacher04"));
    //方法3、
    pair<map<int, string>::iterator, bool>  mypair5 = map1.insert(map<int, string>::value_type(5, "tea
cher05"));
    if(mypair5.second != true){
        cout<<"key 5插入失败"<<endl;
    }else{  
        cout<<mypair5.first->first<<" "<<mypair5.first->second<<endl;
    }       
    pair<map<int, string>::iterator, bool>  mypair6 = map1.insert(map<int, string>::value_type(5, "tea
cher06"));
    if(mypair6.second != true){
        cout<<"key 5插入失败"<<endl; //因为键值相同,所以插入会失败;
    }else{
        cout<<mypair6.first->first<<" "<<mypair6.first->second<<endl;
    }

    //前三种初始化方法的返回值都为：pair(iterator, bool)

    //方法4、
    map1[7] = "teacher07";
    map1[7] = "teacher08";

    map<int, string>::iterator it;
    for(it = map1.begin(); it != map1.end(); it++){
        cout<<it->first<<"\t"<<it->second<<endl;
    }
    cout<<"遍历结束"<<endl;

    return  0;
}
```

### 3.3、map查找

代码如下：

```cpp
#include<iostream>
#include<map>
using namespace std;

int main(void){
    map<int, string> map1;
    //因为map是key-value结构,所以可以做成pair(对组)
    //初始化map:
    //方法1、
    map1.insert(pair<int, string>(1, "teacher01"));
    map1.insert(pair<int, string>(2, "teacher02"));
    //方法2、
    map1.insert(make_pair(3, "teacher03"));
    map1.insert(make_pair(4, "teacher04"));
    //方法3、
    map1.insert(map<int, string>::value_type(5, "teacher05"));
    map1.insert(map<int, string>::value_type(6, "teacher06"));
    //方法4、
    map1[7] = "teacher07";
    map1[8] = "teacher08";


    //容器的遍历
    map<int, string>::iterator it; 
    for(it = map1.begin(); it != map1.end(); it++){
        cout<<it->first<<" "<<it->second<<endl;   //map的遍历,跟pair(对组)一样,first表示第一个(键key),second表示第二个(值value)；
    }
    cout<<"遍历结束"<<endl;

    //map的查找，返回值都是迭代器
    map<int, string>::iterator it2 = map1.find(2);
    if(it2 == map1.end()){
        cout<<"key 100的值不存在"<<endl;
    }else{
        cout<<it2->first<<"\t"<<it2->second<<endl;
    }
    //equal_range,异常处理
    pair<map<int, string>::iterator, map<int, string>::iterator> mypair = map1.equal_range(5);  //此时返回2个迭代器,形成一个pair(对组)
    //第一个迭代器,是>=5的位置
    //第二个迭代器是 >5的位置
    //使用第一个迭代器
    if(mypair.first == map1.end()){
        cout<<"第一个迭代器,是>=5的位置不存在"<<endl;
    }else{
        cout<<mypair.first->first<<"\t"<<mypair.first->second<<endl;
    }
    //使用第二个迭代器
    if(mypair.second == map1.end()){
        cout<<"第二个迭代器,是>5的位置不存在"<<endl;
    }else{
        cout<<mypair.second->first<<"\t"<<mypair.second->second<<endl;
    }

    return 0;
}
```

## 四、multimap的基本操作

代码如下：

```cpp
#include<iostream>
#include<string>
#include<map>
using namespace std;

//multimap的重要应用场景：数据分组;
class Person{
    public:
        string name;
        int    age;
        string tel;
        double saly;
};

int main(void){
    Person p1, p2, p3, p4, p5; 
    p1.name = "王1";
    p1.age = 31; 
    p2.name = "王2";
    p2.age = 32; 
    p3.name = "张3";
    p3.age = 33; 
    p4.name = "张4";
    p4.age = 34; 
    p5.name = "赵5";
    p5.age = 35; 
    multimap<string, Person> map1;
    //sale部门
    map1.insert(make_pair("sale", p1));
    map1.insert(make_pair("sale", p2));
    //development
    map1.insert(make_pair("development", p3));
    map1.insert(make_pair("development", p4));
    //financial
    map1.insert(make_pair("Financial", p5));

    multimap<string, Person>::iterator it;
    for(it = map1.begin(); it != map1.end(); it++){
        //将age=32的人,名字更改为name32;
        if(it->second.age == 32){
            it->second.name = "name32";
        }
        cout<<it->first<<"\t"<<it->second.name<<endl;
    }
    cout<<"遍历结束"<<endl;

    //显示开发部的人员信息
    int num = map1.count("development");

    cout<<"development部门人数:"<<num<<endl;
    cout<<"development部门员工信息"<<endl;

    multimap<string, Person>::iterator it1 = map1.find("development");   
    int tag = 0;
    while(it1 != map1.end() && tag < num){
        cout<<it1->first<<"\t"<<it1->second.name<<endl;
        it1++;
        tag++;
    }

    return 0;
}
```

## 五、说明

原创文章链接：[C++进阶系列之STL（6）---set，map相关操作](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484010&idx=1&sn=a49cd7bfe1c4b02072cd459e74507d0c&chksm=f94c8857ce3b014174e6f39573186b94cac97eeae4623d538922057a47ddc57ec8a2b5d3587d&scene=21#wechat_redirect)
