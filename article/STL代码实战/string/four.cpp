#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;

int main(void){
	string s1 = "abcdefghijkl";
	//将对象s1------->char *;
	printf("%s\n", s1.c_str());

	//将s1中的内容copy到buf中
	char buff[80];  //必须的有空间
	s1.copy(buff, s1.length());//拷贝时不会加上'\0';
	cout<<buff<<endl;

	//字符串的连接
	string s2 = "aaa";
	string s3 = "bbb";
	//s2 = s2 + s3; //在C++中的+代表字符串的连接;
	s2.append(s3);  //append():表示字符串的连接;
	cout<<s2<<endl;



	return 0;
}
