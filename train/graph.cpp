#include "Train.h"
#include "global.h"

void posToGraph(AniObj* obj)
{
    switch(trainList.train[obj->trainID]->trackID)
    {
        case 1:
            if(trainList.train[obj->trainID]->pos>=0&&trainList.train[obj->trainID]->pos<4000)
            {
                obj->x = 100;
                obj->y = 274-(double)trainList.train[obj->trainID]->pos/4000*(274-80);
                obj->dir = 1;
            }
            else if(trainList.train[obj->trainID]->pos>=4000&&trainList.train[obj->trainID]->pos<6000)
            {
                obj->x = (double)(trainList.train[obj->trainID]->pos-4000)/2000*(185-100)+100;
                obj->y = 80;
                obj->dir = 0;
            }
            else if(trainList.train[obj->trainID]->pos>=6000&&trainList.train[obj->trainID]->pos<10000)
            {
                obj->x = 185;
                obj->y = 80+(double)(trainList.train[obj->trainID]->pos-6000)/4000*(274-80);
                obj->dir = 1;
            }
            else
            {
                obj->x = 185-(double)(trainList.train[obj->trainID]->pos-10000)/2000*(185-100);
                obj->y = 274;
                obj->dir = 0;
            }
            break;
        case 2:
            if(trainList.train[obj->trainID]->pos>=0&&trainList.train[obj->trainID]->pos<6000)
            {
                obj->x = 492-(double)trainList.train[obj->trainID]->pos/6000*(492-185);
                obj->y = 220;
                obj->dir = 0;
            }
            else if(trainList.train[obj->trainID]->pos>=6000&&trainList.train[obj->trainID]->pos<8000)
            {
                obj->x = 185;
                obj->y = 220-(double)(trainList.train[obj->trainID]->pos-6000)/2000*(220-133);
                obj->dir = 1;
            }
            else if(trainList.train[obj->trainID]->pos>=8000&&trainList.train[obj->trainID]->pos<14000)
            {
                obj->x = 185 + (double)(trainList.train[obj->trainID]->pos-8000)/6000*(492-185);
                obj->y = 133;
                obj->dir = 0;
            }
            else if(trainList.train[obj->trainID]->pos>=14000&&trainList.train[obj->trainID]->pos<16000)
            {
                obj->x = 492;
                obj->y = 133 + (double)(trainList.train[obj->trainID]->pos-14000)/2000*(220-133);
                obj->dir = 1;
            }
            break;
        case 3:
            if(trainList.train[obj->trainID]->pos>=0&&trainList.train[obj->trainID]->pos<4000)
            {
                obj->x = 240;
                obj->y = 417 - (double)trainList.train[obj->trainID]->pos/4000*(417-220);
                obj->dir = 1;
            }
            else if(trainList.train[obj->trainID]->pos>=4000&&trainList.train[obj->trainID]->pos<8000)
            {
                obj->x = 240 + (double)(trainList.train[obj->trainID]->pos-4000)/4000*(438-240);
                obj->y = 220;
                obj->dir = 0;
            }
            else if(trainList.train[obj->trainID]->pos>=8000&&trainList.train[obj->trainID]->pos<12000)
            {
                obj->x = 438;
                obj->y = 220 + (double)(trainList.train[obj->trainID]->pos-8000)/4000*(417-220);
                obj->dir = 1;
            }
            else if(trainList.train[obj->trainID]->pos>=12000&&trainList.train[obj->trainID]->pos<16000)
            {
                obj->x = 438 - (double)(trainList.train[obj->trainID]->pos-12000)/4000*(438-240);
                obj->y = 417;
                obj->dir = 0;
            }
            break;

    }

}

//��ʼ��
void initobj(AniObj* obj,int trainID)
{
    obj->trainID = trainID;
    posToGraph(obj);
}

//��������ֵ�滭
void drawobj(AniObj* obj)
{
	putimage(obj->x,obj->y,trainPic);
}

DWORD WINAPI printGraph(LPVOID pPararneter)
{
	AniObj obj[MAX_TRAIN_AMOUNT]; //�����������
	int i,j;

	for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
	{
	    if(trainList.train[i]!=NULL)
        {
            initobj(&obj[i],i); //��ʼ��
        }
	}

	for ( ; is_run(); delay_fps(60) )
	{
        for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
        {
            if(trainList.train[i]!=NULL)
            {
                posToGraph(&obj[i]);
            }
        }

		cleardevice();
		putimage(0,0,backGround);

        for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
        {
            if(trainList.train[i]!=NULL)
            {
                drawobj(&obj[i]);
            }
        }
	}
	closegraph();
}

DWORD WINAPI insByMouse(LPVOID pPararneter)
{
	setfont(18, 0, "����");

	mouse_msg msg = {0};
	for ( ; is_run(); delay_fps(60))
	{
		//��ȡ�����Ϣ�����������ȴ����ȴ�������ϢΪֹ
		//���Ƶأ��к�kbhit��������ĺ���MouseHit�����ڼ����û�������Ϣ
		while (mousemsg())
		{
			msg = getmouse();
		}

		//��ʽ�����Ϊ�ַ��������ں������
		//msg��flag������ο��ĵ�����mouse_msg_e, mouse_flag_e������

		cleardevice();
        putimage(0,0,backGround);
		xyprintf(0, 0, "x = %10d  y = %10d",
			msg.x, msg.y, msg.wheel);
		xyprintf(0, 20, "move  = %d down  = %d up    = %d",
			(int)msg.is_move(),
			(int)msg.is_down(),
			(int)msg.is_up());
		xyprintf(0, 40, "left  = %d mid   = %d right = %d",
			(int)msg.is_left(),
			(int)msg.is_mid(),
			(int)msg.is_right());
		xyprintf(0, 60, "wheel = %d  wheel rotate = %d",
			(int)msg.is_wheel(),
			msg.wheel);
	}
	closegraph();
}