#include<iostream>
#include<string.h>
#include<set>
using namespace std;


//自定义数据类型存放在set容器中
class Student{
	public:
		Student(char *name, int age){
			strcpy(this->name, name);
			this->age = age;
		}

	public:
		char name[64];
		int  age;

};

struct FuncStudent{ //此处的仿函数就是写一个类,类里面重载了(),从而可以自定义排序规则
	bool operator()(const Student &left, const Student &right){ // 此时对()进行运算符的重载
		if(left.age < right.age){
			return true; //按照从小到大进行元素的排列
		}else{
			return false;
		}
	}
};

//自定义的set的排序,的用到仿函数
int main(void){
	Student s1("s1", 31);
	Student s2("s2", 32);  //在插入时会自动的调用仿函数
	Student s3("s3", 33);
	Student s4("s4", 34); //复杂的数据类型,2个31,能否插入成功
	//按照关键字(此时是age，因为是按照age进行的排序)如果重复,则不会插入成功;
	

	set<Student, FuncStudent> set1; // 此时的set集合中存放的是自定义的数据类型,和按照自己定义仿函数自己制定规则进行排序
//在插入set时,的进行排序,的提供回调函数的入口地址(提供仿函数)
	set1.insert(s1);
	set1.insert(s2);
	set1.insert(s3);
	set1.insert(s4);

	set<Student, FuncStudent>::iterator it = set1.begin(); //按照年龄进行的排序
	for(; it != set1.end(); it++){
		cout<<it->age<<"\t"<<it->name<<endl;
	}


	//如何判断insert()函数的返回值
	Student s5("s5", 35);
	Student s6("s5", 31);

	//用pair对组来实现inser()返回值的判定
	pair<set<Student, FuncStudent>::iterator, bool> pair1 = set1.insert(s5);
	if(pair1.second == true){
		cout<<"插入s5成功"<<endl;
	}else{
		cout<<"插入s5失败"<<endl;
	}

	pair<set<Student, FuncStudent>::iterator, bool> pair2 = set1.insert(s6);
	if(pair2.second == true){
		cout<<"插入s6成功"<<endl;
	}else{
		cout<<"插入s6失败"<<endl;
	}

	return 0;
}
