#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int main(void){
	string s1 = "hello1 hello2 hello3";

	string::iterator it = find(s1.begin(), s1.end(), 'l'); //返回的是一个迭代器;
	if(it != s1.end()){
		s1.erase(it);  //删除找到的第一个位置;
	}
	cout<<s1<<endl;

	s1.erase(s1.begin(), s1.end()); //全部的进行删除;

	string s2 = "BBB";
	s2.insert(1, "AAA");  //头插法
	cout<<s2<<endl;

	//
	transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
	cout<<s2<<endl;
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	cout<<s2<<endl;
	
	return 0;
}
