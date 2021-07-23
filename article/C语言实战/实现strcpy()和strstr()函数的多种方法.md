- [一、编程实现 strcpy() 函数](#一编程实现-strcpy-函数)
- [二、求子串出现在字符串中的次数](#二求子串出现在字符串中的次数)
- [三、去掉字符串的前后空格](#三去掉字符串的前后空格)
- [四、说明](#四说明)

大家好，持续带来 C 中基础知识点，我希望的是，各位有所思考，把代码理解消化，在自己敲一遍，才能有所感受与提升。

## 一、编程实现 strcpy() 函数

1、方法一

```c
#include<stdio.h>

int main(void){
    char str1[80] = "abcdefg";
    char str2[80];
    int i;

    for(i = 0; str1[i]; i++){
        str2[i] = str1[i];
    }   

    str2[i] = 0;
    printf("%s\n", str1);
    printf("%s\n", str2);

    return 0;
}
```

2、方法二，一行核心代码实现字符串复制

```c
#include<stdio.h>

int str_copy(char *str1, char *str2);
int str_copy(char *str1, char *str2){
/*  
    for(; *str1; str1++, str2++){
        *str2 = *str1;
    }
    *str2 = 0;
}

    for(; *str1; ){
        *str2++ = *str1++;
    }

    *str2 = 0;

    while((*str2 = *str1) != 0){
        str1++;     //此时,就不用出循环在赋指为0；
        str2++;
    }

    while((*str2++ = *str1++) != 0);
*/  
    if(str1 == NULL || str2 == NULL){
        return -1; 
    }

    while(*str2++ = *str1++);

    return 0;

int main(void){
    char str1[80] = "abcdefg";
    char str2[80];
    //char *str2 = NULL;
    int ret = 0;

    ret = str_copy(str1, str2);
    if(ret != 0){
        printf("有一个地址为空,所以有错\n");
    }else{
        printf("%s\n", str1);
        printf("%s\n", str2);
    }

    return 0;
}

```

运行结果：
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsjwn6bRxD9vUqRyFiac4JjfQvX1uNcTwzticuGT5c2VLT18K5ODQBicLErstUHwUCTcFNqQfxsLPHlw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

## 二、求子串出现在字符串中的次数

```c
#include<stdio.h>
#include<string.h>

void strstrCount(char *p, char *q, int *count);
void strstrCount(char *p, char *q, int *count){
    int c = 0;

    if(p == NULL || q == NULL){
        printf("有地址为空,不能查找子串个数\n");
        return;
    }   

    while(p = strstr(p, q)){
        c++;
        p = p + strlen(q);
        if(p == NULL){
            break;
        }   
    }   

    *count = c;
}

int main(void){
    char *p = "abc12421abc34345abc325423abc";
    char *q = "abc";
    int count = 0;

    strstrCount(p, q, &count);
    printf("%d\n", count);

    return 0;
}
```

运行结果：
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsjwn6bRxD9vUqRyFiac4JjfTNS5dRtW26EJTRuZ0qafY2PFibIaaQGFcAKIqibeORH3oQ8YJ41szP0g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

## 三、去掉字符串的前后空格

```c
#include<stdio.h>
#include<string.h>
#include<malloc.h>

void trimSpace(char **str1, char *str2);
void trimSpace(char **str1, char *str2){
    int length = strlen(str2);
    char *tmp;

    *str1 = (char *)malloc(sizeof(char)*length);
    tmp = *str1;

    for(; *str2; str2++){
        if(*str2 != ' '){
            *tmp++ = *str2;
        }   
    }   
    *tmp = 0;
}

int main(void){
    char str[] = "               abcdefg               "; 
    char *str1;

    printf("%s\n", str);
    trimSpace(&str1, str);
    printf("%s\n", str1);
} 
```

运行结果
<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbsjwn6bRxD9vUqRyFiac4JjfiadhCeZcic1iafaHHdCQBNEf48E0uQgt88Dic9lRnI8c7QDib1eHJibdWLqg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

**以上的代码都是我亲自实践过的，有些细节多多思考，每天进步一点点，去理解清楚，在敲出来！**

## 四、说明

原创文章链接：[实现strcpy()和strstr()函数的多种方法](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483682&idx=1&sn=44efebae423d9eaf62b2c91648064a7e&chksm=f94c8b1fce3b02097128064913561e3a14113086ac6d93bd160c69d42f5c5aae4a462ca34a37&scene=21#wechat_redirect)
