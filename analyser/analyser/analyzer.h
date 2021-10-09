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
	bool readFileToBuffer();//读入到缓冲区 这个函数后来没用 因为直接集成到 手写的 getChar()里
	void changeState();//改变state的状态
	bool canMakeId(char c);//可不可以是标识符
	bool canMake8Base(char c);//可不可以生成8进制
	bool canMake16Base(char c);//可不可以生成16进制
	bool isDigit(char c);//是不是数字
	bool isLetter(char c);//是不是数字
	bool isUnderline(char c);//是不是下划线
	void dealError(string info="");//根据错误表打印错误
	char getChar();//自己手写的配合缓冲区切换的getchar
	void fallBackPoint();//回退指针 利用 mod运算
	void printResult(string info="");//打印每个识别到的单词 根据info传的类别不同
	void printSum();//打印汇总信息 统计多少行 多少单词 符号
public:
	FILE* cProgram; //输入C程序文件指针
	FILE* resultFile;//输出记号流的文件指针
	FILE* sumFile;//输出汇总信息的文件指针
	FILE* errorFile;//输出错误信息的文件指针
	FILE* errorType;//只读文件 用于读取错误的种类
	char buffer[bLength];//指针
	int pointer1;//第一个指针
	int pointer2;//第二个指针
	bool willEnd;//提示读取的文件是不是将要结束了 后来没用到
	int lineNum;//实际行号
	int pLineNum;//预测行号
	int wordNum;//单词的数量
	unordered_map<string, pair<string,string>> keyWords;//关键字的哈希表
	unordered_map<string, int> numOfWords;//所有字符的哈希表
	unordered_map<string, pair<string, string>> symbolTable;//id的符号表 删减版 详细见实验报告
	vector<string> errorVector;//错误表
	int state;//状态
	string token;//已经扫过的一个单词
	bool flag = 0;//用于切换缓冲区的服务
};