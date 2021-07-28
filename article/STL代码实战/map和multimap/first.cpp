#include<iostream>
#include<string>
#include<map>
using namespace std;
//map是关联式容器,存放的是一个键值对(key-value),提供了基于key的快速检索能力
//map中的key的值是唯一的,集合中的元素按照一定的顺序排列,元素的插入过程是按照排序的规则插入,所以不能指定插入位置
//map可以直接存取key所对应的value,支持[]:map[key] = value;
//multimap与map的区别：
//map的每个键只能出现一次,而multimap中相同的键可以出现多次,multimap不支持[]

int main(void){
	map<int, string> map1;

	//map的插入方法一:通过pair对组方式，map的插入只要保证key不同即可;
	map1.insert(pair<int, string>(1, "teacher01"));
	map1.insert(pair<int, string>(2, "teacher02"));

	//方法2
	map1.insert(make_pair(3, "teacher03"));
	map1.insert(make_pair(4, "teacher04"));

	//方法3
	map1.insert(map<int, string>::value_type(5, "teacher05"));
	map1.insert(map<int, string>::value_type(6, "teacher06"));

	//方法4
	map1[7] = "teacher07";
	map1[8] = "teacher08";

	//map的遍历算法
	map<int, string>::iterator it = map1.begin();
	for(; it != map1.end(); it++){
		cout<<it->first<<"\t"<<it->second<<endl; //容器的遍历和pair的是一样的
	}
	//map元素的删除
	while(!map1.empty()){
		map<int, string>::iterator it1 = map1.begin();
		cout<<it1->first<<"\t"<<it1->second<<endl;
		map1.erase(it1);
	}

	//插入方法,map中的insert()返回的都是pair<iterator, bool>:若插入相同的key即报错;
	pair<map<int, string>::iterator, bool> pair1 = map1.insert(pair<int, string>(9, "teacher09"));
	if(pair1.second == true){
		cout<<"插入成功"<<endl;
		cout<<pair1.first->first<<"\t"<<pair1.first->second<<endl;
	}else{
		cout<<"插入失败"<<endl;
	}
	map1[9] = "teacher10";  //这种方式进行插入,若key已经存在,则不会报错,只是进行修改;
	cout<<map1[9]<<endl;


	
	return 0;
}
