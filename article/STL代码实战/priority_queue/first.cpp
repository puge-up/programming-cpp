#include<iostream>
#include<queue>  //用的是优先级队列
using namespace std;

int main(void){
	priority_queue<int> p1;  //默认的情况下,是最大值优先级队列
	priority_queue<int, vector<int>, less<int> >  p2; //预定义函数
	priority_queue<int, vector<int>, greater<int> > p3; //最小值优先级队列

	p1.push(33);
	p1.push(1);
	p1.push(11);
	p1.push(55);
	p1.push(22);

	cout<<p1.size()<<endl;
	cout<<p1.top()<<endl; //即就是最大的数字

	while(p1.size() > 0){
		cout<<p1.top()<<endl;  //降序排列
	 	p1.pop();
	}

	cout<<endl;

	p3.push(33);
	p3.push(1);
	p3.push(11);
	p3.push(55);
	p3.push(22);

	cout<<p3.size()<<endl;
	cout<<p3.top()<<endl; //即就是最小的数字

	while(p3.size() > 0){
		cout<<p3.top()<<endl;  //升序排列
	 	p3.pop();
	}

	return 0;
}
