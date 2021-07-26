- [一、OS](#一os)
- [二、系统编程](#二系统编程)
- [三、IPC](#三ipc)

## 一、OS

进程、线程、进程调度、内存管理、文件系统、安全。

函数调用模型

<div align=center><img src='https://s5.51cto.com/wyfs02/M01/87/BB/wKioL1fgixyhP2jOAAAh3VhSc8A444.png-wh_500x0-wm_3-wmp_4-s_3806879227.png' width="50%" height="50%"></div>

## 二、系统编程

**Linux下--->玩的就是API的调用；**

**在进行Linux网络编程时，应该特别注意函数的返回值，判断成功与否至关重要！**

## 三、IPC

学习IPC的模型分析

<div align=center><img src='https://s5.51cto.com/wyfs02/M01/87/BF/wKiom1fgkG2h_iGSAABAdJoEfbM213.png-wh_500x0-wm_3-wmp_4-s_3589654447.png' width="50%" height="50%"></div>

其使用的API汇总

x|消息队列|信号量|共享内存
|:--|:--|:--|:--|
头文件|<sys/msg.h>|<sys/sem.h>|<sys.shm.h>
创建/打开IPC的函数|msgget()|semget()|shmget()
控制IPC操作的函数|msgctl()|semctl()|shmctl()
IPC操作函数|msgsnd(),msgrcv()|semop()|shmat(),shmdt()
<p align=center>(System V IPC函数汇总)</p>
