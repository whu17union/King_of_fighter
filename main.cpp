#include"Control.h"

IMAGE bg[5][20];//加载几套背景，以便后面选择
int count_bg = 0;
IMAGE hp;//血条
IMAGE pau;//暂停

int win = 0;

void loadbg()
{
	char buff[128];
	for (int m = 0; m < 2; m++)
		for (int i = 0; i < 8; i++)
		{
			sprintf(buff, "source\\background\\bg%d (%d).bmp", m + 1, i + 1);
			loadimage(&bg[m][i], buff, 640, 480);
		}
	loadimage(&hp, "source\\1.png");
}

//贴血量、头像、时间、气量等
void draw_fight(role* p1, role* p2)
{
	//背景图
	if (bg_num == 0)
		if (count_bg == 8)
			count_bg = 0;
	else if (bg_num == 1)
		if (count_bg == 12)
			count_bg = 0;
	
	putimage(0, 0, &bg[bg_num][count_bg++]);


	//贴总的hp，头像
	transparentimage(NULL, 10, 30, &hp, 0x000000);//总的血量

												  //P1头像、血量
	transparentimage(NULL, 0, 30, &p1->head[0][0], 0x000000);

	//P2头像、血量
	int x1 = 640 - p2->head[0][0].getwidth();
	transparentimage(NULL, x1, 30, &p2->head[1][0], 0x000000);

	fillpoly(4, p1->point);
	fillpoly(4, p2->point);
	setfillcolor(RED);

	//P1血量变化
	int p1_change = 100 - p1->blood;
	if (p1->blood < 0) //血量为空
	{
		p1->blood = 0;
		p1->point[0] = 51;
		p1->point[2] = 61;
	}
	else //未到空
	{
		p1->point[0] = 250 - (p1_change / 10) * 20;
		p1->point[2] = 260 - (p1_change / 10) * 20;
	}

	//P2血量变化
	int p2_change = 100 - p2->blood;
	if (p2->blood < 0) {
		p2->blood = 0;
		p2->point[4] = 590;
		p2->point[6] = 600;
	}
	else {
		p2->point[4] = 391 + (p2_change / 10) * 20;
		p2->point[6] = 401 + (p2_change / 10) * 20;
	}

	//一局游戏结束
	if (p1->blood <= 0)
		win = 2;
	else if (p2->blood <= 0)
		win = 1;

}

//控制双方人物、最重要的是使各个操作互斥
void command(role* p1, role* p2) {
	BeginBatchDraw();

	draw_fight(p1, p2);//画战斗背景，如血量变化、背景图，人物头像

					   /*action说明
					   *	switch(action)
					   *		case 1:跳跃;	case 2:拳击;
					   *		case 3:腿击;	case 4:技能1;
					   *		case 5:技能2;	case 6:技能3;
					   *		case 7:移动;	case 8:防御;
					   *		case 0:站立;	case 9:被打
					   */

					   //使P1的各操作异步，使P2的各操作异步
					   //P1操作
	if (GetAsyncKeyState('S') & 0x8000 && (p1->action == 8 || p1->action == 0))
	{
		p1->action = 8;
		p1->Defend(p2);
	}
	else if (!(GetAsyncKeyState('S') & 0x8000) && p1->action == 8)
		p1->action = 0;


	//挨打状态
	if (p1->action == 9) {
		p1->Beaten(p2);
		if (p1->count_beaten != 0)
			p1->action = 9;
		else
			p1->action = 0;
	}

	//进入跳跃状态 优先让跳跃完成 coun_jump==0时完成
	if ((GetAsyncKeyState('W') & 0x8000 && p1->action == 0) || p1->action == 1) {
		p1->Jump(p2);
		if (p1->count_jump != 0)
			p1->action = 1;
		else
			p1->action = 0;
	}

	//如果不在跳跃状态则允许进入攻击或释放技能状态 
	if (GetAsyncKeyState('J') & 0x8000 && p1->action == 0 || p1->action == 2) {
		p1->fistAttack(p2);
		if (p1->count_fist != 0)
			p1->action = 2;
		else
			p1->action = 0;
	}

	if (GetAsyncKeyState('K') & 0x8000 && p1->action == 0 || p1->action == 3) {
		p1->legAttack(p2);
		if (p1->count_leg != 0)
			p1->action = 3;
		else
			p1->action = 0;
	}

	//技能必须完全释放
	if (GetAsyncKeyState('U') & 0x8000 && p1->action == 0 || p1->action == 4) {
		p1->skill_I(p2);
		if (p1->count_skill1 != 0)
			p1->action = 4;
		else
			p1->action = 0;
	}
	if (GetAsyncKeyState('I') & 0x8000 && p1->action == 0 || p1->action == 5) {
		p1->skill_II(p2);
		if (p1->count_skill2 != 0)
			p1->action = 5;
		else
			p1->action = 0;
	}
	if (GetAsyncKeyState('O') & 0x8000 && p1->action == 0 || p1->action == 6) {
		p1->skill_III(p2);
		if (p1->count_skill3 != 0)
			p1->action = 6;
		else
			p1->action = 0;
	}

	//如果不在跳跃或攻击施法状态 则可以移动
	if (GetAsyncKeyState('A') & 0x8000 && (p1->action == 0 || p1->action == 7)) {
		p1->LeftMove(p2);
		p1->action = 7;
	}

	if (GetAsyncKeyState('D') & 0x8000 && (p1->action == 0 || p1->action == 7)) {
		p1->RightMove(p2);
		p1->action = 7;
	}

	if (p1->action == 0) {
		p1->Stand(p2);
	}
	else if (p1->action == 7)
		p1->action = 0;



	//P2操作
	//防御状态
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && (p2->action == 8 || p2->action == 0))
	{
		p2->action = 8;
		p2->Defend(p1);
	}
	else if (!(GetAsyncKeyState(VK_DOWN) & 0x8000) && p2->action == 8)
		p2->action = 0;

	//挨打状态
	if (p2->action == 9) {
		p2->Beaten(p1);
		if (p2->count_beaten != 0)
			p2->action = 9;
		else
			p2->action = 0;
	}
	//进入跳跃状态 优先让跳跃完成 coun_jump==0时完成
	if ((GetAsyncKeyState(VK_UP) & 0x8000 && p2->action == 0) || p2->action == 1) {
		p2->Jump(p1);
		if (p2->count_jump != 0)
			p2->action = 1;
		else
			p2->action = 0;
	}

	//如果不在跳跃状态则允许进入攻击或释放技能状态 
	if (GetAsyncKeyState('Z') & 0x8000 & 0x8000 && p2->action == 0 || p2->action == 2) {
		p2->fistAttack(p1);
		if (p2->count_fist != 0)
			p2->action = 2;
		else
			p2->action = 0;
	}

	if (GetAsyncKeyState('X') & 0x8000 && p2->action == 0 || p2->action == 3) {
		p2->legAttack(p1);
		if (p2->count_leg != 0)
			p2->action = 3;
		else
			p2->action = 0;
	}

	//技能必须完全释放
	if (GetAsyncKeyState('C') & 0x8000 && p2->action == 0 || p2->action == 4) {
		p2->skill_I(p1);
		if (p2->count_skill1 != 0)
			p2->action = 4;
		else
			p2->action = 0;
	}
	if (GetAsyncKeyState('V') & 0x8000 && p2->action == 0 || p2->action == 5) {
		p2->skill_II(p1);
		if (p2->count_skill2 != 0)
			p2->action = 5;
		else
			p2->action = 0;
	}
	if (GetAsyncKeyState('B') & 0x8000 && p2->action == 0 || p2->action == 6) {
		p2->skill_III(p1);
		if (p2->count_skill3 != 0)
			p2->action = 6;
		else
			p2->action = 0;
	}

	//如果不在跳跃或攻击施法状态 则可以移动
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && (p2->action == 0 || p2->action == 7)) {
		p2->LeftMove(p1);
		p2->action = 7;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && (p2->action == 0 || p2->action == 7)) {
		p2->RightMove(p1);
		p2->action = 7;
	}

	if (p2->action == 0) {
		p2->Stand(p1);
	}
	else if (p2->action == 7)
		p2->action = 0;
	EndBatchDraw();
}




int main()
{
	initgraph(640, 480);
	loadbg();

	/*  1P wasd 选择人物，j确定.jkluio攻击等
	*	2P 上下左右 选择人物，1确定,zxcvbn攻击等
	*/
	Control c;
	c.start();
	bool repate = true;//首次为true
	while (repate)
	{
		c.select();//人物选择
		/*c.r1 = new Kula();
		c.r1->type = 1;
		//初始化属于P1
		c.r1->x = 30;
		c.r1->y = 330;
		int a[8] = { 250,40,260,50,261,50,251,40 };
		for (int i = 0; i < 8; i++)
			c.r1->point[i] = a[i];

		c.r2 = new MaiShiranui();
		c.r2->type = 2;
		c.r2->x = 520;
		c.r2->y = 330;
		int b[8] = { 400,40,390,50,391,50,401,40 };
		for (int i = 0; i < 8; i++)
			c.r2->point[i] = b[i];*/
		while (1)
		{
			//暂停
			command(c.r1, c.r2);
			if (win != 0)break;
		}
		repate = c.end(win);
		win = 0;
		//返回值为true，继续游戏
		//返回值为false，退出游戏
	}
	return 0;
}
/*
先报一下人物，然后
我们在这一周内把自己选的人物的移动、攻击、技能写完
然后在进行其他的完善工作

1、开始\结束界面的制作
游戏进入界面(两个选择，进入游戏或退出——配点背景音乐？)
选择人物界面(人物展示与选择同步)
游戏开始前(血量、时间、背景选择，存在背景小图展示)
游戏结束后（KO或时间到0，胜利的人物图片展示，然后出现重新游戏或退出)

2、对战界面的制作
连击数展示
最上层人物头像，血量，时间显示
最下面有小按钮(暂停、返回、静音)
炁量(能量？)怎么变化

3、对战
P1\P2对象位置的变化
碰撞检测
防御与不防御状态，血量减多少

暂时想到这么多，到时候再分工。
哦对还有，
我们在这周末要开始写第二个文档——软件设计
——也是两个人，有人要和我一起写吗？
最后还有一次测试计划文档，6个人2个人一个。
*/
