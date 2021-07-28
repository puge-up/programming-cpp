#include<iostream>
#include<set>
using namespace std;

int main(void){
	multiset<int> set1;
	int tmp = 0;

	cout<<"请输入multiset集合的值:"<<endl;
	cin>>tmp;
	while(tmp){
		set1.insert(tmp);
		cout<<"请输入multiset集合的值:"<<endl;
		cin>>tmp;
	}

	multiset<int>::iterator it = set1.begin();
	for(; it != set1.end(); it++){
		cout<<*it<<" ";
	}
	cout<<endl;

	while(!set1.empty()){
		set1.erase(set1.begin());
	}

	cout<<set1.size()<<endl;
	
	return 0;
}
