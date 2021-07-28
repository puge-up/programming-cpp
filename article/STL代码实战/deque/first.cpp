#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;


//push_front()  头部插入
//pop_front()   头部删除
//push_back()   尾部插入 
//pop_back()    尾部删除
int main(void){
	deque<int> d1;

	d1.push_back(1);
	d1.push_back(3);
	d1.push_back(5);

	d1.push_front(-1);
	d1.push_front(-3);
	d1.push_front(-5);

	deque<int>::iterator it = d1.begin();
	for(; it != d1.end(); it++){
		cout<<*it<<" ";
	}
	cout<<endl;

	cout<<d1.front()<<endl;
	cout<<d1.back()<<endl;
	//查找-3在数组下标的位置
	deque<int>::iterator it1 = find(d1.begin(), d1.end(), -3);
	if(it1 != d1.end()){
		cout<<"下标:"<<distance(d1.begin(), it1)<<endl; //distance()是求查找的元素在数组中的下标;
	}else{
		cout<<"没有找到-3的元素"<<endl;
	}

	return 0;
}
