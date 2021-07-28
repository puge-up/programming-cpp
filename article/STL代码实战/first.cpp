#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(void){
	vector<int> v1;

	v1.push_back(1); //v1是对象,必须可以copy
	v1.push_back(3);
	v1.push_back(5);
	v1.push_back(3);
	v1.push_back(3);
	v1.push_back(3);
	vector<int>::iterator it = v1.begin(); //迭代器相当与指针
	for(; it != v1.end(); it++){
		cout<<*it<<" ";
	}
	cout<<endl;

	int num1 = count(v1.begin(), v1.end(), 3); //遍历,统计vector中的值为3的个数
	cout<<num1<<endl;

	return 0;
}
