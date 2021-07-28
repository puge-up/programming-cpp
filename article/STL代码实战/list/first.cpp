#include<iostream>
#include<list>  
//双向链表容器,可高效的进行插入删除元素
//list不可以随机存取元素,不支持at()和[],可以it++/it--,不可以it+5
//list节点序号从0开始
//插入元素，指的是前插
//删除操作：[0,3)
using namespace std;

int main(void){
	list<int> l;

	cout<<l.size()<<endl;
	for(int i = 0; i < 10; i++){
		l.push_back(i+1);  //尾插法
	}
	l.push_back(2);  //尾插法
	l.push_back(2);  //尾插法
	cout<<l.size()<<endl;

//list不能随机访问，it = it + 5; 错误

//	it = l.begin();
//	l.insert(it, 100);  //指的是前插
//	cout<<l.front()<<endl;  

//list中的删除
//	l.clear();   //删除容器所有数据
//	l.erase(l.begin(), l.end());  //删除区间元素 [0,3)
//	l.erase(it);   //删除pos位置的数据,用的是迭代器的定位;
	l.remove(2);  //删除指定元素的值

	list<int>::iterator it = l.begin();
	while(it != l.end()){
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}
