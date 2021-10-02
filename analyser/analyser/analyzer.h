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
	analyzer();//���캯��
	bool iniKeyWords();//��ʼ����ϣ��
	bool readFileToBuffer();
	void changeState();//�ı�state��״̬
	bool canMakeId(char c);//�ɲ������Ǳ�ʶ��
	bool canMake8Base(char c);
	bool canMake16Base(char c);
	bool isDigit(char c);//�ǲ�������
	bool isLetter(char c);
	bool isUnderline(char c);
	void dealError(string info="");
	char getChar();//�Լ���д����ϻ������л���getchar
	void fallBackPoint();//����ָ��
	void printResult(string info="");
public:
	FILE* cProgram; //�ļ�ָ��
	FILE* resultFile;//����ļ�ָ��
	char buffer[bLength];
	int pointer1;//��һ��ָ��
	int pointer2;//�ڶ���ָ��
	bool willEnd;//��ʾ��ȡ���ļ��ǲ��ǽ�Ҫ������
	int lineNum;//ʵ���к�
	int pLineNum;//Ԥ���к�
	int wordNum;//���ʵ�����
	unordered_map<string, pair<string,string>> keyWords;//�ؼ��ֵĹ�ϣ��
	unordered_map<string, int> numOfWords;//�����ַ��Ĺ�ϣ��
	int state;//״̬
	string token;//�Ѿ�ɨ����һ������
	bool flag = 0;
};