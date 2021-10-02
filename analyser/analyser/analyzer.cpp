# include "analyzer.h"
# include <cstdio>
# include <cstdlib>
# include <iostream>


analyzer::analyzer()
{
	iniKeyWords();//��ʼ���ؼ��ʱ�
	resultFile = fopen("result.txt", "w");//��ʼ��
	this->cProgram = fopen("c.txt", "r");
	this->state = 0;
	this->willEnd = 0;
	this->wordNum = 0;
	this->lineNum = 0;
	this->pLineNum = 1;//Ԥ���к���1 ����'\n'�����ȼ�
}

bool analyzer::iniKeyWords()
{
	FILE* keyWordFile;//�ļ�ָ��
	keyWordFile = fopen("keyWords.txt", "r");
	if (keyWordFile == NULL) return 0;
	char str[20] = {0};//������ַ���
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
		case 0: //��ʼ״̬
		{
			//���ϵض�ȡ�ַ� ���������ո��tabҪ����
			token.clear();
			while (1)
			{
				ch = this->getChar();
				this->lineNum = this->pLineNum;
				if (ch != ' ' && ch != '\t') break; //������ǿո��tab�Ϳ��Խ�����һ�� ����Ǿ�һֱ�ظ���ȡ
			}
			//ʶ���ַ�
			switch (ch)
			{
			//�����ʶ�� ��ʶ���� _ ������ĸ��ͷ
			case '_':
			//��ĸ��ͷ
			case 'a':case'b':case'c':case 'd':case'e':case'f':case 'g':case'h':case'i':
			case 'j':case'k':case'l':case 'm':case'n':case'o':case 'p':case'q':case'r':
			case 's':case't':case'u':case 'v':case'w':case'x':case 'y':case'z':
			//��ĸ��ͷ
			case 'A':case 'B':case'C':case'D':case 'E':case'F':case'G':case 'H':case'I':
			case 'J':case 'K':case'L':case'M':case 'N':case'O':case'P':case 'Q':case'R':
			case 'S':case 'T':case'U':case'V':case 'W':case'X':case'Y':case 'Z':
			{
				state = 1;
				this->token += ch;
				break;
			}
			//��0��ͷ������16����Ҳ������10���ơ�
			case '0':
			{
				token += ch;
				state = 8; break;
			}
			//���ֿ�ͷ
			case '1': case '2': case '3': case '4': case '5': case '6': case '7':case '8': case '9':
			{
				state = 2; token += ch; break;
			}
			//С���㿪ͷ
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
		case 1://��ʶ��״̬
		{
			
			ch = this->getChar();
			if (canMakeId(ch))
			{
				this->token += ch;//������
				state = 1;
			}
			else
			{
				state = 0;//ת������ʼ״̬
				this->fallBackPoint();//����ָ��
				if (this->keyWords.count(this->token))//�ж��ǲ����ڹؼ��ֱ���
				{
					this->numOfWords[token]++;
					this->printResult();
				}
				else
				{
					this->numOfWords[token]++;
					//������ű�
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
				//����
				printResult("dec");
			}
			else
			{
				state = 0;
				fallBackPoint();
				//����
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
				//����
				//��ӡ
				printResult("dec");
			}
			else
			{
				state = 0;
				fallBackPoint();
				//����
				//��ӡ
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
				//����
				printResult("dec");
			}
			else
			{
				state = 0;
				fallBackPoint();
				//����
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
				//����
				printResult("dec");
			}
			else
			{
				state = 0;
				fallBackPoint();
				//����
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
			this->pLineNum++;//Ԥ��������1
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
	//ע��EOF��-1
	int cnt = 0;//����

	if (this->pointer2 == 0 && flag==0)
	{
		cnt = fread(this->buffer, sizeof(char), hBLength, this->cProgram);
		if (cnt < hBLength) buffer[cnt] = -1;//��ӽ������� ��Ϊfread�����-1����
		flag = 1;
	}
		
	if (this->pointer2 == hBLength && flag == 1)
	{
		cnt = fread(this->buffer + hBLength, sizeof(char), hBLength, this->cProgram);
		if (cnt < hBLength) buffer[cnt+hBLength] = -1;//��ӽ������� ��Ϊfread�����-1����
		flag = 0;
	}

	char ch = this->buffer[this->pointer2];
	this->pointer2 = (pointer2 + 1) % bLength;
	return ch;
}

void analyzer::fallBackPoint()
{
	//����ģ����
	this->pointer2 = ((this->pointer2 - 1) + bLength) % bLength;
}

void analyzer::printResult(string info)
{
	
	//����Ҫ�����ж�
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
