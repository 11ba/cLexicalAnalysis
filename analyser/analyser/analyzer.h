#pragma once
#include <unordered_map>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
# define bLength 2048
# define hBLength 1024
class analyzer
{
public:
	analyzer();//构造函数
	bool iniKeyWords();//初始化哈希表
	bool inierrorType();//初始化错误类型
	bool readFileToBuffer();
	void changeState();//改变state的状态
	bool canMakeId(char c);//可不可以是标识符
	bool canMake8Base(char c);
	bool canMake16Base(char c);
	bool isDigit(char c);//是不是数字
	bool isLetter(char c);
	bool isUnderline(char c);
	void dealError(string info="");
	char getChar();//自己手写的配合缓冲区切换的getchar
	void fallBackPoint();//回退指针
	void printResult(string info="");
	void printSum();
public:
	FILE* cProgram; //输入C程序文件指针
	FILE* resultFile;//输出记号流的文件指针
	FILE* sumFile;//输出汇总信息的文件指针
	FILE* errorFile;//输出错误信息的文件指针
	FILE* errorType;//只读文件 用于读取错误的种类
	char buffer[bLength];
	int pointer1;//第一个指针
	int pointer2;//第二个指针
	bool willEnd;//提示读取的文件是不是将要结束了
	int lineNum;//实际行号
	int pLineNum;//预测行号
	int wordNum;//单词的数量
	unordered_map<string, pair<string,string>> keyWords;//关键字的哈希表
	unordered_map<string, int> numOfWords;//所有字符的哈希表
	vector<string> errorVector;
	int state;//状态
	string token;//已经扫过的一个单词
	bool flag = 0;//用于切换缓冲区的服务
};