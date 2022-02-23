#pragma once
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include <iostream>
using namespace std;

//按钮控件			(记录各个按钮的位置，状态,并创建按下按键的界面)
class button {

public:
	void Creat(int x1, int y1, int x2, int y2,const  wchar_t *title, void (*func)());		//文本创建位置( L"*" 默认是const类型)
	bool Check(int x,int y);					//检查x，y坐标是否触发时间
	void Function();							//因为userfunc是私有权限，因此间接调用公共函数访问
	button();
	~button();
	
private:
	wchar_t* m_text;				//控件文本内容
	int m_maxlen;					//最大文本长度
	void (*userfunc)() = NULL;		// 控件消息(调用函数指针)

	int m_left;						//按钮有效范围，辅助触发事件判断
	int m_top;
	int m_right;
	int m_bottom;
};

/*一级菜单功能按钮*/
button ShowStudent;				//显示学生
button About;					//查看说明
button ChangePwd;				//修改密码
button Exit;					//退出系统


/*二级菜单功能按钮*/
button AddSTU;
button DeleteSTU;
button SortSTU;
button Back;
button NextPage;
button PreviousPage;


/*button函数定义*/

void button::Creat(int x1, int y1, int x2, int y2,const wchar_t *title,void (*func)()) {

	m_text = new wchar_t[wcslen(title)+1];
	userfunc = func;

	m_left = x1;
	m_top = y1;
	m_right = x2;
	m_bottom = y2;
}

void button::Function() {
	userfunc();
}

bool button::Check(int x,int y) {
	return x > m_left && x<m_right&& y>m_top && y < m_bottom;
}

button::button() {
	m_text = NULL;
	userfunc = NULL;
	m_maxlen = 10;
	m_left = 0;
	m_top = 0;
	m_right = 0;
	m_bottom = 0;
}

button::~button() {
	if (m_text != NULL)
		delete m_text;
}