#pragma once
#include"role.h"

class BenimaruNikaido :public role
{
public:
	bool flag = true;//只进行一次扣血
	IMAGE stand[2][8];//站立图片
	IMAGE jump[2][6];//跳跃图片
	IMAGE move[2][7];//移动图片
	IMAGE fist[2][5];//拳击图片
	IMAGE leg[2][8];//腿击图片
	IMAGE skill1[2][20];//技能1图片
	IMAGE skill2[2][16];//技能2图片
	IMAGE skill3[2][23];//技能3图片
	IMAGE beaten[2][10];//挨打图片
	IMAGE defend[2][1];//防御图片

public:

	BenimaruNikaido()
	{
		name = "BenimaruNikaido";
		this->InitImage();
		y = 315;
	}

	//资源初始化
	void InitImage()
	{
		char buff[128];//图片资源路径

					   //加载头像
		loadimage(&head[0][0], "source\\BenimaruNikaido\\二阶堂红丸1_头像.png", 50, 50);
		loadimage(&head[1][0], "source\\BenimaruNikaido\\二阶堂红丸2_头像.png", 50, 50);

		//加载站立图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 8; i++)
			{
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_站立 (%d).png", m + 1, i + 1);
				loadimage(&stand[m][i], buff);
			}

		//加载跳跃图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 6; i++) {
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_跳跃 (%d).png", m + 1, i + 1);
				loadimage(&jump[m][i], buff);
			}

		//加载移动图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 7; i++) {
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_移动 (%d).png", m + 1, i + 1);
				loadimage(&move[m][i], buff);
			}

		//加载拳击图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 5; i++) {
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_拳击 (%d).png", m + 1, i + 1);
				loadimage(&fist[m][i], buff);
			}

		//加载腿击图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 8; i++) {
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_腿击 (%d).png", m + 1, i + 1);
				loadimage(&leg[m][i], buff);
			}

		//加载技能1图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 20; i++) {
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_技能I (%d).png", m + 1, i + 1);
				loadimage(&skill1[m][i], buff);
			}

		//加载技能2图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 16; i++) {
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_技能II (%d).png", m + 1, i + 1);
				loadimage(&skill2[m][i], buff);
			}

		//加载技能3图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 23; i++) {
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_技能III (%d).png", m + 1, i + 1);
				loadimage(&skill3[m][i], buff);
			}

		//加载挨打图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 10; i++) {
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_挨打 (%d).png", m + 1, i + 1);
				loadimage(&beaten[m][i], buff);
			}

		//加载防御图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 1; i++) {
				sprintf(buff, "source\\BenimaruNikaido\\二阶堂红丸%d_防御 (%d).png", m + 1, i + 1);
				loadimage(&defend[m][i], buff);
			}

		//初始化属于P1或P2
		if (type == 1)
		{
			x = 30;
			y = 330;
			int a[8] = { 250,40,260,50,261,50,251,40 };
			for (int i = 0; i < 8; i++)
				point[i] = a[i];
		}
		else
		{
			x = 570;
			y = 330;
			int a[8] = { 400,40,390,50,391,50,401,40 };
			for (int i = 0; i < 8; i++)
				point[i] = a[i];
		}
	}


	//挨打
	void Beaten(role *p2) {
		if (x < p2->x)
			transparentimage(NULL, x, y, &beaten[0][count_beaten++], 0x000000);
		else
			transparentimage(NULL, x, y, &beaten[1][count_beaten++], 0x000000);
		if (count_beaten == 8)count_beaten = 0;
		Sleep(50);
	}


	//站立动作
	void Stand(role* p2) {
		if (x<p2->x)
			transparentimage(NULL, x, y, &stand[0][count_stand++], 0x000000);
		else
			transparentimage(NULL, x, y, &stand[1][count_stand++], 0x000000);
		if (count_stand == 8)count_stand = 0;
		Sleep(50);
	}

	//角色右移
	void RightMove(role* p2) {
		x += 15;//右移
		if (x >= 560) x = 560;//边界
		if (x<p2->x)
			transparentimage(NULL, x, y, &move[0][count_move++], 0x000000);
		else
			transparentimage(NULL, x, y, &move[1][count_move++], 0x000000);
		if (count_move == 7)count_move = 0;
		Sleep(50);
	}

	//角色左移
	void LeftMove(role* p2) {
		x -= 15;//左移
		if (x <= 0)x = 0;//边界
		if (x < p2->x)
			transparentimage(NULL, x, y, &move[0][count_move++], 0x000000);
		else
			transparentimage(NULL, x, y, &move[1][count_move++], 0x000000);
		if (count_move == 7)count_move = 0;
		Sleep(50);
	}

	//角色跳跃
	void Jump(role* p2) {
		if (count_jump <= 2)//跳跃
			y -= 30;
		if (count_jump >= 3)//落下
			y += 30;
		//跳跃途中可以左移和右移
		if (GetAsyncKeyState('A') & 0x8000) {
			x -= 20;
			if (x <= 0)x = 0;//边界
		}
		if (GetAsyncKeyState('D') & 0x8000) {
			x += 20;
			if (x >= 560)x = 560;//边界
		}
		if (x < p2->x)
			transparentimage(NULL, x, y, &jump[0][count_jump++], 0x000000);
		else
			transparentimage(NULL, x, y, &jump[1][count_jump++], 0x000000);
		if (count_jump == 6)count_jump = 0;
		Sleep(30);
	}

	//拳击
	void fistAttack(role* p2) {
		img_x = fist[0][count_fist].getwidth();//当前图片的宽度，在左边、右边图片宽度一样
		if (x < p2->x)
		{
			transparentimage(NULL, x, y, &fist[0][count_fist++], 0x000000);
			//图片相碰且不为防御状态
			if (p2->x<x + img_x&&p2->action != 8 && flag)
			{
				flag = false;//一次拳击只扣一次血，一次动作后要复位
				p2->action = 9;//承伤状态
				p2->blood -= 10;//扣血，后根据血量画出血条
			}
		}
		else
		{
			if (count_fist == 0 || count_fist == 3 || count_fist == 4)
				transparentimage(NULL, x, y, &fist[1][count_fist++], 0x000000);
			else
				transparentimage(NULL, x - 30, y, &fist[1][count_fist++], 0x000000);
			//同上
			if (x - 20<p2->x + p2->img_x&&p2->action != 8 && flag)
			{
				flag = false;//一次拳击只扣一次血
				p2->action = 9;//承伤状态
				p2->blood -= 10;//扣血，后根据血量画出血条
			}

		}
		if (count_fist == 5)
		{
			count_fist = 0;
			flag = true;//下一次拳击可以扣血
		}
		Sleep(50);
	}

	//腿击
	void legAttack(role* p2) {
		img_x = leg[0][count_leg].getwidth();//当前图片的宽度，在左边、右边图片宽度一样
		if (x < p2->x)
		{
			transparentimage(NULL, x, y, &leg[0][count_leg++], 0x000000);
			if (p2->x<x + img_x&&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				p2->action = 9;//承伤状态
				p2->blood -= 10;//扣血，后根据血量画出血条
			}
		}
		else
		{
			if (count_leg == 0 || count_leg == 1 || count_leg == 5 || count_leg == 6 || count_leg == 7)
				transparentimage(NULL, x, y, &leg[1][count_leg++], 0x000000);
			else
				transparentimage(NULL, x - 30, y, &leg[1][count_leg++], 0x000000);
			if (x - 25<p2->x + p2->img_x&&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				p2->action = 9;//承伤状态
				p2->blood -= 10;//扣血，后根据血量画出血条
			}
		}
		if (count_leg == 8)
		{
			count_leg = 0;
			flag = true;//下一次腿击可以扣血
		}
		Sleep(50);
	}

	//技能1
	void skill_I(role* p2) {
		img_x = skill1[0][count_skill1].getwidth();//技能宽度
		if (x < p2->x)
		{
			transparentimage(NULL, x, y, &skill1[0][count_skill1++], 0x000000);
			if (count_skill1 >= 5) //技能特效产生时的贴图
			{
				transparentimage(NULL, x + 100, y, &skill1[0][count_skill1 + 5], 0x000000);
				//技能的位置加上技能宽度，确定攻击距离
				if (p2->x<x + 100 + img_x && p2->action != 8 && flag)
				{
					flag = false;//一次只扣一次血
					p2->action = 9;//承伤状态
					p2->blood -= 20;//扣血，后根据血量画出血条
				}
			}
		}
		else
		{
			transparentimage(NULL, x, y, &skill1[1][count_skill1++], 0x000000);
			if (count_skill1 >= 5) //技能特效产生时的贴图
			{
				transparentimage(NULL, x - 70, y, &skill1[1][count_skill1 + 5], 0x000000);
				if (x<p2->x + 70 + img_x && p2->action != 8 && flag)
				{
					flag = false;//一次只扣一次血
					p2->action = 9;//承伤状态
					p2->blood -= 20;//扣血，后根据血量画出血条
				}
			}
		}
		if (count_skill1 == 9)
		{
			count_skill1 = 0;
			flag = true;//下一次技能1可以扣血
		}
		Sleep(50);
	}

	//技能2
	void skill_II(role* p2) {
		img_x = skill2[0][count_skill2].getwidth();//技能宽度
		if (x < p2->x) {
			transparentimage(NULL, x, y, &skill2[0][count_skill2++], 0x000000);
			transparentimage(NULL, x + 150, y, &skill2[0][count_skill2 + 7], 0x000000);
			//与技能1同理 
			if (p2->x<x + 150 + img_x && p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				p2->action = 9;//承伤状态
				p2->blood -= 20;//扣血，后根据血量画出血条
			}
		}
		else {
			transparentimage(NULL, x, y, &skill2[1][count_skill2++], 0x000000);
			transparentimage(NULL, x - 120, y, &skill2[1][count_skill2 + 7], 0x000000);
			//同上  
			if (x<p2->x + 120 + img_x && p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				p2->action = 9;//承伤状态
				p2->blood -= 20;//扣血，后根据血量画出血条
			}
		}
		if (count_skill2 == 6)
		{
			count_skill2 = 0;
			flag = true;//下一次技能2可以扣血
		}
		Sleep(50);
	}

	//技能3
	void skill_III(role* p2) {
		if (x < p2->x) {
			transparentimage(NULL, x, y, &skill3[0][count_skill3++], 0x000000);
			transparentimage(NULL, x + 200, y + 50, &skill3[0][count_skill3 + 9], 0x000000);
			//地波攻击，还需考虑是否p2处于跳跃状态
			if (p2->x<x + 200 + img_x && p2->action != 8 && p2->action != 1 && flag)
			{
				flag = false;//一次只扣一次血
				p2->action = 9;//承伤状态
				p2->blood -= 20;//扣血，后根据血量画出血条
			}
		}
		else {
			transparentimage(NULL, x, y, &skill3[1][count_skill3++], 0x000000);
			transparentimage(NULL, x - 260, y + 50, &skill3[1][count_skill3 + 9], 0x000000);
			//同上
			if (x<p2->x + 260 + img_x && p2->action != 8 && p2->action != 1 && flag)
			{
				flag = false;//一次只扣一次血
				p2->action = 9;//承伤状态
				p2->blood -= 20;//扣血，后根据血量画出血条
			}

		}
		if (count_skill3 == 9)
		{
			count_skill3 = 0;
			flag = true;//下一次技能3可以扣血
		}
		Sleep(30);
	}

	//防御
	void Defend(role* p2) {
		if (x < p2->x)
			transparentimage(NULL, x, y + 20, &defend[0][0], 0x000000);
		else
			transparentimage(NULL, x, y + 20, &defend[1][0], 0x000000);
		Sleep(50);
	}


};
