#include"utili.h"

void InputData(OperStruct *pt);

void InputData(OperStruct *pt){
    printf("please input op1 and op2 : ");
    scanf("%d %d", &(pt->op1), &(pt->op2));
}

//Cli
int main(void){
    int sockCli = socket(AF_INET, SOCK_STREAM, 0); 
    if(sockCli == -1){
        perror("socket");
        return -1; 
    }   
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

    socklen_t len = sizeof(struct sockaddr);
    int res = connect(sockCli, (struct sockaddr*)&addrSer, len);
    if(res == -1){
        perror("connect");
        close(sockCli);
        return -1; 
    }else{
        printf("Client Connect Server Success.\n");
    }

    char cmd[2];
    OperStruct  op;
    int result;
    while(1){
        printf("Please input operator : ");
        scanf("%s",cmd);
        if(strcmp(cmd, "+") == 0){
            op.oper = ADD;
            InputData(&op);
        }else if(strcmp(cmd,"-") == 0){
            op.oper = SUB;
            InputData(&op);
        }else if(strcmp(cmd,"*") == 0){
            op.oper = MUL;
            InputData(&op);
        }else if(strcmp(cmd,"/") == 0){
            op.oper = DIV;
            InputData(&op);
        }else if(strcmp(cmd, "quit") == 0){
            op.oper = QUIT;
        }else{
            printf("Cmd invalid.\n");   
       }

        res = send(sockCli, &op, sizeof(op), 0);
        if(res == -1){
            printf("send data fail.\n");
            continue;
        }
        if(op.oper == QUIT)
            break;
        res = recv(sockCli, &result, sizeof(result), 0);
        if(res == -1){
            printf("recv data fail.\n");
            continue;
        }
        printf("result = %d\n", result);
    }
    close(sockCli);
    return 0;
}