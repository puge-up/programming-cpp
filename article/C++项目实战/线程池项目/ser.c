#include"utili.h"

typedef struct PoolStruct{
    int sockConn;
    THREAD_TAG flag; 
}PoolStruct;

typedef PoolStruct threadpool[THREAD_POOL_NUM];
threadpool pool;
pthread_t  tid[THREAD_POOL_NUM];

void* Thread_Handler(void *arg);

void* Thread_Handler(void *arg){
    int index = *(int *)arg;

    printf("[%d] thread start up.\n", index);

    OperStruct op; 
    int result;
    while(1){
        if(pool[index].flag == BUSY){
            printf("[%d] thread start wroking.\n", index);
            int res = recv(pool[index].sockConn, &op, sizeof(op), 0); 
            if(res == -1){
                printf("recv data fail.\n");
                continue;
            }
            if(op.oper == ADD){
                result = op.op1 + op.op2;
            }else if(op.oper == SUB){
                result = op.op1 - op.op2;
            }else if(op.oper == MUL){
                result = op.op1 * op.op2;
            }else if(op.oper == DIV){
                result = op.op1 / op.op2;
            }else if(op.oper == QUIT){
                break;
            }
            res = send(pool[index].sockConn, &result, sizeof(result), 0);
            if(res == -1){
                printf("send data fail.\n");
                continue;
            }
        }else{
            printf("[%d] thread sleep.\n",index);
            sleep(1);
        }
    }
    close(pool[index].sockConn);
    pthread_exit(0);
}    
int main(void){
    int sockSer = socket(AF_INET, SOCK_STREAM, 0);
    if(sockSer == -1){
        perror("socket");
        return -1;
    }
    struct sockaddr_in addrSer, addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

    socklen_t len = sizeof(struct sockaddr);
    int res = bind(sockSer, (struct sockaddr*)&addrSer, len);
    if(res == -1){
        perror("bind");
        close(sockSer);
        return -1;
    }

    listen(sockSer, LISTEN_QUEUE);

    int i;
    for(i=0; i<THREAD_POOL_NUM; ++i){
        pthread_create(&tid[i], NULL, Thread_Handler, &i);
        sleep(1);
    }
    for(i=0; i<THREAD_POOL_NUM; ++i){    
        pool[i].sockConn = 0;
        pool[i].flag = IDEL;
    }

    int sockConn;
    while(1){
        printf("Server Wait Client Connect.......\n");
        sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
        if(sockConn == -1){
            printf("Server Accept Client Connect Fail.\n");
            continue;
        }else{
            printf("Server Accept Client Connect Success.\n");
            printf("Client IP:>%s\n", inet_ntoa(addrCli.sin_addr));
            printf("Client Port:>%d\n",ntohs(addrCli.sin_port));
        }
        for(i=0; i<THREAD_POOL_NUM; ++i){
            if(pool[i].flag == IDEL){
                pool[i].flag = BUSY;
                pool[i].sockConn = sockConn;
                break;
            }
        }
    }
    close(sockSer);
    return 0;
}