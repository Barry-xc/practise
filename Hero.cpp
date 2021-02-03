/********************************************************
功能：键盘输入更新骑士坐标和武器坐标，打印骑士，打印武器
********************************************************/
#include"main.h"

//全局变量
int intervein=0;		//交错脚
HERO Knight;			//骑士结构体
Weapon Weapon1;			//武器结构体
Bullet* bullet[1000000];//子弹结构体
int cpcy=0;				//子弹结构体数组下标		
int shoot=15;			//子弹射击方向
int count=0;			//子弹时间计数器
int bullet_speed = 4;	//子弹发射时间间隔

//变量声明
extern IMAGE Hero_R;			//右
extern IMAGE Hero_mask_R;		//右掩码
extern IMAGE Hero_R_2;			//右跑
extern IMAGE Hero_mask_R_2;		//右跑掩码图
extern IMAGE Hero_L;			//左
extern IMAGE Hero_mask_L;		//左掩码图
extern IMAGE Hero_L_2;			//左跑
extern IMAGE Hero_mask_L_2;		//左跑掩码图
extern IMAGE Weapon1_L;			//弹射冲锋枪反
extern IMAGE Weapon1_L_Y;		//弹射冲锋枪反掩码图
extern IMAGE Weapon1_R;			//弹射冲锋枪
extern IMAGE Weapon1_R_Y;		//弹射冲锋枪掩码图
extern IMAGE Weapon1_R_o;		//旋转后
extern IMAGE Weapon1_R_Y_o;		//旋转后
extern IMAGE Weapon1_L_o;		//旋转后
extern IMAGE Weapon1_L_Y_o;		//旋转后
extern IMAGE Bullet1;			//英雄子弹
extern IMAGE Bullet1Y;			//英雄子弹掩码图
extern IMAGE Bullet1_o;			//旋转后
extern IMAGE Bullet1Y_o;		//旋转后

/********************************************************
函数功能:根据键盘输入，更新骑士结构体坐标值、方向值
参数	:无
返回值	:无
*********************************************************/
void Hero_Move()
{
	if(GetAsyncKeyState(VK_UP)&0x8000)
	{
		
		if(Knight.y>10)
		{
			Knight.y-=15;
		}
		else 
		{
			Knight.y=10;
		}
		printf("\t%d,%d\n",Knight.x,Knight.y);
		Weapon1.dir=1;
		intervein++;
	}
	if(GetAsyncKeyState(VK_DOWN)&0x8000)
	{	
		if(Knight.y<415)
		{
			Knight.y+=15;
		}
		else 
		{
			Knight.y=415;
		}
		Weapon1.dir=2;
		printf("\t%d,%d\n",Knight.x,Knight.y);
		intervein++;
	}
	if(GetAsyncKeyState(VK_LEFT)&0x8000)
	{
		if(Knight.x>30)
		{
			Knight.x-=15;
		}
		else
		{
			Knight.x=30;
		}
		Knight.dir=0;
		Weapon1.dir=3;
		intervein++;
		printf("\t%d,%d\n",Knight.x,Knight.y);
	}
	if(GetAsyncKeyState(VK_RIGHT)&0x8000)
	{
		Knight.x+=15;
		Knight.dir=1;	
		Weapon1.dir=4;
		intervein++;
		printf("\t%d,%d\n",Knight.x,Knight.y);
	}
}




/********************************************************
函数功能:打印更新坐标后的骑士
参数	:无
返回值	:无
*********************************************************/
void Print_Hero()
{
	Sleep(50);
	BeginBatchDraw();

	//向右移动
	if(Knight.dir==1)
	{
		if(intervein%2==0)
		{
			putimage(Knight.x,Knight.y,&Hero_mask_R,NOTSRCERASE);
			putimage(Knight.x,Knight.y,&Hero_R,SRCINVERT);
		}
		else if(intervein%2==1)
		{
			putimage(Knight.x,Knight.y,&Hero_mask_R_2,NOTSRCERASE);
			putimage(Knight.x,Knight.y,&Hero_R_2,SRCINVERT);
		}	
	}
	
	//向左移动
	else if(Knight.dir==0)
	{
	
		if(intervein%2==0)
		{
			putimage(Knight.x,Knight.y,&Hero_mask_L,NOTSRCERASE);
			putimage(Knight.x,Knight.y,&Hero_L,SRCINVERT);
		}
		else if(intervein%2==1)
		{
			putimage(Knight.x,Knight.y,&Hero_mask_L_2,NOTSRCERASE);
			putimage(Knight.x,Knight.y,&Hero_L_2,SRCINVERT);
		}	
	}
	FlushBatchDraw();
}




/********************************************************
函数功能:打印更新坐标后的英雄武器
参数	:无
返回值	:无
*********************************************************/
void Print_Weapon()
{
	BeginBatchDraw();
	if(Knight.dir==1 && Weapon1.dir==4)//英雄右，枪右
	{
		RotateImage(&Weapon1_R_o,&Weapon1_R,PI/175);
		RotateImage(&Weapon1_R_Y_o,&Weapon1_R_Y,PI/175);
		BeginBatchDraw();
		putimage(Knight.x,Knight.y+35,&Weapon1_R_Y_o,NOTSRCERASE);
		putimage(Knight.x,Knight.y+35,&Weapon1_R_o,SRCINVERT);
		EndBatchDraw();
	}
	else if(Knight.dir==1 && Weapon1.dir==1)//英雄右，枪上
	{
		RotateImage(&Weapon1_R_o,&Weapon1_R,PI/0.666);
		RotateImage(&Weapon1_R_Y_o,&Weapon1_R_Y,PI/0.666);
		putimage(Knight.x+10,Knight.y+20,&Weapon1_R_Y_o,NOTSRCERASE);
		putimage(Knight.x+10,Knight.y+20,&Weapon1_R_o,SRCINVERT);
	}
	else if(Knight.dir==1 && Weapon1.dir==2)//英雄右，枪下
	{
		RotateImage(&Weapon1_R_o,&Weapon1_R,PI/2);
		RotateImage(&Weapon1_R_Y_o,&Weapon1_R_Y,PI/2);
		putimage(Knight.x+5,Knight.y+5,&Weapon1_R_Y_o,NOTSRCERASE);
		putimage(Knight.x+5,Knight.y+5,&Weapon1_R_o,SRCINVERT);
	}
	else if(Knight.dir==0 && Weapon1.dir==3)//英雄左，枪左
	{
		RotateImage(&Weapon1_L_o,&Weapon1_L,PI/180);
		RotateImage(&Weapon1_L_Y_o,&Weapon1_L_Y,PI/180);
		putimage(Knight.x-5,Knight.y+35,&Weapon1_L_Y_o,NOTSRCERASE);
		putimage(Knight.x-5,Knight.y+35,&Weapon1_L_o,SRCINVERT);
	}
	else if(Knight.dir==0 && Weapon1.dir==1)//英雄左，枪上
	{
		RotateImage(&Weapon1_L_o,&Weapon1_L,PI/2);
		RotateImage(&Weapon1_L_Y_o,&Weapon1_L_Y,PI/2);
		putimage(Knight.x+35,Knight.y+15,&Weapon1_L_Y_o,NOTSRCERASE);
		putimage(Knight.x+35,Knight.y+15,&Weapon1_L_o,SRCINVERT);
	}
	else if(Knight.dir==0 && Weapon1.dir==2)//英雄左，枪下
	{
		RotateImage(&Weapon1_L_o,&Weapon1_L,PI/0.666);
		RotateImage(&Weapon1_L_Y_o,&Weapon1_L_Y,PI/0.666);
		putimage(Knight.x+35,Knight.y,&Weapon1_L_Y_o,NOTSRCERASE);
		putimage(Knight.x+35,Knight.y,&Weapon1_L_o,SRCINVERT);
	}
	EndBatchDraw();
	FlushBatchDraw();
}



/********************************************************
函数功能:当检测到空格键，增加子弹结构体数组下标
参数	:无
返回值	:无
*********************************************************/
void Hero_Shoot()//检测子弹按键
{
	if(GetAsyncKeyState(VK_SPACE))
	{
		count++;
		if(Knight.dir==1 && Weapon1.dir==4)	//英雄右，武器右
		{
			shoot=0;
			if( count % bullet_speed == 0)
			{
				shoot=1;
				count=0;
			}
		}
		else if(Knight.dir==1 && Weapon1.dir==1)//英雄右，武器上
		{
			shoot = 0;
			if( count % bullet_speed == 0)
			{
				shoot = 3;
				count = 0;
			}
		}
		else if(Knight.dir==1 && Weapon1.dir==2)//英雄右，武器下
		{
			shoot = 0;
			if( count % bullet_speed == 0)
			{
				shoot = 4;
				count = 0;
			}	
		}
		else if(Knight.dir==0 && Weapon1.dir==1)//英雄左，武器上
		{
			shoot = 0;
			if( count % bullet_speed == 0)
			{
				shoot = 5;
				count = 0;
			}
		}
		else if(Knight.dir==0 && Weapon1.dir==3)//英雄左，武器左
		{
			shoot=0;
			if(count % bullet_speed == 0)
			{
				shoot = 2;
				count = 0;
			}
		}
	
		else if(Knight.dir==0 && Weapon1.dir==2)//英雄左，武器下
		{
			shoot=0;
			if(count % bullet_speed == 0)
			{
				shoot = 6;
				count = 0;
			}
		}
	}
}


/********************************************************
函数功能:根据子弹结构体数组中的所有合法坐标，打印子弹
参数	:无
返回值	:无
*********************************************************/
void One_Shoot()
{
	int i;
	loadimage(&Bullet1,_T("D:\\mini元气骑士\\素材\\bullet\\rpk冲锋枪.png"));
	loadimage(&Bullet1Y,_T("D:\\mini元气骑士\\素材\\bullet\\rpk冲锋枪Y.png"));

	if(shoot==1)//右右
	{
		bullet[cpcy]=(Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x=Knight.x+75;
		bullet[cpcy]->y=Knight.y+40;
		bullet[cpcy]->dir=1;//右右
		shoot=0;
		cpcy++;
	}
	else if(shoot==2)//左左
	{
		bullet[cpcy]=(Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x=Knight.x-20;
		bullet[cpcy]->y=Knight.y+37;
		bullet[cpcy]->dir=2;//左左
		shoot=0;
		cpcy++;
	}
	else if(shoot == 3)//右上
	{
		bullet[cpcy] = (Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x = Knight.x + 13;
		bullet[cpcy]->y = Knight.y - 5;
		bullet[cpcy]->dir = 3;//右上
		shoot = 0;
		cpcy++;		
	}
	else if(shoot == 4)//右下
	{
		bullet[cpcy] = (Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x = Knight.x + 19;
		bullet[cpcy]->y = Knight.y + 80;
		bullet[cpcy]->dir = 4;//右下
		shoot = 0;
		cpcy++;
	}
	else if(shoot == 5)//左上
	{
		bullet[cpcy] = (Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x = Knight.x + 48;
		bullet[cpcy]->y = Knight.y - 10;
		bullet[cpcy]->dir = 5;//左上
		shoot = 0;
		cpcy++;
	}
	else if(shoot == 6)//左下
	{
		bullet[cpcy] = (Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x = Knight.x + 40;
		bullet[cpcy]->y = Knight.y + 75;
		bullet[cpcy]->dir = 6;//左下
		shoot = 0;
		cpcy++;
	}


	for(i=0;i<=cpcy-1;i++)
	{
		if(bullet[i]->x >= 0 && bullet[i]->x <= 997)//子弹有效范围
		{
			BeginBatchDraw();
			if(bullet[i]->dir == 1)
			{
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1Y,NOTSRCERASE);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1,SRCINVERT);
				FlushBatchDraw();	
				bullet[i]->x+=50;
			}
			else if(bullet[i]->dir == 2)
			{
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1Y,NOTSRCERASE);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1,SRCINVERT);
				FlushBatchDraw();
				bullet[i]->x-=50;
			}
			else if(bullet[i]->dir == 3)
			{
				RotateImage(&Bullet1_o,&Bullet1,PI/0.67);
				RotateImage(&Bullet1Y_o,&Bullet1Y,PI/0.67);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1Y_o,NOTSRCERASE);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1_o,SRCINVERT);
				FlushBatchDraw();
				bullet[i]->y -= 50;
			}
			else if(bullet[i]->dir == 4)
			{
				RotateImage(&Bullet1_o,&Bullet1,PI/2.1);
				RotateImage(&Bullet1Y_o,&Bullet1Y,PI/2.1);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1Y_o,NOTSRCERASE);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1_o,SRCINVERT);
				FlushBatchDraw();
				bullet[i]->y += 50;
			}
			else if(bullet[i]->dir == 5)
			{
				RotateImage(&Bullet1_o,&Bullet1,PI/0.67);
				RotateImage(&Bullet1Y_o,&Bullet1Y,PI/0.67);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1Y_o,NOTSRCERASE);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1_o,SRCINVERT);
				FlushBatchDraw();
				bullet[i]->y -= 50;
			}
			else if(bullet[i]->dir == 6)
			{
				RotateImage(&Bullet1_o,&Bullet1,PI/2.1);
				RotateImage(&Bullet1Y_o,&Bullet1Y,PI/2.1);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1Y_o,NOTSRCERASE);
				putimage(bullet[i]->x,bullet[i]->y,&Bullet1_o,SRCINVERT);
				FlushBatchDraw();
				bullet[i]->y += 50;
			}
			EndBatchDraw();
		}		
	}
}