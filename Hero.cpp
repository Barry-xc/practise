/********************************************************
���ܣ��������������ʿ������������꣬��ӡ��ʿ����ӡ����
********************************************************/
#include"main.h"

//ȫ�ֱ���
int intervein=0;		//�����
HERO Knight;			//��ʿ�ṹ��
Weapon Weapon1;			//�����ṹ��
Bullet* bullet[1000000];//�ӵ��ṹ��
int cpcy=0;				//�ӵ��ṹ�������±�		
int shoot=15;			//�ӵ��������
int count=0;			//�ӵ�ʱ�������
int bullet_speed = 4;	//�ӵ�����ʱ����

//��������
extern IMAGE Hero_R;			//��
extern IMAGE Hero_mask_R;		//������
extern IMAGE Hero_R_2;			//����
extern IMAGE Hero_mask_R_2;		//��������ͼ
extern IMAGE Hero_L;			//��
extern IMAGE Hero_mask_L;		//������ͼ
extern IMAGE Hero_L_2;			//����
extern IMAGE Hero_mask_L_2;		//��������ͼ
extern IMAGE Weapon1_L;			//������ǹ��
extern IMAGE Weapon1_L_Y;		//������ǹ������ͼ
extern IMAGE Weapon1_R;			//������ǹ
extern IMAGE Weapon1_R_Y;		//������ǹ����ͼ
extern IMAGE Weapon1_R_o;		//��ת��
extern IMAGE Weapon1_R_Y_o;		//��ת��
extern IMAGE Weapon1_L_o;		//��ת��
extern IMAGE Weapon1_L_Y_o;		//��ת��
extern IMAGE Bullet1;			//Ӣ���ӵ�
extern IMAGE Bullet1Y;			//Ӣ���ӵ�����ͼ
extern IMAGE Bullet1_o;			//��ת��
extern IMAGE Bullet1Y_o;		//��ת��

/********************************************************
��������:���ݼ������룬������ʿ�ṹ������ֵ������ֵ
����	:��
����ֵ	:��
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
��������:��ӡ������������ʿ
����	:��
����ֵ	:��
*********************************************************/
void Print_Hero()
{
	Sleep(50);
	BeginBatchDraw();

	//�����ƶ�
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
	
	//�����ƶ�
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
��������:��ӡ����������Ӣ������
����	:��
����ֵ	:��
*********************************************************/
void Print_Weapon()
{
	BeginBatchDraw();
	if(Knight.dir==1 && Weapon1.dir==4)//Ӣ���ң�ǹ��
	{
		RotateImage(&Weapon1_R_o,&Weapon1_R,PI/175);
		RotateImage(&Weapon1_R_Y_o,&Weapon1_R_Y,PI/175);
		BeginBatchDraw();
		putimage(Knight.x,Knight.y+35,&Weapon1_R_Y_o,NOTSRCERASE);
		putimage(Knight.x,Knight.y+35,&Weapon1_R_o,SRCINVERT);
		EndBatchDraw();
	}
	else if(Knight.dir==1 && Weapon1.dir==1)//Ӣ���ң�ǹ��
	{
		RotateImage(&Weapon1_R_o,&Weapon1_R,PI/0.666);
		RotateImage(&Weapon1_R_Y_o,&Weapon1_R_Y,PI/0.666);
		putimage(Knight.x+10,Knight.y+20,&Weapon1_R_Y_o,NOTSRCERASE);
		putimage(Knight.x+10,Knight.y+20,&Weapon1_R_o,SRCINVERT);
	}
	else if(Knight.dir==1 && Weapon1.dir==2)//Ӣ���ң�ǹ��
	{
		RotateImage(&Weapon1_R_o,&Weapon1_R,PI/2);
		RotateImage(&Weapon1_R_Y_o,&Weapon1_R_Y,PI/2);
		putimage(Knight.x+5,Knight.y+5,&Weapon1_R_Y_o,NOTSRCERASE);
		putimage(Knight.x+5,Knight.y+5,&Weapon1_R_o,SRCINVERT);
	}
	else if(Knight.dir==0 && Weapon1.dir==3)//Ӣ����ǹ��
	{
		RotateImage(&Weapon1_L_o,&Weapon1_L,PI/180);
		RotateImage(&Weapon1_L_Y_o,&Weapon1_L_Y,PI/180);
		putimage(Knight.x-5,Knight.y+35,&Weapon1_L_Y_o,NOTSRCERASE);
		putimage(Knight.x-5,Knight.y+35,&Weapon1_L_o,SRCINVERT);
	}
	else if(Knight.dir==0 && Weapon1.dir==1)//Ӣ����ǹ��
	{
		RotateImage(&Weapon1_L_o,&Weapon1_L,PI/2);
		RotateImage(&Weapon1_L_Y_o,&Weapon1_L_Y,PI/2);
		putimage(Knight.x+35,Knight.y+15,&Weapon1_L_Y_o,NOTSRCERASE);
		putimage(Knight.x+35,Knight.y+15,&Weapon1_L_o,SRCINVERT);
	}
	else if(Knight.dir==0 && Weapon1.dir==2)//Ӣ����ǹ��
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
��������:����⵽�ո���������ӵ��ṹ�������±�
����	:��
����ֵ	:��
*********************************************************/
void Hero_Shoot()//����ӵ�����
{
	if(GetAsyncKeyState(VK_SPACE))
	{
		count++;
		if(Knight.dir==1 && Weapon1.dir==4)	//Ӣ���ң�������
		{
			shoot=0;
			if( count % bullet_speed == 0)
			{
				shoot=1;
				count=0;
			}
		}
		else if(Knight.dir==1 && Weapon1.dir==1)//Ӣ���ң�������
		{
			shoot = 0;
			if( count % bullet_speed == 0)
			{
				shoot = 3;
				count = 0;
			}
		}
		else if(Knight.dir==1 && Weapon1.dir==2)//Ӣ���ң�������
		{
			shoot = 0;
			if( count % bullet_speed == 0)
			{
				shoot = 4;
				count = 0;
			}	
		}
		else if(Knight.dir==0 && Weapon1.dir==1)//Ӣ����������
		{
			shoot = 0;
			if( count % bullet_speed == 0)
			{
				shoot = 5;
				count = 0;
			}
		}
		else if(Knight.dir==0 && Weapon1.dir==3)//Ӣ����������
		{
			shoot=0;
			if(count % bullet_speed == 0)
			{
				shoot = 2;
				count = 0;
			}
		}
	
		else if(Knight.dir==0 && Weapon1.dir==2)//Ӣ����������
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
��������:�����ӵ��ṹ�������е����кϷ����꣬��ӡ�ӵ�
����	:��
����ֵ	:��
*********************************************************/
void One_Shoot()
{
	int i;
	loadimage(&Bullet1,_T("D:\\miniԪ����ʿ\\�ز�\\bullet\\rpk���ǹ.png"));
	loadimage(&Bullet1Y,_T("D:\\miniԪ����ʿ\\�ز�\\bullet\\rpk���ǹY.png"));

	if(shoot==1)//����
	{
		bullet[cpcy]=(Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x=Knight.x+75;
		bullet[cpcy]->y=Knight.y+40;
		bullet[cpcy]->dir=1;//����
		shoot=0;
		cpcy++;
	}
	else if(shoot==2)//����
	{
		bullet[cpcy]=(Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x=Knight.x-20;
		bullet[cpcy]->y=Knight.y+37;
		bullet[cpcy]->dir=2;//����
		shoot=0;
		cpcy++;
	}
	else if(shoot == 3)//����
	{
		bullet[cpcy] = (Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x = Knight.x + 13;
		bullet[cpcy]->y = Knight.y - 5;
		bullet[cpcy]->dir = 3;//����
		shoot = 0;
		cpcy++;		
	}
	else if(shoot == 4)//����
	{
		bullet[cpcy] = (Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x = Knight.x + 19;
		bullet[cpcy]->y = Knight.y + 80;
		bullet[cpcy]->dir = 4;//����
		shoot = 0;
		cpcy++;
	}
	else if(shoot == 5)//����
	{
		bullet[cpcy] = (Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x = Knight.x + 48;
		bullet[cpcy]->y = Knight.y - 10;
		bullet[cpcy]->dir = 5;//����
		shoot = 0;
		cpcy++;
	}
	else if(shoot == 6)//����
	{
		bullet[cpcy] = (Bullet *)malloc(sizeof(Bullet));
		bullet[cpcy]->x = Knight.x + 40;
		bullet[cpcy]->y = Knight.y + 75;
		bullet[cpcy]->dir = 6;//����
		shoot = 0;
		cpcy++;
	}


	for(i=0;i<=cpcy-1;i++)
	{
		if(bullet[i]->x >= 0 && bullet[i]->x <= 997)//�ӵ���Ч��Χ
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