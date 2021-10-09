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
	printf("本次词法分析开始!\n");
	clock_t start, end;
	start = clock();
	analyzer cAnalyzer;//创建词法分析器
	cAnalyzer.changeState(); //读入状态改变状态 结果和错误已经输出了
	cAnalyzer.printSum();//输出统计的总数
	end = clock();
	printf("本次词法分析用时 %lf 秒\n", double(end - start) / CLOCKS_PER_SEC);
	printf("本次词法分析结束了!\n");
	return 0;
}