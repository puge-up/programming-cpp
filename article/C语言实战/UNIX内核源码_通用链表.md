- [一、结构体的高级部分](#一结构体的高级部分)
  - [1.1、一段如下代码](#11一段如下代码)
  - [1.2、运行结果](#12运行结果)
  - [1.3、模型解释](#13模型解释)
- [二、三种链表的分析](#二三种链表的分析)
- [三、通用链表的实现](#三通用链表的实现)
  - [3.1、linkList.h 代码如下](#31linklisth-代码如下)
  - [3.2、运行结果](#32运行结果)
  - [3.3、核心思想](#33核心思想)
- [四、说明](#四说明)

## 一、结构体的高级部分

### 1.1、一段如下代码

```c
#include<stdio.h>

typedef struct Teacher{
    char name[64];
    int age;  //求age的偏移量
    int p;
    char *pname;
}Teacher;

int main(void){
//  Teacher *p = NULL;
    Teacher s;
    Teacher *p; 
    p = &s; 
//  int offsize = (int)&(p->age);
//  int offsize = (int)&(((Teacher *)0)->age); 利用映射到0地址空间,求其相对的偏移量大小;
    int offsize = (int)&(p->age) - (int)p;   //利用内存地址直接定位,求偏移的字节数
    printf("%d\n", offsize);
    
    return 0;
}
```

### 1.2、运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtsRjn7qrbM9nOQRkWzyCJ1hibgry1eZV61JBRFfUYNjLibAqwLAFZn5URWHAicyXUTQhjnsLMO7OR5g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

从结果来看，此时age结构体变量相当于结构体而言，偏移量为64字节。

### 1.3、模型解释

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtsRjn7qrbM9nOQRkWzyCJ1m2ODKaRYUDgRTn932w6fDGI071nuiaL5l039DSPxojZMMRRiacNuBNFQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 二、三种链表的分析

1. **传统链表；**
2. **Linux内核链表：使用的就是结构体的偏移量技术来定位的；**
3. **通用链表：因为结构体的第一个成员变量的地址和结构体的地址是同一个地址，所以放一个结构体，内部只有一个成员变量指针，用来进行链表的操作，将具体的算法和数据类型相分离；实现了一种"我不包含万物，万物包含我的"哲学思想；**

模型图如下：
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtsRjn7qrbM9nOQRkWzyCJ1vGQtFoDHPAjbZ9yV6lV2FYrfvS62yQJ5DsSrrHZWfUpiaNCpgia3NDvg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

通用链表的模型图：
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtsRjn7qrbM9nOQRkWzyCJ1EnqyUwVbYvfav19LqpRHHVbUuaUwumBREZnhziaEIaViabuoeUk8RZTw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、通用链表的实现

### 3.1、linkList.h 代码如下

```c
#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_
#include<malloc.h>
#include<string.h>
typedef void LinkList; 


//核心思想：在用户级别可能自定义数据类型,而底层的实现则是通过void *类型接受用户的数据类型;(void * 可以
接受任何类型的指针类型),最后在通过强制类型转换到相应的数据类型进行使用!!!
typedef struct LINK_NODE{
    struct LINK_NODE *next;
}LINK_NODE;


typedef struct HEAD{
    LINK_NODE head;
    int length;
}HEAD;

LinkList *LinkList_Create();
void LinkList_Destroy(LinkList *list);
void LinkList_Clear(LinkList *list);
int LinkList_Length(LinkList *list);
int LinkList_Insert(LinkList *list, LINK_NODE *node, int pos);
LINK_NODE *LinkList_Get(LinkList *list, int pos);
LINK_NODE *LinkList_Delete(LinkList *list, int pos);

LinkList *LinkList_Create(){
    HEAD *ret = NULL;

    ret = (HEAD *)malloc(sizeof(HEAD));
    memset(ret, 0, sizeof(HEAD));

    ret->length = 0;
    ret->head.next = NULL;

    return ret;

}
void LinkList_Destroy(LinkList *list){
    if(list != NULL){
        free(list);
        list = NULL;
    }

}
//让链表回到初始值
void LinkList_Clear(LinkList *list){
    HEAD *ret = NULL;
    if(list == NULL){
        return;
    }
    ret = (HEAD *)list;
    ret->length = 0;
    ret->head.next = NULL;
}
int LinkList_Length(LinkList *list){
    HEAD *ret = NULL;
    if(list == NULL){
        return -1;
    }
    ret = (HEAD *)list;
    return ret->length;

}
int LinkList_Insert(LinkList *list, LINK_NODE *node, int pos){
    HEAD *tList;
    int i;
    LINK_NODE *current = NULL;

    if(list == NULL || node == NULL || pos < 0){
        printf("func LinkList_Insert() err\n");
        return -1;
    }

    tList = (HEAD *)list;
    current = &(tList->head);
    for(i = 0; i < pos || current->next != NULL; i++){  
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
    tList->length++;

    return 0;
}
LINK_NODE *LinkList_Get(LinkList *list, int pos){
    int i;
    HEAD *tList;
    LINK_NODE *current = NULL;

    if(list == NULL ||  pos < 0){
        printf("func LinkList_Insert() err\n");
        return NULL;
    }

    tList = (HEAD *)list;
    current = &(tList->head);
    for(i = 0; i < pos && (current->next != NULL); i++){
        current = current->next;
    }

    return current->next;   
}
LINK_NODE *LinkList_Delete(LinkList *list, int pos){
    LINK_NODE *ret = NULL;
    int i;
    HEAD *tList;
    LINK_NODE *current = NULL;

    if(list == NULL ||  pos < 0){
        printf("func LinkList_Insert() err\n");
        return NULL;
    }

    tList = (HEAD *)list;
    current = &(tList->head);
    for(i = 0; i < pos && (current->next != NULL); i++){
        current = current->next;
    }

    ret = current->next;
    current->next = ret->next;
    tList->length--;

    return ret;
}
#endif
```

main.c文件内容

```c
#include<stdio.h>
#include"./linkList.h"

typedef struct Teacher{
    LINK_NODE node;
    int age;
    char name[64];
}Teacher;

int main(void){
    int len;
    int i;
    int ret = 0;
    LinkList *list = NULL;
    Teacher t1, t2, t3, t4, t5; 
    t1.age = 31; 
    t2.age = 32; 
    t3.age = 33; 
    t4.age = 34; 
    t5.age = 35; 

    list = LinkList_Create();
    if(list == NULL){
        return -1; 
    }   

    len = LinkList_Length(list);
    ret = LinkList_Insert(list, (LINK_NODE *)&t1, 0); //采用的是头插法
    ret = LinkList_Insert(list, (LINK_NODE *)&t2, 0); //采用的是头插法
    ret = LinkList_Insert(list, (LINK_NODE *)&t3, 0); //采用的是头插法
    ret = LinkList_Insert(list, (LINK_NODE *)&t4, 0); //采用的是头插法
    ret = LinkList_Insert(list, (LINK_NODE *)&t5, 0); //采用的是头插法

    //遍历
    for(i = 0; i < LinkList_Length(list); i++){
        Teacher *tmp = (Teacher *)LinkList_Get(list, i);
        if(tmp == NULL){
            return -1;
        }
        printf("%d: ", tmp->age);
    }
    printf("\n");

    //printf("salkjfdkl\n");
    //删除链表
    while(LinkList_Length(list) > 0){
        LinkList_Delete(list, 0);
    }

    printf("hello\n");
    return 0;
}
```

### 3.2、运行结果

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtsRjn7qrbM9nOQRkWzyCJ1n4kiczeyibFak3IVx7OY0grN8FuSp2GenUHiaiauLYA65KVicgxKib1ibfdng/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

### 3.3、核心思想

**将数据类型与数据结构分离开来，我们在内部实现具体的链表各种操作，提供给外面一个接口，满足不同业务的数据类型的需求，从而达到一种高效的开发。**

## 四、说明

原创文章链接：[UNIX内核源码---通用链表](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483702&idx=1&sn=07ce1728cf648a05b96878c046c202d6&chksm=f94c8b0bce3b021dd1798232c7067b29767aab2f43f95cf895b5710addf91f3720faf4d8031f&scene=21#wechat_redirect)
