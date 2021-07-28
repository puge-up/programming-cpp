#include<iostream>
#include<vector>
using namespace std;

int main(void){
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(5);
	vector<int> v2 = v1;
	

	cout<<v1.size()<<endl;  //求动态数组的长度
	cout<<v1.back()<<endl; //获取尾部元素;
	v1.pop_back();         //删除尾部元素
	cout<<v1.size()<<endl;
	cout<<v1.front()<<endl;  //获取头部元素

	v1.front() = 11;  //函数返回值当左值，返回的是引用;
	cout<<v1.front()<<endl;

	//数组形式的遍历vector；
	vector<int> v3(10);  //对vector的空间的开辟,10个大小的空间;
	for(int i = 0; i < v1.size(); i++){
		cout<<v1[i]<<" ";
	}
	//迭代器的遍历
	cout<<endl;
	vector<int>::iterator it = v1.begin();
	for(; it != v1.end(); it++){
		cout<<*it<<" ";
	}

	return 0;
}
