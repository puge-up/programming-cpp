#include<iostream>
#include<set>
#include<time.h>
#include<stdlib.h>
using namespace std;

//set是一个集合容器,其中所包含的元素是唯一的,集合中的元素按照一定的顺序排列
//元素的插入过程是按顺序规则插入,不能指定插入位置
//set底层的实现是红黑树,再插入和删除操作上比vector快;
//set不能使用at()和[]直接存取元素;

//multiset与set的区别:
//set每个元素只能出现一次
//multiset中同一个值可以出现多次
//不可以直接修改set/multiset容器中的值,因为该类容器是自动排序的,如果希望修改一个元素值,必须先删除原有元素,在插入新的元素;

int main(void){
	set<int> set1;

	srand(time(NULL));
	for(int i = 0; i < 5; i++){
		int tmp = rand()%5;
		set1.insert(tmp);
	}
	set1.insert(100); //插入数字,不能有重复的,默认是从小到大的
	set1.insert(100);
	set1.insert(100);

	//对基础的数据类型,set可以自动排序,默认从小到大;
	//对复杂的数据类型,的自己写一个类,该类中重载了(),自己定义比较方法;
	set<int>::iterator it = set1.begin();
	for(; it != set1.end(); it++){
		cout<<*it<<" ";
	}
	cout<<endl;
	
	//删除集合
	while(!set1.empty()){
		set<int>::iterator it1 = set1.begin();
		cout<<*it1<<" ";
		set1.erase(set1.begin());
	}

	return 0;
}
