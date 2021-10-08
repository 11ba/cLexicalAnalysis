# include <iostream>
# include <algorithm>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <unordered_map>
# include <vector>
# include <string>
# include "analyzer.h"
using namespace std;


int main(void)
{
	analyzer cAnalyzer;//创建词法分析器
	cAnalyzer.changeState(); //读入状态改变状态 结果和错误已经输出了
	cAnalyzer.printSum();//输出统计的总数
	return 0;
}