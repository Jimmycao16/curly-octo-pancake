#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

#define Maxsize 100
#define OK 1
#define ERROR 0
typedef char ElemType;
typedef int Status;
typedef struct SqStack{//ջ�Ķ���
	ElemType* base;
	ElemType* top;
	int stacksize;
}SqStack;
Status InitSqStack(SqStack& S) {//ջ�ĳ�ʼ��
	S.base = new ElemType[Maxsize];
	S.top = S.base;
	S.stacksize = Maxsize;
	return OK;
}
void Push(SqStack& S,ElemType e) {//Ԫ����ջ
	if (S.top - S.base == S.stacksize)
	{
		cout << "��ջ����" << endl;
		exit(0);
	}
	*S.top++ = e;
}
void Pop(SqStack& S, ElemType& e) {//Ԫ�س�ջ
	if (S.base == S.top)
	{
		cout << "��ջ�ѿ�" << endl;
		exit(0);
	}
	e = *--S.top;
}
ElemType GetTop(SqStack S) {//����ջ��Ԫ��
	if (S.top == S.base)
	{
		cout << "��ջ�ѿ�" << endl;
		exit(0);
	}
	ElemType* p = S.top;
	p--;
	ElemType e = *p;
	return e;
}
bool IsMatch(ElemType a[])//�ж������Ƿ�ƥ��
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
int ComparePriority(ElemType x1, ElemType x2) {//�ж�ջ��Ԫ��������Ԫ�ص����ȼ�
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
int StackLength(SqStack S) {//��ջ�ĳ���
	return S.top - S.base;
}
void Fun(SqStack &S,ElemType ptr[]) {//������ʽ����
	ElemType ch, e;
	int i = 0;
	cout << "�����ĺ�׺���ʽΪ��" << endl;
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
	cout << "**********��ӭʹ�ñ��ʽ���빦��**********" << endl;
	cout << "**********�����ܽ���������׺���ʽת��Ϊ��׺���ʽ**********" << endl;
	int choice = 0;
	do
	{
	    cout << "��������׺���ʽ��#����:" << endl;
		cin >> str;
		while (IsMatch(str) == false)
		{

			cout << "���Ų�ƥ��!!" << endl;
			cout << "������������׺���ʽ��#������" << endl;
			cin >> str;

		}
		Fun(S, str);
		cout << "������1ѡ�����ʹ�û�����0ѡ���˳�" << endl;
		cin >> choice;
	} while (choice == 1);
	cout << "��лʹ�ñ��ʽ���빦�ܣ�����" << endl;

	return 0;
}

