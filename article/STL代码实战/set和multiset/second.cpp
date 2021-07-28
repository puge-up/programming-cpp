#include<iostream>
#include<set>
using namespace std;

int main(void){
	set<int> set1;   //默认的情况下,从小到大
	set<int, less<int> > set2;
	set<int, greater<int> > set3;  //此时从大到小的 排序

	set3.insert(2);
	set3.insert(4);
	set3.insert(1);
	set3.insert(0);
	set3.insert(9);

	set<int, greater<int> >::iterator it = set3.begin();
	for(; it != set3.end(); it++){
		cout<<*it<<" ";
	}
	cout<<endl;

	return 0;
}
