- [一、仿函数](#一仿函数)
- [二、仿函数和回调函数的区别](#二仿函数和回调函数的区别)
- [三、说明](#三说明)

## 一、仿函数

- **本质：是一个对象，用起来像函数；**
- **原因：在类内对()进行了重载；**

## 二、仿函数和回调函数的区别

代码如下：

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

//函数对象:类重载了();
//函数对象和函数是很类似的;

template<typename Type>
class ShowElem{
    public:
        ShowElem(){
            n = 0;
        }   
        void operator()(Type &t){   //重载了(),此时可以叫做函数对象;
            n++;
            cout<<t<<endl;
        }   
        void printN(){
            cout<<"n:"<<n<<endl;    
        }   
    protected:
    private:
        int n;
};

void main01(){
    int a = 10;
    ShowElem<int> showElem;
    showElem(a); //函数对象的()的执行,很像一个函数;所以又叫做仿函数;
                 //函数对象可以跟函数的调用一样,直接把对象当作函数名称来使用!!!
}

//函数对象和普通函数的区别;
template<typename Type>  //函数模版
void FuncShowElem(Type &t){
    cout<<t<<endl;
}

void FuncShowElem2(int &t){ //普通函数
    cout<<t<<endl;
}

void main02(){
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    for_each(v1.begin(), v1.end(), ShowElem<int>()); //匿名函数对象 匿名仿函数;
    cout<<endl;
    for_each(v1.begin(), v1.end(), FuncShowElem2); //通过回调函数;谁使用for_each()

}

int main(void){
    main01();
    main02();

    return 0;
}
```

运行结果：

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbtSgOOeSbnHjfqoq3VP8EwvSDgnicCSxkxG1VVAjGEcQ1AicFF4Vs6jlGQPxPicbr1MykwRxvGqRoCQw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

## 三、说明

原创文章链接：[C++进阶系列之STL（8）---仿函数](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484012&idx=1&sn=1b04e505a1e24a013551b664e4590a13&chksm=f94c8851ce3b0147baed71aa4c59b680bab6eb7a126d19d8deccfdd42b67c8829f3145a79b92&scene=21#wechat_redirect)
