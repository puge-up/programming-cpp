- [一、ip](#一ip)
- [二、nmcli](#二nmcli)
- [三、nmcli创建新的连接](#三nmcli创建新的连接)
- [四、说明](#四说明)

Linux 网络简单配置是 Linux 基础之一。

TCP/IP四层模型、IPV4地址、IPV4路由、网络接口名称；

**Red Hat7之前的系统以eth0, eth1等名字来命名网卡，在rhel7系统中开始使用新的命名规范：基于固件、设备结构、设备类型。**

## 一、ip

- ip 命令可用于显示设备和地址信息
- ip命令也可用于显示关于网络性能的统计信息
- ip route 显示路由信息

## 二、nmcli

使用nmcli配置网络，一些常见的命令：

name|连接的名称
|:--|:--|
UUID|连接的UUID
TYPE|连接的类型
DEVIDE|连接绑定的设备

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdA1FR7XQ6iaOQO6MERnG1Fby30nSppIBOBhxqYehTSuBF9bicEIk3LABw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(仅显示活动的连接)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdDL57f7FsKxtcQLuXmVA6Qfia9GanOGgYHbmribfwiag9wy5icKG7ZNv3bg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(某特定连接)</p>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdS5ibR553iaGn7os2NoF1jiaC7PyVHsSzicicHibIof5sCqB7srgZCVjNOqcA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(特定连接的详细信息)</p>

## 三、nmcli创建新的连接

使用nmcli创建新的连接，连接其实就是给一个物理网卡创建一个配置信息。

定义一个名字为default的连接，该连接会通过DHCP自动获取IP地址等信息。

命令：nmcli con add con-name "default" type ethernet ifname eth0

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdQViaHWAHD9ibk0QtyG5eVX3b1dmf8iaSAbblo8DpTpIY42DFo2vsGMkKA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdibiavK244I2O61IJicCd4ib9FqhEgwL2GUKJKrUL4TU947uwibxlTc16UFA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8Qdv0k6jibsbvib6rQMljKgSz9OdknAicc2ichlKEWW2WZib9mC2RV8CNzklSg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdnOcxjONmNtJpVBn9L6YzVVfZZkBSH55nOEpYF6ByOmic3yy9A9MicNMQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

**通过nmcli修改网络接口，可以通过nmcli con mod 参数修改现有的连接。**

关闭static的自动连接功能：nmcli con mod "static" connection.autoconnect no

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbvcm6SGotmhLI7NG9e3h8QdhBhhXNkw5O815ed196JicHRK6hWIJSRicoIg1ZibicSUrUwtbPic41yOPuw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>
<p align=center>(关闭static的自动连接功能)</p>

其他命令：
命令|解释
|:--|:--|
nmcli con del ""|删除一个连接
nmcli net off|关闭所有接口的连接
nmcli dev dis|关闭某个接口，并临时禁用自动连接
nmcli con down ""|断开某个连接

图形界面配置网络：nm-connection-editor

## 四、说明

原创文章链接：[Linux 网络简单配置](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247483800&idx=1&sn=fbbd2dcaedb96473b9b22fe81cca4d27&chksm=f94c8ba5ce3b02b30daf49fe452ff850354705ab3e6044dfc323c87435d99d44ce5706fab83b&scene=21#wechat_redirect)
