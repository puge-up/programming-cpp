- [一、模板的特化](#一模板的特化)
- [二、萃取](#二萃取)
- [三、整个搭建框架](#三整个搭建框架)
  - [3.1、框架代码](#31框架代码)
  - [3.2、测试代码](#32测试代码)
  - [3.3、测试结果](#33测试结果)
- [四、分析](#四分析)
- [五、说明](#五说明)

## 一、模板的特化

泛化模板：对各种不同版本的特殊化处理---->特化;

## 二、萃取

**拿相同的代码提取不同的类型；**

## 三、整个搭建框架

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvKIe8bdo5z3qqRKYnOaw5HiaaOfbDXVoPbiaTcLFuuT6lEt0x9G8ibOLbQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**在这里已经不关心空间配置器是如何实现的；**

### 3.1、框架代码

```cpp
#ifndef _MEMORY_H_
#define _MEMORY_H_

#include"stl_alloc.h"
#include"stl_iterator.h"
#include"type_traits.h"
#include"stl_construct.h"
#include"stl_uninitialized.h"

#endif
////////////////////////////////////////////////////////////////////////////////////

#if 1
#include<iostream>
#include<new>
#include<malloc.h>
using namespace std;
//#define __THROW_BAD_ALLOC   throw   bad_alloc
#define __THROW_BAD_ALLOC  cerr<<"Throw bad alloc, Out Of Memory."<<endl; exit(1)
#elif  !defined  (__THROW_BAD_ALLOC)
#include<iostream.h>
#define __THROW_BAD_ALLOC   cerr<<"out of memory"<<endl; exit(1);
#endif

template<int inst>
class __malloc_alloc_template{
private:
    static void* oom_malloc(size_t);
    static void* oom_realloc(void *, size_t);
    static void(* __malloc_alloc_oom_handler)();

public:
    static void* allocate(size_t n){
        void *result = malloc(n);
        if(0 == result){
            result = oom_malloc(n);
        }
        return result;
    }
    static void   deallocate(void *p, size_t){
        free(p);
    }
    static void* reallocate(void *p, size_t, size_t new_sz){
        void *result = realloc(p, new_sz);
        if(0 == result){
            oom_realloc(p,new_sz);
        }
        return result;
    }
public:
    //set_new_handler(Out_Of_Memory);
    static void(*set_malloc_handler(void(*f)()))(){
        void(*old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return old;
    }
};

template<int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template<int inst>
void* __malloc_alloc_template<inst>::oom_malloc(size_t n){
    void *result;
    void(* my_malloc_handler)();

    for(;;){
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(0 == my_malloc_handler){ 
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)();
        result = malloc(n);
        if(result){
            return result;
        }
    }
}


template<int inst>
void* __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n){
    void(*my_malloc_handler)();
    void *result;
    for(;;){
        my_malloc_handler = __malloc_alloc_oom_handler;
        if(0 == my_malloc_handler){
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)();
        result = realloc(p, n);
        if(result){
            return result;
        }
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;

/////////////////////////////////////////////////////////////////////////////////////

enum {__ALIGN = 8};
enum {__MAX_BYTES  = 128};
enum {__NFREELISTS = __MAX_BYTES / __ALIGN};

template<bool threads, int inst>
class __default_alloc_template{
public:
    static void* allocate(size_t n);
    static void  deallocate(void *p, size_t n);
    static void* reallocate(void *p, size_t, size_t new_sz);
private:
    static size_t  ROUND_UP(size_t bytes){
        return (((bytes) + __ALIGN-1) & ~(__ALIGN-1));
    }
private:
    union obj{
        union obj * free_list_link;
        char client_data[1];
    };
private:
    static obj* volatile free_list[__NFREELISTS];
    static size_t FREELIST_INDEX(size_t bytes){
        return ((bytes)+__ALIGN-1) / __ALIGN-1;
    }
private:
    static char *start_free;
    static char *end_free;
    static size_t heap_size;
    static void *refill(size_t n);
    static char* chunk_alloc(size_t size, int &nobjs);
};


template<bool threads, int inst>
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
void* __default_alloc_template<threads, inst>::allocate(size_t n){
    obj * volatile *my_free_list;
    obj *result;

    if(n > __MAX_BYTES){
        return malloc_alloc::allocate(n);
    }

    my_free_list = free_list + FREELIST_INDEX(n);
    result = *my_free_list;

    if(result == 0){
        void *r = refill(ROUND_UP(n));
        return r;
    }

    *my_free_list = result->free_list_link;
    return result; 
}

template<bool threads, int inst>
void* __default_alloc_template<threads, inst>::refill(size_t n){
    int nobjs = 20;
    char *chunk = chunk_alloc(n, nobjs);
    obj * volatile *my_free_list;

    obj *result;
    obj *current_obj, *next_obj;
    int i;

    if(1 == nobjs){
        return chunk;
    }

    my_free_list = free_list + FREELIST_INDEX(n);
    result = (obj*)chunk;
    *my_free_list = next_obj = (obj*)(chunk+n);

    for(i=1; ; ++i){
        current_obj = next_obj;
        next_obj = (obj*)((char*)next_obj+n);
        if(nobjs - 1 == i){
            current_obj->free_list_link = 0;
            break;
        }else{
            current_obj->free_list_link = next_obj;
        }
    }
    return result;
}

template<bool threads, int inst>
char* __default_alloc_template<threads, inst>::chunk_alloc(size_t size, int &nobjs){
    char *result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free;
    if(bytes_left >= total_bytes){
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    else if(bytes_left >= size){
        nobjs = bytes_left / size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    }else{
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        if(bytes_left > 0){
            obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
            ((obj*)start_free)->free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }

        start_free = (char *)malloc(bytes_to_get);
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

        heap_size  += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return chunk_alloc(size, nobjs);
    }
}

/////////////////////////////////////////////////////////////////////////////////
#ifdef __USE_MALLOC
typedef malloc_alloc  alloc;
#else
typedef __default_alloc_template<0,0> alloc;
#endif

template<class T, class Alloc>
class simple_alloc{ 
public:
    static T* allocate(size_t n){
        return 0==n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
    }
    static T* allocate(void){
        return (T*)Alloc::allocate(sizeof(T));
    }
    static void deallocate(T *p, size_t n){
        if(0!=n) Alloc::deallocate(p, n*sizeof(T));
    }
    static void deallocate(T *p){
        Alloc::deallocate(p,sizeof(T));
    }
};
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STL_CONFIG_H
#define __STL_CONFIG_H

//#define __USE_MALLOC


#endif

//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __STL_CONSTRUCT_H
#define __STL_CONSTRUCT_H

template <class T1, class T2>
void construct(T1* p, const T2& value){
      new (p) T1(value);
}

#endif
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STL_ITERATOR_H
#define __STL_ITERATOR_H

template <class T>
T* value_type(const T*){
    return (T*)(0); 
}

#endif
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STL_UNINITIALIZED_H
#define __STL_UNINITIALIZED_H


template<class ForwardIterator, class Size, class T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, 
                                                const T &x, _true_type){
    cout<<"yyyyyyyyyyy"<<endl;
    return fill_n(first, n, x);
}

template<class ForwardIterator, class Size, class T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, 
                                            const T &x, _false_type){
    ForwardIterator cur = first;
    for(; n>0; --n, ++cur){
        cout<<"xxxxxxxxxxxx"<<endl;
        construct( &*cur, x); //construct(cur, x);
    }
    return cur;
}


template<class ForwardIterator, class Size, class T, class T1>
ForwardIterator _uninitialized_fill_n(ForwardIterator first, Size n, const T &x,  T1*){
    //typedef _false_type  is_POD;
    typedef typename _type_traits<T1>::is_POD_type   is_POD;
    //return _uninitialized_fill_n(first, n, x, _false_type());
    return _uninitialized_fill_n_aux(first, n, x, is_POD());
}

template<class ForwardIterator, class Size, class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T &x){
    return _uninitialized_fill_n(first, n, x, value_type(first));
}

#endif
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STL_VECTOR_H
#define __STL_VECTOR_H

template<class T, class Alloc=alloc>
class vector{
public:
    typedef T           value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef value_type& reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
public:
    vector() : start(0), finish(0), end_of_storage(0){}
    vector(size_type n){
        fill_initialize(n, T());
    }
protected:
    void fill_initialize(size_type n, const T &value){
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }
    iterator allocate_and_fill(size_type n, const T &x){
        iterator result = data_allocator::allocate(n);
        uninitialized_fill_n(result, n, x);
        return result;
    }
protected:
    typedef simple_alloc<value_type, Alloc> data_allocator;
    iterator start;
    iterator finish;
    iterator end_of_storage;
};


#endif
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TYPE_TRAITS_H
#define __TYPE_TRAITS_H


//

struct _true_type {};
struct _false_type{};

template <class type>
struct _type_traits { 
    typedef _true_type     this_dummy_member_must_be_first;
    typedef _false_type    has_trivial_default_constructor;
    typedef _false_type    has_trivial_copy_constructor;
    typedef _false_type    has_trivial_assignment_operator;
    typedef _false_type    has_trivial_destructor;
    typedef _false_type    is_POD_type;
};

template<>
struct _type_traits<int> {
    typedef _true_type    has_trivial_default_constructor;
    typedef _true_type    has_trivial_copy_constructor;
    typedef _true_type    has_trivial_assignment_operator;
    typedef _true_type    has_trivial_destructor;
    typedef _true_type    is_POD_type;
};

#endif
///////////////////////////////////////////////////////////////////////////////////////
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include"memory.h"
#include"stl_vector.h"

#endif
///////////////////////////////////////////////////////////////////////////////////////
```

### 3.2、测试代码

```cpp
#include<iostream>
#include<stdlib.h>
#include"vector.h"
using namespace std;

class Test{};

int main(){
    vector<Test> v(10);  //开辟了10个元素的空间;
    return 0;
```

### 3.3、测试结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvfLTWeicwVOGrpknWQSdeSvl7baDZiaCvjribcS5UFIALAjE6A1D8zyH9A/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 四、分析

1. **vector的空间灵活性更高；**
2. **POD：也就是标量型别，也就是传统的型别，采取最保险安全的做法,调用构造函数；否则的话，就是调用系统的，基本类型就是true；**
3. **空构造了2个类型，针对不同萃取得到其_false_type或_true_type ; 就可以调用不同的函数，进行空间的分配，存在效率上的差异，_true_type：将调用系统的填充函数，效率比较高；**
4. **容器、算法单独好实现，关键是通用性，模板是一种很好的解决方案，真正关键之处还在 : 迭代器的实现；**
5. **空间配置器负责分配、回收空间，只有一个；迭代器针对不同的容器有不同的实现方法!!!**

## 五、说明

原创文章链接：[C++进阶系列之STL（3）---STL的框架实现](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484007&idx=1&sn=043602c820fc2d48716ac93ff36ea793&chksm=f94c885ace3b014c879f5b0bf9b7a2b7881474c4698c9ee0c76e1ff193254380ab60094211a3&scene=21#wechat_redirect)
