- [一、Linux 系统文件](#一linux-系统文件)
- [二、修改权限](#二修改权限)
- [三、增加用户和用户组](#三增加用户和用户组)
- [四、补充几个使用命令](#四补充几个使用命令)
- [五、说明](#五说明)

## 一、Linux 系统文件

Linux 下文件的属性与内容是分开存放的，文件属性有 inode 编号，内容在block 块中

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvP1jvjicPEIaicEpQ27Jxa0KOUdQDyTxf816YRpobcQwGhQib5icJtr2M6NBOZhh4thOIDGQE3kmkaxw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="80%" height="80%"></div>
<p align=center>(Linux文件属性)</p>

10 个中的第一个字母表示文件类型：

- -：一般文件
- d: 目录文件
- b: 块设备文件
- c: 字符设备文件
- l: 链接文件
- p: 管道文件（临时文件）

---

**Linux 多用户多任务，只有一个 root 管理者，具有无限权限！！！**

r 读 4、w 写 2、x 执行 1，其后依次 3 个字母一组，分别表示: 文件所有者权限u，文件所属用户组权限g，其他用户文件 o。

## 二、修改权限

- chown：(修改所有者，也可修改组)
- chgrp：(修改组)
- chmod：(修改权限), 数字和字母两种修改方法，字母(u/g/o)+(r/w/x)，表示增加此权限，字母(u/g/o)-(r/w/x)，表示去掉此权限。

## 三、增加用户和用户组

- useradd -g(修改默认组) -G(修改扩展组/附加组)
- userdel
- usergroup
- usermod
- passwd

- id 用户： 查看所属组，扩展组等。
- 用户的信息在: /etc/passwd、/etc/group、etc/shadow下

## 四、补充几个使用命令

- Ctrl + d：退出登录
- Ctrl + c：结束执行
- Tab：自动补齐
- Shift + ctrl + "+"：放大字体
- Ctrl + -：缩小字体  
- man指令的退出：q

## 五、说明

原创文章链接：[Linux 文件属性与用户组](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483713&idx=1&sn=2f448845c232627509d4442a8db05ffd&chksm=f94c8b7cce3b026a48c83536b64b8379590a15a4944aee013682f1ca9565d40524c6cc1eaec8&scene=21#wechat_redirect)
