#pragma once
#include"Allrole.h"

#include <windows.h>
#include <stdlib.h>
#include <Mmsystem.h>
#include <stdio.h>
#include "windows.h"
#pragma comment(lib,"winmm.lib")

IMAGE bg_chioce[2][1];//只有两套背景
int bg_num = 0;//背景选择

class Control
{
public:
	role *r1, *r2;
	int width, height;
	Control();
	void start();
	void select();
	bool end(int p);
};

Control::Control()
{
	r1 = r2 = NULL;
	width = 640;
	height = 480;
	loadimage(&bg_chioce[0][0], "source\\background\\bg1 (1).bmp", 320, 240);
	loadimage(&bg_chioce[1][0], "source\\background\\bg2 (1).bmp", 320, 240);
}

void Control::start()
{
	IMAGE bg, start;
	mciSendString("play source\\背景音乐.mp3", NULL, 0, NULL);
	char ch;
	initgraph(width, height);
	loadimage(&bg, "source\\control\\bg_start.bmp", width, height);
	loadimage(&start, "source\\control\\start.bmp");
	putimage(0, 0, &bg);
	putimage(width / 2 - 30, height * 3 / 4, &start);
	ch = _getch();
	while (ch == EOF)
	{
		ch = _getch();
	}
}

void Control::select()
{
	mciSendString("pause source\\背景音乐.mp3", NULL, 0, NULL);
	IMAGE select, model1, model2, vs, bg;
	int count1 = 1, count2 = 1;
	bool sure = false;
	int ch;
	char path_selsect[30] = "source\\control\\select1_1.png";
	//选人物1,2的路径
	char path_model1[30] = "source\\control\\model1.png", path_model2[30] = "source\\control\\model1.png";
	//vs图片的路径
	char path_vs[30] = "source\\control\\vs.png", path_bg[30] = "source\\control\\bg.jpg";
	//加载图片
	loadimage(&select, path_selsect, width / 4, width / 6);
	loadimage(&model1, path_model1, width / 8, width * 2 / 9);
	loadimage(&model2, path_model2, width / 8, width * 2 / 9);
	loadimage(&vs, path_vs);
	loadimage(&bg, path_bg, width, height);
	cleardevice();
	//粘贴图片
	putimage(0, 0, &bg);
	transparentimage(NULL, 213, 120, &select, RGB(255, 255, 255));
	transparentimage(NULL, 160, 280, &model1, RGB(255, 255, 255));
	transparentimage(NULL, 360, 280, &model2, RGB(255, 255, 255));
	transparentimage(NULL, 235, 300, &vs, RGB(255, 255, 255));

	while (1)
	{
		ch = _getch();
		bool change = true;
		switch (ch)
		{
		case 'a':
		case 'A':
			if (count1 == 1 || count1 == 4)
			{
				count1 += 2;
			}
			else
			{
				count1 -= 1;
			}
			break;
		case 's':
		case 'S':
			if (count1 >= 1 && count1 <= 3)
			{
				count1 += 3;
			}
			else
			{
				count1 -= 3;
			}
			break;
		case 'w':
		case 'W':
			if (count1 >= 1 && count1 <= 3)
			{
				count1 += 3;
			}
			else
			{
				count1 -= 3;
			}
			break;
		case 'd':
		case 'D':
			if (count1 == 3 || count1 == 6)
			{
				count1 -= 2;
			}
			else
			{
				count1 += 1;
			}
			break;
		case 'j':
		case 'J':
			sure = true;
			break;
		default:
			change = false;
			break;
		}

		if (sure)
		{
			break;
		}

		if (change)
		{
			sprintf_s(path_selsect, "source\\control\\select1_%d.png", count1);
			sprintf_s(path_model1, "source\\control\\model%d.png", count1);
			loadimage(&select, path_selsect, width / 4, width / 6);
			loadimage(&model1, path_model1, width / 8, width * 2 / 9);
			cleardevice();
			putimage(0, 0, &bg);
			transparentimage(NULL, 213, 120, &select, RGB(255, 255, 255));
			transparentimage(NULL, 160, 280, &model1, RGB(255, 255, 255));
			transparentimage(NULL, 360, 280, &model2, RGB(255, 255, 255));
			transparentimage(NULL, 235, 300, &vs, RGB(255, 255, 255));

		}
	}
	
	switch (count1)
	{
	case 1:r1 = new K(); break;
	case 2:r1 = new Jing(); break;
	case 3:r1 = new BenimaruNikaido(); break;
	case 4:r1 = new Kula(); break;
	case 5:r1 = new MaiShiranui(); break;
	case 6:r1 = new LoriYagami(); break;
	default:exit(1);
	}
	r1->type = 1;
	//初始化属于P1
	r1->x = 30;
	int a[8] = { 250,40,260,50,261,50,251,40 };
	for (int i = 0; i < 8; i++)
		r1->point[i] = a[i];

	sure = false;

	sprintf_s(path_selsect, "source\\control\\select2_1.png");
	loadimage(&select, path_selsect, width / 4, width / 6);
	cleardevice();
	putimage(0, 0, &bg);
	transparentimage(NULL, 213, 120, &select, RGB(255, 255, 255));
	transparentimage(NULL, 160, 280, &model1, RGB(255, 255, 255));
	transparentimage(NULL, 360, 280, &model2, RGB(255, 255, 255));
	transparentimage(NULL, 235, 300, &vs, RGB(255, 255, 255));


	while (1)
	{
		ch = _getch();
		if (ch != 224 && ch != '1')
		{
			continue;
		}
		if (ch == 224)
		{
			ch = _getch();
		}
		bool change = true;
		switch (ch)
		{
		case 75:
			if (count2 == 1 || count2 == 4)
			{
				count2 += 2;
			}
			else
			{
				count2 -= 1;
			}
			break;
		case 80:
			if (count2 >= 1 && count2 <= 3)
			{
				count2 += 3;
			}
			else
			{
				count2 -= 3;
			}
			break;
		case 72:
			if (count2 >= 1 && count2 <= 3)
			{
				count2 += 3;
			}
			else
			{
				count2 -= 3;
			}
			break;
		case 77:
			if (count2 == 3 || count2 == 6)
			{
				count2 -= 2;
			}
			else
			{
				count2 += 1;
			}
			break;
		case '1':
			sure = true;
			break;
		default:
			change = false;
			break;
		}

		if (sure)
		{
			break;
		}

		if (change)
		{
			sprintf_s(path_selsect, "source\\control\\select2_%d.png", count2);
			sprintf_s(path_model2, "source\\control\\model%d.png", count2);
			loadimage(&select, path_selsect, width / 4, width / 6);
			loadimage(&model2, path_model2, width / 8, width * 2 / 9);
			cleardevice();
			putimage(0, 0, &bg);
			transparentimage(NULL, 213, 120, &select, RGB(255, 255, 255));
			transparentimage(NULL, 160, 280, &model1, RGB(255, 255, 255));
			transparentimage(NULL, 360, 280, &model2, RGB(255, 255, 255));
			transparentimage(NULL, 235, 300, &vs, RGB(255, 255, 255));

		}
	}
	
	switch (count2)
	{
	case 1:r2 = new K(); break;
	case 2:r2 = new Jing(); break;
	case 3:r2 = new BenimaruNikaido(); break;
	case 4:r2 = new Kula(); break;
	case 5:r2 = new MaiShiranui(); break;
	case 6:r2 = new LoriYagami(); break;
	default:exit(1);
	}
	r2->type = 2;
	r2->x = 520;
	int b[8] = { 400,40,390,50,391,50,401,40 };
	for (int i = 0; i < 8; i++)
		r2->point[i] = b[i];

	//上述完成人物选择，现进行背景选择
	bool ext = false;
	cleardevice();
	putimage(0, 0, &bg);
	settextstyle(30, 0, _T("黑体"));
	TCHAR s[] = _T("背景选择");
	outtextxy(265, 50, s);
	while (1)
	{
		putimage(160, 120, &bg_chioce[bg_num][0]);
		ch = _getch();
		switch (ch)
		{
		case 'd':
		case 'D':
			if (bg_num <= 1)bg_num++;
			if (bg_num == 2)bg_num = 0;
			break;
		case 'a':
		case 'A':
			if (bg_num >= 0)bg_num--;
			if (bg_num == -1)bg_num = 1;
			break;
		case 'j':
		case 'J':
			ext = true;
			break;
		}
		if (ext)
			break;
	}
}

bool Control::end(int p)
//返回值为true，继续游戏
//返回值为false，退出游戏
{
	IMAGE tuichu, jixv, bg, winner, is, ko, p1, p2;
	char ch;
	loadimage(&jixv, "source\\control\\jixv.png");
	loadimage(&tuichu, "source\\control\\tuichu.png");
	loadimage(&bg, "source\\control\\bg.jpg", width, height);
	loadimage(&winner, "source\\control\\winner.png");
	loadimage(&is, "source\\control\\is.png");
	loadimage(&ko, "source\\control\\ko.png");
	loadimage(&p1, "source\\control\\p1.png");
	loadimage(&p2, "source\\control\\p2.png");
	cleardevice();
	putimage(0, 0, &bg);
	transparentimage(NULL, width / 2 - 150, height / 2 - 100, &ko, RGB(255, 255, 255));
	Sleep(1000);
	cleardevice();
	putimage(0, 0, &bg);
	transparentimage(NULL, width / 2 - 325, height / 2 - 200, &winner, RGB(255, 255, 255));
	Sleep(600);
	transparentimage(NULL, width / 2 - 150, height / 2 - 75, &is, RGB(255, 255, 255));
	Sleep(600);
	if (p == 1)
		transparentimage(NULL, width / 2 - 150, height / 2 + 75, &p1, RGB(255, 255, 255));
	else if (p == 2)
		transparentimage(NULL, width / 2 - 150, height / 2 + 75, &p2, RGB(255, 255, 255));
	Sleep(1500);
	cleardevice();
	putimage(0, 0, &bg);
	putimage(width / 2 - 150, height / 2 - 75, &jixv);
	putimage(width / 2 - 150, height / 2 + 75, &tuichu);
	do
	{
		ch = _getch();
		if (ch == '1')
			return false;
		if (ch == '0')
			return true;
	} while (ch != '1' && ch != '0');
}