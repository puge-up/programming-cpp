#include<iostream>
#include<string>
#include<map>
using namespace std;

class Person{
	public:
		string name;
		int    age;
};

//multimap:1个key可以对应多个value =====>解决分组的问题;
int main(void){
	Person p1, p2, p3, p4, p5;
	p1.name = "王1";
	p1.age = 31;

	p2.name = "王2";
	p2.age = 32;

	p3.name = "王3";
	p3.age = 33;
	
	p4.name = "王4";
	p4.age = 34;

	p5.name = "王5";
	p5.age = 35;
	multimap<string, Person> map1;
	//sale部门
	map1.insert(make_pair("sale", p1));
	map1.insert(make_pair("sale", p2));
	//development
	map1.insert(make_pair("development", p3));
	map1.insert(make_pair("development", p4));
	//financial
	map1.insert(make_pair("financial", p5));

	multimap<string, Person>::iterator it = map1.begin();
	for(; it != map1.end(); it++){
		cout<<it->first<<"\t"<<it->second.name<<endl;
	}
	cout<<"遍历结束"<<endl;	
	int num = map1.count("development");
	cout<<"development部门的人数: "<<map1.count("development")<<endl;
	multimap<string, Person>::iterator it2 = map1.find("development");

	int tag = 0;
	while(it2 != map1.end() && tag++ < num){
		cout<<it2->first<<"\t"<<it2->second.name<<endl;
		it2++;
	}
	
	//将name = 王5修改为王7
	multimap<string, Person>::iterator it3 = map1.begin();
	for(; it3 != map1.end(); it3++){
		if(it3->second.name == "王5"){
			it3->second.name = "王7";
			cout<<it3->second.name<<endl;
		}
	}
	return 0;
}
