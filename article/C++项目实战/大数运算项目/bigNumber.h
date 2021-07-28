#ifndef _BIG_NUMBER_H_
#define _BIG_NUMBER_H_

#include<iostream>
#include<algorithm>
#include<vector>
#include<stdio.h>
#include<assert.h>
using namespace std;

void bigAdd(vector<int> &res, vector<int> &v1, vector<int> &v2);
char addItem(int a, int b, char &sign);
void bigSub(vector<int> &res, vector<int> &v1, vector<int> &v2);
char subItem(int a, int b, char &sign);
bool operator>=(const vector<int> &v1, const vector<int> &v2); 
bool operator==(const vector<int> &v1, const vector<int> &v2);
void bigMul(vector<int> &res, const vector<int> &v1, const vector<int> &v2);
void mulItem(vector<int> &tmp, const vector<int> &v1, int a);
void moveAdd(vector<int> &res, const vector<int> &tmp, int pos);

#endif
