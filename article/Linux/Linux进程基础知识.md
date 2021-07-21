- [一、进程](#一进程)
- [二、Linux进程状态](#二linux进程状态)
- [三、进程命令](#三进程命令)
- [四、监控进程活动](#四监控进程活动)
- [五、说明](#五说明)

对于 Linux 系统而言，掌握进程知识，才有可能学好网络编程，解决实际问题。

## 一、进程

一个可执行的程序在被执行之后的实例。

每个进程都有一个唯一的 ID--PID，也有一个父进程 ID--PPID，所有进程都是第一个进程的后代，在 Red Hat7 中为 systemd。

进程的生命周期有：就绪态，执行状态，等待，消亡状态。

## 二、Linux进程状态

用 man 7 signal 查看。

- R ：可运行状态
- S : 可中断睡眠状态(当某个时间或信号满足条件时，该进程会被唤醒)
- D ：不可中断睡眠状态(其唤醒的资源完全无法预料)
- K ：可通过信号强行停止
- Z：僵尸进程
- X：进程成功退出
- T：进程被停止

列出进程的命令：ps aux, ps -ef  (-e 列出所有进程，-f 列出进程的详细信息)

## 三、进程命令

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUuaYQd7fxQrIBMNuftcvsEVxeJbESO3XwJfjWvHxQ56ibI7rVmYaFa3NA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(调出火狐浏览器)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUuBjPialbMuOlmtJg6beBHiaqrryGh0ssyJKYL0x0oibANWeLbkVQHiazOeA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(火狐浏览器放置后台运行)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUub0B4uhL9ibvtPL1WfA11nOtkXZ4CuX846qaGMbEaiaNwxCuXCvF47Qvg/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(查看后台进程)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUu7tSJoDWPahRjgbIDibUu91A4zyFwWgvLCag5YmNK6cOzGXLOWTPapIA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(后台进程转为前台进程)</p>

- **Ctrl + z 将进程放到后台并暂停**
- **Ctrl + c 将进程强制结束**
- **bg %jobid 将前台进程转到后台**

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUukAAyWtcBpvqib7LvBMDm438tuib3QPcg2nEiccyjLOQ8K0ujbqszLlUGg/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(列出所支持的信号)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUuuXbJF4bCKtwDmMzsWWibWDoV3GQ0cvyggzPcicJvUUfKkuxKKN1aQjLQ/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(杀死进程)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUuVZamDVtic25eHvuv3Ek0JsPmuWbOD7Iov7Ulo7KlOFVQR21iakF2ePOg/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(列出进程目录树)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUu68CEAzicq0ddwyO6hvo3vjS2MibocKQlW8cb2Kk8xoLS5VVmUSsNaAJg/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(杀死sleep的所有进程)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUu9Xiaib3a80amVusJofUlhcz3nZTyic5ibNYqjfl4gPyicPAytzqbywd0IuA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(pkill的使用)</p>

- **格式：kill signal PID 只能杀死一个进程**
- **格式：killall 进程名字**
- **killall -signal 进程名字**
- **killall -signal -u username 进程名字**
- **pkill 类似 killall，但命令可以模糊匹配。**

## 四、监控进程活动

**系统负载的计算和意义：进程以及子进程和线程产生的计算指令都会让CPU执行，这些进程组成“运行队列”，等待CPU执行，这个队列就是系统负载。**

每个CPU拥有独立的请求队列。可看/proc/cpuinfo。

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbukM2xCss1iazdBjVpD0JJUuy69KKfJpufOUIVqltOSYP6icxvgegHoBicMvVpXCnsibHDafCBe9vkzcA/640?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(查看cpu信息)</p>

top 命令实时监控进程状态。

## 五、说明

原创文章链接：[Linux 进程基础知识](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483748&idx=1&sn=d1d824cb775f8b1a188ee556153a5b92&chksm=f94c8b59ce3b024f4d71dbdd06916bfeb385d52b042aeb4b332257407e3234307043511c772c&scene=21#wechat_redirect)
