#pragma once

class Calculator
{
private:
	enum Length{ MAX_LEN = 16, MATHOPT_LEN = 5 };
	char _FirstNumber[MAX_LEN];
	char _SecondNumber[MAX_LEN];
	char _MathSymbols[MATHOPT_LEN];
	UINT _MathOption;
	HWND _hStatic;
	BOOL _CalState;
	BOOL _hasPoint1;
	BOOL _hasPoint2;
	BOOL _hasMinus1;
	BOOL _hasMinus2;
public:
	Calculator();	
	~Calculator();
	void GethWnd(HWND hWnd);    //��ȡ���
	void CharMsg(char a);   //������Ϣ
	void BtnMsg(UINT a);    //��ť��Ϣ
	void GetEnter(const char * iNum);    //��ȡ����
	void ShowNum();   //��ʾ����
	void GetOption(UINT a);  //��ȡ���㷽ʽ
	void ShowResult();    //������	
	void Reset();   //������ֵ
	
};

