# include <iostream>
# include <algorithm>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <unordered_map>
# include <vector>
# include <string>
# include <ctime>
# include "analyzer.h"
using namespace std;


int main(void)
{
	printf("���δʷ�������ʼ!\n");
	clock_t start, end;
	analyzer cAnalyzer;//�����ʷ�������
	if (!cAnalyzer.getTheCProgram())//�����ļ�����
	{
		printf("��������ļ�������!");
		return 0;
	} 
	start = clock();//��ʱ��ʼ
	cAnalyzer.changeState(); //����״̬�ı�״̬ ����ʹ����Ѿ������
	cAnalyzer.printSum();//���ͳ�Ƶ�����
	end = clock();//��ʱ����
	double duration = double(end - start) / (CLK_TCK);
	printf("���δʷ�������ʱ %f ��\n", duration);
	printf("���δʷ�����������! ��(�R��Q)��\n");
	return 0;
}