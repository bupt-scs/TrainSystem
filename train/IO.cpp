#include "Train.h"
#include "global.h"
void startShow(){
    char ch;
    FILE* fptr = fopen("file/hello.txt","r");
    while(fscanf(fptr,"%c",&ch)!=EOF)
        printf("%c",ch);
    printf("\n                          欢迎使用我们的小火车调度系统~\n");
    fclose(fptr);
}


void writeTrain(int ID,int trackID,unsigned long pos,int spd)
{
    if(trainList.train[ID]==NULL)
    {
        trainList.train[ID] =(Train*) malloc(sizeof(Train));
        trainList.amount++;
    }
	trainList.train[ID]->ID = ID;
	trainList.train[ID]->trackID = trackID;
	trainList.train[ID]->pos = pos;
	trainList.train[ID]->spd = spd;
	trainList.train[ID]->status = STOP; //默认为运行
}
void writeTrack(int ID,unsigned long length,int cycle,int stationAmount,unsigned long stationPos[])
{
    int i=1;
    if(trackList.track[ID]==NULL)
    {
        trackList.amount++;
        trackList.track[ID] =(Track*) malloc(sizeof(Track));
    }
    trackList.track[ID]->ID = ID;
    trackList.track[ID]->length = length;
    trackList.track[ID]->cycle = cycle;
    trackList.track[ID]->stationAmount = stationAmount;
    for(i=1;i<=stationAmount;i++)
    {
        trackList.track[ID]->stationPos[i-1] = stationPos[i-1];
    }
}
void writeCommonTrack(int ID,int track1,int track2,int track1in,int track2in,int track1out,int track2out)
{
    if(commonTrackList.commonTrack[ID] == NULL)
    {
        commonTrackList.commonTrack[ID] =(CommonTrack*) malloc(sizeof(CommonTrack));
        commonTrackList.amount++;
    }
    commonTrackList.commonTrack[ID]->track1 = track1;
    commonTrackList.commonTrack[ID]->track2 = track2;
    commonTrackList.commonTrack[ID]->track1in = track1in;
    commonTrackList.commonTrack[ID]->track1out = track1out;
    commonTrackList.commonTrack[ID]->track2in = track2in;
    commonTrackList.commonTrack[ID]->track2out = track2out;

}
//检查commonTrackList.track[ID],若为NULL,在这里为新的CommonTrack申请空间,并写入各参数。
//若不为NULL,将参数覆盖写入。 最后检查所有Train的位置,判断占用情况,并写入commonTrackList.track[ID]->status]

void dataInit()
{
	char s[25],ch;
	int i,j,ID,trackID,pos,spd,length,cycle,stationAmount;
    unsigned long stationPos[MAX_STATION_AMOUNT];
//------------------------------火车部分---------------------------------
    for(i=0;i<=MAX_TRAIN_AMOUNT;i++)
    {
        trainList.train[i] = NULL;
    }
	FILE *fptr = fopen("file/trainConfig.txt","r");

	if(fptr==NULL)
	{
		printf("打开火车信息文件失败,请重试。");
	}
    //读取部分
	fgets(s,1000,fptr);
	fscanf(fptr,"%d",&trainList.amount);
	fgets(s,1000,fptr);


	for(i=1;i<=trainList.amount;i++)
	{
		fgets(s,1000,fptr);

		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&ID);
		fgets(s,1000,fptr);

		trainList.train[ID]=(Train*)malloc(sizeof(Train));

        trainList.train[ID]->ID = ID;
		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&trainList.train[ID]->trackID);
		fgets(s,1000,fptr);

		fgets(s,1000,fptr);
		fscanf(fptr,"%ld",&trainList.train[ID]->pos);
		fgets(s,1000,fptr);

		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&trainList.train[ID]->spd);
		fgets(s,1000,fptr);

		trainList.train[ID]->status = STOP;
	}

	//输出当前状况
    showTrain();
    fclose(fptr);

	printf("是否需要更改\"小火车配置\"的信息？Y/N:");
    ch = getchar();
    while(ch!='Y'&&ch!='N'&&ch!='y'&&ch!='n')
    {
        printf("请输入Y或N决定是否修改\"小火车配置\"的信息:");
        ch=getchar();
    }
    if(ch=='N'||ch=='n')
        ;
    else
    {
        ID=99999;
        puts(hr);
        printf("以上为现有火车,请问需要进行什么操作？\n1.增加新的小火车\n2.修改已有小火车信息\n3.删除小火车\n4.设定终了\n请输入(1~4):");
        fflush(stdin);
        ch = getchar();
        while(ch!='4')
        {
            switch(ch)
            {
                case '1':
                    printf("请输入新加入火车编号,该编号小于%d:",MAX_TRAIN_AMOUNT);
                    scanf("%d",&ID);
                    while(trainList.train[ID]!=NULL||ID>MAX_TRAIN_AMOUNT)
                    {
                        printf("已存在该火车或输入不符合规范！请重新输入！（该编号小于%d）:",MAX_TRAIN_AMOUNT);
                        scanf("%d",&ID);
                    }
                    printf("将新加入火车放置在哪条轨道上:");
                    scanf("%d",&trackID);
                    printf("请输入新加入火车的坐标:");
                    scanf("%d",&pos);
                    printf("请输入新加入火车速度:");
                    scanf("%d",&spd);
                    writeTrain(ID,trackID,pos,spd);

                    break;
                case '2':
                    printf("请输入待修改的火车编号,该编号小于%d:",MAX_TRAIN_AMOUNT);
                    scanf("%d",&ID);
                    while(trainList.train[ID]==NULL||ID>MAX_TRAIN_AMOUNT)
                    {
                        printf("不存在该火车或输入不符合规范！请重新输入！（该编号小于%d）:",MAX_TRAIN_AMOUNT);
                        scanf("%d",&ID);
                    }
                    printf("请输入需要修改的火车编号,该编号小于%d:",MAX_TRAIN_AMOUNT);
                    scanf("%d",&ID);
                    printf("该火车放置在哪条轨道上:");
                    scanf("%d",&trackID);
                    printf("该火车坐标为:");
                    scanf("%d",&pos);
                    printf("该火车速度为:");
                    scanf("%d",&spd);
                    writeTrain(ID,trackID,pos,spd);
                    break;
                case '3':
                    printf("请问要删除哪辆火车:");
                    scanf("%d",&ID);
                    while(trainList.train[ID]==NULL||ID>MAX_TRAIN_AMOUNT)
                    {
                        printf("不存在该火车或输入不符合规范！请重新输入:");
                        scanf("%d",&ID);
                    }
                    free(trainList.train[ID]);
                    trainList.train[ID] = NULL;
                    trainList.amount--;
                    break;
            }
            showTrain();
            puts(hr);
            printf("以上为现有火车,请问需要进行什么操作？\n1.增加新的小火车\n2.修改已有小火车信息\n3.删除小火车\n4.设定终了\n请输入(1~4):");
            fflush(stdin);
            ch = getchar();
        }
        fptr = fopen("file/trainConfig.txt","w");
        fprintf(fptr,"火车总数:\n%d\n",trainList.amount);
        for(i=1;i<=MAX_TRAIN_AMOUNT;i++)
        {
            if(trainList.train[i]!=NULL)
            {
                fprintf(fptr,"\n列车ID:\n%d\n",trainList.train[i]->ID);
                fprintf(fptr,"所在轨道:\n%d\n",trainList.train[i]->trackID);
                fprintf(fptr,"坐标:\n%d\n",trainList.train[i]->pos);
                fprintf(fptr,"速度:\n%d\n",trainList.train[i]->spd);
            }
        }
        fclose(fptr);
    }
    system("cls");
    startShow();
    printf("内容已保存\n");
    showTrain();
    printf("此为当前火车信息,按回车键进行下一步。");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("cls");
//----------------------------------单一轨道部分---------------------------
    startShow();
	//初始化指针
	for(i=0;i<=MAX_TRACK_AMOUNT;i++)
    {
        trackList.track[i] = NULL;
    }

	fptr = fopen("file/trackConfig.txt","r");
	if(fptr==NULL)
	{
		printf("打开轨道信息文件失败,请重试。");
	}
	fgets(s,1000,fptr);						//轨道总数

	fscanf(fptr,"%d",&trackList.amount);
	fgets(s,1000,fptr);

	for(i=1;i<=trackList.amount;i++)
	{
		fgets(s,1000,fptr);

		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&ID);
		fgets(s,1000,fptr);

        trackList.track[ID] =(Track*) malloc(sizeof(Track));
        trackList.track[ID]->ID = ID;

		fgets(s,1000,fptr);
		fscanf(fptr,"%u",&trackList.track[ID]->length);
		fgets(s,1000,fptr);

		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&trackList.track[ID]->cycle);
		fgets(s,1000,fptr);

		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&trackList.track[ID]->stationAmount);
		fgets(s,1000,fptr);

		fgets(s,1000,fptr);
		for(j=0;j<trackList.track[ID]->stationAmount;j++)
		{
			fscanf(fptr,"%d",&trackList.track[ID]->stationPos[j]);
			fgets(s,1000,fptr);
		}
	}
	showTrack();
	puts(hr);
    fclose(fptr);

	printf("是否需要更改\"轨道配置\"的信息？Y/N:");
    ch = getchar();
    while(ch!='Y'&&ch!='N'&&ch!='y'&&ch!='n')
    {
        printf("请输入Y或N决定是否修改\"轨道配置\"的信息:");
        ch=getchar();
    }
    if(ch=='N'||ch=='n')
        ;
    else
    {
        ID=99999;
        puts(hr);
        printf("以上为现有轨道,请问需要进行什么操作？\n1.增加新的轨道\n2.修改已有轨道信息\n3.设定终了\n请输入(1~3):");
        fflush(stdin);
        ch = getchar();
        while(ch!='3')
        {
            switch(ch)
            {
                case '1':
                    printf("请输入新加入轨道编号,该编号小于%d:",MAX_TRACK_AMOUNT);
                    scanf("%d",&ID);
                    while(trackList.track[ID]!=NULL||ID>MAX_TRACK_AMOUNT)
                    {
                        printf("已存在该轨道或输入不符合规范！请重新输入！（该编号小于%d）:",MAX_TRAIN_AMOUNT);
                        scanf("%d",&ID);
                    }
                    printf("轨道长度为:");
                    scanf("%d",&length);
                    printf("是否环路？（是为1,否为0）:");
                    scanf("%d",&cycle);
                    printf("共有几个车站？");
                    scanf("%d",&stationAmount);
                    printf("各车站坐标（每行输入一个坐标）:\n");
                    for(i=0;i<stationAmount;i++)
                    {
                        scanf("%d",&stationPos[i]);
                    }
                    writeTrack(ID,length,cycle,stationAmount,stationPos);
                    break;
                case '2':
                    printf("请输入待修改的轨道编号,该编号小于%d:",MAX_TRACK_AMOUNT);
                    scanf("%d",&ID);
                    while(trackList.track[ID]==NULL||ID>MAX_TRACK_AMOUNT)
                    {
                        printf("不存在该轨道或输入不符合规范！请重新输入！（该编号小于%d）:",MAX_TRAIN_AMOUNT);
                        scanf("%d",&ID);
                    }
                    printf("轨道长度为:");
                    scanf("%d",&length);
                    printf("是否环路？（是为1,否为0）:");
                    scanf("%d",&cycle);
                    printf("共有几个车站？");
                    scanf("%d",&stationAmount);
                    printf("各车站坐标（每行输入一个坐标）:\n");
                    for(i=0;i<stationAmount;i++)
                    {
                        scanf("%d",&stationPos[i]);
                    }
                    writeTrack(ID,length,cycle,stationAmount,stationPos);
                    break;
            }
            showTrack();
            puts(hr);
            printf("以上为现有轨道,请问需要进行什么操作？\n1.增加新的轨道\n2.修改已有轨道信息\n3.设定终了\n请输入(1~3):");
            fflush(stdin);
            ch = getchar();
        }
        fptr = fopen("file/trackConfig.txt","w");
        fprintf(fptr,"轨道总数:\n%d\n",trackList.amount);
        for(i=1;i<=MAX_TRACK_AMOUNT;i++)
        {
            if(trackList.track[i]!=NULL)
            {
                fprintf(fptr,"\n轨道ID:\n%d\n",trackList.track[i]->ID);
                fprintf(fptr,"轨道长度:\n%u\n",trackList.track[i]->length);
                fprintf(fptr,"是否环路:\n%d\n",trackList.track[i]->cycle);
                fprintf(fptr,"车站总数:\n%d\n",trackList.track[i]->stationAmount);
                fprintf(fptr,"各车站坐标:\n");
                for(j=0;j<trackList.track[i]->stationAmount;j++)
                {
                    fprintf(fptr,"%d\n",trackList.track[i]->stationPos[j]);
                }
            }
        }
        fclose(fptr);
    }
    system("cls");
    startShow();
    printf("内容已保存\n");
    showTrack();
    printf("此为当前\"轨道\"信息,按回车键进行下一步。");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("cls");
//-------------------------------------公共轨道部分-------------------------------------
    startShow();
    for(i=0;i<=MAX_COMMON_TRACK_AMOUNT;i++)
    {
        commonTrackList.commonTrack[i] = NULL;
    }

	fptr = fopen("file/commontrackConfig.txt","r");
	if(fptr==NULL)
	{
		printf("打开\"公共轨道\"信息文件失败,请重试。");
	}

	fgets(s,1000,fptr);						//公共轨道总数
	fscanf(fptr,"%d",&commonTrackList.amount);
	fgets(s,1000,fptr);

	for(i=1;i<=commonTrackList.amount;i++)
	{
		fgets(s,1000,fptr);

		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&ID);
		fgets(s,1000,fptr);

        commonTrackList.commonTrack[ID] =(CommonTrack*)malloc(sizeof(CommonTrack));
        commonTrackList.commonTrack[ID]->ID = ID;

		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&commonTrackList.commonTrack[ID]->track1);
        fgets(s,1000,fptr);
		fscanf(fptr,"%d",&commonTrackList.commonTrack[ID]->track2);
	//	printf("%d%d",commonTrackList.commonTrack[ID]->track1,commonTrackList.commonTrack[ID]->track2);
		fgets(s,1000,fptr);

        fgets(s,1000,fptr);
		fscanf(fptr,"%d",&commonTrackList.commonTrack[ID]->track1in);
		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&commonTrackList.commonTrack[ID]->track1out);
		fgets(s,1000,fptr);

        fgets(s,1000,fptr);
		fscanf(fptr,"%d",&commonTrackList.commonTrack[ID]->track2in);
		fgets(s,1000,fptr);
		fscanf(fptr,"%d",&commonTrackList.commonTrack[ID]->track2out);
		fgets(s,1000,fptr);
	}
	//输出当前状况
    showCommonTrack();
    puts(hr);
    printf("请确认公共轨道信息,回车键开始运行调控系统。");
    getchar();
    fflush(stdin);
	fclose(fptr);
	system("cls");
	startShow();
	printf("1.先到询问人工\n2.先到快车优先\n3.先到随机策略\n4.等待询问人工\n5.等待快车优先\n6.等待随机策略\n\n");
	printf("请选择公共轨道调度策略(输入?获取策略说明):");
	ch = getchar();
	fflush(stdin);
	do{
        while((ch<'1'||ch>'6')&&(ch!='?'))
        {
            fflush(stdin);
            printf("请重新输入:");
            ch = getchar();
        }
        if(ch=='?'||ch=='？'){
            printf("\n策略说明：\n\t先到询问人工，先到快车优先，先到随机策略：\n\t\t");
            printf("列车到达公共轨道入口后就进入，除非有另一辆车要同时进入公共轨道。\n\t\t");
            printf("若有两辆车同时进入公共轨道，则按询问人工/快车优先/随机处理。\n\n\t");
            printf("等待询问人工，等待快车优先，等待随机策略：\n\t\t");
            printf("列车到达公共轨道入口后停车等待，直到有另一辆车也要进入公共轨道。\n\t\t");
            printf("按询问人工/快车优先/随机处理。\n\n");
            printf("请选择公共轨道调度策略(输入？获取策略说明):");
            ch = getchar();
        }
	}
	while(ch<'1'||ch>'6');

	if(ch<='3') CTW=0;
	else CTW=1;
	 if(CTW) printf("等待");
    switch(ch){
        case '1':case '4': CTSTG=ASK;printf("询问人工策略已选择\n");break;
        case '2':case '5': CTSTG=FFI;printf("快车先行策略已选择\n");break;
        case '3':case '6': CTSTG=RAD;printf("随机策略已选择\n");break;
    }

}

void showTrain()
{
	int i,j;
	//输出当前状况
	puts(hr);
	printf("列车总数为:%d\n目前各列车状况:\n",trainList.amount);
	for(i=0;i<MAX_TRAIN_AMOUNT;i++)
	{
	    if(trainList.train[i]!=NULL)
        {
            trainList.train[i]->defaultDockTime=(clock_t)3000;
            printf("编号为%d的火车,当前行驶在第%d条轨道,位置为%d,\t速度为%d,状态为%s,\t站点停靠时间为%d ms,",
                trainList.train[i]->ID,
                trainList.train[i]->trackID,
                trainList.train[i]->pos,
                abs(trainList.train[i]->spd),
                strTrainState(trainList.train[i]->status),
                trainList.train[i]->defaultDockTime
            );

            if(trainList.train[i]->spd<0)
                printf("逆时针运行\t");
            else
                printf("顺时针运行\t");
            if(trackList.track[trainList.train[i]->trackID]!=NULL)
            {
                if(trainList.train[i]->spd>0)
                {
                    for(j=1;j<=(trainList.train[i]->pos*20/trackList.track[trainList.train[i]->trackID]->length);j++)
                        printf("-");
                    printf("^^");
                    printf("+");
                    for(j=1;j<=20-trainList.train[i]->pos*20/trackList.track[trainList.train[i]->trackID]->length;j++)
                        printf("-");
                }
                else
                {
                    for(j=1;j <= trainList.train[i]->pos*20/trackList.track[trainList.train[i]->trackID]->length;j++)
                        printf("-");
                    printf("+");
                    printf("^^");
                    for(j=1;j <= 20-trainList.train[i]->pos*20/trackList.track[trainList.train[i]->trackID]->length;j++)
                        printf("-");
                }
            }
            printf("\n");
        }
	}
}


void showTrack()
{
    puts(hr);
    int i,j;
	printf("轨道总数为:%d\n其中各轨道参数:\n",trackList.amount);
	for(i=0;i<MAX_TRACK_AMOUNT;i++)
	{
        if(trackList.track[i]!=NULL)
        {
            printf("编号为%d的轨道,总长度为%u,",
			trackList.track[i]->ID,
			trackList.track[i]->length
            );
            if(trackList.track[i]->cycle==1)
            {
                printf("为环路,");
            }
            else
            {
                printf("并非环路,");
            }

            if(!trackList.track[i]->stationAmount) printf("无车站");
            else{
                printf("共有%d个车站,他们的坐标分别为",
                trackList.track[i]->stationAmount);
                for(j=0;j<trackList.track[i]->stationAmount;j++){
                    printf(" %d",trackList.track[i]->stationPos[j]);
                }
            }

            printf("\n");
        }
	}
}
void fshowTrack(char* fName)
{
    FILE* f=fopen(fName,"a");
    fputs(hr,f);
    int i,j;
	fprintf(f,"轨道总数为:%d\n其中各轨道参数:\n",trackList.amount);
	for(i=0;i<MAX_TRACK_AMOUNT;i++)
	{
        if(trackList.track[i]!=NULL)
        {
            fprintf(f,"编号为%d的轨道,总长度为%u,",
			trackList.track[i]->ID,
			trackList.track[i]->length
            );
            if(trackList.track[i]->cycle==1)
            {
               fprintf(f,"为环路,");
            }
            else
            {
                fprintf(f,"并非环路,");
            }

            if(!trackList.track[i]->stationAmount) fprintf(f,"无车站");
            else{
                fprintf(f,"共有%d个车站,他们的坐标分别为",
                trackList.track[i]->stationAmount);
                for(j=0;j<trackList.track[i]->stationAmount;j++){
                    fprintf(f," %d",trackList.track[i]->stationPos[j]);
                }
            }

           fprintf(f,"\n");
        }
	}
	fclose(f);
}

void showCommonTrack()
{
    int i,j;
    printf("公共轨道的总数为:%d\n其中各轨道参数:\n",commonTrackList.amount);
	for(i=0;i<MAX_COMMON_TRACK_AMOUNT;i++)
	{
        if(commonTrackList.commonTrack[i]!=NULL)
        {
            printf("第%d组的公共轨道,为第%d与%d号轨道的公共部分,",
                commonTrackList.commonTrack[i]->ID,
                commonTrackList.commonTrack[i]->track1,
                commonTrackList.commonTrack[i]->track2
            );
            printf("在第%d条轨道中,入口坐标为%d,出口坐标为%d,",
                commonTrackList.commonTrack[i]->track1,
                commonTrackList.commonTrack[i]->track1in,
                commonTrackList.commonTrack[i]->track1out
            );
            printf("在第%d条轨道中,入口坐标为%d,出口坐标为%d,",
                commonTrackList.commonTrack[i]->track2,
                commonTrackList.commonTrack[i]->track2in,
                commonTrackList.commonTrack[i]->track2out
            );
            printf("目前状态:");
            if(commonTrackList.commonTrack[i]->status ==FREE)
            {
                printf("空闲\n");
            }
            else if(commonTrackList.commonTrack[i]->status == BUSY)
            {
                for(j=0;j<MAX_TRAIN_AMOUNT;j++)
                {
                    if(trainList.train[j]!=NULL)
                    {
                        if(trainList.train[j]->trackID==commonTrackList.commonTrack[i]->track1)
                        {
                            if(trainList.train[j]->pos>commonTrackList.commonTrack[i]->track1in&&
                               trainList.train[j]->pos<commonTrackList.commonTrack[i]->track1out)
                                printf("已被%d占用\n",trainList.train[j]->ID);
                        }
                        if(trainList.train[j]->trackID==commonTrackList.commonTrack[i]->track2)
                        {
                            if(trainList.train[j]->pos>commonTrackList.commonTrack[i]->track2in&&
                               trainList.train[j]->pos<commonTrackList.commonTrack[i]->track2out)
                                printf("已被%d占用\n",trainList.train[j]->ID);
                        }
                    }
                }
            }
            else
            {
                printf("处于预定中\n");
            }
        }
	}
}
void fshowCommonTrack(char* fName)
{
    FILE* f=fopen(fName,"a");
    int i,j;
    fprintf(f,"\n公共轨道的总数为:%d\n其中各轨道参数:\n",commonTrackList.amount);
	for(i=0;i<MAX_COMMON_TRACK_AMOUNT;i++)
	{
        if(commonTrackList.commonTrack[i]!=NULL)
        {
            fprintf(f,"公共轨道 %d ,为 %d 与 %d 号轨道的公共部分,",
                commonTrackList.commonTrack[i]->ID,
                commonTrackList.commonTrack[i]->track1,
                commonTrackList.commonTrack[i]->track2
            );
            fprintf(f,"在 %d 号轨道中,入口坐标为%d,出口坐标为%d,",
                commonTrackList.commonTrack[i]->track1,
                commonTrackList.commonTrack[i]->track1in,
                commonTrackList.commonTrack[i]->track1out
            );
            fprintf(f,"在 %d 号条轨道中,入口坐标为%d,出口坐标为%d\n",
                commonTrackList.commonTrack[i]->track2,
                commonTrackList.commonTrack[i]->track2in,
                commonTrackList.commonTrack[i]->track2out
            );
        }
	}
	fprintf(f,"\n");
	fclose(f);
}


void fLog(char show,char* fileName,int trainID,char* msg,clock_t curTime){

    FILE* f=fopen(fileName,"a");
    fprintf(f,"[%d ms]",curTime);
    int i;
	//输出当前状况
	if(show){
        fprintf(f,"--------------------------------------------------------------------------\n");

        //fshowCommonTrack(fileName);
        //fprintf(f,"\n");

        fprintf(f," 列车总数为:%d\n目前各列车状况:\n",trainList.amount);
        for(i=0;i<MAX_TRAIN_AMOUNT;i++)
        {
            if(trainList.train[i]!=NULL)
            {
                fprintf(f,"第%d辆火车,当前行驶在第%d条轨道,位置为%d,速度为%d,状态为%s",
                trainList.train[i]->ID,
                trainList.train[i]->trackID,
                trainList.train[i]->pos,
                trainList.train[i]->spd,
                strTrainState(trainList.train[i]->status)
                );
                fprintf(f,"\n\n");
            }
        }
	}

	if(trainID>=0) fprintf(f,"列车 %d : ",trainID);
	fputs(msg,f);
	fprintf(f,"\n\n");
	fclose(f);
}

//在moveAllTrain()中调用。
//将用户对列车的指令写入指令列表trainIns[],在早期版本中,这个函数从文件读入指令,将当前时间的指令写入trainIns[]
void userIns(clock_t curTime,clock_t frameDur)
{

    double time;
    int ID;
    char s[10];
    FILE* fptr;
    fptr = fopen("file/insConfig.txt","r");
    for(;fscanf(fptr,"%lf",&time)==1;)
    {
        time*=CLOCKS_PER_SEC;
        fscanf(fptr,"%s",s);
        fscanf(fptr,"%d",&ID);
        if(curTime<=time&&(curTime+frameDur)>=time)
        {
            trainIns[ID] = enumIns(s);
        }
    }
    fclose(fptr);
    if(inputIns.trainID!=9999)
    {
        trainIns[inputIns.trainID] = inputIns.ins;
        inputIns.trainID = 9999;
    }
}


DWORD WINAPI insDuringRun(LPVOID pPararneter)
{
    int ID=0;
    char s[10],ch;
	while(1)
	{
	    fflush(stdin);
        ch = getchar();
        WaitForSingleObject(hMutex,INFINITE);
        printf("指令列表:\n");
        printf("1.ACC(启动)  2.BRK(停止)  3.DOCK(停靠)  4.SPD(变速)  q.修改策略  其余输入取消指令:");
        ch = getchar();
        fflush(stdin);
        switch(ch){
            case '1':
                printf("请输入需要启动的列车序号:");
                scanf("%d",&ID);
                if(ID<=0||ID>MAX_TRAIN_AMOUNT)
                {
                    printf("输入有误!");
                    Sleep(1);
                }
                else
                {
                    inputIns.ins = ACC;
                    inputIns.trainID = ID;
                }
                break;
            case '2':
                printf("请输入需要停止的列车序号:");
                scanf("%d",&ID);
                if(ID<=0||ID>MAX_TRAIN_AMOUNT)
                {
                    printf("输入有误!");
                    Sleep(1);
                }
                else
                {
                    inputIns.ins = BRK;
                    inputIns.trainID = ID;
                }
                break;
            case '3':
                printf("请输入在下一站点停靠的列车序号:");
                scanf("%d",&ID);
                if(ID<=0||ID>MAX_TRAIN_AMOUNT)
                {
                    printf("输入有误!");
                    Sleep(1);
                }
                else
                {
                    inputIns.ins = DOCK;
                    inputIns.trainID = ID;
                }
                break;
            case '4':
                printf("请输入需要修改速度的列车序号:");
                scanf("%d",&ID);
                if(ID<=0||ID>MAX_TRAIN_AMOUNT)
                {
                    printf("输入有误!");
                    Sleep(1);
                }
                else
                {
                    printf("速度原来为:%d,修改为:",trainList.train[ID]->spd);
                    scanf("%d",&trainList.train[ID]->spd);
                    printf("速度已修正");
                }
                break;
            case 'q':case 'Q':
                printf("1.先到询问人工\n2.先到快车优先\n3.先到随机策略\n4.等待询问人工\n5.等待快车优先\n6.等待随机策略\n\n");
                printf("请选择公共轨道调度策略(输入?获取策略说明):");
                fflush(stdin);
                ch = getchar();
                do{
                    while((ch<'1'||ch>'6')&&(ch!='?'&&ch!='？'))
                    {
                        fflush(stdin);
                        printf("请重新输入:");
                        ch = getchar();
                    }
                    if(ch=='?'||ch=='？'){
                        printf("\n策略说明：\n\t先到询问人工，先到快车优先，先到随机策略：\n\t\t");
                        printf("列车到达公共轨道入口后就进入，除非有另一辆车要同时进入公共轨道。\n\t\t");
                        printf("若有两辆车同时进入公共轨道，则按询问人工/快车优先/随机处理。\n\n\t");
                        printf("等待询问人工，等待快车优先，等待随机策略：\n\t\t");
                        printf("列车到达公共轨道入口后停车等待，直到有另一辆车也要进入公共轨道。\n\t\t");
                        printf("按询问人工/快车优先/随机处理。\n\n");
                        printf("请选择公共轨道调度策略(输入？获取策略说明):");
                        ch = getchar();
                    }
                }
                while(ch<'1'||ch>'6');

                if(ch<='3') CTW=0;
                else CTW=1;
                switch(ch){
                    case '1':case '4': CTSTG=ASK;printf("ASK策略已选择\n");break;
                    case '2':case '5': CTSTG=FFI;printf("FFI策略已选择\n");break;
                    case '3':case '6': CTSTG=RAD;printf("RAD策略已选择\n");break;
                }
                if(CTW) printf("CTW策略已选择\n");
            default:
                break;
        }
        fflush(stdin);
        ReleaseMutex(hMutex);
	}
}
