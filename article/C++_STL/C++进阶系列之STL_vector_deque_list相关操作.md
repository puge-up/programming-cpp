- [一、vector的基本操作](#一vector的基本操作)
  - [1.1、对动态数组元素的添加和删除、获取](#11对动态数组元素的添加和删除获取)
  - [1.2、vector的初始化](#12vector的初始化)
  - [1.3、vector中迭代器的正向和反向遍历](#13vector中迭代器的正向和反向遍历)
  - [1.4、vector中的元素删除操作](#14vector中的元素删除操作)
- [二、deque的基本操作](#二deque的基本操作)
- [三、stack的基本操作](#三stack的基本操作)
- [四、queue的基本操作](#四queue的基本操作)
- [五、priority_queue的基本操作](#五priority_queue的基本操作)
- [六、list的基本操作](#六list的基本操作)
  - [6.1、list的遍历](#61list的遍历)
  - [6.2、list的删除](#62list的删除)
- [七、说明](#七说明)

## 一、vector的基本操作

### 1.1、对动态数组元素的添加和删除、获取

代码如下：

```cpp
#include<iostream>
#include<vector>
using namespace std;

//数组元素的添加和删除、获取
int main(void){
    vector<int> v1; 

    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    cout<<"len:"<<v1.size()<<endl;
    cout<<"获取头部元素:"<<v1.front()<<endl;

    //修改头部、尾部元素的值
    //函数返回值当左值,应该返回一个引用;
    v1.front() = 11; 
    v1.back() = 55; 

    while(v1.size() > 0){ 
        cout<<v1.back()<<" ";    //获取尾部元素;
        v1.pop_back(); //删除尾部元素
     }   
    cout<<endl;

}
```

### 1.2、vector的初始化

代码如下：

```cpp
#include<iostream>
#include<vector>
using namespace std;

void printV(vector<int> &v){
    for(int i = 0; i < v.size(); i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

int main(void){
    //vector类
    vector<int> v1;

    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);

    vector<int> v2 = v1; //对象初始化
    vector<int> v3(v1.begin(), v1.begin()+2); //对象初始化
/*
    //vector的遍历
    for(i =a 0; i < v1.size(); i++){
        v1[i] = i + 1;
    }
    int i;
    for(i = 0; i < v1.size(); i++){
        cout<<v1[i]<<" ";
    }
    cout<<endl;
*/
    printV(v1);

    //push_back()的强化记忆;
    vector<int> v5(10); //前10个元素初始化为0；
    v5.push_back(100);
    v5.push_back(200);
    printV(v5);
    return 0;    
}
```

### 1.3、vector中迭代器的正向和反向遍历

代码如下：

```cpp
#include<iostream>
#include<vector>
using namespace std;

int main(void){
    vector<int> v1(10); //初始化空间的值都为0；
    for(int i = 0; i < 10; i++){
        v1[i] = i+1;
    }   
//迭代器
//1(begin)、3、5 、(end) 当it = v1.end()的时候,说明这个容器已经遍历完了;
//end()的位置,应该是5的后面;
    //正向遍历
    vector<int>::iterator it; 
    for(it = v1.begin(); it != v1.end(); it++){
        cout<<*it<<" ";
    }   
    cout<<endl;

    //反向遍历
    vector<int>::reverse_iterator rit;
    for(rit = v1.rbegin(); rit != v1.rend(); rit++){
        cout<<*rit<<" ";
    }   
    cout<<endl;

    return 0;
}
```

### 1.4、vector中的元素删除操作

代码如下：

```cpp
#include<iostream>
#include<vector>
using namespace std;

void printV(vector<int> &v){
    for(int i = 0; i < v.size(); i++){
        cout<<v[i]<<" ";
    }   
    cout<<endl;
}

//删除
int main(void){
    vector<int> v1(10);

    for(int i = 0; i < 10; i++){
        v1[i] = i + 1;
    }   
    //区间删除
    v1.erase(v1.begin(), v1.begin()+3); //删除开始的3个元素
    //指定(元素)位置删除
    v1.erase(v1.begin()); //在头部删除一个

    //根据元素的值
    v1[1] = 2;
    v1[3] = 2;

    vector<int>::iterator it;
    for(it = v1.begin(); it != v1.end(); it++){
        if(*it == 2){
            v1.erase(it); //删除的是元素,参数是迭代器
        }
    }

    v1.insert(v1.begin(), 100);
    v1.insert(v1.end(), 200);
    printV(v1);
    return 0;
}
```

## 二、deque的基本操作

双端数组的基本操作；

代码如下：

```cpp
#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

void printD(deque<int> &d){
    deque<int>::iterator it; 
    for(it = d.begin(); it != d.end(); it++){
        cout<<*it<<" ";
    }   
    cout<<endl;
}

int main(void){
    deque<int> d1; 
    d1.push_back(1);
    d1.push_back(3);
    d1.push_back(5);

    d1.push_front(-11);
    d1.push_front(-33);
    d1.push_front(-55);

    cout<<"头部元素:"<<d1.front()<<endl;
    cout<<"尾部元素:"<<d1.back()<<endl;
    printD(d1);
    d1.pop_front();
    d1.pop_back();
    printD(d1);

    //查找-33在数组中的下标
    deque<int>::iterator it;
    it = find(d1.begin(), d1.end(), -33);
    if(it != d1.end()){
        cout<<"-33数组的下标是:"<<distance(d1.begin(), it)<<endl; //查找下标;
    }else{
        cout<<"没有找到值为-33"<<endl;
    }

    return 0;
}
```

## 三、stack的基本操作

代码如下：

```cpp
#include<iostream>
#include<stack>
using namespace std;

class Teacher{
    public:
        void printS(){
            cout<<"age :"<<age<<endl;
        }
    public:
        int age;
        char name[15];
};

int main(void){
    Teacher t1,t2,t3;

    t1.age = 31;
    t2.age = 32;
    t3.age = 33;

    stack<Teacher *> s;
    s.push(&t1);
    s.push(&t2);
    s.push(&t3);

    while(!s.empty()){
        Teacher *tmp = s.top();
        tmp->printS();
        s.pop();
    }

    return 0;
}

/*
int main(void){
    Teacher t1,t2,t3;

    t1.age = 31;
    t2.age = 32;
    t3.age = 33;

    stack<Teacher> s;
    s.push(t1);
    s.push(t2);
    s.push(t3);

    while(!s.empty()){
        Teacher tmp = s.top();
        tmp.printS();
        s.pop();
    }

    return 0;
}
*/
/*
int main(void){
    stack<int> s;

    //入栈
    for(int i = 0; i < 10; i++){
        s.push(i+1);
    }

    cout<<s.size()<<endl; //栈的大小
    //出栈
    while(!s.empty()){
        int tmp = s.top(); //获取栈顶元素
        cout<<tmp<<" ";
        s.pop();
    }
    cout<<endl;

    return 0;
}
*/
```

## 四、queue的基本操作

代码如下：

```cpp
#include<iostream>
#include<queue>
using namespace std;

class Teacher{
    public:
        int age;
        char name[25];
    public:
        void printQ(){
            cout<<"age :"<<age<<endl;
        }
};

int main(void){
    Teacher q1, q2, q3;

    q1.age = 31;
    q2.age = 32;
    q3.age = 33;

    queue<Teacher *> q;
    q.push(&q1);
    q.push(&q2);
    q.push(&q3);

    while(!q.empty()){
        Teacher *tmp;
        tmp = q.front(); //获取队列头的元素
        tmp->printQ();
        q.pop();
    }

    return 0;
}


/*
//队列中的基础数据类型,
int main(void){
    queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);


    cout<<"对头元素:"<<q.front()<<endl;
    cout<<"队列的大小"<<q.size()<<endl;

    while(!q.empty()){
        cout<<q.front()<<" ";
        q.pop();
    }
    cout<<endl;
    return 0;
}
*/
```

## 五、priority_queue的基本操作

代码如下：

```cpp
#include<iostream>
#include<queue>
using namespace std;

int main(void){
    priority_queue<int> p1; //默认的情况下:是最大优先级队列;
    priority_queue<int, vector<int>, less<int> > p2; 
    priority_queue<int, vector<int>, greater<int> > p3; //是最小的优先级队列

    p1.push(33);
    p1.push(11);
    p1.push(22);
    p1.push(77);
    p1.push(55);
    p1.push(99);

    cout<<"队头元素:"<<p1.top()<<endl;
    cout<<"队列的大小:"<<p1.size()<<endl;

    while(!p1.empty()){
        cout<<p1.top()<<" "; //获取队头的是top();
        p1.pop();
    }   
    cout<<endl;

    cout<<"--------------------测试最小值优先级队列---------------------"<<endl;
    p3.push(33);
    p3.push(11);
    p3.push(22);
    p3.push(77);
    p3.push(55);
    p3.push(99);

    cout<<"队头元素:"<<p3.top()<<endl;
    cout<<"队列的大小:"<<p3.size()<<endl;

    while(!p3.empty()){
        cout<<p3.top()<<" "; //获取队头的是top();
        p3.pop();
    }
    cout<<endl;

    return 0;
}
```

## 六、list的基本操作

### 6.1、list的遍历

代码如下：

```cpp
#include<iostream>
#include<list>
using namespace std;

void printL(list<int> &l){
    list<int>::iterator it; 
    for(it = l.begin(); it != l.end(); it++){
        cout<<*it<<" ";
    }   
    cout<<endl;    
}

//迭代器中的begin()和end()代表的含义：begin代表的是第一个元素的位置,end代表的是最后一个元素的下一个元>
素的位置;
int main(void){
    list<int> l;

    cout<<"list的大小:"<<l.size()<<endl;
    for(int i = 0; i < 10; i++){
        l.push_back(i);
    }   

    printL(l);
    //list不能随即访问;
    list<int>::iterator it = l.begin();
    it++;
    it++;
    it++;
    l.insert(it, 100); //STL中的插入默认是前插;
    printL(l);


//1、list链表的节点的index是从0位置开始的
//2、insert方法都是默认的前插
    return 0;
}
```

### 6.2、list的删除

代码如下：

```cpp
#include<iostream>
#include<list>
using namespace std;


void printL(list<int> &l){
    list<int>::iterator it;
    for(it = l.begin(); it != l.end(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}
//list删除
int main(void){
    list<int> l;

    for(int i = 0; i < 10; i++){
        l.push_back(i);
    }   

    list<int>::iterator it1 = l.begin();
    list<int>::iterator it2 = l.begin();
    it2++;
    it2++;
    it2++;

    l.erase(it1, it2); //删除是左闭右开的操作;[0, 3)
    printL(l);

    l.erase(l.begin());
    printL(l);

    l.insert(l.begin(), 100);
    l.insert(l.begin(), 100);
    l.insert(l.begin(), 100);
    l.insert(l.begin(), 100);
    l.insert(l.begin(), 100);
    printL(l);

    l.remove(100); //删除元素的方法,删除了所有值为100的元素;
    printL(l);

    return 0;
}
```

## 七、说明

原创文章链接：[C++进阶系列之STL（5）---vector，deque，list相关操作](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484009&idx=1&sn=fc69d8e7a266b383193492791c2d11b1&chksm=f94c8854ce3b01426ae280b09852432458f7bd5cef93627f88024136533ccccdc456a08b2d6c&scene=21#wechat_redirect)
