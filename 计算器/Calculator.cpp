#include "stdafx.h"
#include "Calculator.h"
#include<math.h>
#include<stdlib.h>
#include<string>

using namespace std;

#define MAX_LEN 16
#define ADD 28   //+
#define MINUS 24  //-
#define MULTI 19  //*
#define RECIPROC 20  //����
#define DIV 14   //  /
#define MOD 15    //ȡ��
#define SQR  10    //����
#define EQU 25
#define RETURN 100
#define CLEAR 8
#define BACKSPACE 6

char OptString[] = "+-*/%=\b\r";
int OptInt[] = { ADD, MINUS, MULTI, DIV, MOD, EQU, BACKSPACE, RETURN };
string AllString[] = { "0", "1", "2", "3", "4", 
                       "5", "6", "7", "8", "9", "." };
int BtnInt[11] = { 26, 21, 22, 23, 16, 17, 18, 11, 12, 13, 27 };

Calculator::Calculator()     
{
	_hStatic = 0;
	_MathOption = NULL;
	_CalState = FALSE;
	_hasPoint1 = FALSE;
	_hasPoint2 = FALSE;
	_hasMinus1 = FALSE;
	_hasMinus2 = FALSE;
	memset(_MathSymbols, '\0', sizeof(_MathSymbols));
	memset(_FirstNumber, '\0', sizeof(_FirstNumber));
	memset(_SecondNumber, '\0', sizeof(_SecondNumber));
}

Calculator::~Calculator()
{
}

void Calculator::GethWnd(HWND hWnd)
{
	_hStatic = hWnd;
}

void Calculator::GetEnter(const char * iNum)
{
	if (_CalState == FALSE)   //��ȡ��һ������
	{
		if (strlen(_FirstNumber) < 15)     //��󳤶�15����
		{
			if (strlen(_FirstNumber) == 0)    //�״�����
			{
				if (*iNum == '.')
				{
					_hasPoint1 = TRUE;
					_FirstNumber[0] = '0';
					strcat_s(_FirstNumber, iNum);					
				}
				else
					strcat_s(_FirstNumber, iNum);
			}
			else                     //��������
			{
				if (_hasPoint1 == TRUE)       //�Ѿ���С����
				{
					if (*iNum!='.')
						strcat_s(_FirstNumber, iNum);
				}
				else                         //��û��С����
				{
					if (_FirstNumber[0] == '0')    //��λ��0
					{
						if (*iNum == '.')
						{
							_hasPoint1 = TRUE;
							strcat_s(_FirstNumber, iNum);
						}
						else            //��λΪ0���������С����
						{
							if (*iNum != '0')
								_FirstNumber[0] = *iNum;
						}
					}
					else            //��λ��Ϊ0
					{
						if (*iNum == '.')						
							_hasPoint1 = TRUE;
						strcat_s(_FirstNumber, iNum);
						
					}
				}
			}
		}
	}
	else                       //��ȡ�ڶ�������
	{
		if (strlen(_SecondNumber) < 16)
		{
			if (strlen(_SecondNumber) == 0)     //�״�����
			{
				if (*iNum == '.')
				{
					_hasPoint2 = TRUE;
					_SecondNumber[0] = '0';
					strcat_s(_SecondNumber, iNum);
				}
				else
					strcat_s(_SecondNumber, iNum);
			}
			else          //��������
			{
				if (_hasPoint2 == TRUE)
				{
					if (*iNum != '.')
						strcat_s(_SecondNumber, iNum);
				}
				else
				{
					if (_SecondNumber[0] == '0')
					{
						if (*iNum == '.')
						{
							_hasPoint2 = TRUE;
							strcat_s(_SecondNumber, iNum);
						}
						else
						{
							if (*iNum != '0')
								_SecondNumber[0] = *iNum;
						}
					}
					else
					{
						if (*iNum == '.')						
							_hasPoint2 = TRUE;
						strcat_s(_SecondNumber, iNum);
						
					}
				}
			}
		}
	}
}

void Calculator::GetOption(UINT a)
{	
	if (a != EQU&&a != RETURN&&a!=BACKSPACE)
		_MathOption = a;
	
	if (_MathOption != NULL)
		_CalState = TRUE;	

	switch (_MathOption)
	{
	case ADD:   //��
		strcpy_s(_MathSymbols, "\n+\n");
		break;

	case MINUS:  //��
		strcpy_s(_MathSymbols, "\n-\n");
		break;

	case MULTI:  //��
		strcpy_s(_MathSymbols, "\n*\n");
		break;

	case DIV:   //ȡ��
		strcpy_s(_MathSymbols, "\n/\n");
		break;

	case MOD:   //ȡ��
		strcpy_s(_MathSymbols, "\n%\n");
		break;

	case SQR:   //����
		strcpy_s(_MathSymbols, "\n��\n");
		break;

	case RECIPROC:    //��
		
		break;
	}
	ShowNum();
}

void Calculator::ShowResult()
{
	char str[50];
	double Number1, Number2, Num;
	Number1 = strtod(_FirstNumber, NULL);
	Number2 = strtod(_SecondNumber, NULL);

	if (_hasMinus1 == TRUE)
		Number1 = -Number1;
	if (_hasMinus2 == TRUE)
		Number2 = -Number2;

	switch (_MathOption)
	{
	case ADD:   //��
		Num = Number1 + Number2;
		break;

	case MINUS:  //��
		Num = Number1 - Number2;
		break;

	case MULTI:  //��
		Num = Number1*Number2;
		break;

	case DIV:   //ȡ��
		Num = Number1 / Number2;
		break;

	case MOD:   //ȡ��
		Num = fmod(Number1, Number2);
		break;

	case SQR:   //����
		Num = sqrt(Number1);
		break;

	case RECIPROC:    //��
		Number2 = 1.0;
		Num = Number2 / Number1;
		break;
	}
	gcvt(Num, 16, str);
	if (str[strlen(str) - 1] == '.')
		str[strlen(str) - 1] = '\0';
	SetWindowTextA(_hStatic, str);
}

void Calculator::ShowNum()
{
	char TotalNumber[50];
	memset(TotalNumber, '\0', sizeof(TotalNumber));
	if (_hasMinus1 == TRUE)
		strcat_s(TotalNumber, "-");

	if (_CalState == FALSE)
	{
		strcat_s(TotalNumber, _FirstNumber);
		if (strlen(_FirstNumber) == 0)
			SetWindowTextA(_hStatic, "0");
		else
			SetWindowTextA(_hStatic, TotalNumber);
	}
	else
	{
		strcat_s(TotalNumber, _FirstNumber);
		strcat_s(TotalNumber, _MathSymbols);
		if (_hasMinus2 == TRUE)
			strcat_s(TotalNumber, "-");
		strcat_s(TotalNumber, _SecondNumber);
		SetWindowTextA(_hStatic, TotalNumber);
	}
}

void Calculator::Reset()
{
	_MathOption = NULL;
	_CalState = FALSE;
	_hasPoint1 = FALSE;
	_hasPoint2 = FALSE;
	_hasMinus1 = FALSE;
	_hasMinus2 = FALSE;
	memset(_MathSymbols, '\0', sizeof(_MathSymbols));
	memset(_FirstNumber, '\0', sizeof(_FirstNumber));
	memset(_SecondNumber, '\0', sizeof(_SecondNumber));
}

void Calculator::CharMsg(char a)
{
	if (a >= '0'&&a <= '9')          //��������
	{
		GetEnter(AllString[a - '0'].data());
		ShowNum();
	}
	if (a == '.')
	{
		GetEnter(AllString[10].data());
		ShowNum();
	}

	for (int i = 0; i < strlen(OptString) ; i++)   //���������
	{
		if (OptString[i] == a)		
			GetOption(OptInt[i]);	
	}

	if (a == '=' || a == '\r')     //������
	{
		ShowResult();
		Reset();
	}

	if (a == '\b')
	{
		if (_CalState == FALSE)
		{
			if (strlen(_FirstNumber)>0)
				_FirstNumber[strlen(_FirstNumber) - 1] = '\0';
		}
		else
		{
			if (strlen(_SecondNumber) > 0)
				_SecondNumber[strlen(_SecondNumber) - 1] = '\0';
		}
		ShowNum();
	}
}

void Calculator::BtnMsg(UINT a)
{
	for (int i = 0; i < 11; i++)      //���ְ�ť
	{
		if (a == BtnInt[i])
		{
			GetEnter(AllString[i].data());
			ShowNum();
		}
	}
	for (int i = 0; i < 7; i++)    //�������ť
	{
		if (a == OptInt[i])
			GetOption(a);
	}

	if (a == EQU || a == RETURN)     //��������ť
	{
		ShowResult();
		Reset();
	}

	if (a == CLEAR)              //����
	{
		Reset();
		SetWindowTextA(_hStatic, "0");
	}

	if (a == SQR)      //������ť
	{
		GetOption(a);
		ShowResult();
		Reset();
	}

	if (a == 9)
	{
		if (_CalState == FALSE)
		{
			if (_hasMinus1 == FALSE)
				_hasMinus1 = TRUE;
			else
				_hasMinus1 = FALSE;
		}
		else 
		{
			if (_hasMinus2 == FALSE)
				_hasMinus2 = TRUE;
			else
				_hasMinus2 = FALSE;
		}
		ShowNum();
	}

	if (a == 20)
	{
		GetOption(a);
		ShowResult();
		Reset();
	}

	if (a == 6)
	{
		if (_CalState == FALSE)
		{
			if (strlen(_FirstNumber)>0)
				_FirstNumber[strlen(_FirstNumber) - 1] = '\0';
		}
		else
		{
			if (strlen(_SecondNumber) > 0)
				_SecondNumber[strlen(_SecondNumber) - 1] = '\0';
		}
		ShowNum();
	}
}
























