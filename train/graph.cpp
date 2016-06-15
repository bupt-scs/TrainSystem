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
                obj->x = 496-(double)trainList.train[obj->trainID]->pos/6000*(496-185);
                obj->y = 220;
                obj->dir = 0;
            }
            else if(trainList.train[obj->trainID]->pos>=6000&&trainList.train[obj->trainID]->pos<8000)
            {
                obj->x = 185;
                obj->y = 220-(double)(trainList.train[obj->trainID]->pos-6000)/2000*(220-135);
                obj->dir = 1;
            }
            else if(trainList.train[obj->trainID]->pos>=8000&&trainList.train[obj->trainID]->pos<14000)
            {
                obj->x = 185 + (double)(trainList.train[obj->trainID]->pos-8000)/6000*(496-185);
                obj->y = 135;
                obj->dir = 0;
            }
            else if(trainList.train[obj->trainID]->pos>=14000&&trainList.train[obj->trainID]->pos<16000)
            {
                obj->x = 496;
                obj->y = 135 + (double)(trainList.train[obj->trainID]->pos-14000)/2000*(220-135);
                obj->dir = 1;
            }
            break;
        case 3:
            if(trainList.train[obj->trainID]->pos>=0&&trainList.train[obj->trainID]->pos<4000)
            {
                obj->x = 242;
                obj->y = 418 - (double)trainList.train[obj->trainID]->pos/4000*(418-220);
                obj->dir = 1;
            }
            else if(trainList.train[obj->trainID]->pos>=4000&&trainList.train[obj->trainID]->pos<8000)
            {
                obj->x = 242 + (double)(trainList.train[obj->trainID]->pos-4000)/4000*(440-242);
                obj->y = 220;
                obj->dir = 0;
            }
            else if(trainList.train[obj->trainID]->pos>=8000&&trainList.train[obj->trainID]->pos<12000)
            {
                obj->x = 440;
                obj->y = 220 + (double)(trainList.train[obj->trainID]->pos-8000)/4000*(418-220);
                obj->dir = 1;
            }
            else if(trainList.train[obj->trainID]->pos>=12000&&trainList.train[obj->trainID]->pos<16000)
            {
                obj->x = 440 - (double)(trainList.train[obj->trainID]->pos-12000)/4000*(440-242);
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
	int i,trainID = 1;

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

	    WaitForSingleObject(hMutex,INFINITE);
        for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
        {
            if(trainList.train[i]!=NULL)
            {
                posToGraph(&obj[i]);
            }
        }

		cleardevice();

		putimage(0,0,backGround);

        insByMouse(msg,&trainID);//右侧按钮面板

        for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
        {
            if(trainList.train[i]!=NULL)
            {
                drawobj(&obj[i]);
            }
        }
        ReleaseMutex(hMutex);
	}
	closegraph();
	exit(180);
}

void insByMouse(mouse_msg msg,int *trainID)
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

        setcolor(EGERGB(0, 0, 0));
        setfontbkcolor(EGERGB(164, 164, 164));
        setfont(25, 0, "宋体");
        outtextxy(639, 100, "Train 1");
        outtextxy(639, 145, "Train 2");
        outtextxy(639, 190, "Train 3");

        setcolor(EGERGB(255, 236, 77));

        switch(*trainID)
        {
            case 1:outtextxy(639, 100, "Train 1");break;
            case 2:outtextxy(639, 145, "Train 2");break;
            case 3:outtextxy(639, 190, "Train 3");break;
        }

        if(msg.x>639&&msg.x<725&&msg.y>96&&msg.y<129)
        {
            if((int)msg.is_down()==0&& *trainID!=1)
            {
                setcolor(EGERGB(35, 248, 235));
                outtextxy(639, 100, "Train 1");
            }
            else if((int)msg.is_down())
            {
                *trainID = 1;
            }
        }
        else if(msg.x>639&&msg.x<725&&msg.y>141&&msg.y<174)
        {
            if((int)msg.is_down()==0&& *trainID!=2)
            {
                setcolor(EGERGB(35, 248, 235));
                outtextxy(639, 145, "Train 2");
            }
            else if((int)msg.is_down())
            {
                *trainID = 2;
            }
        }
        else if(msg.x>639&&msg.x<725&&msg.y>186&&msg.y<219)
        {
            if((int)msg.is_down()==0&& *trainID!=3)
            {
                setcolor(EGERGB(35, 248, 235));
                outtextxy(639, 190, "Train 3");
            }
            else if((int)msg.is_down())
            {
                *trainID = 3;
            }
        }

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

                inputIns.trainID = *trainID;
                inputIns.ins = ACC;
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

                inputIns.trainID = *trainID;
                inputIns.ins = BRK;
            }
        }//第二行
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

                trainList.train[*trainID]->spd ++;
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

                trainList.train[*trainID]->spd --;
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

                inputIns.trainID = *trainID;
                inputIns.ins = DOCK;
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
     //   char str[20];
      //  itoa(trainList.train[4]->spd, str, 10);
       // outtextxy(0, 0, str);
   //     ReleaseMutex(hMutex);
}
