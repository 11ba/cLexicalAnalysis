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
	bool readFileToBuffer();//���뵽������ �����������û�� ��Ϊֱ�Ӽ��ɵ� ��д�� getChar()��
	void changeState();//�ı�state��״̬
	bool canMakeId(char c);//�ɲ������Ǳ�ʶ��
	bool canMake8Base(char c);//�ɲ���������8����
	bool canMake16Base(char c);//�ɲ���������16����
	bool isDigit(char c);//�ǲ�������
	bool isLetter(char c);//�ǲ�������
	bool isUnderline(char c);//�ǲ����»���
	void dealError(string info="");//���ݴ�����ӡ����
	char getChar();//�Լ���д����ϻ������л���getchar
	void fallBackPoint();//����ָ�� ���� mod����
	void printResult(string info="");//��ӡÿ��ʶ�𵽵ĵ��� ����info�������ͬ
	void printSum();//��ӡ������Ϣ ͳ�ƶ����� ���ٵ��� ����
public:
	FILE* cProgram; //����C�����ļ�ָ��
	FILE* resultFile;//����Ǻ������ļ�ָ��
	FILE* sumFile;//���������Ϣ���ļ�ָ��
	FILE* errorFile;//���������Ϣ���ļ�ָ��
	FILE* errorType;//ֻ���ļ� ���ڶ�ȡ���������
	char buffer[bLength];//ָ��
	int pointer1;//��һ��ָ��
	int pointer2;//�ڶ���ָ��
	bool willEnd;//��ʾ��ȡ���ļ��ǲ��ǽ�Ҫ������ ����û�õ�
	int lineNum;//ʵ���к�
	int pLineNum;//Ԥ���к�
	int wordNum;//���ʵ�����
	unordered_map<string, pair<string,string>> keyWords;//�ؼ��ֵĹ�ϣ��
	unordered_map<string, int> numOfWords;//�����ַ��Ĺ�ϣ��
	unordered_map<string, pair<string, string>> symbolTable;//id�ķ��ű� ɾ���� ��ϸ��ʵ�鱨��
	vector<string> errorVector;//�����
	int state;//״̬
	string token;//�Ѿ�ɨ����һ������
	bool flag = 0;//�����л��������ķ���
};