#pragma once
#include <unordered_map>
#include <cstdio>
#include <string>
using namespace std;
# define bLength 2048
# define hBLength 1024
class analyzer
{
public:
	analyzer();//构造函数
	bool iniKeyWords();//初始化哈希表
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
public:
	FILE* cProgram; //文件指针
	FILE* resultFile;//输出文件指针
	char buffer[bLength];
	int pointer1;//第一个指针
	int pointer2;//第二个指针
	bool willEnd;//提示读取的文件是不是将要结束了
	int lineNum;//实际行号
	int pLineNum;//预测行号
	int wordNum;//单词的数量
	unordered_map<string, pair<string,string>> keyWords;//关键字的哈希表
	unordered_map<string, int> numOfWords;//所有字符的哈希表
	int state;//状态
	string token;//已经扫过的一个单词
	bool flag = 0;
};