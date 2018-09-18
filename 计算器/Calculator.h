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
	void GethWnd(HWND hWnd);    //获取句柄
	void CharMsg(char a);   //键盘消息
	void BtnMsg(UINT a);    //按钮消息
	void GetEnter(const char * iNum);    //获取输入
	void ShowNum();   //显示数字
	void GetOption(UINT a);  //获取运算方式
	void ShowResult();    //计算结果	
	void Reset();   //重设数值
	
};

