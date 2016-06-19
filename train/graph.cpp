#include "Train.h"
#include "global.h"

void Animation(void){
    PIMAGE img[100];
    char filename[100];
    int i;
    initgraph(900,675);
    setbkcolor(BLACK);
    for(i = 0;i < 75;i++){
        img[i] = newimage();
		sprintf(filename,"img/Animation/%d.jpg",i);
		getimage(img[i],filename);
    }
    for(i = 0;i < 75;i++){
        putimage(0,0,img[i]);
        delay_fps(20);
    }
    for(i = 0;i < 75;i++)   delimage(img[i]);
}

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
void drawobj(AniObj* obj,int trainID){
    PIMAGE train;
    char filename[100];
    switch(trainList.train[trainID] -> status){
        case RUN:
        train = newimage();
        sprintf(filename,"img/train/%dRUN.png",trainID);
        getimage(train,filename);
        putimage(obj -> x,obj -> y,train);
        delimage(train);
        break;
        case STATION:
        train = newimage();
        sprintf(filename,"img/train/%dSTATION.png",trainID);
        getimage(train,filename);
        putimage(obj -> x,obj -> y,train);
        delimage(train);
        break;
        case WAIT:
        train = newimage();
        sprintf(filename,"img/train/%dWAIT.png",trainID);
        getimage(train,filename);
        putimage(obj -> x,obj -> y,train);
        delimage(train);
        break;
        case STOP:
        train = newimage();
        sprintf(filename,"img/train/%dSTOP.png",trainID);
        getimage(train,filename);
        putimage(obj -> x,obj -> y,train);
        delimage(train);
        break;
    }
}

void drawComtrack(void){
    PIMAGE comtrack1,comtrack2;
    PIMAGE bg;
    //getimage(bg,"img/background.png");
    switch(commonTrackList.commonTrack[1] -> status){
        case BUSY:
        comtrack1 = newimage();
        getimage(comtrack1,"img/cts/1BUSY.png");
        putimage_alphablend(NULL,comtrack1,181,158,90);
        delimage(comtrack1);
        break;
        case ctWAIT:
        comtrack1 = newimage();
        getimage(comtrack1,"img/cts/1ctWAIT.png");
        putimage_alphablend(NULL,comtrack1,181,158,90);
        delimage(comtrack1);
        break;
        case FREE:
        comtrack1 = newimage();
        getimage(comtrack1,"img/cts/1FREE.png");
        putimage_alphablend(NULL,comtrack1,181,158,90);
        delimage(comtrack1);
        break;
    }
    switch(commonTrackList.commonTrack[2] -> status){
        case BUSY:
        comtrack2 = newimage();
        getimage(comtrack2,"img/cts/2BUSY.png");
        putimage_alphablend(NULL,comtrack2,260,217,90);
        delimage(comtrack2);
        break;
        case ctWAIT:
        comtrack2 = newimage();
        getimage(comtrack2,"img/cts/2ctWAIT.png");
        putimage_alphablend(NULL,comtrack2,260,217,90);
        delimage(comtrack2);
        break;
        case FREE:
        comtrack2 = newimage();
        getimage(comtrack2,"img/cts/2FREE.png");
        putimage_alphablend(NULL,comtrack2,260,217,90);
        delimage(comtrack2);
        break;
    }
}

DWORD WINAPI printGraph(LPVOID pPararneter)
{
	int i,trainID = 1;
	tacticsOrIns=0;

	for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
	{
	    if(trainList.train[i]!=NULL)
        {
            initobj(&obj[i],i); //初始化
        }
	}

    mouse_msg msg = {0};

    Animation();
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

		putimage(0,0,backGround);//背景部分

		setcolor(EGERGB(255, 236, 77));
		char s[100];
            sprintf(s,"运行时间 %.1f s",
                (double)(currentTime-startTime)/CLOCKS_PER_SEC);
            outtextxy(350, 60,s);

        char s1[23];
        switch(CTSTG){
            case JT: sprintf(s1,"交替策略"); break;
            case FFI: sprintf(s1,"快车优先策略"); break;
            case ASK: sprintf(s1,"询问策略"); break;
            case RAD: sprintf(s1,"随机策略"); break;
        }
        sprintf(s,"%s%s",CTW?"等待 ":"先到 ",s1);
        outtextxy(350,83,s);

		printStation();
        printTrainInformation();//图形化文字输出火车状态
        printCommonTrackInformation();;//图形化文字输出公共轨道状态
        printCheckPoint();
        drawComtrack();

        setfont(22, 0, "宋体");
        setfontbkcolor(EGERGB(164, 164, 164));

        if(tacticsOrIns==0)
        {
            setcolor(EGERGB(255, 236, 77));
            outtextxy(633, 81, "选择指令");
            setcolor(EGERGB(0,0,0));
            outtextxy(730, 80, "更改策略");
            insByMouse(msg,&trainID);//右侧按钮面板
        }
        else if(tacticsOrIns==1)
        {
            setcolor(EGERGB(255, 236, 77));
            outtextxy(730, 80, "更改策略");
            setcolor(EGERGB(0,0,0));
            outtextxy(633, 81, "选择指令");
            choiceTactics(msg);//右侧按钮面板
        }

        if(tacticsOrIns!=2)
        {
            setfont(22, 0, "宋体");
            if(msg.x>633&&msg.x<715&&msg.y>80&&msg.y<103)
            {
                if((int)msg.is_down()==0&& tacticsOrIns==1)
                {
                    setcolor(EGERGB(35, 248, 235));
                    outtextxy(633, 81, "选择指令");
                }
                else if((int)msg.is_down())
                {
                    tacticsOrIns=0;
                }
            }
            else if(msg.x>730&&msg.x<830&&msg.y>80&&msg.y<103)
            {
                if((int)msg.is_down()==0&& tacticsOrIns==0)
                {
                    setcolor(EGERGB(35, 248, 235));
                    outtextxy(730, 80, "更改策略");
                }
                else if((int)msg.is_down())
                {
                    tacticsOrIns=1;
                }
            }
        }
        printTrain();
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
        outtextxy(633, 120, "Train 1");
        outtextxy(633, 165, "Train 2");
        outtextxy(633, 210, "Train 3");

        setcolor(EGERGB(255, 236, 77));

        switch(*trainID)
        {
            case 1:outtextxy(633, 120, "Train 1");break;
            case 2:outtextxy(633, 165, "Train 2");break;
            case 3:outtextxy(633, 210, "Train 3");break;
        }

        if(msg.x>633&&msg.x<725&&msg.y>116&&msg.y<149)
        {
            if((int)msg.is_down()==0&& *trainID!=1)
            {
                setcolor(EGERGB(35, 248, 235));
                outtextxy(633, 120, "Train 1");
            }
            else if((int)msg.is_down())
            {
                *trainID = 1;
            }
        }
        else if(msg.x>633&&msg.x<725&&msg.y>161&&msg.y<194)
        {
            if((int)msg.is_down()==0&& *trainID!=2)
            {
                setcolor(EGERGB(35, 248, 235));
                outtextxy(633, 165, "Train 2");
            }
            else if((int)msg.is_down())
            {
                *trainID = 2;
            }
        }
        else if(msg.x>633&&msg.x<725&&msg.y>206&&msg.y<239)
        {
            if((int)msg.is_down()==0&& *trainID!=3)
            {
                setcolor(EGERGB(35, 248, 235));
                outtextxy(633, 210, "Train 3");
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
                if((double)(currentTime-mouseFlag)/CLOCKS_PER_SEC>0.5)
                {
                    if(trainList.train[*trainID]->spd<5)
                    {
                        button = newimage();
                        getimage(button,"img/button/spdup_2.png");
                        putimage(636,322,button);
                        delimage(button);

                        trainList.train[*trainID]->spd ++;

                        mouseFlag = clock();
                    }
                }
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
                if((double)(currentTime-mouseFlag)/CLOCKS_PER_SEC>0.5)
                {
                    if(trainList.train[*trainID]->spd>-5)
                    {
                        button = newimage();
                        getimage(button,"img/button/spddown_2.png");
                        putimage(737,322,button);
                        delimage(button);
                        trainList.train[*trainID]->spd --;
                        mouseFlag = clock();
                    }
                }
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

void printStation()
{
    PIMAGE station;

    if(trainList.train[1]->status==STATION&&trainList.train[1]->pos==trackList.track[1]->stationPos[0])
    {
        station = newimage();
        getimage(station,"img/station/station_1_1.png");
        putimage(80,167,station);
        delimage(station);
    }
    else
    {
        station = newimage();
        getimage(station,"img/station/station_1_0.png");
        putimage(80,167,station);
        delimage(station);
    }

    if(trainList.train[1]->status==STATION&&trainList.train[1]->pos==trackList.track[1]->stationPos[1]
       ||trainList.train[2]->status==STATION&&trainList.train[2]->pos==trackList.track[2]->stationPos[1])
    {
        station = newimage();
        getimage(station,"img/station/station_1_1.png");
        putimage(215,170,station);
        delimage(station);
    }
    else
    {
        station = newimage();
        getimage(station,"img/station/station_1_0.png");
        putimage(215,170,station);
        delimage(station);
    }

    if(trainList.train[2]->status==STATION&&trainList.train[2]->pos==trackList.track[2]->stationPos[0]
       ||trainList.train[3]->status==STATION&&trainList.train[3]->pos==trackList.track[3]->stationPos[0])
    {
        station = newimage();
        getimage(station,"img/station/station_0_1.png");
        putimage(332,246,station);
        delimage(station);
    }
    else
    {
        station = newimage();
        getimage(station,"img/station/station_0_0.png");
        putimage(332,246,station);
        delimage(station);
    }
}

void printCheckPoint()
{
    PIMAGE checkPoint;
    //车1
    if((trainList.train[1]->status==WAIT
       &&trainList.train[1]->pos<=commonTrackList.commonTrack[1]->track1in
       &&trainList.train[1]->pos>=commonTrackList.commonTrack[1]->track1in-100)
       ||(trainList.train[2]->status==WAIT
       &&trainList.train[2]->pos>=commonTrackList.commonTrack[1]->track2out
       &&trainList.train[2]->pos<=commonTrackList.commonTrack[1]->track2out+100))
    {
        putimage(208,118,checkPointRed);
    }
    else
    {
        putimage(208,118,checkPointGreen);
    }


    if((trainList.train[1]->status==WAIT
       &&trainList.train[1]->pos>=commonTrackList.commonTrack[1]->track1out
        &&trainList.train[1]->pos<=commonTrackList.commonTrack[1]->track1out+100)
        ||
        (trainList.train[2]->status==WAIT
       &&trainList.train[2]->pos<=commonTrackList.commonTrack[1]->track2in
       &&trainList.train[2]->pos>=commonTrackList.commonTrack[1]->track2in-100))
    {
        putimage(208,244,checkPointRed);
    }
    else
    {
        putimage(208,244,checkPointGreen);
    }
    //第二个
    if((trainList.train[2]->status==WAIT
       &&trainList.train[2]->pos>=commonTrackList.commonTrack[2]->track1out-100
        &&trainList.train[2]->pos<=commonTrackList.commonTrack[2]->track1out+100)
        ||
        (trainList.train[3]->status==WAIT
       &&trainList.train[3]->pos<=commonTrackList.commonTrack[2]->track2in+100
       &&trainList.train[3]->pos>=commonTrackList.commonTrack[2]->track2in-100))
    {
        putimage(224,244,checkPointRed);
    }
    else
    {
        putimage(224,244,checkPointGreen);
    }

    if((trainList.train[2]->status==WAIT
       &&trainList.train[2]->pos<=commonTrackList.commonTrack[2]->track1in+100
       &&trainList.train[2]->pos>=commonTrackList.commonTrack[2]->track1in-100)
       ||(trainList.train[3]->status==WAIT
       &&trainList.train[3]->pos>=commonTrackList.commonTrack[2]->track2out-100
       &&trainList.train[3]->pos<=commonTrackList.commonTrack[2]->track2out+100))
    {
        checkPoint = newimage();
        getimage(checkPoint,"img/checkPoint/checkPointRed.png");
        putimage(463,244,checkPoint);
        delimage(checkPoint);
    }
    else
    {
        checkPoint = newimage();
        getimage(checkPoint,"img/checkPoint/checkPointGreen.png");
        putimage(463,244,checkPoint);
        delimage(checkPoint);
    }
}

void choiceTactics(mouse_msg msg)
{
    if(CTW==0)
    {
        setcolor(EGERGB(255, 236, 77));
        outtextxy(730, 140, "先到");
        setcolor(EGERGB(0, 0, 0));
        outtextxy(633, 140, "等待");
    }
    else
    {
        setcolor(EGERGB(255, 236, 77));
        outtextxy(633, 140, "等待");
        setcolor(EGERGB(0, 0, 0));
        outtextxy(730, 140, "先到");
    }

    if(msg.x>633&&msg.x<715&&msg.y>140&&msg.y<170)
    {
        if((int)msg.is_down()==0&&CTW==0)
        {
            setcolor(EGERGB(35, 248, 235));
            outtextxy(633,270,"等待");
        }
        else if((int)msg.is_down())
        {
            CTW=1;
        }
    }
    else if(msg.x>730&&msg.x<780&&msg.y>140&&msg.y<170)
    {
        if((int)msg.is_down()==0&&CTW==1)
        {
            setcolor(EGERGB(35, 248, 235));
            outtextxy(730, 140, "先到");
        }
        else if((int)msg.is_down())
        {
            CTW=0;
        }
    }


    setcolor(EGERGB(0, 0, 0));
    outtextxy(633,270,"快车");outtextxy(730,270,"询问");
    outtextxy(633,320,"随机");outtextxy(730,320,"交替");

    setcolor(EGERGB(255, 236, 77));
    switch(CTSTG)
    {
        case FFI:outtextxy(633,270,"快车");break;
        case ASK:outtextxy(730,270,"询问");break;
        case RAD:outtextxy(633,320,"随机");break;
        case JT:outtextxy(730,320,"交替");
    }

    if(msg.x>633&&msg.x<715&&msg.y>270&&msg.y<300)
    {
        if((int)msg.is_down()==0&&CTSTG!=FFI)
        {
            setcolor(EGERGB(35, 248, 235));
            outtextxy(633,270,"快车");
        }
        else if((int)msg.is_down())
        {
            CTSTG=FFI;
        }
    }
    else if(msg.x>730&&msg.x<830&&msg.y>270&&msg.y<300)
    {
        if((int)msg.is_down()==0&&CTSTG!=ASK)
        {
            setcolor(EGERGB(35, 248, 235));
            outtextxy(730,270,"询问");
        }
        else if((int)msg.is_down())
        {
            CTSTG=ASK;
        }
    }
    else if(msg.x>633&&msg.x<715&&msg.y>320&&msg.y<350)
    {
        if((int)msg.is_down()==0&&CTSTG!=RAD)
        {
            setcolor(EGERGB(35, 248, 235));
            outtextxy(633,320,"随机");
        }
        else if((int)msg.is_down())
        {
            CTSTG=RAD;
        }
    }
    else if(msg.x>730&&msg.x<830&&msg.y>320&&msg.y<350)
    {
        if((int)msg.is_down()==0&&CTSTG!=JT)
        {
            setcolor(EGERGB(35, 248, 235));
            outtextxy(730,320,"交替");
        }
        else if((int)msg.is_down())
        {
            CTSTG=JT;
        }
    }
}

void printTrainInformation()
{
    int i;
    char str[20];
    setfont(18, 0, "宋体");

    setcolor(EGERGB(0, 0, 0));
    setfontbkcolor(EGERGB(164, 164, 164));

    outtextxy(205, 508, "速度");
    outtextxy(270, 508, "状态");

    for(i=1;i<=MAX_TRAIN_AMOUNT;i++)
    {
        if(trainList.train[i]!=NULL)
        {
            setcolor(EGERGB(0, 0, 0));
            setfontbkcolor(EGERGB(164, 164, 164));
            strcpy(str,"Train  ");
            str[6] = i+'0';
            outtextxy(110, 538+(i-1)*30, str);

            //itoa(trainList.train[i]->spd, str, 10);
            sprintf(str,"%d",trainList.train[i]->spd);
            outtextxy(215, 538+(i-1)*30, str);

            switch(trainList.train[i]->status)
            {
                case RUN:
                   // setcolor(EGERGB(91, 184, 91));
                    setfontbkcolor(EGERGB(91, 184, 91));
                    outtextxy(270, 538+(i-1)*30, "运行");
                    break;
                case STOP:
                    //setcolor(EGERGB(249, 168, 51));
                    setfontbkcolor(EGERGB(249, 168, 51));
                    outtextxy(270, 538+(i-1)*30, "停止");
                    break;
                case WAIT:
                    //setcolor(EGERGB(69, 171, 201));
                    setfontbkcolor(EGERGB(69, 171, 201));
                    outtextxy(270, 538+(i-1)*30, "等待");
                    break;
                case STATION:{
                    //setcolor(EGERGB(240, 240, 240));
                    setfontbkcolor(EGERGB(240, 240, 240));
                    outtextxy(270, 538+(i-1)*30, "停靠");
                    char s[100];
                    sprintf(s,"剩余时间 %.1f s",
                            trainList.train[i]->dockTime/(double)1000);
                    outtextxy(320, 538+(i-1)*30,s);
                    break;
                }
            }
        }
    }
}

void printCommonTrackInformation()
{
    int i;
    char str[20],num[20];
    setfont(18, 0, "宋体");

    setcolor(EGERGB(0, 0, 0));
    setfontbkcolor(EGERGB(164, 164, 164));

    outtextxy(650, 508, "状态");

    for(i=1;i<=MAX_COMMON_TRACK_AMOUNT;i++)
    {
        if(commonTrackList.commonTrack[i]!=NULL)
        {
            setcolor(EGERGB(0, 0, 0));
            setfontbkcolor(EGERGB(164, 164, 164));
            strcpy(str,"公共轨道  ");
            //itoa(i,num,10);
            sprintf(num,"%d",i);
            strcat(str,num);
            outtextxy(500, 538+(i-1)*50, str);

            switch(commonTrackList.commonTrack[i]->status)
            {
                case FREE:
                   // setcolor(EGERGB(91, 184, 91));
                    setfontbkcolor(EGERGB(69, 171, 201));
                    outtextxy(650, 538+(i-1)*50, "空闲");
                    break;

                case BUSY:
                   // setcolor(EGERGB(91, 184, 91));
                    setfontbkcolor(EGERGB(255, 50, 50));
                    outtextxy(650, 538+(i-1)*50, "占用");
                    break;

                case ctWAIT:
                   // setcolor(EGERGB(91, 184, 91));
                    setfontbkcolor(EGERGB(255, 190, 100));
                    outtextxy(650, 538+(i-1)*50, "等待第二辆车");
                    break;
            }
        }
    }
}

int askForPass(int train1, int train2)
{
    int i;
    cleardevice();
    for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
    {
        if(trainList.train[i]!=NULL)
        {
            posToGraph(&obj[i]);
        }
    }

    putimage(0,0,backGround);//背景部分
    printStation();
    printTrainInformation();//图形化文字输出火车状态
    printCommonTrackInformation();;//图形化文字输出公共轨道状态
    printTrain();
    printCheckPoint();

    setcolor(EGERGB(0, 0, 0));
    setfontbkcolor(EGERGB(164, 164, 164));
    outtextxy(617, 120, "请选择优先通过的火车序号！");

    mouse_msg msg = {0};

	for ( ; is_run(); delay_fps(60) )
	{
        while (mousemsg())
		{
			msg = getmouse();
		}

		setcolor(EGERGB(0, 0, 0));

        char s1[100];
        char s2[100];
        sprintf(s1,"Train %d",train1);
        outtextxy(640, 170,s1);

        char s[100];
        sprintf(s2,"Train %d",train2);
        outtextxy(640, 210,s2);

        if(msg.x>640&&msg.x<715&&msg.y>170&&msg.y<200)
        {
            if((int)msg.is_down()==0)
            {
                setcolor(EGERGB(35, 248, 235));
                outtextxy(640, 170,s1);
            }
            else if((int)msg.is_down())
            {
                return train1;
            }
        }
        else if(msg.x>640&&msg.x<715&&msg.y>210&&msg.y<240)
        {
            if((int)msg.is_down()==0)
            {
                setcolor(EGERGB(35, 248, 235));
                outtextxy(640, 210,s2);
            }
            else if((int)msg.is_down())
            {
                return train2;
            }
        }
	}
}

void printTrain()
{
    int i;
    for (i = 0; i < MAX_TRAIN_AMOUNT; i++)
        {
            if(trainList.train[i]!=NULL)
            {
                drawobj(&obj[i],i);
            }
        }
}
