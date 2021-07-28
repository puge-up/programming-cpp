#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

#define SERVER_PORT  9090
#define SERVER_IP    "127.0.0.1"
#define LISTEN_QUEUE  5
#define BUFFER_SIZE   255


typedef enum{ADD,SUB,MUL,DIV,MOD, QUIT}OPER_TYPE;

typedef struct OperStruct{
    int op1;
    int op2;
    OPER_TYPE oper;
}OperStruct;