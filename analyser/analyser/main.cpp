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
	start = clock();
	analyzer cAnalyzer;//�����ʷ�������
	cAnalyzer.changeState(); //����״̬�ı�״̬ ����ʹ����Ѿ������
	cAnalyzer.printSum();//���ͳ�Ƶ�����
	end = clock();
	printf("���δʷ�������ʱ %lf ��\n", double(end - start) / CLOCKS_PER_SEC);
	printf("���δʷ�����������!\n");
	return 0;
}