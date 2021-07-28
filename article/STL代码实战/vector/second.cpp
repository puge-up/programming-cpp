#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;

int main(void){
	vector<int> v1(10);

	for(int i = 0; i < 10; i++){
		v1[i] = i + 1;
	}

	//当it == v1.end()的时候,容器已经遍历完毕了;
	//逆序迭代器;
	vector<int>::reverse_iterator rit = v1.rbegin();
	for(; rit != v1.rend(); rit++){
		cout<<*rit<<" ";
	}
	cout<<endl;

	//删除元素
	v1.erase(v1.begin(), v1.begin()+3);  //区间删除元素
	v1.erase(v1.begin());  //在头部删除一个元素
	v1[0] = 2;
	v1[1] = 2;
	v1[3] = 2;
	//将vector中的值为2的都删除了
	vector<int>::iterator it = v1.begin();
	for(; it != v1.end();){
		if(*it == 2){   //按照值删除，找到对应的迭代器即可
			it = v1.erase(it);     //当删除迭代器所指向的元素时,会让it自动下移
		}else{
			it++;
		}

	}
	
	v1.insert(v1.begin(), 100);  //头插法,插入100
	v1.insert(v1.end(), 200);    //尾插法,插入100;
	for(int i = 0; i < v1.size(); i++){
		cout<<v1[i]<<" ";
	}

	
	return 0;
}
