#pragma once
#include<graphics.h>
#include<conio.h>
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<windows.h>
// 引用该库才能使用 TransparentBlt 函数
#pragma comment(lib, "MSIMG32.LIB")

/* 透明贴图函数
   参数：
		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
		x, y:	目标贴图位置
		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
		transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
*/
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}
using namespace std;

class role {
public:
	int type = 1;//角色归属P1/P2
	string name;
	int x, y;//位置;
	int img_x;//当前图片宽度图片
	int point[8];
	int fan_x;
	int blood = 100;//血量
	int direction;//站立方向
	int count_stand = 0;
	int count_move = 0;
	int count_jump = 0;
	int count_fist = 0;
	int count_leg = 0;
	int count_skill1 = 0;
	int count_skill2 = 0;
	int count_skill3 = 0;
	int count_beaten = 0;
	int count_defend = 0;
	int action = 0;//进行各种活动的标识
	IMAGE head[2][1];//头像贴图
public:
	virtual void InitImage() = 0;//资源初始化
	virtual void Stand(role* p2) = 0;//站立动作
	virtual void RightMove(role* p2) = 0;//角色右移
	virtual void LeftMove(role* p2) = 0;//角色左移
	virtual void Jump(role* p2) = 0;//角色跳跃
	virtual void fistAttack(role* p2) = 0;//拳击
	virtual void legAttack(role* p2) = 0;//腿击
	virtual void skill_I(role* p2) = 0;//技能1
	virtual void skill_II(role* p2) = 0;//技能2
	virtual void skill_III(role* p2) = 0;//技能3
	//virtual void JumpBack(role *p2) = 0;
	//virtual void Combine1(role *p2) = 0;
	//virtual void Combine2(role *p2) = 0;
	virtual void Beaten(role *p2) = 0;
	virtual void Defend(role* p2) = 0;//防御
	bool ifcollide(role* p2)
	{
		return (abs(x - p2->x) <= 70 && abs(y - p2->y) <= 50);
	}

	role()
	{

	}
};
