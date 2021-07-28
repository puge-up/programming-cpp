#include<iostream>
#include<string>
using namespace std;

int main(void){
	string s1 = "wbm hello wbm 111 wbm 222 wbm 333";

	//string的查找
	//找"wbm"第一次出现的下标位置
	int index = s1.find("wbm", 0); //位置下标从0开始找;没找到返回-1

	//找"wbm"出现的次数	
	int offindex = index;
	int count = 0;
	while(offindex != string::npos){  // != -1;
		count++;
		offindex = s1.find("wbm", offindex+1);
	}
	cout<<count<<endl;

	////////////////////////////////////////////////////////////////////////////////////////////
	//查找后进行替换
	
	offindex = index;
	while(offindex != string::npos){  // != -1;
		s1.replace(offindex, 3, "WBM");  //从offindex下标开始,删除3个字符,替换为"WBM"；
		offindex = s1.find("wbm", offindex+1);
	}

	cout<<s1<<endl;

	return 0;
}
