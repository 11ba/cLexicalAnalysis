# include "analyzer.h"
# include <cstdio>
# include <cstdlib>
# include <iostream>


analyzer::analyzer()
{
	iniKeyWords();//初始化关键词表
	resultFile = fopen("result.txt", "w");//初始化
	this->cProgram = fopen("c.txt", "r");
	this->state = 0;
	this->willEnd = 0;
	this->wordNum = 0;
	this->lineNum = 0;
	this->pLineNum = 1;//预测行号是1 碰到'\n'他就先加
}

bool analyzer::iniKeyWords()
{
	FILE* keyWordFile;//文件指针
	keyWordFile = fopen("keyWords.txt", "r");
	if (keyWordFile == NULL) return 0;
	char str[20] = {0};//读入的字符串
	char str1[20] = { 0 };
	char str2[20] = { 0 };
	while (fscanf(keyWordFile, "%s",str)!=-1)
	{
		int num1 = fscanf(keyWordFile, "%s", str1);
		int num2 = fscanf(keyWordFile, "%s", str2);
		this->keyWords[str] = {str1,str2};
	}
	return 1;
}

bool analyzer::readFileToBuffer()
{
	int cnt = fread(this->buffer, sizeof(char), hBLength, this->cProgram);
	if (cnt < hBLength) this->willEnd = 1;
	return false;
}

void analyzer::changeState()
{
	char ch = 0;
	while (1)
	{
		if (ch == -1) break;
		switch (this->state)
		{
		case 0: //初始状态
		{
			//不断地读取字符 但是遇到空格和tab要忽略
			token.clear();
			while (1)
			{
				ch = this->getChar();
				this->lineNum = this->pLineNum;
				if (ch != ' ' && ch != '\t') break; //如果不是空格和tab就可以进入下一步 如果是就一直重复读取
			}
			//识别字符
			switch (ch)
			{
			//进入标识符 标识符以 _ 或者字母开头
			case '_':
			//字母开头
			case 'a':case'b':case'c':case 'd':case'e':case'f':case 'g':case'h':case'i':
			case 'j':case'k':case'l':case 'm':case'n':case'o':case 'p':case'q':case'r':
			case 's':case't':case'u':case 'v':case'w':case'x':case 'y':case'z':
			//字母开头
			case 'A':case 'B':case'C':case'D':case 'E':case'F':case'G':case 'H':case'I':
			case 'J':case 'K':case'L':case'M':case 'N':case'O':case'P':case 'Q':case'R':
			case 'S':case 'T':case'U':case'V':case 'W':case'X':case'Y':case 'Z':
			{
				state = 1;
				this->token += ch;
				break;
			}
			//以0开头可能是16进制也可能是10进制。
			case '0':
			{
				token += ch;
				state = 8; break;
			}
			//数字开头
			case '1': case '2': case '3': case '4': case '5': case '6': case '7':case '8': case '9':
			{
				state = 2; token += ch; break;
			}
			//小数点开头
			case '.':
			{
				state = 12;
				break;
			}
			case '\n':
			{
				state = 14;
				break;
			}
			default:
				break;
			}
			break;
		}
		case 1://标识符状态
		{
			
			ch = this->getChar();
			if (canMakeId(ch))
			{
				this->token += ch;//连接上
				state = 1;
			}
			else
			{
				state = 0;//转换到初始状态
				this->fallBackPoint();//回退指针
				if (this->keyWords.count(this->token))//判断是不是在关键字表里
				{
					this->numOfWords[token]++;
					this->printResult();
				}
				else
				{
					this->numOfWords[token]++;
					//加入符号表
					this->printResult("id");
				}
			}
			break;
		}
		case 2:
		{
			ch = this->getChar();
			if (isdigit(ch))
			{
				token += ch;
				state = 2;
			}
			else if (ch == '.')
			{
				this->token += ch;
				state = 3;
			}
			else if ('e' == ch || 'E' == ch)
			{
				this->token += ch;
				state = 5;
			}
			else if(isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
				//加入
				printResult("dec");
			}
			else
			{
				state = 0;
				fallBackPoint();
				//加入
				printResult("dec");
			}
			break;
		}
		case 3:
		{
			ch = this->getChar();
			if (isdigit(ch))
			{
				token += ch;
				state = 4;
			}
			else if (ch == 'e' || ch == 'E')
			{
				token += ch;
				state = 5;
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
				//加入
				//打印
				printResult("dec");
			}
			else
			{
				state = 0;
				fallBackPoint();
				//加入
				//打印
				printResult("dec");
			}
			break;
		}
		case 4:
		{
			ch = this->getChar();
			if (isdigit(ch))
			{
				token += ch;
				state = 4;
			}
			else if (ch == 'e' || ch == 'E')
			{
				token += ch;
				state = 5;
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
				//加入
				printResult("dec");
			}
			else
			{
				state = 0;
				fallBackPoint();
				//加入
				printResult("dec");
			}
			break;
		}
		case 5:
		{
			ch = this->getChar();
			if (isdigit(ch))
			{
				token += ch;
				state = 7;
			}
			else if (ch == '+' || ch == '-')
			{
				token += ch;
				state = 6;
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
			}
			else
			{
				state = 0;
				fallBackPoint();
				dealError("2");
			}
			break;
		}
		case 6:
		{
			ch = this->getChar();
			if (isdigit(ch))
			{
				token += ch;
				state = 7;
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
			}
			else
			{
				state = 0;
				fallBackPoint();
				dealError("2");
			}
			break;
		}
		case 7:
		{
			ch = this->getChar();
			if (isdigit(ch))
			{
				token += ch;
				state = 7;
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
				//加入
				printResult("dec");
			}
			else
			{
				state = 0;
				fallBackPoint();
				//加入
				printResult("dec");
			}
			break;
		}
		case 8:
		{
			ch = this->getChar();
			if (canMake8Base(ch))
			{
				token += ch;
				state = 9;
			}
			else if ('.'==ch)
			{
				token += ch;
				state = 3;
			}
			else if ('x'==ch || 'X'==ch)
			{
				token += ch;
				state = 10;
			}
			else if(ch=='8' || ch=='9')
			{
				state = 0;
				fallBackPoint();
				dealError("2");
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
				printResult("oct");
			}
			break;
		}
		case 9:
		{
			ch = this->getChar();
			if (canMake8Base(ch))
			{
				token += ch;
				state = 9;
			}
			else if ('.' == ch)
			{
				token += ch;
				state = 3;
			}
			else if (ch == 'e' || ch == 'E')
			{
				token += ch;
				state = 5;
			}
			else if (ch == '8' || ch == '9')
			{
				state = 0;
				fallBackPoint();
				dealError("2");
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
				printResult("oct");
				
			}
			else
			{
				state = 0;
				fallBackPoint();
				printResult("oct");
			}
			break;
		}
		case 10:
		{
			ch = this->getChar();
			if (canMake16Base(ch))
			{
				token += ch;
				state = 11;
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("2");
			}
			break;
		}
		case 11:
		{
			ch = this->getChar();
			if (canMake16Base(ch))
			{
				token += ch;
				state = 11;
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
				printResult("hex");
			}
			else
			{
				state = 0;
				fallBackPoint();
				printResult("hex");
			}
			break;
		}
		case 12:
		{
			ch = this->getChar();
			if (isdigit(ch))
			{
				token += ch;
				state = 13;
			}
			else if (isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
				printResult();
			}
			else
			{
				state = 0;
				fallBackPoint();
				printResult();
			}
			break;
		}
		case 13:
		{
			ch = this->getChar();
			if (isdigit(ch))
			{
				token += ch;
				state = 13;
			}
			else if (ch=='e' || ch=='E')
			{
				token += ch;
				state = 5;
			}
			else if(isLetter(ch) || isUnderline(ch))
			{
				state = 0;
				fallBackPoint();
				dealError("0");
				printResult("dec");
			}
			else
			{
				state = 0;
				fallBackPoint();
				printResult("dec");

			}
			break;
		}
		case 14:
		{
			this->pLineNum++;//预测行数加1
			state = 0;
			break;
		}
		default:
			break;
		}
	}
	
}

bool analyzer::canMakeId(char c)
{
	if (c == '_') return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	if (c >= '0' && c <= '9') return true;
	return false;
}

bool analyzer::canMake8Base(char c)
{
	if (c >= '0' && c <= '7') return true;
	return false;
}

bool analyzer::canMake16Base(char c)
{
	if (c >= '0' && c <= '9') return 1;
	if (c >= 'a' && c <= 'f') return 1;
	if (c >= 'A' && c <= 'F') return 1;
	return false;
}

bool analyzer::isDigit(char c)
{
	if(c>='0' && c<='9')
		return 1;
	return 0;
}

bool analyzer::isLetter(char c)
{
	if (c >= 'a' && c <= 'z') return 1;
	if (c >= 'A' && c <= 'Z') return 1;
	return 0;
}

bool analyzer::isUnderline(char c)
{
	if (c == '_') return true;
	return false;
}

void analyzer::dealError(string info)
{

}

char analyzer::getChar()
{
	//注意EOF是-1
	int cnt = 0;//计数

	if (this->pointer2 == 0 && flag==0)
	{
		cnt = fread(this->buffer, sizeof(char), hBLength, this->cProgram);
		if (cnt < hBLength) buffer[cnt] = -1;//添加结束符号 因为fread不会把-1读入
		flag = 1;
	}
		
	if (this->pointer2 == hBLength && flag == 1)
	{
		cnt = fread(this->buffer + hBLength, sizeof(char), hBLength, this->cProgram);
		if (cnt < hBLength) buffer[cnt+hBLength] = -1;//添加结束符号 因为fread不会把-1读入
		flag = 0;
	}

	char ch = this->buffer[this->pointer2];
	this->pointer2 = (pointer2 + 1) % bLength;
	return ch;
}

void analyzer::fallBackPoint()
{
	//利用模运算
	this->pointer2 = ((this->pointer2 - 1) + bLength) % bLength;
}

void analyzer::printResult(string info)
{
	
	//这里要加入判断
	if(info=="")
		fprintf(resultFile, "line : %d < %s , %s > \n", this->lineNum, this->keyWords[token].first.c_str(), 
		this->keyWords[token].second.c_str());
	else if(info=="id")
		fprintf(resultFile, "line : %d < %s , %s > \n", this->lineNum, "id",token.c_str());
	else if(info=="dec")
		fprintf(resultFile, "line : %d < %s , %s > \n", this->lineNum, "dec", token.c_str());
	else if(info=="oct")
		fprintf(resultFile, "line : %d < %s , %s > \n", this->lineNum, "oct", token.c_str());
	else if(info=="hex")
		fprintf(resultFile, "line : %d < %s , %s > \n", this->lineNum, "hex", token.c_str());

}
