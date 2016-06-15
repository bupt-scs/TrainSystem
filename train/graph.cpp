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
                obj->x = 495-(double)trainList.train[obj->trainID]->pos/6000*(495-185);
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
                obj->x = 185 + (double)(trainList.train[obj->trainID]->pos-8000)/6000*(495-185);
                obj->y = 133;
                obj->dir = 0;
            }
            else if(trainList.train[obj->trainID]->pos>=14000&&trainList.train[obj->trainID]->pos<16000)
            {
                obj->x = 495;
                obj->y = 133 + (double)(trainList.train[obj->trainID]->pos-14000)/2000*(220-133);
                obj->dir = 1;
            }
            break;
        case 3:
            if(trainList.train[obj->trainID]->pos>=0&&trainList.train[obj->trainID]->pos<4000)
            {
                obj->x = 240;
                obj->y = 418 - (double)trainList.train[obj->trainID]->pos/4000*(418-220);
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
                obj->y = 220 + (double)(trainList.train[obj->trainID]->pos-8000)/4000*(418-220);
                obj->dir = 1;
            }
            else if(trainList.train[obj->trainID]->pos>=12000&&trainList.train[obj->trainID]->pos<16000)
            {
                obj->x = 438 - (double)(trainList.train[obj->trainID]->pos-12000)/4000*(438-240);
                obj->y = 418;
                obj->dir = 0;
            }
            break;
    }
}

//初始化
void initobj(AniObj* obj,int trainID)
{
    obj->trainID = trainID;
    posToGraph(obj);
}

//根据属性值绘画
void drawobj(AniObj* obj)
{
	putimage(obj->x,obj->y,trainPic);
}

DWORD WINAPI printGraph(LPVOID pPararneter)
{
	AniObj obj[MAX_TRAIN_AMOUNT]; //定义对象数组
	int i,j;

	for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
	{
	    if(trainList.train[i]!=NULL)
        {
            initobj(&obj[i],i); //初始化
        }
	}

    mouse_msg msg = {0};

	for ( ; is_run(); delay_fps(60) )
	{
        while (mousemsg())
		{
			msg = getmouse();
		}

	    //WaitForSingleObject(hMutex,INFINITE);
        for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
        {
            if(trainList.train[i]!=NULL)
            {
                posToGraph(&obj[i]);
            }
        }

		cleardevice();
		putimage(0,0,backGround);

        insByMouse(msg);

        for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
        {
            if(trainList.train[i]!=NULL)
            {
                drawobj(&obj[i]);
            }
        }
        //ReleaseMutex(hMutex);
	}
	closegraph();
	exit(180);
}

void insByMouse(mouse_msg msg)
{
        //cleardevice();
        //  putimage(0,0,backGround);
        //ACC
        button = newimage();
        getimage(button,"img/button/acc_0.png");
        putimage(636,262,button);
        delimage(button);
        //BRK
        button = newimage();
        getimage(button,"img/button/brk_0.png");
        putimage(737,262,button);
        delimage(button);
        //SPDUP
        button = newimage();
        getimage(button,"img/button/spdup_0.png");
        putimage(636,322,button);
        delimage(button);
        //SPDDOWN
        button = newimage();
        getimage(button,"img/button/spddown_0.png");
        putimage(737,322,button);
        delimage(button);
        //PAUSE
        button = newimage();
        getimage(button,"img/button/sta_0.png");
        putimage(636,382,button);
        delimage(button);
        //QUIT
        button = newimage();
        getimage(button,"img/button/quit_0.png");
        putimage(737,382,button);
        delimage(button);

        if(msg.x>636&&msg.x<717&&msg.y>262&&msg.y<312)
        {
            if((int)msg.is_down()==0)
            {
                button = newimage();
                getimage(button,"img/button/acc_1.png");
                putimage(636,262,button);
                delimage(button);
            }
            else
            {
                button = newimage();
                getimage(button,"img/button/acc_2.png");
                putimage(636,262,button);
                delimage(button);
            }
        }
        else if(msg.x>737&&msg.x<817&&msg.y>262&&msg.y<312)
        {
            if((int)msg.is_down()==0)
            {
                button = newimage();
                getimage(button,"img/button/brk_1.png");
                putimage(737,262,button);
                delimage(button);
            }
            else
            {
                button = newimage();
                getimage(button,"img/button/brk_2.png");
                putimage(737,262,button);
                delimage(button);
            }
        }
        else if(msg.x>636&&msg.x<717&&msg.y>322&&msg.y<372)
        {
            if((int)msg.is_down()==0)
            {
                button = newimage();
                getimage(button,"img/button/spdup_1.png");
                putimage(636,322,button);
                delimage(button);
            }
            else
            {
                button = newimage();
                getimage(button,"img/button/spdup_2.png");
                putimage(636,322,button);
                delimage(button);
            }
        }
        else if(msg.x>737&&msg.x<817&&msg.y>322&&msg.y<372)
        {
            if((int)msg.is_down()==0)
            {
                button = newimage();
                getimage(button,"img/button/spddown_1.png");
                putimage(737,322,button);
                delimage(button);
            }
            else
            {
                button = newimage();
                getimage(button,"img/button/spddown_2.png");
                putimage(737,322,button);
                delimage(button);
            }
        }//第三行
        else if(msg.x>636&&msg.x<717&&msg.y>382&&msg.y<432)
        {
            if((int)msg.is_down()==0)
            {
                button = newimage();
                getimage(button,"img/button/sta_1.png");
                putimage(636,382,button);
                delimage(button);
            }
            else
            {
                button = newimage();
                getimage(button,"img/button/sta_2.png");
                putimage(636,382,button);
                delimage(button);
            }
        }
        else if(msg.x>737&&msg.x<817&&msg.y>382&&msg.y<432)
        {
            if((int)msg.is_down()==0)
            {
                button = newimage();
                getimage(button,"img/button/quit_1.png");
                putimage(737,382,button);
                delimage(button);
            }
            else
            {
                exit(100);
            }
        }
   //     ReleaseMutex(hMutex);
}
