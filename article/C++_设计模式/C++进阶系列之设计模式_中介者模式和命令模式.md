- [一、中介者模式](#一中介者模式)
- [二、具体实现](#二具体实现)
- [三、命令模式](#三命令模式)
- [四、具体实现](#四具体实现)
- [五、说明](#五说明)

## 一、中介者模式

**就是借用一个中间的类,来完成其他2个类之间要实现的功能!!!**

## 二、具体实现

代码如下：

```cpp
#include<string>
using namespace std;

class Mediator{
    public:
        virtual void getParent() = 0;
    private:
};

class contreMediator{
    public:
    private:
};

  

class Person{
    public:
        Person(string name, int sex, int condi){
            m_name = name;
            m_sex = sex;
            m_condi = condi;
        }
        string getName(){
            return m_name;
        }
        int getSex(){
            return m_sex;
        }

        int getCondi(){
            return m_condi;
        }
        virtual void getParent(Person *p) = 0;

    protected:
        string m_name;
        int m_sex;
        int m_condi;

};

////////////////////////////////////////////////////////////////////////////////////////////

class Woman : public Person{
    public:
        Woman(string name, int sex, int condi) : Person(name, sex, condi){

        }
        void getParent(Person *p){
            if(this->m_sex == p->getSex()){
                cout<<"不是×××"<<endl;   
            }
            if(this->getCondi() == p->getCondi()){
                cout<<this->getName()<<"和"<<p->getName()<<"绝配"<<endl;
            }else{
                cout<<this->getName()<<"和"<<p->getName()<<"不配"<<endl;

            }
        }
    private:
};

//////////////////////////////////////////////////////////////////////////////////////////////////
class Man : public Person{
    public:
        Man(string name, int sex, int condi) : Person(name, sex, condi){

        }
        void getParent(Person *p){
            if(this->m_sex == p->getSex()){
                cout<<"不是×××"<<endl;
            }
            if(this->getCondi() == p->getCondi()){
                cout<<this->getName()<<"和"<<p->getName()<<"绝配"<<endl;
            }else{
                cout<<this->getName()<<"和"<<p->getName()<<"不配"<<endl;

            }     
        }
    private:
};
int main(void){
    Person *xiaofang = new Woman("小芳", 2, 5);
    Person *zhangsan = new Man("张三", 1, 4);
    Person *lisi = new Man("李四", 1, 5);

    xiaofang->getParent(zhangsan);
    xiaofang->getParent(lisi);


    return 0;
}
```

## 三、命令模式

**把一个动作进行分解,分成发布者和接受者；**

## 四、具体实现

代码如下：

```cpp
#include<iostream>
using namespace std;

class Doctor{
    public:
        void treatEye(){
            cout<<"医生 治疗 眼病"<<endl;
        }   
        void treatNose(){
            cout<<"医生 治疗 鼻科病"<<endl;
        }   
    private:
};

class Command{
    public:
        virtual void treat() = 0;
    private:
};


class CommandTreatEye : public Command{
    public:
        CommandTreatEye(Doctor *doctor){
            m_doctor = doctor;
        }
        void treat(){
            m_doctor->treatEye();
        }
    private:
        Doctor *m_doctor;
};

class CommandTreatNose : public Command{
    public:
        CommandTreatNose(Doctor *doctor){
            m_doctor = doctor;
        }
        void treat(){
            m_doctor->treatNose();
        }
    private:
        Doctor *m_doctor;
};

class BeautyNurse{
    public:
        BeautyNurse(Command *command){
            this->command = command;
        }
    public:    
        void SubmittedCase(){  //提交病类, 下单命令
            command->treat();
        }
    private:
        Command *command;
};

int main(void){
    /*
    //1、医生直接看病
    Doctor *doctor = new Doctor;
    doctor->treatEye();
    delete doctor;
    */

    /*
    //2、通过一个命令
    Doctor *doctor = new Doctor;
    Command *command = new CommandTreatEye(doctor);
    command->treat();

    delete command;
    delete doctor;
    */

    //护士提交简历,医生看病;
    Doctor *doctor = new Doctor;
//  Command *command = new CommandTreatEye(doctor);
    Command *command01 = new CommandTreatNose(doctor);
    BeautyNurse *beautyNurse = new BeautyNurse(command01);

    beautyNurse->SubmittedCase();


    delete doctor;
    delete command01;
    delete beautyNurse;

    return 0;
}
```

## 五、说明

原创文章链接：[C++进阶系列之设计模式（8）---中介者模式和命令模式](https://mp.weixin.qq.com/s?__biz=MzUxMzkyNDk0Ng==&mid=2247484060&idx=1&sn=148671f2b70cca1a629a373d28cb6e0b&chksm=f94c88a1ce3b01b74456091c92b4809b4ed567641f2683ca2112a27e5c39e776569a201ae10c&scene=21#wechat_redirect)
