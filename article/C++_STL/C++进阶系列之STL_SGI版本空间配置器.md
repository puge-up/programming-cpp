- [一、STL中的空间配置器](#一stl中的空间配置器)
- [二、一级空间配置器](#二一级空间配置器)
  - [2.1、为内存不足做好准备](#21为内存不足做好准备)
  - [2.2、抽取的代码实现](#22抽取的代码实现)
  - [2.3、一级空间配置器总结](#23一级空间配置器总结)
- [三、二级空间配置器](#三二级空间配置器)
- [四、完整代码、测试代码、测试结果](#四完整代码测试代码测试结果)
  - [4.1、完整代码](#41完整代码)
  - [4.2、测试代码](#42测试代码)
  - [4.3、测试结果](#43测试结果)
- [五、STL中的不成文规定](#五stl中的不成文规定)
- [六、说明](#六说明)

## 一、STL中的空间配置器

在STL中，空间配置器分了2组，分别为一级空间配置器和二级空间配置器，但是它们都有自己各自运用的场合；一般说来，一级空间配置器一般分配的空间大于128B，二级空间配置器的分配空间为小于128B。

其中SGI 中的STL的空间配置器设计哲学如下：

1. 向system heap要求申请空间
2. 考虑多线程的状态
3. 考虑内存不足时的应变措施
4. 考虑过多"小型区块"可能造成的内存碎片问题

**在剖析源码时，为了将问题控制在一定的复杂度内，以下源码皆排除多线程状态的处理；**

- 0：表示非多线程版本；
- inst : 表示不关注多线程的问题；

## 二、一级空间配置器

### 2.1、为内存不足做好准备

- 抛出异常，也就是输出一句话；
- 调用自己设置的函数去处理(比如说是释放一些空间，回收一些碎片的空间)；

**一级空间配置器的本质：模仿实现了set_new_handler机制；**

set_new_handler机制的实现：

1. 定义一个函数指针；
2. 定义一个函数；
3. 赋值比较；

### 2.2、抽取的代码实现

```cpp
#if 1
#include<iostream>
#include<new>
#include<malloc.h>
using namespace std;
//#define __THROW_BAD_ALLOC   throw   bad_alloc
#define __THROW_BAD_ALLOC  cerr<<"Throw bad alloc, Out Of Memory."<<endl; exit(1)  //定义异常,就是输出一句话,并且结束程序.
#elif  !defined  (__THROW_BAD_ALLOC) //如果没有定义这个异常,下面就定义
#include<iostream.h>
#define __THROW_BAD_ALLOC   cerr<<"out of memory"<<endl; exit(1);
#endif

template<int inst>
class __malloc_alloc_template{
private:
    static void* oom_malloc(size_t);  //对申请空间失败的处理函数
    static void* oom_realloc(void *, size_t);  //对扩展空间失败处理的函数
    static void(* __malloc_alloc_oom_handler)(); //定义一个函数指针

public:
    static void* allocate(size_t n){   //分配空间
        void *result = malloc(n);
        if(0 == result)
            result = oom_malloc(n); //分配空间失败，调用oom_malloc()函数
        return result;  //将申请的空间的地址返回
    }
    static void   deallocate(void *p, size_t){
        free(p);  //释放空间
    }
    static void* reallocate(void *p, size_t, size_t new_sz){
        void *result = realloc(p, new_sz);  //扩展新空间;
        if(0 == result) //扩展失败
            oom_realloc(p,new_sz); //调用扩展空间失败的处理函数
        return result;
    }
public:
    //set_new_handler(Out_Of_Memory);
    static void(*set_malloc_handler(void(*f)()))(){  //这是一个指针函数,函数名称:set_malloc_handler,参数:是一个函数指针,返回值:是一个函数指针;
        void(*old)() = __malloc_alloc_oom_handler;  //将原有空间的地址保存在old中;
        __malloc_alloc_oom_handler = f;  //将自己定义的函数地址给__malloc_alloc_oom_handler;
        return old;  //每次可以保存其上一次的地址.
    }
};

template<int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0; //对定义的静态函数指针初始化为0;

template<int inst>
void* __malloc_alloc_template<inst>::oom_malloc(size_t n){ //处理空间失败的问题
    void *result;
    void(* my_malloc_handler)(); //定义一个函数指针;
                                  
    for(;;){
        my_malloc_handler = __malloc_alloc_oom_handler;  
        if(0 == my_malloc_handler){ //自己没有定义处理空间失败的新函数
            __THROW_BAD_ALLOC;  //异常抛出;程序终止;
        }
        (*my_malloc_handler)(); //调用自己编写的处理函数(一般都是回收空间之类的);
        result = malloc(n);  //在此申请分配空间
        if(result){ //申请成功
            return result; //将地址返回;
        }//那么，这个程序将会一直持续到空间分配成功才最终返回.
    }
}


template<int inst>
void* __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n){
    void(*my_malloc_handler)();  //函数指针
    void *result;
    for(;;){
        my_malloc_handler = __malloc_alloc_oom_handler; //将这个给其赋值
        if(0 == my_malloc_handler){  //外面没有定义处理的函数
            __THROW_BAD_ALLOC;  //异常抛出,程序结束.
        }
        (*my_malloc_handler)();  //调用自己编写的处理函数(一般都是回收空间之类的);
        result = realloc(p, n);  //再次扩展空间分配;
        if(result){  //扩展成功,就返回
            return result;
        }  //一直持续成功，知道扩展空间分配成功才返回;
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;   //一级空间配置器:malloc_alloc;
```

第一级空间配置器就是：

1. 对malloc、free的简单封装；
2. 模拟C++的set_new_handler()已处理内存不足的情况；

### 2.3、一级空间配置器总结

1. **一级空间配置器其实就是先自己开辟空间，要是失败了;**
2. **调用处理空间失败的函数，在其内部，先看我们自己在外面有没有写针对这个的处理函数，要是没写，就是异常抛出，程序结束；**
3. **要是写了，就调用我们自己写的函数，在次分配空间，进入死循环中，直到空间分配成功，方可退出循环；**

还要注意的是：

```cpp
static void(*set_malloc_handler(void(*f)()))()；这是一个指针函数;
```

## 三、二级空间配置器

1、当所分配的空间小于128B时，则以内存池去管理 ; 对小额区块，自动将内存调至8的倍数,并维护16个自由链表,各自管理大小分别为: 8 16 24 32 40 48 56 ....128B的小额区块;

2、刚开始所分配的内存空间，一半当做自由链表，一半当做内存池；当再次分配同样大小的空间时，直接先从自由链表中分配；当再次分配其他大小空间时，先看内存池中有无空间,有的话，直接分配，挂载即可。

模型如下：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8Ewv0SGJjibUT2bFhZv9s3qj9gJhBq6ZyG86icnSOdV1a3I89ZfwYMtenZNQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

整个分配空间都是很节省化的:

其抽取代码如下：

```cpp
//二级空间配置器由自由链表和内存池组成;
enum {__ALIGN = 8};  //一块链表8B
enum {__MAX_BYTES  = 128};  //小于128B调用二级的
enum {__NFREELISTS = __MAX_BYTES / __ALIGN}; //一共分配16个自由链表,负责16种次分配能力.

template<bool threads, int inst>  //不考虑多线程状态;
class __default_alloc_template{
public:
    static void* allocate(size_t n);  //分配空间
    static void  deallocate(void *p, size_t n);  //销毁空间
    static void* reallocate(void *p, size_t, size_t new_sz);  //扩展空间
private:
    static size_t  ROUND_UP(size_t bytes){  //向上调整函数;
        return (((bytes) + __ALIGN-1) & ~(__ALIGN-1)); //调为当前字节是8的整数倍.
    }
private:
    union obj{  //共用体
        union obj * free_list_link;  //自由链表的指向
        char client_data[1];
    };
private:
    static obj* volatile free_list[__NFREELISTS];  //定义了一个指针数组;
    static size_t FREELIST_INDEX(size_t bytes){  //求当前字节的自由链表的下标;
        return ((bytes)+__ALIGN-1) / __ALIGN-1;
    }
private:
    static char *start_free; //开始空间的下标
    static char *end_free;   //结束空间的下标
    static size_t heap_size;  //堆空间大小
    static void *refill(size_t n);  //填充函数
    static char* chunk_alloc(size_t size, int &nobjs);  //
};


template<bool threads, int inst> //以下都是对静态变量的初始化,都为0;
char* __default_alloc_template<threads, inst>::start_free = 0;
template<bool threads, int inst>
char* __default_alloc_template<threads, inst>::end_free = 0;
template<bool threads, int inst>
size_t __default_alloc_template<threads, inst>::heap_size = 0;
template<bool threads, int inst>
typename __default_alloc_template<threads, inst>::obj* volatile
__default_alloc_template<threads, inst>::free_list[__NFREELISTS] = 
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

template<bool threads, int inst>
void* __default_alloc_template<threads, inst>::allocate(size_t n){ //分配空间的函数
    obj * volatile *my_free_list;
    obj *result;

    if(n > __MAX_BYTES){  //分配空间的大小大于128B的话，就调用一级空间配置器
        return malloc_alloc::allocate(n);
    }

    my_free_list = free_list + FREELIST_INDEX(n); //free_list是二维数组名称,找往哪个链下挂；
    result = *my_free_list;  //取出其值,因为my_free_list是二阶指针;

    if(result == 0){  //没有内存池空间;
        void *r = refill(ROUND_UP(n));  //调用refill()函数
        return r;
    }

    *my_free_list = result->free_list_link;  //进行挂载连接;
    return result; 
}

template<bool threads, int inst>
void* __default_alloc_template<threads, inst>::refill(size_t n){ //没有可用区块时,就调用refill()函数;
    int nobjs = 20;//就是要分20块;
    char *chunk = chunk_alloc(n, nobjs); //调用内存池函数;
    obj * volatile *my_free_list;

    obj *result;
    obj *current_obj, *next_obj;
    int i;

    if(1 == nobjs){  //当分配到只有一块空间时,直接返回.
        return chunk;
    }

    my_free_list = free_list + FREELIST_INDEX(n); //找到对应的下标，进行连接的工作;
    result = (obj*)chunk;
    *my_free_list = next_obj = (obj*)(chunk+n);

    for(i=1; ; ++i){
        current_obj = next_obj;
        next_obj = (obj*)((char*)next_obj+n);
        if(nobjs - 1 == i){  //进行连接工作;
            current_obj->free_list_link = 0;
            break;
        }else{
            current_obj->free_list_link = next_obj;
        }
    }
    return result; 
}

template<bool threads, int inst>
char* __default_alloc_template<threads, inst>::chunk_alloc(size_t size, int &nobjs){ //内存池函数
    char *result; //关键要明白以下的各种情况;
    size_t total_bytes = size * nobjs;   //这里的size已经是上调过的字节;求取20*size个字节的大小
    size_t bytes_left = end_free - start_free; //刚开始，遗留字节为0;
    if(bytes_left >= total_bytes){  //不成立
        result = start_free;
        start_free += total_bytes;
        return result;
    }else if(bytes_left >= size){ //不成立
        nobjs = bytes_left / size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    }else{  //走的就是下面的这条路线
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4); //申请2倍的total_bytes；
        if(bytes_left > 0){ //遗留字节数=0,所以这条语句不成立;
            obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
            ((obj*)start_free)->free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }

        start_free = (char *)malloc(bytes_to_get); //申请空间;
        if(0 == start_free){
            int i;
            obj * volatile *my_free_list, *p;
            for(i=size; i<=__MAX_BYTES; i += __ALIGN){
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if(0 != p){
                    *my_free_list = p->free_list_link;
                    start_free = (char *)p;
                    end_free = start_free + i;
                    return chunk_alloc(size, nobjs);
                }
            }
            end_free = 0;
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);
        }

        heap_size  += bytes_to_get;  //记录此时堆空间的大小;
        end_free = start_free + bytes_to_get;  //指向了最后;
        return chunk_alloc(size, nobjs);  //上去在此调用这个函数;
    }
}
```

**nobjs = 20; 这个是经验值，开辟空间留有余地，方便直接查找，以后就不用再次开辟空间了，提高了效率;**

这个我们自己给不同的字节情况(小于128B的)，就会知道其中发生了什么;

SGI第二级空间配置器：

1. **维护16个自由链表，分别有16种小型区块的配置能力；如果内存不足，调用一级空间配置器(那里有处理程序)；**
2. **如果申请空间的需求大于128B,就调用一级空间配置器。**

总结：

1. **二级空间配置器(最后山穷水尽)--->调用一级空间配置器---->(1)、抛出异常；**
2. **调用自己编写的处理函数；**

> **STL内存配置思想：C++STL是两级配置内存的，具体来说：第一级负责管理大块内存，要保证有类似new-handler的机制；第二级负责管理小块内存，为了更好的管理内存碎片，建立16个链表，每个链表“穿”着一块一块固定大小的内存，这16个链表（0至15）分别“穿”的内存是8、16、24…128倍数关系。需要内存时，从“合适”的链表取走(因为这里情况比较多，不能一一说道了)，如果“合适”的链表内存不够用了，从内存池里拿，如果内存池不够用了，从运行时heap里拿，如果heap也溢出了，就交给第一级配置器，因为它有set_new-handler机制。所以，当堆上的东西用完之后，得赶紧还回来。**

## 四、完整代码、测试代码、测试结果

### 4.1、完整代码

```cpp
#if 1
#include<iostream>
#include<new>
#include<malloc.h>
using namespace std;
//#define __THROW_BAD_ALLOC   throw   bad_alloc
#define __THROW_BAD_ALLOC  cerr<<"Throw bad alloc, Out Of Memory."<<endl; exit(1)  //定义异常,就是输出一句话,并且结束程序.
#elif  !defined  (__THROW_BAD_ALLOC) //如果没有定义这个异常,下面就定义
#include<iostream.h>
#define __THROW_BAD_ALLOC   cerr<<"out of memory"<<endl; exit(1);
#endif

template<int inst>
class __malloc_alloc_template{
private:
    static void* oom_malloc(size_t);  //对申请空间失败的处理函数
    static void* oom_realloc(void *, size_t);  //对扩展空间失败处理的函数
    static void(* __malloc_alloc_oom_handler)(); //定义一个函数指针

public:
    static void* allocate(size_t n){   //分配空间
        void *result = malloc(n);
        if(0 == result)
            result = oom_malloc(n); //分配空间失败，调用oom_malloc()函数
        return result;  //将申请的空间的地址返回
    }
    static void   deallocate(void *p, size_t){
        free(p);  //释放空间
    }
    static void* reallocate(void *p, size_t, size_t new_sz){
        void *result = realloc(p, new_sz);  //扩展新空间;
        if(0 == result) //扩展失败
            oom_realloc(p,new_sz); //调用扩展空间失败的处理函数
        return result;
    }
public:
    //set_new_handler(Out_Of_Memory);
    static void(*set_malloc_handler(void(*f)()))(){  //这是一个指针函数,函数名称:set_malloc_handler,参数:是一个函数指针,返回值:是一个函数指针;
        void(*old)() = __malloc_alloc_oom_handler;  //将原有空间的地址保存在old中;
        __malloc_alloc_oom_handler = f;  //将自己定义的函数地址给__malloc_alloc_oom_handler;
        return old;  //每次可以保存其上一次的地址.
    }
};

template<int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0; //对定义的静态函数指针初始化为0;

template<int inst>
void* __malloc_alloc_template<inst>::oom_malloc(size_t n){ //处理空间失败的问题
    void *result;
    void(* my_malloc_handler)(); //定义一个函数指针;
                                  
    for(;;){
        my_malloc_handler = __malloc_alloc_oom_handler;  
        if(0 == my_malloc_handler){ //自己没有定义处理空间失败的新函数
            __THROW_BAD_ALLOC;  //异常抛出;程序终止;
        }
        (*my_malloc_handler)(); //调用自己编写的处理函数(一般都是回收空间之类的);
        result = malloc(n);  //在此申请分配空间
        if(result){ //申请成功
            return result; //将地址返回;
        }//那么，这个程序将会一直持续到空间分配成功才最终返回.
    }
}


template<int inst>
void* __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n){
    void(*my_malloc_handler)();  //函数指针
    void *result;
    for(;;){
        my_malloc_handler = __malloc_alloc_oom_handler; //将这个给其赋值
        if(0 == my_malloc_handler){  //外面没有定义处理的函数
            __THROW_BAD_ALLOC;  //异常抛出,程序结束.
        }
        (*my_malloc_handler)();  //调用自己编写的处理函数(一般都是回收空间之类的);
        result = realloc(p, n);  //再次扩展空间分配;
        if(result){  //扩展成功,就返回
            return result;
        }  //一直持续成功，知道扩展空间分配成功才返回;
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;   //一级空间配置器:malloc_alloc;

/////////////////////////////////////////////////////////////////////////////////////
//二级空间配置器由自由链表和内存池组成;
enum {__ALIGN = 8};  //一块链表8B
enum {__MAX_BYTES  = 128};  //小于128B调用二级的
enum {__NFREELISTS = __MAX_BYTES / __ALIGN}; //一共分配16个自由链表,负责16种次分配能力.

template<bool threads, int inst>  //不考虑多线程状态;
class __default_alloc_template{
public:
    static void* allocate(size_t n);  //分配空间
    static void  deallocate(void *p, size_t n);  //销毁空间
    static void* reallocate(void *p, size_t, size_t new_sz);  //扩展空间
private:
    static size_t  ROUND_UP(size_t bytes){  //向上调整函数;
        return (((bytes) + __ALIGN-1) & ~(__ALIGN-1)); //调为当前字节是8的整数倍.
    }
private:
    union obj{  //共用体
        union obj * free_list_link;  //自由链表的指向
        char client_data[1];
    };
private:
    static obj* volatile free_list[__NFREELISTS];  //定义了一个指针数组;
    static size_t FREELIST_INDEX(size_t bytes){  //求当前字节的自由链表的下标;
        return ((bytes)+__ALIGN-1) / __ALIGN-1;
    }
private:
    static char *start_free; //开始空间的下标
    static char *end_free;   //结束空间的下标
    static size_t heap_size;  //堆空间大小
    static void *refill(size_t n);  //填充函数
    static char* chunk_alloc(size_t size, int &nobjs);  //
};


template<bool threads, int inst> //以下都是对静态变量的初始化,都为0;
char* __default_alloc_template<threads, inst>::start_free = 0;
template<bool threads, int inst>
char* __default_alloc_template<threads, inst>::end_free = 0;
template<bool threads, int inst>
size_t __default_alloc_template<threads, inst>::heap_size = 0;
template<bool threads, int inst>
typename __default_alloc_template<threads, inst>::obj* volatile
__default_alloc_template<threads, inst>::free_list[__NFREELISTS] = 
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

template<bool threads, int inst>
void* __default_alloc_template<threads, inst>::allocate(size_t n){ //分配空间的函数
    obj * volatile *my_free_list;
    obj *result;

    if(n > __MAX_BYTES){  //分配空间的大小大于128B的话，就调用一级空间配置器
        return malloc_alloc::allocate(n);
    }

    my_free_list = free_list + FREELIST_INDEX(n); //free_list是二维数组名称,找往哪个链下挂；
    result = *my_free_list;  //取出其值,因为my_free_list是二阶指针;

    if(result == 0){  //没有内存池空间;
        void *r = refill(ROUND_UP(n));  //调用refill()函数
        return r;
    }

    *my_free_list = result->free_list_link;  //进行挂载连接;
    return result; 
}

template<bool threads, int inst>
void* __default_alloc_template<threads, inst>::refill(size_t n){ //没有可用区块时,就调用refill()函数;
    int nobjs = 20;//就是要分20块;
    char *chunk = chunk_alloc(n, nobjs); //调用内存池函数;
    obj * volatile *my_free_list;

    obj *result;
    obj *current_obj, *next_obj;
    int i;

    if(1 == nobjs){  //当分配到只有一块空间时,直接返回.
        return chunk;
    }

    my_free_list = free_list + FREELIST_INDEX(n); //找到对应的下标，进行连接的工作;
    result = (obj*)chunk;
    *my_free_list = next_obj = (obj*)(chunk+n);

    for(i=1; ; ++i){
        current_obj = next_obj;
        next_obj = (obj*)((char*)next_obj+n);
        if(nobjs - 1 == i){  //进行连接工作;
            current_obj->free_list_link = 0;
            break;
        }else{
            current_obj->free_list_link = next_obj;
        }
    }
    return result; 
}

template<bool threads, int inst>
char* __default_alloc_template<threads, inst>::chunk_alloc(size_t size, int &nobjs){ //内存池函数
    char *result; //关键要明白以下的各种情况;
    size_t total_bytes = size * nobjs;   //这里的size已经是上调过的字节;求取20*size个字节的大小
    size_t bytes_left = end_free - start_free; //刚开始，遗留字节为0;
    if(bytes_left >= total_bytes){  //不成立
        result = start_free;
        start_free += total_bytes;
        return result;
    }else if(bytes_left >= size){ //不成立
        nobjs = bytes_left / size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    }else{  //走的就是下面的这条路线
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4); //申请2倍的total_bytes；
        if(bytes_left > 0){ //遗留字节数=0,所以这条语句不成立;
            obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
            ((obj*)start_free)->free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }

        start_free = (char *)malloc(bytes_to_get); //申请空间;
        if(0 == start_free){
            int i;
            obj * volatile *my_free_list, *p;
            for(i=size; i<=__MAX_BYTES; i += __ALIGN){
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if(0 != p){
                    *my_free_list = p->free_list_link;
                    start_free = (char *)p;
                    end_free = start_free + i;
                    return chunk_alloc(size, nobjs);
                }
            }
            end_free = 0;
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);
        }

        heap_size  += bytes_to_get;  //记录此时堆空间的大小;
        end_free = start_free + bytes_to_get;  //指向了最后;
        return chunk_alloc(size, nobjs);  //上去在此调用这个函数;
    }
}
```

### 4.2、测试代码

```cpp
#include<iostream>
#include<stdlib.h>
#include"stl_alloc.h"
using namespace std;

int main(){
    int *p = (int *)__default_alloc_template<0,0>::allocate(sizeof(int));
    int *s = (int *)__default_alloc_template<0,0>::allocate(sizeof(int) * 4);
    int *t = (int *)__default_alloc_template<0,0>::allocate(sizeof(int) * 80);
    int *m = (int *)__default_alloc_template<0,0>::allocate(sizeof(double) * 10);
    int *n = (int *)__default_alloc_template<0,0>::allocate(sizeof(int) * 100);
    int *u = (int *)__default_alloc_template<0,0>::allocate(sizeof(int));
    int *k = (int *)__default_alloc_template<0,0>::allocate(sizeof(int) *2);
    return 0;
}


/*
void Out_Of_Memory(){
    cout<<"Out Of Memory."<<endl;
    exit(1);
}

int main(){
    //__malloc_alloc_template<0>::set_malloc_handler(OMG);
    //set_new_handler()
    //int *p = (int*)malloc(sizeof(int)*10);
    void (*pfun)() = __malloc_alloc_template<0>::set_malloc_handler(Out_Of_Memory);
    int *p = (int*)__malloc_alloc_template<0>::allocate(sizeof(int) * 2073741824);


    __malloc_alloc_template<0>::set_malloc_handler(pfun);

    if(p == NULL)
    {
        cout<<"Error."<<endl;
        exit(1);
    }
    cout<<"OK"<<endl;
    return 0;
}
*/
```

### 4.3、测试结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvufcuJCibicCbV0fkWShI8HznyJMTXWvmQFc9ArBEaHKopcUXv2ZmiaWXw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 五、STL中的不成文规定

- __打头的是内部函数
- 一般都是前插
- 指最后的下一个
- fill_n() 系统函数，填充空间

## 六、说明

原创文章链接：[C++进阶系列之STL（2）---SGI版本空间配置器](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483982&idx=1&sn=044e9861bcc16fcbe9226756d73fa094&chksm=f94c8873ce3b016588288c1cde47facd2ce6ccf91a562b11578e819b7dfbf9b9e3c8233fe6e0&scene=21#wechat_redirect)
