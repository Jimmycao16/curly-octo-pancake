#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

#define Maxsize 100
#define OK 1
#define ERROR 0
typedef char ElemType;
typedef int Status;
typedef struct SqStack{//栈的定义
	ElemType* base;
	ElemType* top;
	int stacksize;
}SqStack;
Status InitSqStack(SqStack& S) {//栈的初始化
	S.base = new ElemType[Maxsize];
	S.top = S.base;
	S.stacksize = Maxsize;
	return OK;
}
void Push(SqStack& S,ElemType e) {//元素入栈
	if (S.top - S.base == S.stacksize)
	{
		cout << "堆栈已满" << endl;
		exit(0);
	}
	*S.top++ = e;
}
void Pop(SqStack& S, ElemType& e) {//元素出栈
	if (S.base == S.top)
	{
		cout << "堆栈已空" << endl;
		exit(0);
	}
	e = *--S.top;
}
ElemType GetTop(SqStack S) {//返回栈顶元素
	if (S.top == S.base)
	{
		cout << "堆栈已空" << endl;
		exit(0);
	}
	ElemType* p = S.top;
	p--;
	ElemType e = *p;
	return e;
}
bool IsMatch(ElemType a[])//判断括号是否匹配
{
	int Flag = 0;
	for (int i = 0; i < strlen(a); i++)
	{
		if (a[i] == '(')
			Flag++;
		if (a[i] == ')')
			Flag--;
	}
	if (Flag == 0)
		return true;
	else
		return false;
}
int ComparePriority(ElemType x1, ElemType x2) {//判断栈顶元素与输入元素的优先级
	int Flag=-1;
	if ((x1 == '+' || x1 == '-') && (x2 == '+' || x2 == '-' || x2 == ')' || x2 == '#'))
		Flag = 1;
	else if ((x1 == '+' || x1 == '-') && (x2 == '*' || x2 == '/' || x2 == ')' || x2 == '('))
		Flag = 0;
	else if ((x1 == '*' || x1 == '/') && (x2 == '+' || x2 == '-' || x2 == '*' || x2 == '/' || x2 == ')' || x2 == '#'))
		Flag = 1;
	else if ((x1 == '*' || x1 == '/') && (x2 == '('))
		Flag = 0;
	else if ((x1 == '(' || x1 == '#') && (x2 == '+' || x2 == '-' || x2 == '*' || x2 == '/' || x2 == '('))
		Flag = 0;
	return Flag;
}
int StackLength(SqStack S) {//求栈的长度
	return S.top - S.base;
}
void Fun(SqStack &S,ElemType ptr[]) {//处理表达式翻译
	ElemType ch, e;
	int i = 0;
	cout << "翻译后的后缀表达式为：" << endl;
	while(ptr[i]!='\n')
	{
		ch = ptr[i];
		if (ch >= '0' && ch <= '9')
			cout << ch;
		else
		{
			if (ch != ')')
			{
				if (ComparePriority(GetTop(S), ch) == 0)
					Push(S, ch);
				else if (ComparePriority(GetTop(S), ch) == 1)
				{
					Pop(S, e);
					cout << e;
					Push(S, ch);
				}
			}
			if (ch == ')')
			{
				while (GetTop(S) != '(')
				{
					Pop(S, e);
					if(e!='('&&e!=')')
					cout << e;
				}
				if (GetTop(S) == '(')
					Pop(S, e);
			}
		}
		if (ch == '#')
		{
			Pop(S, e);
			while (GetTop(S) != '#')
			{
				Pop(S, e);
				cout << e;
			}
			break;
		}
		i++;
	}
	cout << endl;
}

int main()
{
	SqStack S;
	InitSqStack(S); 
	Push(S, '#');
	ElemType str[Maxsize];
	cout << "**********欢迎使用表达式翻译功能**********" << endl;
	cout << "**********本功能将把算术中缀表达式转换为后缀表达式**********" << endl;
	int choice = 0;
	do
	{
	    cout << "请输入中缀表达式以#结束:" << endl;
		cin >> str;
		while (IsMatch(str) == false)
		{

			cout << "括号不匹配!!" << endl;
			cout << "请重新输入中缀表达式以#结束：" << endl;
			cin >> str;

		}
		Fun(S, str);
		cout << "请输入1选择继续使用或输入0选择退出" << endl;
		cin >> choice;
	} while (choice == 1);
	cout << "感谢使用表达式翻译功能！！！" << endl;

	return 0;
}

