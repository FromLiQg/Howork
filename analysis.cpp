
#define  _CRT_SECURE_NO_WARNINGS
#include<string>
#include<iostream>
#include<map>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
string grade, tmpclass, loccode, learncode, time, sub, score;
//单科结构体 
struct Node {
	//该科目总分数 
	double Sum;
	//不及格人数 
	int Fail;
	//80分+人数 
	int High;
	//该科目总人数 
	int Size;
	Node() :Sum(0), Fail(0), High(0),Size(0) {
	}
	//插入一个分数 
	void insert(double tmp) {
		++Size;
		Sum += tmp;
		if (tmp >= 80.0)
			++High;
		if (tmp < 60.0)
			++Fail;
	}
	//计算平均分 
	double average() {
		return Sum / Size;
	}
	void show() {
		cout <<grade<<"\t"<<tmpclass<<"\t"<<sub<< "\t" << Fail << "\t" << High << "\t";
		printf("%.2lf\n", average());
	}
};
//单班结构体 
struct SingleClass {
	//各科目 
	map<string, Node> Subject;
	//插入某一科的单个成绩 
	void insert(string TmpSubject, double TmpScore) {
		map<string, Node>::iterator location = Subject.find(TmpSubject);
		if (location == Subject.end()) {
			Node tmp;
			Subject.insert(make_pair(TmpSubject, tmp)).first->second.insert(TmpScore);
		}
		else {
			location->second.insert(TmpScore);
		}
	}
	void show() {
		map<string, Node>::iterator it = Subject.begin();
		while (it != Subject.end()) {
			//cout << it->first << endl;
			sub = it->first;
			it->second.show();
			it++;
			//cout << endl;
		}
	}
};
//年级结构体
struct Grade {
	map<string, SingleClass> ManyClass;
	void insert(string TmpClass, string TmpSubject, double TmpScore) {
		auto location = ManyClass.find(TmpClass);
		if (location == ManyClass.end()) {
			SingleClass tmp;
			ManyClass.insert(make_pair(TmpClass, tmp)).first->second.insert(TmpSubject, TmpScore);
		}
		else {
			location->second.insert(TmpSubject, TmpScore);
		}
	}
	void show() {
		auto it = ManyClass.begin();
		while (it != ManyClass.end()) {
			//cout << it->first << endl;
			tmpclass = it->first;
			it->second.show();
			it++;
			//cout << endl;
		}
	}
};
//学校结构体
struct School {
	map<string, Grade> ManyGrade;
	void insert(string TmpGrade, string TmpClass, string TmpSubject, double TmpScore) {
		auto location = ManyGrade.find(TmpGrade);
		if (location == ManyGrade.end()) {
			Grade tmp;
			ManyGrade.insert(make_pair(TmpGrade, tmp)).first->second.insert(TmpClass, TmpSubject, TmpScore);
		}
		else {
			location->second.insert(TmpClass, TmpSubject, TmpScore);
		}
	}
	void show() {
		auto it = ManyGrade.begin();
		while (it != ManyGrade.end()) {
		//	cout << it->first << endl;
			grade = it->first;
			it->second.show();
			it++;
		//	cout << endl;
		}
	}
}target;


//读取分数用，防止某个分数出现缺失导致数据格式错误
bool GetNonSpaceString(string &tmp) {
	tmp = "";
	if (cin.eof())return true;
	char c = cin.get();
	while (!cin.eof() && c != '\n' && (c > '9' || c < '0') && (c > 'D' || c < 'A')) {
		c = cin.get();
	}
	if (cin.eof())return true;
	if (c == '\n')return false;
	while (!cin.eof() && c != '\n'&&c != '\t'&&c != ' ') {
		tmp += c;
		c = cin.get();
	}
	if (cin.eof())return true;
	return false;
}
//string 转化成浮点数
double StrToD(string a) {
	int len = a.length(), i = 0;
	double ans = 0;
	while (i < len && (a[i] > '9' || a[i] < '0'))++i;
	while (i < len && (a[i] <= '9'&&a[i] >= '0')) {
		ans *= 10;
		ans += (a[i] - '0');
		++i;
	}
	if (i < len&&a[i] != '.')
		return ans;
	double k = 10.0;
	while (i < len && (a[i] <= '9'&&a[i] >= 0)) {
		ans += (a[i] - '0') / k;
		k *= 10;
		++i;
	}
	return ans;
}

int main() {
	string tar;
	cout << "请输入第几学段" << endl;
	cin >> tar;
	freopen("in.txt","r",stdin);
	freopen("out.xls", "w", stdout);
	//int i = 1;
	while (cin>>grade>>tmpclass>>loccode>>learncode>>time>>sub&& !GetNonSpaceString(score)) {
		double s = StrToD(score);
		//if(i%10000==0)cout <<"读取完第" <<i<<"条数据" <<endl;
		//++i;
		if (time == tar && score!=""&&(score[0] <= '9'&&score[0] >= '0')) {
			target.insert(grade, tmpclass, sub, s);
		}
	}
	//cout << "读取完第" << i << "条数据" << endl;
	//cout << "读取完毕" << endl;
	target.show();
	system("outputIMG.py");
	return 0;
}
