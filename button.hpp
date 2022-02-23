#pragma once
#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include <iostream>
using namespace std;

//��ť�ؼ�			(��¼������ť��λ�ã�״̬,���������°����Ľ���)
class button {

public:
	void Creat(int x1, int y1, int x2, int y2,const  wchar_t *title, void (*func)());		//�ı�����λ��( L"*" Ĭ����const����)
	bool Check(int x,int y);					//���x��y�����Ƿ񴥷�ʱ��
	void Function();							//��Ϊuserfunc��˽��Ȩ�ޣ���˼�ӵ��ù�����������
	button();
	~button();
	
private:
	wchar_t* m_text;				//�ؼ��ı�����
	int m_maxlen;					//����ı�����
	void (*userfunc)() = NULL;		// �ؼ���Ϣ(���ú���ָ��)

	int m_left;						//��ť��Ч��Χ�����������¼��ж�
	int m_top;
	int m_right;
	int m_bottom;
};

/*һ���˵����ܰ�ť*/
button ShowStudent;				//��ʾѧ��
button About;					//�鿴˵��
button ChangePwd;				//�޸�����
button Exit;					//�˳�ϵͳ


/*�����˵����ܰ�ť*/
button AddSTU;
button DeleteSTU;
button SortSTU;
button Back;
button NextPage;
button PreviousPage;


/*button��������*/

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