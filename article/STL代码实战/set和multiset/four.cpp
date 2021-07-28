#include<iostream>
#include<set>
using namespace std;

//set的查找
int main(void){
	set<int> set1;

	for(int i = 0; i < 10; i++){
		set1.insert(i+1);
	}


	set<int>::iterator it = set1.find(5);  //查找元素是5的迭代器的位置
	cout<<*it<<endl;

	int num1 = set1.count(5); //找值为5的元素个数
	cout<<num1<<endl;

	set<int>::iterator it1 = set1.lower_bound(5);  //找值>=5的元素的迭代器的位置
	cout<<*it1<<endl;

	set<int>::iterator it2 = set1.upper_bound(5);  //找值>5的元素的迭代器的位置
	cout<<*it2<<endl;

	pair<set<int>::iterator, set<int>::iterator> mypair = set1.equal_range(5);  //返回值为2个,一个迭代器是>=5，一个迭代器是>5的位置

	cout<<*mypair.first<<endl;
	cout<<*mypair.second<<endl;

	//把5删除掉,set中的删除元素和list的删除方法一致
	set1.erase(5);

	cout<<endl;
	set<int>::iterator it6 = set1.begin();
	for(; it6 != set1.end(); it6++){
		cout<<*it6<<" ";
	}
	cout<<endl;

	return 0;
}

