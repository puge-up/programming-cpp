- [一、yum 配置](#一yum-配置)
- [二、yum命令](#二yum命令)
- [三、说明](#三说明)

对于 Linux 使用 Red Hat 版本的，需要学会 yum 源的配置，其后安装软件、配置开发环境相当方便。

## 一、yum 配置

- mkdir /dvd  :创建一个目录，因为挂载点必须是目录；
- mount /dev/sr0 /dvd：挂载；
- df -h：查看是否挂载上；

vim /etc/yum.repos.d/rhel-dvd.repo：写yum源的配置文件；

yum repolist :看一下本地仓库的信息。

写配置文件：

> [rhel-dvd]
> 
> name=dvd
> 
> baseurl=file:///dvd
> 
> gpgcheck = 0   : 不检查签名
> 
> enable = 1    ：启用当前仓库

注意：

1. **/dvd下必须有镜像，可以拿U盘拷一个镜像文件，或虚拟机->设置->CD/DVD->浏览->复制，粘贴，(从物理机上弄一个iOS镜像文件)：粘过来的存放在/tmp下，利用find命令找到即，再移到/dvd下。**
2. **每次重新进入终端时，必须重新挂载即可，便可安装软件包。**

## 二、yum命令

yum安装软件包：可以解决依赖关系；

yum install gcc 安装gcc开发工具；

yum install gcc -y / yum install -y gcc 安装过程中没有提示，直接安装；

yum remove gcc 移除gcc；

提示信息：-d 只下载不安装。

**在安装软件时最好使用 yum install *vnc* 匹配安装更好，相关的就全部装上了。**

**ubuntu 是开源的Linux操作系统，使用apt命令安装工具，不用配置本地仓库，在安装软件时但必须联网，直接从官网下载！**

## 三、说明

原创文章链接：[Red Hat7版本本地仓库yum源的配置](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483781&idx=1&sn=6f6b43140c1489b5d1daa70537d3d0ad&chksm=f94c8bb8ce3b02ae4435f82923ed53dcefc019a8548ed9649bdb9ac2da953173d241e670d9f5&scene=21#wechat_redirect)
