- [一、核心思想](#一核心思想)
  - [1、几个核心概念](#1几个核心概念)
  - [2、目录与文件](#2目录与文件)
  - [3、常用命令](#3常用命令)
- [二、说明](#二说明)

对于编程学习，不管走算法还是后台，Linux 都是必备技能，win 7 + Ubuntu + VM + Xshell 这套工具是最基础的。

**书籍推荐：《鸟哥的Linux私房菜》**

## 一、核心思想

### 1、几个核心概念

1. "一切皆文件"
2. Linux下是不区分扩展名的，Linux下扩展名是给人看的，其扩展名随便给，无关紧要；但为了自己好区分，还是最好写清楚。
3. Linux下是对大小写很敏感的，严格区分大小写。 

内核(Kernel)Shell、终端模拟器、X Window系统，以下就是交互的形式了

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvwQbcQjRgH7JfiahUSLQt7z9exe6gydBkFVPCpFU8qoz56O8dLq3SCtwGpH3xW9bnU8nTGibaemGWg/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(linux内核交互)</p>

用户进程和内核通过shell进行交互，内核再跟硬件交互。

### 2、目录与文件

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvwQbcQjRgH7JfiahUSLQt7ziaBfq1ltZUCdXYAAoEp494jZUEIHrmYiann2KK8zcKLPKjyvk1SLqYiaA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(命令行解释)</p>

1. 目录也是文件，Linux 下面一切皆文件
2. 相对路径：从当前目录出发；绝对路径：总是从根(/)目录下出发。
3. 文件：是数据存放的载体。

### 3、常用命令

**基本格式：命令名 [选项] [参数]**
**帮助手册：指令 --help  man 指令  info 指令**

- ls：列出当前目录下的列表信息 、-l 长格式  ls -l = ll、-a 隐藏文件、-i inode编号
- cd：转换路径
- cp: 拷贝文件   -r: 递归拷贝(目录)  ./*:拷贝其下的文件，当前的目录不拷贝。
- mv: 移动或从命名
- touch: 创建文件或更新文件时间
- mkdir: 创建新目录
- rmdir: 删除空目录
- rm: 删除目录或文件 -r(递归目录) -f(强制删除)
- pwd: 查看当前完整路径
- cat、more、less: 查看文件的内容
- date: 显示当前时间
- cal: 显示月历
- df: 显示磁盘用量  -h  字节方式
- du: 计算目录下文件占磁盘的大小  -h  字节方式
- head: 显示文件开头部分内容   -n 数字
- tail: 显示文件结尾部分内容  -n  数字
- file: 检查文件类型

**离开系统命令：**
- 重启：reboot、shutdown -r now、init 6
- 关机：halt、shutdown -h now、poweroff、init 0

## 二、说明

原创文章链接：[Linux 文件属性与用户组](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483713&idx=1&sn=2f448845c232627509d4442a8db05ffd&chksm=f94c8b7cce3b026a48c83536b64b8379590a15a4944aee013682f1ca9565d40524c6cc1eaec8&scene=21#wechat_redirect)
