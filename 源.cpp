/*
		@cglssg
		2022��2��16��21:27:01
		��Ŀ��ѧ���ɼ�����ϵͳ	
*/
#include <iostream>
#include "button.hpp"
#include "text.hpp"
#include "func.h"
#define wc wchar_t
using namespace std;

typedef struct STU {
	wc number[10];
	wc name[20];
	wc score[4][20];
	int level;
	//struct STU* next; 
}STU;


bool  Judge_Menu=true;			//�ж��Ƿ���������

//STU stuhead;					//ͷ���
STU stu[100];					//ѧ����Ϣ
int pre_num=0;						//Ŀǰ����
int total_num=100;					//�������
int pre_page = 1;			//��ǰҳ��	
int total_page = 1;			//һ������ҳ
size_t PassWord=123456;

void ShowMenu();
void StudentMessageInterface();
void AddStudent();
void back_click();
void Next_Page();
void Previous_Page();
void AboutMessage();
void ExitSystem();
void login();


int main() {

	initgraph(640, 480);

	login();

	ShowStudent.Creat(250,140,390,190,L"��ʾѧ��", StudentMessageInterface);				/* ���Ļ�����С����Ҫ��������*/
	About.Creat(250, 190, 390, 240, L"����", AboutMessage);
	ChangePwd.Creat(250, 290, 390, 290, L"��������", NULL);
	Exit.Creat(250, 290, 390, 340, L"�˳�ϵͳ", ExitSystem);

	MOUSEMSG msg;

	while (true) {					//����ѭ��
		ShowMenu();					//������������ĺ���Ƕ��while���棬��������ʵ�ֵ������ֵ����ʾ������

		while (true) {						//������������Ӧ�������ܣ�������������������������жϷ�Χ
			msg = GetMouseMsg();
			if (msg.mkLButton == true) {				//�������
				int x = msg.x;
				int y = msg.y;
				if (ShowStudent.Check(x, y)) {			//ShowMenu()��Ѱ����������
					ShowStudent.Function();
					break;
				}
				else if (About.Check(x, y)) {
					About.Function();
					break;
				}
				else if (ChangePwd.Check(x, y)) {

					break;
				}
				else if (Exit.Check(x, y)) {
					Exit.Function();
					break;
				}

			}
		}
	
	}

	_getch();
	closegraph();

	return 0;
}




/*���ܺ���*/
//���ѧ��
void AddStudent() {

	if (pre_num < total_num) {
		
		int choice = 1;
		int being=1;

		while (choice == 1) {

			wc name[20], num[10], sco[10];
			size_t number;
			double score[4];
			int bedoing = 1;		// InputBox �е��ȡ����������Ϣ��������
			bool Input = true;		//ѭ������  ÿ������������������		
						
			if (bedoing) {
				while (Input) {				//����ѧ����Ϣ
					bedoing=InputBox(num, 10, L"ѧ��", L"ѧ��", 0, 0, 0, false);		//����͵��ȷ������ 1 �����ȡ������ 0 
					number = _wtoi(num);
					if (number > 0 && number <= 1000&&bedoing!=0) {
						Input = false;
					}
					else if(bedoing==0) {
						return;
					}
					else {
						MessageBox(NULL, L"��淶���루0 - 1000��", L"����", MB_OK);
					}
				}
			}

			if (!lstrcpynW(stu[pre_num].number, num, 10))				//��ֹת��ʧ��
				return;

			if (bedoing) {
				Input = true;
				while (Input) {
					bedoing = InputBox(name, 10, L"����", L"����", NULL, 0, 0, false);
					if (bedoing == 0)
						return;
					else
						Input = false;
				}
			}

			if (!lstrcpynW(stu[pre_num].name, name, 10))
				return;

			if (bedoing) {
				Input = true;
				while (Input) {
					bedoing=InputBox(sco, 10, L"�����ɼ�", L"�ɼ�", 0, 0, 0, false);
					score[0] = _wtoi(sco);
					if (score[0] >= 0 && score[0] <= 100) {
						Input = false;
						score[0] = number;
					}
					else if(bedoing == 0) {
						return;
					}
					else {
						MessageBox(NULL, L"��淶���루0 - 100��", L"����", MB_OK);
					}

				}
			}

			if (!lstrcpynW(stu[pre_num].score[0], sco, 10))
				break;

			if (bedoing) {
				Input = true;
				while (Input) {
					bedoing=InputBox(sco, 10, L"Ӣ��ɼ�", L"�ɼ�", 0, 0, 0, false);
					score[1] = _wtoi(sco);
					if (score[1] >= 0 && score[1] <= 100) {
						Input = false;
					}else if (bedoing == 0) {
						return;
					}
					else {
						MessageBox(NULL, L"��淶���루0 - 100��", L"����", MB_OK);
					}
				}
			}

			if (!lstrcpynW(stu[pre_num].score[1], sco, 10))
				return;

			if (bedoing) {
				Input = true;
				while (Input) {
					bedoing=InputBox(sco, 10, L"������ɼ�", L"�ɼ�", 0, 0, 0, false);
					score[2] = _wtoi(sco);
					if (score[2] >= 0 && score[2] <= 100) {
						Input = false;
					}
					else if (bedoing == 0) {
						return;
					}
					else {
						MessageBox(NULL, L"��淶���루0 - 100��", L"����", MB_OK);
					}
				}
			}

			if (!lstrcpynW(stu[pre_num].score[2], sco, 10))
				return;
			wsprintf(stu[pre_num].score[3],L"%d",score[0]+score[1]+score[2]);

			pre_num++;

			choice = MessageBox(GetHWnd(), L"�Ƿ������", L"����", MB_OKCANCEL);

			if (choice == 0)
				return;
		}
		
	}
	else {
		MessageBox(NULL, L"��Ǹ������������", L"����", MB_RETRYCANCEL | MB_ICONWARNING);
	}

}

//ɾ��ѧ��
void DeleteStudent() {

	if (pre_num > 0) {

		wc name[20], num[10];
		size_t number;
		
		int being = IDRETRY;

		while (being==IDRETRY) {
			InputBox(num, 10, L"��������ɾ��ѧ����ѧ��", L"ѧ��", 0, 0, 0, true);
			number = _wtoi(num);
			if (number > 0 && number <= 1000) {
				
				for (int i = 0; i <= pre_num;i++) {
					if ((wcscmp(stu[i].number, num)) == 0) {
						MessageBox(NULL, L"ɾ���ɹ�", L"��ȷ", MB_OK);
						for (int j = i; j + 1  <= pre_num; j++) {
							stu[j] = stu[j + 1];
						}
						pre_num--;
						return;
					}
				}
				being=MessageBox(NULL, L"δ�ҵ�������Ϣ", L"����", MB_RETRYCANCEL);	// retry ����IDRETRY(4)
			}
			else {
				MessageBox(NULL, L"�밴��ȷ��ʽ���루0 - 1000��", L"����", MB_OK);
			}
		}
	}
	else {
		MessageBox(GetHWnd(), L"��δ¼��ѧ��", L"����", MB_OK);
	}

}

//ѧ������
void SortStudent() {
	
}


/*����һ������*/
//������
void ShowMenu() {

	int red = 230;
	int green = 230;
	int blue = 230;

	BeginBatchDraw();						//���������滭ģʽ����ֹ������˸

	setbkcolor(RGB(red, green, blue));		//���ó�ʼ����
	setfillcolor(RGB(red, green, blue));
	setlinecolor(LIGHTGRAY);

	solidrectangle(0, 0, 640, 480);			//��׽���

	settextcolor(BLACK);					//���ñ���ģʽ
	setbkmode(OPAQUE);
	settextstyle(50, 0, L"����");
	outtextxy(120, 50, _T("ѧ���ɼ�����ϵͳ"));					

	settextstyle(30, 0, L"����");			//����ѡ�ģʽ
	int x = 260, y = 150;

	setlinestyle(PS_SOLID, 5);
	setlinecolor(BLACK);
	setfillcolor(RGB(red, green, blue));

	fillrectangle(250, 140, 390, 340);								/* ���Ļ�����С����Ҫ��������*/

	outtextxy(260, 150, L"��ʾѧ��");
	line(250, 190, 390, 190);		//line������ѡ��ָ���						
	outtextxy(260, 200, L"�鿴˵��");
	line(250, 240, 390, 240);
	outtextxy(260, 250, L"�޸�����");
	line(250, 290, 390, 290);
	outtextxy(260, 300, L"�˳�ϵͳ");

	EndBatchDraw();

}


/*���ƶ�������*/
//ѧ���ɼ�����
void StudentMessageInterface() {

	int prePageNum = 0;			//��ǰһҳ�ж�����

	pre_page = 1;				//ÿ�ν���ѧ���ɼ����涼չʾ��һҳѧ����Ϣ

	while (true) {

		cleardevice();					//��ջ���
		BeginBatchDraw();
		setlinecolor(BLACK);
		setfillcolor(LIGHTGRAY);
		fillrectangle(30, 10, 600, 70);					/* ���Ļ�����С����Ҫ��������*/
		fillrectangle(30, 70, 600, 130);
		fillrectangle(30, 130, 600, 190);
		fillrectangle(30, 190, 600, 250);
		fillrectangle(30, 250, 600, 310);
		fillrectangle(30, 310, 600, 370);


		setbkmode(LIGHTGRAY);
		settextstyle(20, 0, L"����");
		settextcolor(BLACK);

		outtextxy(50, 30, L"ѧ��");
		outtextxy(120, 30, L"����");
		outtextxy(200, 30, L"����");						
		outtextxy(270, 30, L"Ӣ��");
		outtextxy(350, 30, L"�����");
		outtextxy(450, 30, L"�ۺ�");
		outtextxy(530, 30, L"����");

		setlinestyle(PS_SOLID, 3);
		fillrectangle(80, 390, 140, 430);				//�������� for ����line��������
		fillrectangle(140, 390, 200, 430);
		fillrectangle(200, 390, 260, 430);

		outtextxy(20, 400, L"����");						/*�ֱ��Ӧ button    Back   AddSTU   DeleteSTU   SortSTU */
		outtextxy(90, 400, L"����");
		outtextxy(150, 400, L"ɾ��");
		outtextxy(210, 400, L"����");
		
		//	settextstyle(50, 0, _T("Wingdings"));

		
		wchar_t a[8];

		outtextxy(400, 400, L"<-");						//��һҳ
		outtextxy(500, 400, L"->");						//��һҳ
		wsprintfW(a, L"%d/%d", pre_page, total_page );
		outtextxy(440, 400, a);

		EndBatchDraw();

/*************************ʵ�ִ�ӡ��Ϣ�ĺ��Ĳ���,��һҳ����һҳֻ���� pre_page �ϲ��������� *********************************/

		if (pre_num % 5 == 0 && pre_num != 0) {		//ѧ����Ϣ����̶�̬���������ÿһ�ζ�Ҫ�ж���Ϣ
			total_page = pre_num / 5;
		}
		else if (pre_num % 5 != 0 && pre_num != 0) {		
			total_page = pre_num / 5 + 1;
		}

		if (pre_page == total_page&&pre_num%5!=0) {			
			prePageNum = pre_num % 5;
		}
		else {
			prePageNum = 5;
		}

		for (int i = (pre_page-1)*5; i < (pre_page - 1) * 5 + prePageNum; i++) {			/*��ӡѧ����Ϣ*/

			outtextxy(60, 90 + (i % 5) * 60, stu[i].number);/*����Ҫ�� i%5 �������ӡ�ڶ�ҳ������λ�û�ӵ�һҳĩβ��ʼ */

			outtextxy(130, 90 + (i % 5) * 60, stu[i].name);

			outtextxy(210, 90 + (i % 5) * 60, stu[i].score[0]);

			outtextxy(280, 90 + (i % 5) * 60, stu[i].score[1]);

			outtextxy(370, 90 + (i % 5) * 60, stu[i].score[2]);

			outtextxy(470, 90 + (i % 5) * 60, stu[i].score[3]);

			//outtextxy(540, 90+i*60, L"Lev");

		}

/***********************************************************************************************************************/

		Back.Creat(10, 390, 70, 430, L"����", back_click);			//������ؼ��ص�������  back_clickûɶ�ã��ص㻹�ǿ� being 
		AddSTU.Creat(80, 390, 140, 420,L"����",AddStudent);
		DeleteSTU.Creat(140, 390, 200, 420, L"ɾ��", DeleteStudent);
		SortSTU.Creat(200, 390, 260, 420, L"����", SortStudent);
		NextPage.Creat(400,400,450,450,L"��һҳ",Previous_Page);
		PreviousPage.Creat(500, 400, 550, 450, L"��һҳ", Next_Page);

		MOUSEMSG msg;
		while (true) {
			FlushMouseMsgBuffer();									//��ʱ��������Ϣ����������ֹ��һ�ε� x y ����
			msg = GetMouseMsg();
			int x = msg.x;
			int y = msg.y;
			if (msg.mkLButton == true) {
				
				if (Back.Check(x, y)) {
					Back.Function();
					return;
				}
				if (AddSTU.Check(x,y)) {
					AddSTU.Function();
					break;
				}
				if (DeleteSTU.Check(x,y)) {
					DeleteSTU.Function();
					break;
				}
				if (SortSTU.Check(x,y)) {
					SortSTU.Function();
					break;
				}
				if (NextPage.Check(x, y)) {
					NextPage.Function();
					break;
				}
				if (PreviousPage.Check(x, y)) {
					PreviousPage.Function();
					break;
				}

			}
		}		
	}
}

//������Ϣ
void AboutMessage() {

	Back.Creat(10, 390, 70, 430, L"����", back_click);					/*���� Back ������*/
	FlushMouseMsgBuffer();
	while (true) {
		
		cleardevice();
		setfillcolor(LIGHTGRAY);
		setlinestyle(PS_SOLID, 3); 
		setbkmode(LIGHTGRAY);
		settextstyle(20, 0, L"����");
		settextcolor(BLACK);

		fillrectangle(10, 390, 70, 430);

		BeginBatchDraw();
		outtextxy(20, 400, L"����");
		outtextxy(100, 100, L"�汾��ѧ���ɼ�����ϵͳ 2.0 Pro Max Plus");
		outtextxy(300, 200, L"��ϵ�ˣ�XXXXXXXXXXXXXX");
		outtextxy(300, 200, L"��л����ʹ�ã�����");
		EndBatchDraw();
		
		MOUSEMSG msg;
		msg = GetMouseMsg();
		while (msg.mkLButton==true) {
			if (Back.Check(msg.x, msg.y)) {
				Back.Function();
				return;
			}
		}
		Sleep(1);
	}
	
}

//�˳�ϵͳ
void ExitSystem() {
	exit(0);
}

//������Ϣ����ʵ�֣�
void back_click() {
	
}

//��һҳ
void Next_Page() {
	if (pre_page < total_page)
		pre_page++;
	else
		MessageBox(GetHWnd(), L"�������һҳ", L"�Ƿ�����", MB_OK|MB_ICONERROR);
}

void Previous_Page() {
	if (pre_page >1)
		pre_page--;
	else
		MessageBox(GetHWnd(), L"���ǵ�һҳ", L"�Ƿ�����", MB_OK|MB_ICONERROR);
}

//��¼ϵͳ
void login() {

	wc pwd[20];
	InputBox(pwd, 10, L"����������", L"�˶�����", 0, 0, true);

	int psd_INT = _wtoi(pwd);

	while (!(psd_INT == PassWord));

}