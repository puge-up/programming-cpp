- [一、文件描述块儿](#一文件描述块儿)
- [二、文件描述符](#二文件描述符)
- [三、Linux下的I-O](#三linux下的i-o)
- [四、标准输入、标准输出、标准错误输出](#四标准输入标准输出标准错误输出)
- [五、文件描述符的复制](#五文件描述符的复制)
  - [5.1、dup()的文件描述符的复制](#51dup的文件描述符的复制)
  - [5.2、dup2()的文件描述符的复制](#52dup2的文件描述符的复制)
- [六、文件I/O的API](#六文件io的api)
- [七、write()和read()函数](#七write和read函数)

## 一、文件描述块儿

我们从代码的角度看，文件描述块儿就是FILE结构体，当一个进程打开一个文件系统上的文件时，就是生成一个文件描述块儿信息，该信息除了要描述被访问的文件的基本信息(文件名称，路径，权限等等)，更重要的是描述当前进程对文件的读写情况。

模型关系如下：

<div align=center><img src='https://s4.51cto.com/wyfs02/M02/87/39/wKiom1fX11Sgk-kIAAAuuYJXrIA967.png-wh_500x0-wm_3-wmp_4-s_2067259007.png' width="50%" height="50%"></div>

文件描述块内容在/usr/include/libio.h头文件里

其文件描述块内容如下：

```cpp
struct _IO_FILE {
  int _flags;       /* High-order word is _IO_MAGIC; rest is flags. */
  #define _IO_file_flags _flags
 
    /* The following pointers correspond to the C++ streambuf protocol. */
    /* Note:  Tk uses the _IO_read_ptr and _IO_read_end fields directly. */
    char* _IO_read_ptr;   /* Current read pointer */
    char* _IO_read_end;   /* End of get area. */
    char* _IO_read_base;  /* Start of putback+get area. */
    char* _IO_write_base; /* Start of put area. */
    char* _IO_write_ptr;  /* Current put pointer. */
    char* _IO_write_end;  /* End of put area. */
  char* _IO_buf_base;   /* Start of reserve area. */
  char* _IO_buf_end;    /* End of reserve area. */
  /* The following fields are used to support backing up and undo. */
  char *_IO_save_base; /* Pointer to start of non-current get area. */
  char *_IO_backup_base;  /* Pointer to first valid character of backup area */
  char *_IO_save_end; /* Pointer to end of non-current get area. */

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
#if 0
  int _blksize;
#else
  int _flags2;
#endif
  _IO_off_t _old_offset; /* This used to be _offset but it's too small.  */

#define __HAVE_COLUMN /* temporary */
  /* 1+column number of pbase(); 0 is unknown. */
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  /*  char* _save_gptr;  char* _save_egptr; */

  _IO_lock_t *_lock;
#ifdef _IO_USE_OLD_IO_FILE
};
```

## 二、文件描述符

 一个进程可以打开多个文件，此时该进程中就会有多个文件描述块儿；文件描述符就是文件描述块儿在该进程中的唯一一个编号。通过该唯一编号就能代表文件描述块儿。所以，在Linux下提供了一套通过文件描述符操作文件读取的方法。

**文件描述符作为一个编号，就只是一个int类型的数据，其编号从0开始，依次向后累加，差值为1。**

**每打开一个文件就会产生一个新的文件描述块儿，就会为其分配一个文件描述符；**

**文件描述符的分配原则 : 要尽最大努力保持文件描述符的编号的连续性，之所以如此原则，是为了节省编号资源。**

**当要关闭一个已经打开的文件时，对应的文件描述符就会被回收，打开新文件时，会寻找最小的可用的文件描述符(包括已经回收的文件描述符)。**

文件描述符与文件描述块儿是一对一的关系，在Linux下，对文件的读写操作都施加在文件描述符上。对文件描述符的操作，其实就等同于对文件描述块儿的操作(例如：使用文件描述符就可以实现对文件的读写操作)。

## 三、Linux下的I-O

input和output，**在Linux下所有的I/O设备都被抽象为设备文件**(块儿设备文件和字符设备文件)，通过对这些文件的读写操作，即就是对相关的设备的I/O操作。

**所以read表示输入，write表示输出。**

## 四、标准输入、标准输出、标准错误输出

任何一个进程启动时，在默认的情况下都会拥有已经打开的三个文件描述块儿，他们就是：标准输入、标准输出、标准错误输出。

```cpp
/* Standard streams.  */
extern struct _IO_FILE *stdin;      /* Standard input stream.  */
extern struct _IO_FILE *stdout;     /* Standard output stream.  */
extern struct _IO_FILE *stderr;     /* Standard error output stream.  */
```

**也同时对应三个不同的文件描述符，分别是0,1,2。**

标准输入、标准输出、标准错误输出都对应了相关的设备文件，这三个文件描述符儿都是打开的对应的设备文件。**事实上在当前的Linux的网络环境中，这三个文件描述符打开的是同一个设备文件**。这个设备文件在/dev/pts目录下，对应当前进程的shell环境提供的终端文件。

**文件关闭的本质：断开进程与文件系统中文件的关联关系，即就是将文件描述块儿回收，当然回收时会向操作系统内核报告，以便操作系统内核清除该进程对相关文件的访问标识。**

**进程中可以关闭对应的设备文件的文件描述块儿，也就是说可以关闭标准输入、标准输出、标准错误输出。**

```cpp
#include<stdio.h>

int main(void){
        printf("This is before;\n");
        close(1); //关闭标准输出
        printf("This is after;\n");
        return 0;
}
```

运行结果

<div align=center><img src='https://s3.51cto.com/wyfs02/M01/87/3A/wKioL1fYGwvzDrMhAABAwTRv57o701.png-wh_500x0-wm_3-wmp_4-s_1382141244.png' width="50%" height="50%"></div>

</br>

由于标准输出被关闭，所以其后的输出将不会打印到屏幕上，输出到哪里去了，不知道。

## 五、文件描述符的复制

文件描述符的复制指的是，将被复制的文件描述符对应的文件描述块儿复制一份(原模原样，即就是包括被复制文件描述块儿当前的状态)，然后返回该文件描述块儿的文件描述符。

### 5.1、dup()的文件描述符的复制

```cpp
#include<stdio.h>
#include<string.h>

int main(void){
        char buffer[80] = "Welcome \n";
        int fd = dup(1);

        printf("fd = %d\n", fd);
        write(fd, buffer, strlen(buffer));
        return 0;
}
```

### 5.2、dup2()的文件描述符的复制

dup2()就是将第一个参数的文件描述符对应的文件描述块儿复制一份，挂载给第二个参数，如果第二个参数之前有对应的文件描述块儿，则会先进行关闭。

即就是dup2()就完成了重定向功能!

```cpp
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>

int main(void){
        char buffer[80] = "Wello to xian\n";
        int fd = open("./data.txt", O_CREAT | O_RDWR, 0755);
        if(fd < 0){
                perror("");
                return -1;
        }

        dup2(fd, 1);
        write(fd, buffer, strlen(buffer));
        return 0;
}
```

运行结果

<div align=center><img src='https://s3.51cto.com/wyfs02/M01/87/3C/wKiom1fYIM6SXrRiAABJ1lOK8zI248.png-wh_500x0-wm_3-wmp_4-s_2208407003.png' width="50%" height="50%"></div>

## 六、文件I/O的API

方法声明|解释
|:--|:--|
int close(int fd);|返回值为0表示成功，非0表示失败。
int open(char *path, int flag, int mode);|open("./data.txt", O_CREAT \| O_RDWR, 0755);返回值大于0表示成功，且是一个可用的文件描述符；失败，返回比0小。
int write(int fd, const void *buffer, int size);|返回值大于0表示成功，且表示输出的数据的字节个数。失败，返回小于0；
int read(int fd, void *buffer, int size);|返回值大于0表示成功，且表示读入的数据的字节个数。失败，返回小于0；		

void *是一种特殊的指针类型，表示无类型指针，即就是可以指向任意类型的指针。

下面写一个文件读写的例子：

```cpp
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>

int main(void){
        int fd;
        char buf[20] = "Red hat Linux";

        fd = open("./tmp.txt", O_CREAT | O_EXCL | O_RDWR, 0755);
        if(fd < 0){
                perror("");
                return -1;
        }
        int len = write(fd, buf, strlen(buf));
        printf("写入了 : %d个字节\n", len);
        //0 1 2三个设备文件其实是同一个文件
        write(1, buf, strlen(buf)); //标准输出到屏幕
        printf("\n");  
        read(1, buf, sizeof(buf)); //从标准输出(屏幕)读入
        write(0, buf, strlen(buf)); //因为同一个文件，输出到屏幕
        return 0;
        // write()都是输出到屏幕的，read()都是从屏幕读入的。
}
```

运行结果

<div align=center><img src='https://s3.51cto.com/wyfs02/M01/87/3C/wKiom1fYKw6D1mK2AABPGSoV02M399.png-wh_500x0-wm_3-wmp_4-s_2835535175.png' width="50%" height="50%"></div>

## 七、write()和read()函数

1. **0 1 2都是同一文件，关键看，write()函数功能，写入，read()函数功能，读出；**
2. **在对三种0 1 2 标准文件的操作时，write()是显示到屏幕的功能，read()是从屏幕读入到指定buf中的内容。**
