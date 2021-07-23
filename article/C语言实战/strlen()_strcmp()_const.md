- [一、strlen() 函数的实现](#一strlen-函数的实现)
- [二、strcmp() 函数的实现](#二strcmp-函数的实现)
- [三、const 的用法](#三const-的用法)
- [四、说明](#四说明)

在 C 语言中，对于基础库函数的实现，是非常的重要的，很考验一个人的基本功，今天主要是写strlen()、strcmp() 这 2 个常用函数的具体实现。

## 一、strlen() 函数的实现

strlen(char  *str); 主要计算字符串的长度

```c
#include<stdio.h>

int strLen(char *str);
int strLen(char *str){
   int i = 0;
   
   while(*str){
       str++;
       i++;
   }
   
   return i;
}

void main(void){
   char *str = "abcdefg";
   int length;
   
   length = strLen(str);
   printf("%d\n", length);
}
```

## 二、strcmp() 函数的实现

strcmp(char *str1, char *str2); 比较 2 个字符串是否相同。

```c
#include<stdio.h>

int strCmp(char *str1, char *str2);

int strCmp(char *str1, char *str2){
   while(*str1 == *str2 && *str1 && *str2){
       str1++;
       str2++;
   }
   
   return *str1 - *str2;
}

void main(void){
   char *str1 = "hello";
   char *str2 = "hell";
   
   printf("%d\n", strCmp(str1, str2));
}
```

## 三、const 的用法

在 C 语言中，const 是只读。

1. const int a = 100 <=> int const a = 100;  a 空间是只读空间，a 空间的值不能更改；
2. const int *a; <=> int const *a;  *a 的值不能改变，a指针变量的值可以更改；
3. int* const a;  *a 的值可以更改，a 指针变量只读，不能改其值
4. const int* const a;   *a, a 均只读空间，其值不可更改

**const 离谁进，修饰谁，谁就不可更改。**

注意，用 Linux 进行编程，需要注意：

1. Linux 下 64 位与 32 位的区别：int 都是 4 字节的。64 位下，long 8 字节， 指针 8 字节；
2. Linux下注释块：

```c
#if  0 (注释)  1 (不注释)

...........   

#endif 
```

3. gcc -c 只编译不连接  gcc   .c   -o  目标文件 编译和连接
4. objdump -d test (可执行文件) > x86  反汇编文件查看 X86 内容

**编译结果往往与平台，编译器关系很大。**

## 四、说明

原创文章链接：[strlen()、strcmp()、const](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483676&idx=1&sn=c39b0edea41d37e4307d167fdc27ff6f&chksm=f94c8b21ce3b0237b16f899dc228989ce91ff48a98ff172aa52c4fdf0b3072e2caa84bedf2dc&scene=21#wechat_redirect)
