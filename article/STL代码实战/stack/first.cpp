#include<iostream>
#include<stack>
using namespace std;

int main(void){
	stack<int> s1;

	for(int i = 0; i < 10; i++){
		s1.push(i+1); //入栈
	}

	cout<<s1.size()<<endl;  //栈的大小
	while(!s1.empty()){  //判栈空
		int tmp = s1.top(); //读栈顶元素
		cout<<tmp<<" ";
		s1.pop();  //弹出栈顶元素
	}
	cout<<endl;

	return 0;
}
