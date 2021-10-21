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
	analyzer cAnalyzer;//创建词法分析器
	if (!cAnalyzer.getTheCProgram())//输入文件名字
	{
		printf("你输入的文件不存在!");
		return 0;
	} 
	start = clock();//计时开始
	cAnalyzer.changeState(); //读入状态改变状态 结果和错误已经输出了
	cAnalyzer.printSum();//输出统计的总数
	end = clock();//计时结束
	double duration = double(end - start) / (CLK_TCK);
	printf("本次词法分析用时 %f 秒\n", duration);
	printf("本次词法分析结束了! ㄟ(≧◇≦)ㄏ\n");
	return 0;
}