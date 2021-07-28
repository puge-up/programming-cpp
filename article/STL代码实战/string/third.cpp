#include<iostream>
#include<string>
using namespace std;

//string类的初始化
int main(void){
	string s1 = "abcdefg";
	string s2("abcdefg");
	string s3 = s2;  //通过拷贝构造函数来初始化

//string的遍历，
	//因为重载了[],数组方式进行访问;
	for(int i = 0; i < s1.length(); i++){
			cout<<s1[i]<<" ";
	}
	//迭代器进行访问
	string::iterator it = s1.begin();
	for(; it != s1.end(); it++){
		cout<<*it<<" ";
	}

	try{
		//利用at()进行访问
		for(int i = 0; i < s1.length(); i++){
			cout<<s1.at(i)<<" ";  //这个at方法，当数组下标越界时,将抛出异常;
		}
	}
	catch(...){
		cout<<"发生异常"<<endl;
	}
	

	return 0;
}
