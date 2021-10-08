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
	analyzer();//���캯��
	bool iniKeyWords();//��ʼ����ϣ��
	bool inierrorType();//��ʼ����������
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
	void printSum();
public:
	FILE* cProgram; //����C�����ļ�ָ��
	FILE* resultFile;//����Ǻ������ļ�ָ��
	FILE* sumFile;//���������Ϣ���ļ�ָ��
	FILE* errorFile;//���������Ϣ���ļ�ָ��
	FILE* errorType;//ֻ���ļ� ���ڶ�ȡ���������
	char buffer[bLength];
	int pointer1;//��һ��ָ��
	int pointer2;//�ڶ���ָ��
	bool willEnd;//��ʾ��ȡ���ļ��ǲ��ǽ�Ҫ������
	int lineNum;//ʵ���к�
	int pLineNum;//Ԥ���к�
	int wordNum;//���ʵ�����
	unordered_map<string, pair<string,string>> keyWords;//�ؼ��ֵĹ�ϣ��
	unordered_map<string, int> numOfWords;//�����ַ��Ĺ�ϣ��
	vector<string> errorVector;
	int state;//״̬
	string token;//�Ѿ�ɨ����һ������
	bool flag = 0;//�����л��������ķ���
};