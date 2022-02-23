/*
		@cglssg
		2022年2月16日21:27:01
		项目：学生成绩管理系统	
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


bool  Judge_Menu=true;			//判断是否在主界面

//STU stuhead;					//头结点
STU stu[100];					//学生信息
int pre_num=0;						//目前人数
int total_num=100;					//最大人数
int pre_page = 1;			//当前页数	
int total_page = 1;			//一共多少页
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

	ShowStudent.Creat(250,140,390,190,L"显示学生", StudentMessageInterface);				/* 更改画布大小这里要重新设置*/
	About.Creat(250, 190, 390, 240, L"关于", AboutMessage);
	ChangePwd.Creat(250, 290, 390, 290, L"更改密码", NULL);
	Exit.Creat(250, 290, 390, 340, L"退出系统", ExitSystem);

	MOUSEMSG msg;

	while (true) {					//主控循环
		ShowMenu();					//将绘制主界面的函数嵌在while里面，这样就能实现点击返回值后显示主界面

		while (true) {						//在主界面则响应其他功能，进入二级界面就限制主界面的判断范围
			msg = GetMouseMsg();
			if (msg.mkLButton == true) {				//左键按下
				int x = msg.x;
				int y = msg.y;
				if (ShowStudent.Check(x, y)) {			//ShowMenu()中寻找坐标区域
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




/*功能函数*/
//添加学生
void AddStudent() {

	if (pre_num < total_num) {
		
		int choice = 1;
		int being=1;

		while (choice == 1) {

			wc name[20], num[10], sco[10];
			size_t number;
			double score[4];
			int bedoing = 1;		// InputBox 中点击取消，后面信息不在输入
			bool Input = true;		//循环控制  每次输入错误后重新输入		
						
			if (bedoing) {
				while (Input) {				//输入学生信息
					bedoing=InputBox(num, 10, L"学号", L"学号", 0, 0, 0, false);		//输入和点击确定返回 1 ，点击取消返回 0 
					number = _wtoi(num);
					if (number > 0 && number <= 1000&&bedoing!=0) {
						Input = false;
					}
					else if(bedoing==0) {
						return;
					}
					else {
						MessageBox(NULL, L"请规范输入（0 - 1000）", L"错误", MB_OK);
					}
				}
			}

			if (!lstrcpynW(stu[pre_num].number, num, 10))				//防止转换失败
				return;

			if (bedoing) {
				Input = true;
				while (Input) {
					bedoing = InputBox(name, 10, L"姓名", L"姓名", NULL, 0, 0, false);
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
					bedoing=InputBox(sco, 10, L"高数成绩", L"成绩", 0, 0, 0, false);
					score[0] = _wtoi(sco);
					if (score[0] >= 0 && score[0] <= 100) {
						Input = false;
						score[0] = number;
					}
					else if(bedoing == 0) {
						return;
					}
					else {
						MessageBox(NULL, L"请规范输入（0 - 100）", L"错误", MB_OK);
					}

				}
			}

			if (!lstrcpynW(stu[pre_num].score[0], sco, 10))
				break;

			if (bedoing) {
				Input = true;
				while (Input) {
					bedoing=InputBox(sco, 10, L"英语成绩", L"成绩", 0, 0, 0, false);
					score[1] = _wtoi(sco);
					if (score[1] >= 0 && score[1] <= 100) {
						Input = false;
					}else if (bedoing == 0) {
						return;
					}
					else {
						MessageBox(NULL, L"请规范输入（0 - 100）", L"错误", MB_OK);
					}
				}
			}

			if (!lstrcpynW(stu[pre_num].score[1], sco, 10))
				return;

			if (bedoing) {
				Input = true;
				while (Input) {
					bedoing=InputBox(sco, 10, L"计算机成绩", L"成绩", 0, 0, 0, false);
					score[2] = _wtoi(sco);
					if (score[2] >= 0 && score[2] <= 100) {
						Input = false;
					}
					else if (bedoing == 0) {
						return;
					}
					else {
						MessageBox(NULL, L"请规范输入（0 - 100）", L"错误", MB_OK);
					}
				}
			}

			if (!lstrcpynW(stu[pre_num].score[2], sco, 10))
				return;
			wsprintf(stu[pre_num].score[3],L"%d",score[0]+score[1]+score[2]);

			pre_num++;

			choice = MessageBox(GetHWnd(), L"是否继续？", L"请求", MB_OKCANCEL);

			if (choice == 0)
				return;
		}
		
	}
	else {
		MessageBox(NULL, L"抱歉！上限已满！", L"警告", MB_RETRYCANCEL | MB_ICONWARNING);
	}

}

//删除学生
void DeleteStudent() {

	if (pre_num > 0) {

		wc name[20], num[10];
		size_t number;
		
		int being = IDRETRY;

		while (being==IDRETRY) {
			InputBox(num, 10, L"请输入所删除学生的学号", L"学号", 0, 0, 0, true);
			number = _wtoi(num);
			if (number > 0 && number <= 1000) {
				
				for (int i = 0; i <= pre_num;i++) {
					if ((wcscmp(stu[i].number, num)) == 0) {
						MessageBox(NULL, L"删除成功", L"正确", MB_OK);
						for (int j = i; j + 1  <= pre_num; j++) {
							stu[j] = stu[j + 1];
						}
						pre_num--;
						return;
					}
				}
				being=MessageBox(NULL, L"未找到该生信息", L"错误", MB_RETRYCANCEL);	// retry 返回IDRETRY(4)
			}
			else {
				MessageBox(NULL, L"请按正确格式输入（0 - 1000）", L"错误", MB_OK);
			}
		}
	}
	else {
		MessageBox(GetHWnd(), L"暂未录入学生", L"错误", MB_OK);
	}

}

//学生排序
void SortStudent() {
	
}


/*绘制一级界面*/
//主界面
void ShowMenu() {

	int red = 230;
	int green = 230;
	int blue = 230;

	BeginBatchDraw();						//开启批量绘画模式，防止画板闪烁

	setbkcolor(RGB(red, green, blue));		//配置初始环境
	setfillcolor(RGB(red, green, blue));
	setlinecolor(LIGHTGRAY);

	solidrectangle(0, 0, 640, 480);			//填白界面

	settextcolor(BLACK);					//设置标题模式
	setbkmode(OPAQUE);
	settextstyle(50, 0, L"宋体");
	outtextxy(120, 50, _T("学生成绩管理系统"));					

	settextstyle(30, 0, L"宋体");			//设置选项卡模式
	int x = 260, y = 150;

	setlinestyle(PS_SOLID, 5);
	setlinecolor(BLACK);
	setfillcolor(RGB(red, green, blue));

	fillrectangle(250, 140, 390, 340);								/* 更改画布大小这里要重新设置*/

	outtextxy(260, 150, L"显示学生");
	line(250, 190, 390, 190);		//line将其余选项卡分隔开						
	outtextxy(260, 200, L"查看说明");
	line(250, 240, 390, 240);
	outtextxy(260, 250, L"修改密码");
	line(250, 290, 390, 290);
	outtextxy(260, 300, L"退出系统");

	EndBatchDraw();

}


/*绘制二级界面*/
//学生成绩界面
void StudentMessageInterface() {

	int prePageNum = 0;			//当前一页有多少人

	pre_page = 1;				//每次进入学生成绩界面都展示第一页学生信息

	while (true) {

		cleardevice();					//清空画布
		BeginBatchDraw();
		setlinecolor(BLACK);
		setfillcolor(LIGHTGRAY);
		fillrectangle(30, 10, 600, 70);					/* 更改画布大小这里要重新设置*/
		fillrectangle(30, 70, 600, 130);
		fillrectangle(30, 130, 600, 190);
		fillrectangle(30, 190, 600, 250);
		fillrectangle(30, 250, 600, 310);
		fillrectangle(30, 310, 600, 370);


		setbkmode(LIGHTGRAY);
		settextstyle(20, 0, L"宋体");
		settextcolor(BLACK);

		outtextxy(50, 30, L"学号");
		outtextxy(120, 30, L"姓名");
		outtextxy(200, 30, L"高数");						
		outtextxy(270, 30, L"英语");
		outtextxy(350, 30, L"计算机");
		outtextxy(450, 30, L"综合");
		outtextxy(530, 30, L"排名");

		setlinestyle(PS_SOLID, 3);
		fillrectangle(80, 390, 140, 430);				//可以利用 for 调用line来划画线
		fillrectangle(140, 390, 200, 430);
		fillrectangle(200, 390, 260, 430);

		outtextxy(20, 400, L"返回");						/*分别对应 button    Back   AddSTU   DeleteSTU   SortSTU */
		outtextxy(90, 400, L"增加");
		outtextxy(150, 400, L"删除");
		outtextxy(210, 400, L"排序");
		
		//	settextstyle(50, 0, _T("Wingdings"));

		
		wchar_t a[8];

		outtextxy(400, 400, L"<-");						//上一页
		outtextxy(500, 400, L"->");						//下一页
		wsprintfW(a, L"%d/%d", pre_page, total_page );
		outtextxy(440, 400, a);

		EndBatchDraw();

/*************************实现打印信息的核心部分,上一页和下一页只用在 pre_page 上操作就行了 *********************************/

		if (pre_num % 5 == 0 && pre_num != 0) {		//学生信息随过程动态增长，因此每一次都要判断信息
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

		for (int i = (pre_page-1)*5; i < (pre_page - 1) * 5 + prePageNum; i++) {			/*打印学生信息*/

			outtextxy(60, 90 + (i % 5) * 60, stu[i].number);/*必须要有 i%5 ，否则打印第二页的物理位置会从第一页末尾开始 */

			outtextxy(130, 90 + (i % 5) * 60, stu[i].name);

			outtextxy(210, 90 + (i % 5) * 60, stu[i].score[0]);

			outtextxy(280, 90 + (i % 5) * 60, stu[i].score[1]);

			outtextxy(370, 90 + (i % 5) * 60, stu[i].score[2]);

			outtextxy(470, 90 + (i % 5) * 60, stu[i].score[3]);

			//outtextxy(540, 90+i*60, L"Lev");

		}

/***********************************************************************************************************************/

		Back.Creat(10, 390, 70, 430, L"返回", back_click);			//点击返回键回到主界面  back_click没啥用，重点还是看 being 
		AddSTU.Creat(80, 390, 140, 420,L"增加",AddStudent);
		DeleteSTU.Creat(140, 390, 200, 420, L"删除", DeleteStudent);
		SortSTU.Creat(200, 390, 260, 420, L"排序", SortStudent);
		NextPage.Creat(400,400,450,450,L"上一页",Previous_Page);
		PreviousPage.Creat(500, 400, 550, 450, L"下一页", Next_Page);

		MOUSEMSG msg;
		while (true) {
			FlushMouseMsgBuffer();									//及时清空鼠标信息缓冲区，防止上一次的 x y 干扰
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

//关于信息
void AboutMessage() {

	Back.Creat(10, 390, 70, 430, L"返回", back_click);					/*更新 Back 的属性*/
	FlushMouseMsgBuffer();
	while (true) {
		
		cleardevice();
		setfillcolor(LIGHTGRAY);
		setlinestyle(PS_SOLID, 3); 
		setbkmode(LIGHTGRAY);
		settextstyle(20, 0, L"宋体");
		settextcolor(BLACK);

		fillrectangle(10, 390, 70, 430);

		BeginBatchDraw();
		outtextxy(20, 400, L"返回");
		outtextxy(100, 100, L"版本：学生成绩管理系统 2.0 Pro Max Plus");
		outtextxy(300, 200, L"联系人：XXXXXXXXXXXXXX");
		outtextxy(300, 200, L"感谢您的使用！！！");
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

//退出系统
void ExitSystem() {
	exit(0);
}

//返回信息（空实现）
void back_click() {
	
}

//下一页
void Next_Page() {
	if (pre_page < total_page)
		pre_page++;
	else
		MessageBox(GetHWnd(), L"已是最后一页", L"非法操作", MB_OK|MB_ICONERROR);
}

void Previous_Page() {
	if (pre_page >1)
		pre_page--;
	else
		MessageBox(GetHWnd(), L"已是第一页", L"非法操作", MB_OK|MB_ICONERROR);
}

//登录系统
void login() {

	wc pwd[20];
	InputBox(pwd, 10, L"请输入密码", L"核对密码", 0, 0, true);

	int psd_INT = _wtoi(pwd);

	while (!(psd_INT == PassWord));

}