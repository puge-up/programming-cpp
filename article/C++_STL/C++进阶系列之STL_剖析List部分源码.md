- [一、STL](#一stl)
- [二、list(双向循环链表)](#二list双向循环链表)
- [三、list部分源码实现剖析](#三list部分源码实现剖析)
  - [3.1、list模型如下](#31list模型如下)
  - [3.2、list的构造函数和析构函数](#32list的构造函数和析构函数)
  - [3.3、list的迭代器](#33list的迭代器)
- [四、总结](#四总结)
- [五、说明](#五说明)

## 一、STL

**库函数的设计第一位是通用性，模板为其提供了可能；标准模板库中的所有算法和容器都是通过模板实现的。**

**STL(标准模板库)是 C++最有特色，最实用的部分之一。**

STL整个架构模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcbYBRibqTq5GHxUYzLXydVfvfkNYqEvegJFsom7PjBawcP8RmJY4kgsg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、list(双向循环链表)

调用STL系统的 list，用系统的双向循环链表结构处理：

```cpp
#include<iostream>
#include<list> //调用系统的list,双向循环链表结构
using namespace std;

int main(void){
     
    list<int> mylist;
    for(int i = 1; i <= 10; i++){
        mylist.push_back(i);  //接口，末尾增加
    }
    list<int>::iterator it = mylist.begin(); //迭代器，
    while(it != mylist.end()){
        cout<<*it<<"-->"; //打印内部数字
        ++it;   //每次往后移一个
    }
    cout<<"NULL"<<endl;
}
```

## 三、list部分源码实现剖析

### 3.1、list模型如下

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbu026TbKHtyEBTlTLXk8eTcYwjtoC22kpDNLFsOYKHvdt8POGIXdfEXf9baLQHQglvOQ4Bj1FKKicQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

阅读其源代码，分析了部分的功能：

```cpp
#ifndef _LIST_H   //条件宏编译，避免重复定义
#define _LIST_H

#include<assert.h>   //断言引入的头文件
#include<malloc.h>   //申请空间所引入的头文件

template<class _Ty> //此处先不涉及空间置配器
class list{    //list类
public:
    struct _Node;
    typedef struct _Node* _Nodeptr;  //指向节点的指针类型
    struct _Node{   //_Node这个是节点类型
        _Nodeptr _Prev;    //前驱节点
        _Nodeptr _Next;    //后继节点
        _Ty      _Value;   //模板数据类型
    };
    struct _Acc{  //定义_Acc这个类型
        typedef struct _Node*& _Nodepref;  //指向节点类型指针的引用
        typedef _Ty&           _Vref;      //这个数据类型的引用
        static _Nodepref _Next(_Nodeptr _P)//静态方法， 返回值是节点指针的引用 ，参数是指向节点的指针
        {return ((_Nodepref)(*_P)._Next);}//：*_P得到这个节点，()强制类型转换的优先级没有.高，所以此时先取_Next，在进行强制类型转换的工作，返回一个指向节点指针的引用。
        static _Nodepref _Prev(_Nodeptr _P)
        {return ((_Nodepref)(*_P)._Prev);}
        static _Vref _Value(_Nodeptr _P)
        {return ((_Vref)(*_P)._Value);} 
    };
public:  //以下的类型是_A这个类下面的类型，_A这个类在空间置配器中定义
    typedef typename _A::value_type           value_type;
    typedef typename _A::pointer_type         pointer_type;
    typedef typename _A::const_pointer_type   const_pointer_type;
    typedef typename _A::reference_type       reference_type;
    typedef typename _A::const_reference_type const_reference_type;
    typedef typename _A::size_type            size_type;  //这个类型其实就是size_t

private:
    _Nodeptr  _Head;   //指向头结点的指针
    size_type _Size;   //有几个节点个数
};

#endif
```

以上代码主要是struct  _Acc这个类的理解好至关重要！！！

### 3.2、list的构造函数和析构函数

```cpp
public:
    explicit list():_Head(_Buynode()),_Size(0)  //explicit显示调用此构造函数，给头一个指向，刚开始0个
    {}
    ~list()
    {     //释放空间和空间配置器有关，在现阶段先不关心。
        erase(begin(), end());  //调用开始，结束函数释放空间；
        _Freenode(_Head);       //释放头；
        _Head = 0, _Size = 0;   //都赋空；
    }
    ..................................................
protected:
    _Nodeptr _Buynode(_Nodeptr _Narg=0, _Nodeptr _Parg=0)  // 返回值为节点指针类型，参数都为节点指针类型，传的应该是后继和前驱指针，默认都为0；
    {
        _Nodeptr _S = (_Nodeptr)malloc(sizeof(_Node));//申请一个节点空间，把地址给了_S;
        
        assert(_S != NULL);  //所申请的空间存在的话
        _Acc::_Next(_S) = _Narg!=0 ? _Narg : _S; //给新生成的节点的_Next赋值
        _Acc::_Prev(_S) = _Parg!=0 ? _Parg : _S; //给新生成的节点的_Prev赋值
        return _S; //返回这个新生成节点的地址
    }
//这个_Buynode函数的意思是：当创建的是第一个节点时，自己一个节点连向自己，构成双向循环链表，其他的情况则是插入到两个节点之间！！！
........................................................
```

### 3.3、list的迭代器

```cpp
public:
    class iterator{   //迭代器也是一个类，是list的内部类；
    public:
        iterator()
        {}
        iterator(_Nodeptr _P):_Ptr(_P)
        {}
    public:
        iterator& operator++(){  // ++it,前++的运算符重载
            _Ptr=_Ptr->_Next; //因为是链表结构，内部实现迭代器的++,是进行了++的重载；使其指针的移动到下一个节点；
            return *this;   //返回的是这个节点的引用。
        }
        iterator operator++(int)// it++
        {
            _It it(_Ptr);  //先保存原先节点
            _Ptr = _Ptr->_Next; //移到下一个节点
            return it;  //返回原先的；
        }
        iterator operator--(int); //类似
        iterator& operator--();
        reference_type operator*()const //对*的重载
        {return _Ptr->_Value;}   //返回这个节点的_Value值
        pointer_type operator->()const //对->的重载
        //{return &_Ptr->_Value;}  自己实现的，->的优先级高于&，所以将_Value的地址返回
        {return (&**this);}  //系统中的，this是迭代器的地址，*this是迭代器对象，再来一个*时，调用上面的(对*的重载)，此时还是返回_Value的地址。
    public:
        bool operator!=(const iterator &it)const  //迭代器对象的比较
        {return _Ptr!=it._Ptr;}  //比的是指向节点的指针；
    public:
        _Nodeptr _Mynode()const //得到当前节点的地址；
        {return _Ptr;}
    protected:
        _Nodeptr _Ptr;   //迭代器的数据成员是一个指向节点的指针。
    };
    typedef iterator _It;  //_It 就是迭代器类型
public:
    iterator begin(){return iterator(_Acc::_Next(_Head));}  //begin()函数得到头结点的后继(第一个有效节点的地址)
    iterator begin()const;
    iterator end(){return iterator(_Head);}  //end()函数得到的是头结点(也就是最后一个节点的后继地址);
public:                        //前面的已经讲的很清楚了，后面的都是调用即可；
    void push_back(const _Ty &x)  
    {insert(end(),x);}
    void push_front(const _Ty &x)
    {insert(begin(),x);}
public:
    iterator insert(iterator _P, const _Ty &_X=_Ty())
    {
        _Nodeptr _S = _P._Mynode();  //得到节点地址
        _Acc::_Prev(_S) = _Buynode(_S, _Acc::_Prev(_S));  //下面的三句调用前面的函数_Buynode()实现了插入功能;
        _S = _Acc::_Prev(_S);
        _Acc::_Next(_Acc::_Prev(_S)) = _S;
        ++_Size;  //个数加1
        return iterator(_S);
    }
    void insert(iterator _P, size_type _M, const _Ty &_X) //插入个数_M个，以下几个调用前面函数；
    {
        for(; 0<_M; --_M)
            insert(_P,_X);
    }
    void insert(iterator _P, const _Ty *_F, const _Ty *_L) //区间的插入
    {
        for(; _F!=_L; ++_F)
            insert(_P, *_F);
    }
    void insert(iterator _P, _It _F, _It _L)  //迭代器的插入
    {
        for(; _F!=_L; ++_F)
            insert(_P, *_F);
    }
    /*
    void push_back(const _Ty &x)  //尾随增加最后
    {
        _Nodeptr _S = _Buynode(_Head, _Acc::_Prev(_Head)); //实现插入功能
        _Acc::_Value(_S) = x;
        _Acc::_Next(_Acc::_Prev(_Head)) = _S;
        _Acc::_Prev(_Head) = _S;
        _Size++;  //最后加1
    }

    iterator erase(iterator _P)// 删除空间
    {
        _Nodeptr _S = (_P++)._Mynode();
        _Acc::_Next(_Acc::_Prev(_S)) = _Acc::_Next(_S);
        _Acc::_Prev(_Acc::_Next(_S)) = _Acc::_Prev(_S);
 
        --_Size;  //个数减少1个
        return _P;
    }
    iterator erase(iterator _F, iterator _L) //调用函数，删除区间
    {
        while(_F != _L)
            erase(_F++);
        return _F;
    }
    void clear() //清除所有空间
    {erase(begin(), end());}

#endif

```

## 四、总结

1. **迭代器的本质有了了解，是一个内部类，它将是一个对象，内部数据成员是一个指向节点的指针；**
2. **迭代器对->的重载返回的是节点内部数据的地址，而不是节点的地址；**
3. **迭代器对每种数据结构的实现均不相同，(Stack, queue, list...........)**
4. **空间配置器：对所有的数据结构而言，只有一份，作用：申请，释放空间，构造，析构对象。**

## 五、说明

原创文章链接：[C++进阶系列之STL（1）---剖析List部分源码](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483978&idx=1&sn=b89b8bc5ff0fdb43c589c2e261aa0dce&chksm=f94c8877ce3b0161680d57a39d3797e15decbea573fd95661af64e213c374cf1b58cab212c65&scene=21#wechat_redirect)
