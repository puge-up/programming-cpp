- [一、epoll()](#一epoll)
- [二、epoll_wait()](#二epoll_wait)
- [三、epoll()的核心思想](#三epoll的核心思想)
- [四、代码实现](#四代码实现)
  - [4.1、utili.h](#41utilih)
  - [4.2、ser.c](#42serc)
  - [4.3、cli.c](#43clic)
  - [4.4、运行结果](#44运行结果)

## 一、epoll()

epoll()是Linux特有的I/O复用函数，它的实现与使用上和select()、poll()、有很大差异。

epoll()用一组函数来完成任务，而不是单个函数；其次，epoll()把文件描述放到内核事件表中，只需一个额外的文件描述符，来标识内核中唯一的这个事件表。

需要使用的API：

```cpp
int epoll_create(int size);

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

需要使用的结构体信息：

```cpp
typedef union epoll_data {
  void        *ptr;
  int          fd;  //一般情况下，都用的是这个文件描述符
  uint32_t     u32;
  uint64_t     u64;
} epoll_data_t;

struct epoll_event {
  uint32_t     events;      /* Epoll events */
  epoll_data_t data;        /* User data variable */
};
```

```cpp
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

## 二、epoll_wait()

关键：对epoll_wait()函数的核心理解

1. **返回值：事件表中就绪客户端的个数；**
2. **参数events：将事件表中的就绪客户端的信息放到了events数组中。**

## 三、epoll()的核心思想

**就是创建一个内核事件表，存放所监听客户端的套接字和当前的事件，在利用epoll_wait()函数查找就绪的套接字，最后经过增加、删除、修改利用epoll_ctl()函数进行；当然了，这其中还有一批搭配使用的宏；**

## 四、代码实现

### 4.1、utili.h

```cpp
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<assert.h>

#include<sys/select.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT  8787
#define LISTEN_QUEUE 5
#define SIZE 10
#define BUFFER_SIZE 256

#include<poll.h>
#define OPEN_MAX 1000

#include<sys/epoll.h>
#define FDSIZE      1000
#define EPOLLEVENTS 100
```

### 4.2、ser.c

```cpp
#include"../utili.h"

static int socket_bind(const char *ip, int port){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    //addrSer.sin_addr.s_addr = inet_addr(ip);
    inet_pton(AF_INET, ip, &addrSer.sin_addr);
    addrSer.sin_port = htons(port);
    bind(listenfd, (struct sockaddr*)&addrSer, sizeof(struct sockaddr));
    return listenfd;
}

static void add_event(int epollfd, int fd, int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollfd, int fd, int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}
static void modify_event(int epollfd, int fd, int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

static void handle_accept(int epollfd, int listenfd){
    int clifd;
    struct sockaddr_in addrCli;
    socklen_t len = sizeof(struct sockaddr);
    clifd = accept(listenfd, (struct sockaddr*)&addrCli, &len);
    if(clifd != -1){
        add_event(epollfd, clifd, EPOLLIN);
    }
}

static void do_read(int epollfd,  int fd, char *buf){
    int nread = read(fd, buf, BUFFER_SIZE);
    if(nread == -1){
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }else{
        printf("read msg:>%s\n",buf);
        modify_event(epollfd, fd, EPOLLOUT);
    }
}
static void do_write(int epollfd, int fd, char *buf){
    int nwrite = write(fd, buf, strlen(buf)+1);
    if(nwrite == -1){
        close(fd);
        delete_event(epollfd, fd, EPOLLOUT);
    } else{
        modify_event(epollfd, fd , EPOLLIN);
    }
    memset(buf, 0, BUFFER_SIZE);

}

static void handle_events(int epollfd, struct epoll_event *events, int num,
                            int listenfd, char *buf){
    int i;
    int fd;
    for(i=0; i<num; ++i){
        fd = events[i].data.fd;
        if((fd==listenfd) && (events[i].events&EPOLLIN)) //根据其结果分别进入三种状态
            handle_accept(epollfd, listenfd);  //申请与服务器连接
        else if(events[i].events & EPOLLIN)
            do_read(epollfd, fd, buf);  //只读
        else if(events[i].events & EPOLLOUT)        
            do_write(epollfd, fd, buf);  //只写
    }
}


static void do_epoll(int listenfd){
    int ret;
    char buffer[BUFFER_SIZE];
    struct epoll_event events[EPOLLEVENTS];
    int epollfd = epoll_create(FDSIZE);
    add_event(epollfd, listenfd, EPOLLIN);
    for(;;){
        //select poll
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
        handle_events(epollfd, events, ret, listenfd, buffer);
    }
    close(epollfd);
}

int main(void){
    int listenfd;
    listenfd = socket_bind(SERVER_IP, SERVER_PORT);
    listen(listenfd, LISTEN_QUEUE);
    do_epoll(listenfd);
    return 0;
}
```

### 4.3、cli.c

```cpp
#include"../utili.h"

static void add_event(int epollfd, int fd, int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollfd, int fd, int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd; 
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state){
    struct epoll_event ev; 
    ev.events = state;
    ev.data.fd = fd; 
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}



static void do_read(int epollfd,  int fd, int sockfd, char *buf){
    int nread = read(fd, buf, BUFFER_SIZE);
    if(nread == -1) {
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }else{
        if(fd == STDIN_FILENO)
            add_event(epollfd, fd, EPOLLIN);
        else{
            delete_event(epollfd, fd, EPOLLIN);
            add_event(epollfd, STDOUT_FILENO, EPOLLOUT);
        }
    }
    printf("Ser :>%s", buf);
}

static void do_write(int epollfd, int fd, int sockfd, char *buf){
    int nwrite = write(fd, buf, strlen(buf)+1);
    if(nwrite == -1){
        perror("write");
        close(fd);
    }else{
        if(fd == STDOUT_FILENO){
            delete_event(epollfd, fd, EPOLLOUT);
        }else{
            modify_event(epollfd, fd, EPOLLIN);
        }
    }    
    memset(buf, 0, BUFFER_SIZE);
}


static void handle_events(int epollfd, struct epoll_event *events, int num,
                            int sockfd, char *buf){
    int i;
    int fd;
    for(i=0; i<num; ++i){
        fd = events[i].data.fd;
        if(events[i].events & EPOLLIN)
            do_read(epollfd, fd, sockfd, buf);
        else if(events[i].events, fd, sockfd, buf)
            do_write(epollfd, fd, sockfd, buf);
    }
}
static void handle_connection(int sockfd){
    struct epoll_event events[EPOLLEVENTS];
    int epollfd = epoll_create(FDSIZE);
    add_event(epollfd, STDIN_FILENO, EPOLLIN);

    int ret;
    char buffer[BUFFER_SIZE];
    for(;;){
        ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);
        handle_events(epollfd, events, ret, sockfd, buffer);
    }
    close(epollfd);
}

int main(void){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);
    connect(sockfd, (struct sockaddr*)&addrSer, sizeof(struct sockaddr));

    handle_connection(sockfd);
    close(sockfd);
    return 0;
}
```

### 4.4、运行结果

服务器端就是等待客户端的使用；

客户端1

<div align=center><img src='https://s3.51cto.com/wyfs02/M01/88/17/wKioL1fpqXei35d_AAAZ3YfRI20994.png-wh_500x0-wm_3-wmp_4-s_1441849682.png' width="50%" height="50%"></div>

客户端2

<div align=center><img src='https://s3.51cto.com/wyfs02/M02/88/17/wKioL1fpqbCTD-LIAAAW7mAZK28187.png-wh_500x0-wm_3-wmp_4-s_1055467077.png' width="50%" height="50%"></div>

</br>

**利用epoll()函数，不用轮询每个套接字，效率更高效一些；**
