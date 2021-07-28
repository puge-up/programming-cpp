#include<iostream>
#include<map>
using namespace std;

int main(void){
	map<int, string> map1;

	map1[1] = "teacher01";
	map1[2] = "teacher02";
	map1[3] = "teacher03";
	map1[6] = "teacher06";
	map1[5] = "teacher05";
	map1[4] = "teacher04";

	map<int, string>::iterator it = map1.begin();
	for(; it != map1.end(); it++){
		cout<<it->first<<"\t"<<it->second<<endl;
	}
	

	//map的查找,异常处理
	map<int, string>::iterator it = map1.find(4);
	if(it == map1.end()){ //map查找失败的处理
		cout<<"key=100的值不存在"<<endl;
	}else{
		cout<<it->first<<"\t"<<it->second<<endl;
	}a
	

	pair<map<int, string>::iterator, map<int, string>::iterator> pair1 = map1.equal_range(5); //返回2个迭代器,形成一个pair
	//第一个迭代器是>=5的位置
	//第二个迭代器的>5的位置
	if(pair1.first == map1.end()){
		cout<<"第一个迭代器不存在"<<endl;
	}else{
		cout<<pair1.first->first<<"\t"<<pair1.first->second<<endl;
	}

	if(pair1.second == map1.end()){
		cout<<"第二个迭代器不存在"<<endl;
	}else{
		cout<<pair1.second->first<<"\t"<<pair1.second->second<<endl;
	}

	return 0;
}


