#pragma once
#include"role.h"

class Kula :public role
{
	int count_move_front = 0;
	int count_move_back = 0;
	int count_jumpback = 0;
	
	bool flag = true;//只进行一次扣血
	IMAGE stand[2][18];//站立图片
	IMAGE jump[2][9];//跳跃图片
	IMAGE move_front[2][10];//前移图片
	IMAGE move_back[2][10];//后移
	IMAGE jumpback[2][5];//双击后移键
	IMAGE fist[2][11];//拳击图片
	IMAGE leg[2][10];//腿击图片
	IMAGE skill1[2][14];//技能1图片
	IMAGE skill2[2][24];//技能2图片
	IMAGE skill3[2][22];//技能3图片
	IMAGE bepang[2][4];//被打
	IMAGE defend[2][2];//防御图片
public:
	Kula()
	{
		name = "Kula";
		this->InitImage();
		y = 330;
	}
	void InitImage()
	{
		char buff[128];//图片资源路径

		//加载头像
		//for (int m = 0; m <= 1; m++)
		loadimage(&head[0][0], "source\\Kula\\库拉2_头像.png", 50, 50);
		loadimage(&head[1][0], "source\\Kula\\库拉1_头像.png", 50, 50);

		//加载站立图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 20; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_站立 (%d).png", m + 1, i + 1);
				loadimage(&stand[m][i], buff);
			}

		//加载跳跃图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 9; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_跳跃 (%d).png", m + 1, i + 1);
				loadimage(&jump[m][i], buff);
			}
		//加载移动图片
		for (int m = 0; m <= 1; m++)//右
			for (int i = 0; i < 10; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_前移 (%d).png", m + 1, i + 1);
				loadimage(&move_front[m][i], buff);
			}
		for (int m = 0; m <= 1; m++)//左
			for (int i = 0; i < 10; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_后移 (%d).png", m + 1, i + 1);
				loadimage(&move_back[m][i], buff);
			}
		//后跳
		for (int m = 0; m <= 1; m++)//右
			for (int i = 0; i < 5; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_后跳 (%d).png", m + 1, i + 1);
				loadimage(&jumpback[m][i], buff);
			}
		//加载拳击图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 11; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_拳击 (%d).png", m + 1, i + 1);
				loadimage(&fist[m][i], buff);
			}
		//加载腿击图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 10; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_腿击 (%d).png", m + 1, i + 1);
				loadimage(&leg[m][i], buff);
			}
		//加载技能1图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 14; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_ 技能I (%d).png", m + 1, i + 1);
				loadimage(&skill1[m][i], buff);
			}

		//加载技能2图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 24; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_技能II (%d).png", m + 1, i + 1);
				loadimage(&skill2[m][i], buff);
			}

		//加载技能3图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 22; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_技能III (%d).png", m + 1, i + 1);
					loadimage(&skill3[m][i], buff);
			}
		

		//加载被打图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 4; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_被打 (%d).png", m + 1, i + 1);
				loadimage(&bepang[m][i], buff);
			}

		//加载防御图片
		for (int m = 0; m <= 1; m++)
			for (int i = 0; i < 2; i++)
			{
				sprintf(buff, "source\\Kula\\库拉%d_ 防御 (%d).png", m + 1, i + 1);
				loadimage(&defend[m][i], buff);
			}

	}

	void Stand(role* p2)
	{
		img_x = stand[0][count_stand].getwidth();
		if (x < p2->x)//在左边
		{			
			if (count_stand >= 7 && count_stand < 13)
				transparentimage(NULL, x - 3, y - 10, &stand[0][count_stand++], 0x000000);
			else
				transparentimage(NULL, x, y - 10, &stand[0][count_stand++], 0x000000);
		}
		else//在右边
		{
			if (count_stand >= 7 && count_stand < 13)
				transparentimage(NULL, x - 3, y - 10, &stand[1][count_stand++], 0x000000);
			else
				transparentimage(NULL, x, y - 10, &stand[1][count_stand++], 0x000000);
		}
		if (count_stand == 18)count_stand = 0;//重复
		Sleep(50);
	}

	void RightMove(role* p2)
	{
		
		if (x < p2->x && ifcollide(p2));
		else
			x += 15;//人物位置右移
		if (x >= 560) x = 560;//边界判断
							  //朝向判断
		if (x < p2->x)//在左边,朝右边
		{
			img_x = move_front[0][count_move_front].getwidth();
			transparentimage(NULL, x, y - 10, &move_front[0][count_move_front++], 0x000000);
		}
		else//在右边，朝左边
		{
			img_x = move_back[1][count_move_back].getwidth();
			transparentimage(NULL, x, y - 10, &move_back[1][count_move_back++], 0x000000);
		}
		if (count_move_front == 10)count_move_front = 0;
		if (count_move_back == 10)count_move_back = 0;
		Sleep(50);
	}

	void LeftMove(role* p2)
	{
		if (x > p2->x&& ifcollide(p2));
		else
			x -= 15;//人物左移
		if (x <= 0)x = 0;//边界判断
						 //朝向判断
		if (x < p2->x)//在左边,朝右边
		{
			img_x = move_back[0][count_move_back].getwidth();
			transparentimage(NULL, x, y - 10, &move_back[0][count_move_back++], 0x000000);
		}
		else//在右边，朝左边
		{
			img_x = move_front[1][count_move_front].getwidth();
			transparentimage(NULL, x, y - 10, &move_front[1][count_move_front++], 0x000000);
		}
		if (count_move_front == 10)count_move_front = 0;
		if (count_move_back == 10)count_move_back = 0;
		Sleep(50);
	}

	
	void Jump(role* p2)
	{
		img_x = jump[0][count_jump].getwidth();
		if (count_jump <= 3)//跳跃上升
			y -= 20;
		if (count_jump >= 5)//落地
			y += 20;
		if (type == 2)
		{
			if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
				if (x > p2->x&& ifcollide(p2));
				else
					x -= 20;
				if (x <= 0)x = 0;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
				if (x < p2->x && ifcollide(p2));
				else
					x += 20;
				if (x >= 560)x = 560;
			}
		}
		else
		{
			if (GetAsyncKeyState('A') & 0x8000) {
				if (x > p2->x&& ifcollide(p2));
				else
					x -= 20;
				if (x <= 0)x = 0;
			}
			if (GetAsyncKeyState('D') & 0x8000) {
				if (x < p2->x && ifcollide(p2));
				else
					x += 20;
				if (x >= 560)x = 560;
			}
		}
		if (x < p2->x)
			transparentimage(NULL, x, y - 10, &jump[0][count_jump++], 0x000000);
		else
			transparentimage(NULL, x, y - 10, &jump[1][count_jump++], 0x000000);
		if (count_jump == 9)count_jump = 0;
		Sleep(50);
	}

	void fistAttack(role* p2)
	{
		img_x = fist[0][count_fist].getwidth();
		if (x < p2->x) {
			if (count_fist >= 2 && count_fist<10)
				transparentimage(NULL, x, y -5, &fist[0][count_fist++], 0x000000);
			else
				transparentimage(NULL, x, y - 10, &fist[0][count_fist++], 0x000000);

			//图片相碰且不为防御状态
			//img_x为当时图片的宽度,即leg[0][count_leg].getWidth()这样的
			//ifcollide(p2) &&p2->x<x + img_x
			if (ifcollide(p2) &&p2->action != 8 && flag)
			{
				flag = false;//一次拳击只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 10;//扣血，后根据血量画出血条
			}
		}
		else {
			if (count_fist >= 2 && count_fist<10)
				transparentimage(NULL, x - 20, y -5, &fist[1][count_fist++], 0x000000);
			else
				transparentimage(NULL, x - 20, y - 10, &fist[1][count_fist++], 0x000000);

			//p1在右边，拳击左边
			//img_x为当时图片的宽度
			//  x - 20<p2->x + p2->img_x
			if (ifcollide(p2) &&p2->action != 8 && flag)
			{
				flag = false;//一次拳击只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 10;//扣血，后根据血量画出血条
			}
		}
		if (count_fist == 11)
		{
			count_fist = 0;
			flag = true;//下一次拳击可以扣伤害
		}
		Sleep(10);
	}

	void legAttack(role* p2)
	{
		img_x = leg[0][count_leg].getwidth();
		int dis_y;
		dis_y = leg[0][count_leg].getheight() - leg[0][0].getheight();
		if (x < p2->x)
		{
			if (count_leg >= 3 && count_leg < 7)
				if (x>25)
					transparentimage(NULL, x - 25, y - dis_y - 2, &leg[0][count_leg++], 0x000000);
				else
					transparentimage(NULL, 0, y - dis_y - 2, &leg[0][count_leg++], 0x000000);
			else
				if (x > 25)
					transparentimage(NULL, x - 25, y - dis_y - 2, &leg[0][count_leg++], 0x000000);
				else
					transparentimage(NULL, 0, y - dis_y - 2, &leg[0][count_leg++], 0x000000);

			//图片相碰且不为防御状态   
			//img_x为当时图片的宽度
			//ifcollide(p2)  p2->x <x + img_x
			if (ifcollide(p2) &&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 10;//扣血，后根据血量画出血条
			}
		}
		else
		{
			if (count_leg >= 3 && count_leg < 7)
				if (x>25)
					transparentimage(NULL, x - 25, y - dis_y - 2 , &leg[1][count_leg++], 0x000000);
				else
					transparentimage(NULL, 0, y - dis_y - 2, &leg[1][count_leg++], 0x000000);
			else
				if (x > 25)
					transparentimage(NULL, x - 25, y - dis_y - 2, &leg[1][count_leg++], 0x000000);
				else
					transparentimage(NULL, 0, y - dis_y - 2, &leg[1][count_leg++], 0x000000);

			//图片相碰且不为防御状态   
			//ifcollide(p2)  x - 25<p2->x + p2->img_x
			if (ifcollide(p2) &&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 10;//扣血，后根据血量画出血条
			}
		}

		if (count_leg == 10)
		{
			count_leg = 0;
			flag = true;
		}
		Sleep(10);
	}

	void skill_I(role* p2)
	{
		img_x = skill1[0][count_skill1].getwidth();
		if (x < p2->x) {
			x += 10;
			transparentimage(NULL, x, y - 22, &skill1[0][count_skill1++], 0x000000);
			//图片相碰且不为防御状态   
			//ifcollide(p2)  p2->x<x + img_x
			if (ifcollide(p2) &&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 20;//扣血，后根据血量画出血条
			}
		}
		else {
			x -= 10;
			transparentimage(NULL, x, y - 22, &skill1[1][count_skill1++], 0x000000);
			//图片相碰且不为防御状态   
			//ifcollide(p2)  x<p2->x + p2->img_x
			if (ifcollide(p2) &&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 10;//扣血，后根据血量画出血条
			}
		}
		if (count_skill1 == 14)
		{
			count_skill1 = 0;
			flag = true;
		}
		Sleep(20);
	}

	void skill_II(role* p2)
	{
		img_x = skill2[0][count_skill2].getwidth();
		int ex = 0;
		int dis_y;
		dis_y = skill2[0][count_skill2].getheight() - skill2[0][0].getheight();
		if (x < p2->x) {
			if (count_skill2 <= 7)
				transparentimage(NULL, x, y - dis_y - 17, &skill2[0][count_skill2++], 0x000000);
			else
			{
				if (count_skill2 == 14)
					transparentimage(NULL, x - 35, y - dis_y + 3, &skill2[0][count_skill2++], 0x000000);
				else if (count_skill2 == 8)
					transparentimage(NULL, x - 35, y - dis_y + 3, &skill2[0][count_skill2++], 0x000000);
				else
					transparentimage(NULL, x - 10, y - dis_y - 17, &skill2[0][count_skill2++], 0x000000);

				if (x + 400 < 530)
				{
					ex = 400;
					transparentimage(NULL, x + 400, y - dis_y + 3, &skill2[0][count_skill2 + 8], 0x000000);
				}
				else
				{
					ex = 530 - skill2[0][count_skill2 + 8].getwidth();//减去图片的宽度
					transparentimage(NULL, 530, y - dis_y + 3, &skill2[0][count_skill2 + 8], 0x000000);
				}

				if (count_skill2 == 14)
					Sleep(200);
			}
			//人物有发出的武器，武器触碰到对手且不为防御状态
			//这个技能是放一个冰球，判断伤害时应是冰球触碰到了对手且不超过，ex为冰球离本身的位置    
			if (x + ex + skill2[0][count_skill2 + 8].getwidth()>p2->x//冰球图右边超过人物x
				&&x + ex<p2->x + p2->img_x//冰球图左边，未超过人物图左边
				&&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 20;//扣血，后根据血量画出血条
			}
		}
		else {
			if (count_skill2 <= 7)
			{
				transparentimage(NULL, x, y - dis_y - 17, &skill2[1][count_skill2++], 0x000000);
			}
			else
			{
				if (count_skill2 == 14)
					transparentimage(NULL, x - 35, y - dis_y + 3, &skill2[1][count_skill2++], 0x000000);
				else if (count_skill2 == 8)
					transparentimage(NULL, x - 35, y - dis_y + 3, &skill2[1][count_skill2++], 0x000000);
				else
					transparentimage(NULL, x - 10, y - dis_y - 17, &skill2[1][count_skill2++], 0x000000);

				if (x - 400 > 0)
				{
					ex = 400;
					transparentimage(NULL, x - 400, y - dis_y + 3, &skill2[1][count_skill2 + 8], 0x000000);
				}
				else
				{
					ex = x-skill2[0][count_skill2 + 8].getwidth();//0+图片的宽度
					transparentimage(NULL, 0, y - dis_y + 3, &skill2[1][count_skill2 + 8], 0x000000);
				}
				if (count_skill2 == 14)
					Sleep(200);
			}
			//人物有发出的武器，武器触碰到对手且不为防御状态
			//这个技能是放一个冰球，判断伤害时应是冰球触碰到了对手且不超过，ex为冰球离本身的位置    
			if (x - ex<p2->x + p2->img_x//冰球图超过人物图右边
				&&x - ex - skill2[1][count_skill2 + 8].getwidth()>p2->x//冰球图右边未超过人物图左边
				&&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 20;//扣血，后根据血量画出血条
			}
		}
		if (count_skill2 == 16)
		{
			flag = true;
			count_skill2 = 0;
		}
		Sleep(20);
	}

	void skill_III(role* p2)
	{
		img_x = skill3[0][count_skill3].getwidth();
		int dis_x, dis_y1, dis_y2;
		dis_y1 = skill3[0][count_skill3].getheight() - skill3[0][0].getheight();
		dis_y2 = skill3[0][count_skill3 + 10].getheight() - skill3[0][14].getheight();
		dis_x = count_skill3 - 3>0 ? count_skill3 - 3 : 0;
		if (x < p2->x) {
			if (count_skill3 < 4)
				transparentimage(NULL, x, y - 11 - dis_y1, &skill3[0][count_skill3++], 0x000000);
			else if (count_skill3 >= 4 && count_skill3 <= 11)
			{
				transparentimage(NULL, x, y - 11 - dis_y1, &skill3[0][count_skill3++], 0x000000);
				//冰柱图
				if (count_skill3 == 7 || count_skill3 == 8)
					transparentimage(NULL, x + (dis_x + 2) * 30, y - dis_y2 + 22, &skill3[0][count_skill3 + 10], 0x000000);
				else if (count_skill3 == 11)
					transparentimage(NULL, x + (dis_x + 2) * 30, y - dis_y2 + 42, &skill3[0][count_skill3 + 10], 0x000000);
				else
					transparentimage(NULL, x + (dis_x + 2) * 30, y - dis_y2 + 32, &skill3[0][count_skill3 + 10], 0x000000);
				Sleep(100);
			}
			else
				transparentimage(NULL, x, y - 12 - dis_y1, &skill3[0][count_skill3++], 0x000000);
			//对手与冰柱相撞
			if (x + (dis_x + 2) * 30>p2->x&&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 20;//扣血，后根据血量画出血条
			}
		}
		else {
			if (count_skill3 < 4)
				transparentimage(NULL, x, y - 12 - dis_y1, &skill3[1][count_skill3++], 0x000000);
			else if (count_skill3 >= 4 && count_skill3 <= 11)
			{
				dis_x = count_skill3 - 3>0 ? count_skill3 - 3 : 0;
				transparentimage(NULL, x, y - 25 - dis_y1, &skill3[1][count_skill3++], 0x000000);
				if (count_skill3 == 7 || count_skill3 == 8)
					transparentimage(NULL, x - (dis_x + 2) * 30, y - dis_y2 + 22, &skill3[1][count_skill3 + 10], 0x000000);
				else if (count_skill3 == 11)
					transparentimage(NULL, x - (dis_x + 2) * 30, y - dis_y2 + 42, &skill3[1][count_skill3 + 10], 0x000000);
				else
					transparentimage(NULL, x - (dis_x + 2) * 30, y - dis_y2 + 32, &skill3[1][count_skill3 + 10], 0x000000);
				Sleep(100);
			}
			else
				transparentimage(NULL, x, y - 12 - dis_y1, &skill3[1][count_skill3++], 0x000000);
			//对手与冰柱相撞
			if (x - (dis_x + 2) * 30<p2->x+p2->img_x&&p2->action != 8 && flag)
			{
				flag = false;//一次只扣一次血
				//p2->Beaten(this);//显示挨打
				p2->action = 9;
				p2->blood -= 20;//扣血，后根据血量画出血条
			}
		}
		if (count_skill3 == 14)
		{
			flag = true;
			count_skill3 = 0;
		}
		Sleep(30);
	}


	void Beaten(role *p2)
	{
		if (x < p2->x) {
			transparentimage(NULL, x, y - 11, &bepang[0][count_beaten++], 0x000000);
		}
		else {
			transparentimage(NULL, x, y - 11, &bepang[1][count_beaten++], 0x000000);
		}
		
		if (count_beaten == 4)count_beaten = 0;
		Sleep(30);
	}
	void Defend(role* p2)
	{
		img_x = defend[0][0].getwidth();
		if (x < p2->x)//在左边
		{
			transparentimage(NULL, x, y - 11, &defend[0][0], 0x000000);
			transparentimage(NULL, x + img_x, y - 11, &defend[0][1], 0x000000);
		}
		else//在右边
		{
			img_x = defend[0][0].getwidth()-20;
			transparentimage(NULL, x, y - 11, &defend[1][0], 0x000000);
			transparentimage(NULL, x - img_x, y - 11, &defend[1][1], 0x000000);
		}
		//if (count_stand == 18)count_stand = 0;//重复
		Sleep(50);
	}

		/*void Combine1(role *p2)
		{
			if (x < p2->x) {
				x += 15;
				transparentimage(NULL, x, y - 30, &combine1[0][count_combine1++], 0x000000);
			}
			else {
				x -= 15;
				transparentimage(NULL, x, y - 30, &combine1[1][count_combine1++], 0x000000);

			}
			if (count_combine1 == 7)count_combine1 = 0;
			Sleep(30);
		}

		void Combine2(role *p2)
		{
			int dis_x = combine2[0][1].getwidth();
			int dis_y = combine2[0][1].getheight() / 6;
			if (x < p2->x) {
				if (count_combine2 <= 1)
					transparentimage(NULL, x, y - 13, &combine2[0][count_combine2++], 0x000000);
				else
				{
					transparentimage(NULL, x, y - 13, &combine2[0][1], 0x000000);
					transparentimage(NULL, x + dis_x - 2, y - dis_y + 12, &combine2[0][count_combine2++], 0x000000);
				}
			}
			else {
				if (count_combine2 <= 1)
					transparentimage(NULL, x, y - 13, &combine2[1][count_combine2++], 0x000000);
				else
				{
					dis_x = x - combine2[1][count_combine2].getwidth();
					transparentimage(NULL, x, y - 13, &combine2[1][1], 0x000000);
					transparentimage(NULL,dis_x - 2, y - dis_y + 12, &combine2[1][count_combine2++], 0x000000);
				}

			}
			if (count_combine2 == 15)count_combine2 = 0;
			Sleep(10);
		}
		void JumpBack(role* p2)
	{
		if (x < p2->x)//在左边,朝右边
		{
			x -= 25;//人物左移
			if (x <= 0)x = 0;//边界判断
			transparentimage(NULL, x, y - 13, &jumpback[0][count_jumpback++], 0x000000);
		}
		else//在右边，朝左边
		{
			x += 25;//人物右移
			if (x >= 540)x = 540;//边界判断
			transparentimage(NULL, x, y - 13, &jumpback[1][count_jumpback++], 0x000000);
		}
		if (count_jumpback == 5)count_jumpback = 0;
		Sleep(50);
	}
	
		*/
};