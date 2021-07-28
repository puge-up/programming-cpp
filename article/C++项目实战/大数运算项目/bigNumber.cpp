#include"./bigNumber.h"

void moveAdd(vector<int> &res, const vector<int> &tmp, int pos){
	int i = pos;
	int j = 1;
	char sign = 0;

	while(i <= res.size() && j <= tmp.size()){
		res[i] = addItem(res[i], tmp[j], sign);
		i++;
		j++;
	}
	while(sign > 0 && i <= res.size()){
		res[i] = (int)addItem(res[i], 0, sign);
		i++;
	}
	while(j <= tmp.size()){
		int add = (int)addItem(0, tmp[j], sign);
		res.push_back(add);
		j++;
	}
	if(sign >= 1){
		res.push_back(sign);
	}
}
void mulItem(vector<int> &tmp, const vector<int> &v1, int a){
	char res = 0;
	char sign = 0;
	int i;

	for(i = 1; i <= v1.size(); i++){
		res = v1[i] * a + sign;
		sign = res/10;
		res %= 10;
		tmp.push_back(res);
	}
	if(sign > 0){
		tmp.push_back(sign)	;
	}
}
void bigMul(vector<int> &res, const vector<int> &v1, const vector<int> &v2){
	vector<int> tmp;

	res.clear();
	for(int i = 1; i <= v2.size(); i++){
		tmp.clear();
		mulItem(tmp, v1, v2[i]);
		moveAdd(res, tmp, i);
	}

}
bool operator==(const vector<int> &v1, const vector<int> &v2){
	if(v1.size() != v2.size()){
		return false;
	}

	int i = v1.size()-1;
	while(i >= 1){
		if(v1[i] != v2[i]){
			return false;
		}
		i--;
	}
	return true;
}
bool operator>=(const vector<int> &v1, const vector<int> &v2){
	if(v1.size() > v2.size()){
		return true;
	}else if(v1.size() < v2.size()){
		return false;
	}

	int i = v1.size()-1;
	while(i >= 1){
		if(v1[i] > v2[i]){
			return true;
		}else if(v1[i] < v2[i]){
			return false;
		}
		i--;
	}
	return true;
}

char subItem(int a, int b, char &sign){
	char sub;

	if(a >= b+sign){
		sub = a - b - sign;
		sign = 0;
	}else{
		sub = a + 10 - b - sign;
		sign = 1;
	}
	return sub;
}
void bigSub(vector<int> &res, vector<int> &v1, vector<int> &v2){
	assert(v1 >= v2);

	if(v1 == v2){
		res.push_back(0);
		return;
	} 
	int i = 1;
	int j = 1;
	char sign = 0;
	char sub = 0;
	
	while(i < v1.size() && j < v2.size()){
		sub = subItem(v1[i++], v2[j++], sign);
		res.push_back(sub);
	}
	while(i < v1.size()){
		sub = subItem(v1[i++], 0, sign);
		res.push_back(sub);
	}

}
char addItem(int a, int b, char &sign){
	char sum = a + b + sign;

	sign = sum / 10;
	sum %= 10;

	return sum;
}
void bigAdd(vector<int> &res, vector<int> &v1, vector<int> &v2){
	int i = 1;
	int j = 1;
	char sign = 0;
	char sum;

	while(i < v1.size() && j < v2.size()){
		sum = addItem(v1[i++], v2[j++], sign);
		res.push_back(sum);
	}

	while(i < v1.size()){
		sum = addItem(v1[i++], 0, sign);
		res.push_back(sum);
	}
	while(j < v2.size()){
		sum = addItem(0, v2[j++], sign);
		res.push_back(sum);
	}
	if(sign > 0){
		res.push_back(sign);
	}
}

int main(void){
	vector<int> v1;
	vector<int> v2;
	vector<int> res;
	int i;
	char str1[80] = {0};
	char str2[80] = {0};

	printf("str1 : ");
	gets(str1);
	printf("str2 : ");
	gets(str2);
	v1.push_back(0);
	for(i = 0; str1[i]; i++){
		v1.push_back(str1[i] - '0');
	}

	v2.push_back(0);
	for(i = 0; str2[i]; i++){
		v2.push_back(str2[i] - '0');
	}
	reverse(v1.begin()+1, v1.end());
	reverse(v2.begin()+1, v2.end());
	
	res.push_back(0);
	bigAdd(res, v1, v2);
	//bigSub(res, v1, v2);
	//bigMul(res, v1, v2);
	reverse(res.begin()+1, res.end());
	for(i = 1; i < res.size(); i++){
		cout<<res[i];
	}
	
	return 0;
}
