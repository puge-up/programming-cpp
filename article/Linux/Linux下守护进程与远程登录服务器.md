- [一、systemd](#一systemd)
- [二、常见命令](#二常见命令)
- [三、配置和远程登录服务器](#三配置和远程登录服务器)
- [四、scp rsync](#四scp-rsync)
- [五、说明](#五说明)

对于 Linux 的学习，远程登录服务器是必备操作，在公司工作基本上都是远程登录服务器，即提前掌握学习是非常有必要的，在校期间可以用 Xshell 链接 VM 上的虚拟机即可。


## 一、systemd

在Red Hat7版本中，系统启动和服务器进程由systemd进行管理；systemctl命令用于管理各种类型的systemd对象，它们称为单元。

systemctl -t help 显示可用单元类型列表。一些常见的单元类型：

1. 服务单元具有.service扩展名
2. 套接字单元具有.socket扩展名
3. 路径单元具有.path扩展名

## 二、常见命令

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtibue6vNKYstPLGSnVLvf5T7ZTeQ06gDa5Ug7RR6EewfDRUMNOfq9qyTRDicubIFOqay63icibIgAzpg/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(查看服务的状态)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtibue6vNKYstPLGSnVLvf5T17pIibZ0frelsUNysic6EZcqwPqcUMew1PWw2UT7dGK0vPMdiataZb6cw/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(查看是否开机启动)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtibue6vNKYstPLGSnVLvf5TVZsIkhs2iaQhkxiatKnfuFCzrhO2KAwcOCf6iaeEpnqmulzA63k0ujicRQ/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(列出服务的启动顺序)</p>

常见的systemctl控制命令：

命令|解释
|:--|:--
systemctl stop UNIT|停止一项服务
systemctl start UNIT|启动一项服务
systemctl restart UNIT|重启服务
systemctl reload unit|重新加载服务的配置文件
systemctl mask UNIT|禁用服务
systemctl unmask UNIT|服务变为可用
systemctl enable UNIT|开机自动启动
systemctl disable UNIT|禁止服务开机自启
systemctl list-dependencies UNIT|列出指定单元的依赖关系

## 三、配置和远程登录服务器

1. **w -f 显示当前登录到计算机的用户列表。**
2. **基于秘钥的登录：ssh 用户名@IP，ssh-keygen   ：生成私钥对，私钥文件：~/.ssh/idrsa  公钥文件：~/.ssh/idrsa。**
3. **ssh-copy-id -i ~/.ssh/id_rsa.pub 用户名@IP  :将公钥复制到远程服务器上，公钥信息将保存到远程服务器上相应用户的 ~/.ssh/authorized_keys文件中。**

通过以上三步，下次ssh 用户名@IP 就可以不用输入密码，进行基于密钥的登录。

自定义SSH服务配置：SSHD的配置文件：/etc/ssh/sshd_config。

可以设置只允许root用户登录ssh，也可以设置只允许root基于秘钥登录等……，但是设置完后必须重启：systemctl restart sshd。

## 四、scp rsync

**scp 命令 ：本地文件拷贝到远程/远程文件传输本地；**

scp 本地文件所在路径 用户名@IP：要存放的路径；

scp 用户名@IP：文件路径 本机要存放的文件路径；

注意：整个目录拷贝的话：-r 递归拷贝。

了解：sftp 使用ssh加密文件传输，安全 sftp 用户@IP。

rsync远程同步文件：

选项|解释
|:--|:--|
-r|同步整个目录
-l|同步符号链接
-p|保留文件权限
-t|保留文件时间戳信息
-g|保留文件组所有权
-o|保留文件所有者

## 五、说明

原创文章链接：[Linux下守护进程与远程登录服务器](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483774&idx=1&sn=0b9e45ad2d15f2dd1284e17577126936&chksm=f94c8b43ce3b0255b3706ff9e4be0e2a8bf5357d7489f373abb7ed56f8bfb7080cb05db6eb1d&scene=21#wechat_redirect)
