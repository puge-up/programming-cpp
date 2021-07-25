- [一、C与Mysql](#一c与mysql)
- [二、C调用Mysql的基础模型](#二c调用mysql的基础模型)
- [三、C查询Mysql](#三c查询mysql)
- [四、C开发Mysql客户端](#四c开发mysql客户端)
- [五、说明](#五说明)

## 一、C与Mysql

因为Mysql是用C语言开发的，所以会有一系列的API可以调用；

## 二、C调用Mysql的基础模型

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

int main(void){
    int ret = 0;
    MYSQL mysql;
    MYSQL *connect = NULL;

    connect = mysql_init(&mysql);  //初始化
    if(connect == NULL){
        ret = -1; 
        printf("func mysql_init() err\n");
        return ret;
    }   
    connect = mysql_real_connect(connect, "localhost", "root", "123456", "mydb1", 0, NULL, 0); 
    if(connect == NULL){    //连接mysql
        ret = -1; 
        printf("func mysql_real_connect() err\n");
        return ret;
    }   
    printf("func mysql_real_connect() ok\n");

    mysql_close(&mysql);
    printf("hello world\n");
     
    return ret;
```

运行命令：

> gcc dm01_hello.c -o dm01_hello -I/usr/include -L/usr/lib64/mysql -lmysqlclient -lm -lrt -ldl -lstdc++ -lpthread

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt15YuSjdV4xwh5u0AgAcVj1vproL0yssgoI4Xv8ia6rRkl4V0MeWdopmg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、C查询Mysql

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

/*
 *中文问题
 *mysql_query   查询
 *mysql_store_result 获取句柄
 *
 *locate mysql.h 可以查找这个.h文件所在的目录
 *
 *
 */
int main(void){
    int ret = 0;
    MYSQL mysql;
    MYSQL *connect = NULL;

    connect = mysql_init(&mysql);
    if(connect == NULL){
        ret = mysql_errno(&mysql);

        printf("func mysql_init() err\n");
        return ret;
    }

    connect = mysql_real_connect(connect, "localhost", "root", "123456", "mydb1", 0, NULL, 0);
    //中文问题的解决
    mysql_set_character_set(&mysql, "utf8");
    if(connect == NULL){
        ret = mysql_errno(&mysql);
        printf("func mysql_real_connect() err\n");
        return ret;
    }
    //查询
    const char *query = "select * from student";
    ret = mysql_query(&mysql, query);
    if(ret != NULL){
        ret = mysql_errno(&mysql);

        printf("func mysql_query() err\n");
        return ret;
    }
    //获取结果集和
    //结果集和中可能含有多行数据，获取结果集
    //mysql_store_result设计理念:告诉句柄,我一下子全部把数据从服务器端取到客户端,然后缓存起来
    MYSQL_RES *result = mysql_store_result(&mysql);
    //使用的过程中从服务器端获取结果
    //MYSQL_RES *result = mysql_use_result(&mysql);
    
    //可得该数据库中这张表每行有多少元素
    unsigned int num = mysql_field_count(&mysql);
    int i;
    MYSQL_ROW row = NULL;  //在mysql.h中可以看到
    //打印表头
    MYSQL_FIELD *fields = mysql_fetch_fields(result);
    for(i = 0; i < num; i++){
        printf("%s\t", fields[i].name);
    }
    printf("\n");
    //打印表中内容
    while(row = mysql_fetch_row(result)){
        for(i = 0; i < num; i++){
            printf("%s\t", row[i]);
        }
        printf("\n");
    }

/*
 *  这里是我们自己看到该表一行有多少元素
    while(row = mysql_fetch_row(result)){
        printf("%s, %s, %s, %s, %s, %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    }
*/
    mysql_free_result(result);  
    
    mysql_close(&mysql);
    printf("hello world\n");

    return ret;   
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt11YBYg1BdbfOsSibM8uo26NMk0XgvV5Y2KfteP9uxBvlMmbVtrUC5Elw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 四、C开发Mysql客户端

只实现了查询的功能：

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

int main(int argc, char **argv){
    int ret = 0;
    MYSQL mysql;
    MYSQL *connect = NULL;
    char sqlbuf[80];

    connect = mysql_init(&mysql);
    if(connect == NULL){
        ret = mysql_errno(&mysql);

        printf("func mysql_init() err\n");
        return ret;
    }

    connect = mysql_real_connect(connect, "localhost", "root", "123456", argv[1], 0, NULL, 0);
    //中文问题的解决
    mysql_set_character_set(&mysql, "utf8");
    if(connect == NULL){
        ret = mysql_errno(&mysql);
        printf("func mysql_real_connect() err\n");
        return ret;
    }

    for(;;){
        memset(sqlbuf, 0, sizeof(sqlbuf));
        printf("mysql> :");
        //scanf()语句对tab 空格 回车 都省去了，对sql语句将会发生截断,用gets()可保持sql语句的原样性
        gets(sqlbuf);

        //退出
        if(strncmp("exit", sqlbuf, 4) == 0 || strncmp("quit", sqlbuf, 4) == 0){
            break;
        }
        //查询是否为SQL语句
        //ret = mysql_query(&mysql, "set name utf8");
        ret = mysql_query(&mysql, sqlbuf);
        if(ret != NULL){
            ret = mysql_errno(&mysql);

            printf("func mysql_query() err\n");
            return ret;
        }


        if(strncmp("select", sqlbuf, 6) == 0 || strncmp("SELECT", sqlbuf, 6) == 0){

            MYSQL_RES *result = mysql_store_result(&mysql);
            
            unsigned int num = mysql_field_count(&mysql);  //表头有多少列
            int i;     
            MYSQL_ROW row = NULL;  //在mysql.h中可以看到
            //打印表头
            MYSQL_FIELD *fields = mysql_fetch_fields(result);
            for(i = 0; i < num; i++){  //打印表头
                printf("%s\t", fields[i].name);
            }
            printf("\n");

            //打印表中内容
            while(row = mysql_fetch_row(result)){
                for(i = 0; i < num; i++){
                    printf("%s\t", row[i]);
                }
                printf("\n");
            }
            mysql_free_result(result);
        }
    }

    mysql_close(&mysql);
    printf("hello world\n");

    return ret;
}
```

1、看看mysql.h文件：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1Sfb6rSSP4lZhddWzJ4pJL2iaV8tDhtSAfoPw9lWlWE4V9ZOIUwQ3MmQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1azMoFFn3uTxyXjA99aCa9vU92RP2f1pq0iapZBvIc1c6zIFABG7gRwQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2、可以知道：MYSQL_ROW的真实类型：char **；

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1YLhrLZdEicVQ6ImOciauFfNCT4oh3sibrUcC8Lnz2GiaUbxnW0efnDiaoIA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

3、看看Mysql：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1cxbfPnIMZ8pg1qekiaJ88qI7zvuXaQWXYbYFjLJJ1CpsqKdqjserF3g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1GUjphZrExDe2M0jHn5GL5ic52her9h3cPcOzhNO7J3qCwv8GglwZVvw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

4、由于客户端的C语言开发数据库，我只实现了查询功能，其他的功能没有实现，导致没有打印出来，但是现在已经可以通过这个客户端对数据库进行操作了；

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1p7wS1QXbia7t38YguapV19Yp9KLKhslTkj8DRJcTl1aDY0PRMULibzSA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 五、说明

原创文章链接：[C开发Mysql客户端](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484091&idx=1&sn=c732eeb5c8cf167f3ab2b9fa18579c3f&chksm=f94c8886ce3b0190d2b0b065ae3624a16e17558ad643d897ef57031ddf17c0f4914f435c1f12&scene=21#wechat_redirect)
