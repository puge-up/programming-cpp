#include<iostream>
#include<queue>
using namespace std;

int main(void){
	queue<int> q;

	for(int i = 0; i < 3; i++){
		q.push(i+1);  //入队列
	}
	cout<<q.front()<<endl; //取队头
	cout<<q.size()<<endl;  //求队列的大小

	while(!q.empty()){  //判断是否队空
		int tmp = q.front(); //取队头元素
		cout<<tmp<<" ";
		q.pop();  //删除队头
	}

	return 0;
}
