- [一、poll()](#一poll)
- [二、代码实现](#二代码实现)
  - [2.1、utili.h](#21utilih)
  - [2.2、ser.c](#22serc)
  - [2.3、cli.c](#23clic)
  - [2.4、运行结果](#24运行结果)

## 一、poll()

poll()系统调用和select()类似，也是轮询一定数量的文件描述符，以测试其是否有就绪者。

API函数：

```cpp
int poll(struct pollfd *fds, nfds_t nfds, int timeout);

// 参数：nfds+1；

struct pollfd {
    int fd;        /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};
```

**其中，fd成员是指定的文件描述符，events成员告诉poll监听哪些事件，revents是由内核修改。**

**有一些宏作为辅助事件参数；**

## 二、代码实现

### 2.1、utili.h

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
```

### 2.2、ser.c

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

static void handle_connection(struct pollfd *connfds, int num){
    char buffer[BUFFER_SIZE];
    int i;
    for(i=1; i<=num; ++i){
        if(connfds[i].fd == -1) 
            continue;
        if(connfds[i].revents & POLLIN){
            recv(connfds[i].fd, buffer, BUFFER_SIZE, 0); 
            printf("Server accept client msg:>%s\n",buffer);
            send(connfds[i].fd, buffer, strlen(buffer)+1, 0); 
        }   
    }   
}
static void do_poll(int listenfd){
    struct sockaddr_in addrCli;
    int connfd;
    struct pollfd clientfds[OPEN_MAX];
    clientfds[0].fd = listenfd;
    clientfds[0].events = POLLIN;
    int i;
    for(i=1; i<OPEN_MAX; ++i){
        clientfds[i].fd = -1;
    }

    int nready;
    int max = 0;
    for(;;){
        nready = poll(clientfds, max+1, -1);
        if(nready == -1){
            perror("poll");
            return;
        }
        if(nready == 0){
            printf("Server Wait Time Out.\n");
            continue;
        }
        if(clientfds[0].revents & POLLIN){  //收发消息
            socklen_t len = sizeof(struct sockaddr);
            connfd = accept(listenfd, (struct sockaddr*)&addrCli, &len);
            int i;
            for(i=1; i<OPEN_MAX; ++i){
                if(clientfds[i].fd == -1){
                    clientfds[i].fd = connfd;
                    break;
                }
            }

            if(i == OPEN_MAX){
                printf("Over Load.\n");
                exit(1);
            }

            clientfds[i].events = POLLIN;
            max = (i>max ? i : max);
        }

        handle_connection(clientfds, max);  //建立连接
    }
}
int main(void){
    int listenfd;
    listenfd = socket_bind(SERVER_IP, SERVER_PORT);
    listen(listenfd, LISTEN_QUEUE);
    do_poll(listenfd);
    return 0;
}
```

### 2.3、cli.c

```cpp
#include"../utili.h"

static void handle_connection(int sockfd){
    struct pollfd pfds[2];
    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN;
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;

    char buffer[BUFFER_SIZE];
    for(;;){
        poll(pfds, 2, -1);  //-1表示永不超时
        if(pfds[0].revents & POLLIN){
            recv(sockfd, buffer, BUFFER_SIZE, 0); 
            printf("msg:> %s\n",buffer);
        }   
        if(pfds[1].revents & POLLIN){
            scanf("%s", buffer);
            //read(STDIN_FILENO, buffer, BUFFER_SIZE);
            send(sockfd, buffer, strlen(buffer)+1, 0); 
        }   
    }   
}
int main(void){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);
    connect(sockfd, (struct sockaddr*)&addrSer, sizeof(struct sockaddr));

    handle_connection(sockfd);
    return 0;
}
```

### 2.4、运行结果

服务器端：

<div align=center><img src='https://s3.51cto.com/wyfs02/M00/88/19/wKiom1fpUfCi0wBWAABAoQ1HNE0226.png-wh_500x0-wm_3-wmp_4-s_995272177.png' width="50%" height="50%"></div>

客户端1：

<div align=center><img src='https://s3.51cto.com/wyfs02/M02/88/16/wKioL1fpUjrD3uxiAAAll0njD24146.png-wh_500x0-wm_3-wmp_4-s_4244803526.png' width="50%" height="50%"></div>

客户端2：

<div align=center><img src='https://s4.51cto.com/wyfs02/M01/88/19/wKiom1fpUoCjyuP_AAAkjmdZIgc333.png-wh_500x0-wm_3-wmp_4-s_991912699.png' width="50%" height="50%"></div>
