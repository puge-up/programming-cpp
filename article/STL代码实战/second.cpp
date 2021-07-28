#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//找出数组中第一个只出现一次的数字；
//3 4 6 1 3 6 4
int main(void){
	int array[] = {3, 4, 6, 1, 3, 6, 4};
	vector<int> v1;
	for(int i = 0; i < sizeof(array)/sizeof(int); i++){
		v1.push_back(array[i]);
	}

	vector<int>::iterator it = v1.begin();
	for(; it != v1.end(); it++){
		if(count(v1.begin(), v1.end(), *it) == 1){
			cout<<*it<<endl;
			break;
		}
	}


	return 0;
}
