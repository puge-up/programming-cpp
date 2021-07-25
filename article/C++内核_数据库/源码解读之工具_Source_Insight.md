- [一、Source Insight](#一source-insight)
- [二、Source Insight的基本使用](#二source-insight的基本使用)
- [三、Linux内核代码的查找](#三linux内核代码的查找)
- [四、说明](#四说明)

## 一、Source Insight

这个工具又叫做**程序编辑器和代码浏览器**，支持C/C++、C#、java等的分析，是一款功能强大的处理大型项目所需的软件，是一个程序员的必备软件；

针对Linux内核的剖析，是几百M大的文件，上百万行的代码，从中快速的浏览，找到你所需要的函数、变量名称，代码的追踪都是很好的，此时不可能一行一行的查找代码，所以就有了这个需求，这款软件就是解决这个问题的。

在工程项目中，它的作用是巨大的，针对几百、上千行的代码没有必要使用这个软件，现在针对的是Linux内核，工欲善其事必先利其器，所以首选这款软件帮助我们学习！！！

软件的安装

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1kp0yXTuNwRicOUtFzTDibNohKDGH0yTPEzk2Xevb21qgo68lJayvBakQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

这个软件在网上很好找的，安装的过程就是一直下一步，最后找一个注册码就行了；

## 二、Source Insight的基本使用

我演示一下怎么使用它来添加Linux的内核代码到这个软件中。

1、Project-->new Project

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1vXPU6EicMWNuwRgysIs6YywJWvuASdQic01GqlJla1gFTpxWwAlTe1iaA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

2、点击new Project就会出现

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1lIMRwYsJibUTpb00NzYolRGucCn22RoqTrHVibIPpGFfWR2iauMjyuPLg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

3、点击ok后

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1pKGzAWfjvB8BKrtuIERakS7QOlk1vtpDo6KCwYMRI8PicmqkfJnxJibw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

4、点击ok后

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1zcfhZgqoBqcx6gjQFicuIibwLCnbyFqzzn8lRF75dvAEMg2WWvghjomg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1HKb4uXTscKgh1fUder2qpttSYE74DXgywNWAj6wbcjTh9OGMLEbu5g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

5、点击close后

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1yz7dPdYtBr1OiaehcGW4621ibVKhRbic5FfSVn6BqDnNE6OibhmwyCCGQA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

以上就已经代表把项目加入到这个软件当中了；

6、还的形成代码之间函数的依赖性和变量的查找

Project--->Synchronize Files  点击就会出现下面

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1vIRrrwUAJYI8UHnIXXczo3aWdXyboibOyof8hlpogNqZ9KiaQEj0oicjA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

以上就完成了添加项目到这个软件中的所有步骤。

## 三、Linux内核代码的查找

1、文件的查找

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1TsibR3w6EHhmSmST0xjibNdYTgy55KIiaCgGxLJ1hicPhAUeArONuMePqA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>


2、文件中变量的查找

点击后，shift+F8 高亮显示

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt10WAszSg13YJl5zjFCEmEiaQEWG4caWOiaQR59hFTToBhU6pcdFsKwhicg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

3、ctrl + / 查找

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1UZcGEMvu0S3St46pHTFVHkR5s6cYMlmIicl3AVOicTIjev0QzpsAr44g/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

4、追踪查询

ctrl + 点进去；

5、查询函数，这里都是当前文件中的函数名称

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbv7jib7sBHhqUrZEt6A27lt1ohrWuacBxDOjScKYyXibIt4TCRiakHibz1ibcibhFKhMVbTdzHUK9QBCnZg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

</br>

以上就是Source Insight的部分使用，其实熟练操作后，会发现真的比较好用；

其它的关于这个软件的查查就可以处理了，关键在经常使用！！！

## 四、说明

原创文章链接：[源码解读之工具->Source Insight](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484090&idx=1&sn=01d40eb3c2bd00fd65d7f3e290044d48&chksm=f94c8887ce3b01916a4931408dbc32ba6a56db67befe7bc9ac46d8790e45fd4a6e0781e9eafe&scene=21#wechat_redirect)
