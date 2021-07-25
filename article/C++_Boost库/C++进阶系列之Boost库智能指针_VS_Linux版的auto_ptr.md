1、VC版智能指针

上次的对其auto_ptr内部结构的实现有些问题：
(1)、赋值语句

```cpp
 auto_ptr<_Ty>& operator=(const auto_ptr<_Ty> &_Y){
        if(this != &_Y){
            if(_Ptr != _Y._Ptr){
                if(_Owns)
                    delete _Ptr;
                _Owns = _Y._Owns;
            }
            else if(_Y._Owns){   //这个地方上次写错了,自己考虑的不周到，
                                 //应该判断其是否为真，真的赋值，假的话，不能，
                _Owns = _Y._Owns; //因为此时万一是下面主函数所写的，就会发生
            }                   //内存空间没人管理，内存泄漏！！！
            _Ptr = _Y.release();
        }
        return *this;
    }

    int main(void){
        int *p = new int(10);
        
        auto_ptr<int> pa(p);
        auto_ptr<int> pa1(pa);
        pa1 = pa;    //上面赋值语句防的就是这种情况，担心同一空间没人管理，导致没法释放！！！
    }
```

<div align=center><img src='https://mmbiz.qpic.cn/mmbiz_png/cu0TUlMDjbuYDzIIAcqN4oK0b0rH5qKKRibW8BC3rrhyoHsYiaiaZDfQiaQkuiabuHd7h8WLJkC3T9ou0fBC4VBPcDg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1' width="50%" height="50%"></div>

(2)、就是VC版的在release()函数中也可以转移彻底，程序如下：


