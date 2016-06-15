#include "Train.h"
#include "global.h"
//找train前方的第一个车站位置
unsigned long findNextStation(Train* train){
	unsigned long nextPos;//返回这个
	Track* curTrack=trackList.track[train->trackID];
	unsigned long pos=train->pos;
	unsigned long length=curTrack->length;


	if( (train->spd)>0 ){
		int i=0;
		for(;i<curTrack->stationAmount;i++)
			if(curTrack->stationPos[i]>=pos) break;
		if(pos>curTrack->stationPos[i])//火车在最后一个站之后
			if(curTrack->cycle) nextPos=curTrack->stationPos[0];
			else nextPos=length-1;
		else nextPos=curTrack->stationPos[i];
		return nextPos;
	}
	else{
		int i=0;
		for(;i<curTrack->stationAmount;i++)
			if(curTrack->stationPos[i]>=pos) break;

		if(pos>=curTrack->stationPos[i]) nextPos=curTrack->stationPos[i];
		else if(i==0)//车在第一个站及之前
				if(curTrack->cycle)
					nextPos=curTrack->stationPos[curTrack->stationAmount-1];
				else nextPos=0;
			 else nextPos=curTrack->stationPos[i-1];
		return nextPos;
	}
}

//向指定的列车传递ins指令，列车根据ins和自己的status进行一步行动，坐标变换与帧时长frameDur有关。
void moveTrain(Train* train,Ins ins,clock_t curTime,clock_t frameDur)
{
    switch(ins){
        case DOCK:
            fLog(0,"Log.txt",train->ID,"接收指令 DOCK(靠站)",curTime);
            printf("\n列车 ID %d 接收了DOCK(靠站)指令\n",train->ID);
            break;
        case BRK:
            fLog(0,"Log.txt",train->ID,"接收指令 BRK(制动)",curTime);
            printf("\n列车 ID %d 接收了BRK(制动)指令\n",train->ID);
            break;
        case ACC:
            fLog(0,"Log.txt",train->ID,"接收指令 ACC(前进)",curTime);
            printf("\n列车 ID %d 接收了ACC(前进)指令\n",train->ID);
            break;
    }
	//状态转换
	switch(train->status){
		case STOP:
			if(ins==ACC) train->status=RUN;
			break;
		case STATION:
			if(ins==ACC) train->status=RUN;
			break;

		case RUN:
			if(ins==DOCK) {
				train->status=STATION;
				train->dockTime=train->defaultDockTime;
				//printf("ddt=%ld\n",train->defaultDockTime);
			}
			if(ins==BRK) train->status=STOP;
			break;
		case WAIT:
			if(ins==DOCK) {
				train->status=STATION;
				train->dockTime=train->defaultDockTime;
				break;
			}
			if(ins==BRK) {train->status=STOP; break;}

			int i=commonTrackList.amount;//遍历公共轨道,找到自己的。如果FREE了就RUN
			int id=0;
			while(i&&id<MAX_COMMON_TRACK_AMOUNT){
				CommonTrack* ct=commonTrackList.commonTrack[id];
				if(ct!=NULL){
					i--;
					unsigned long cp=train->pos;
					unsigned long np=cp+train->spd*frameDur;
					unsigned long ctin1=min(ct->track1in,ct->track1out);
					unsigned long ctout1=max(ct->track1in,ct->track1out);
					unsigned long ctin2=min(ct->track2in,ct->track2out);
					unsigned long ctout2=max(ct->track2in,ct->track2out);
					if(ct->track1==train->trackID||ct->track2==train->trackID)
					{
					    if((train->spd>0&&cp<=ctin1&&ctin1<=np)||(train->spd<0&&cp>=ctout1&&ctout1>=np))
						if(ct->track1==train->trackID&&ct->status==FREE){
                            train->status=RUN;
                            trainWaiting[ct->ID]=NULL;
                            FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                                fprintf(log,"列车ID %d 等待的公共轨道%d已空闲，列车启动。\n",
                                        train->ID,ct->ID);
                            fclose(log);
                            //fLog(0,"Log.txt",train->ID,"公共轨道已可以进入,启动",curTime);
                            printf("\n列车ID %d 等待的公共轨道已空闲，列车启动。\n",train->ID);
						}
						if((train->spd>0&&cp<=ctin2&&ctin2<=np)||(train->spd<0&&cp>=ctout2&&ctout2>=np))
						if(ct->track2==train->trackID&&ct->status==FREE){
                            train->status=RUN;
                            trainWaiting[ct->ID]=NULL;
                            FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                                fprintf(log,"列车ID %d 等待的公共轨道%d已空闲，列车启动。\n",
                                        train->ID,ct->ID);
                            fclose(log);
                            //fLog(0,"Log.txt",train->ID,"公共轨道已可以进入,启动",curTime);
                            printf("\n列车ID %d 等待的公共轨道已空闲，列车启动。\n",train->ID);
						}
					}
				}
				id++;
			}
			break;
	}

	int x=(train->spd)*frameDur;
	Track* curTrack=trackList.track[train->trackID];

	switch(train->status){//坐标增加
		case RUN:
			if(curTrack->cycle){
				train->pos=(train->pos+x+curTrack->length)%(curTrack->length);
				break;
			}
			else{//非环路：到头就停
				if(train->spd>0)
					train->pos=min((train->pos+x),(curTrack->length-1));
				else
					train->pos=max((train->pos+x),0);
				break;
			}

		case STATION://到站就停，否则走。非环路的轨道两端是站
        {
            unsigned long nextStation=findNextStation(train);
			long X=nextStation-train->pos;
			char s[255];
			//sprintf(s,"\nnext %u \nX %d \nx %d\n",nextStation,X,x);
            //fLog(0,"Log.txt",train->ID,s,curTime);
			if(X==0){//靠站，停够时间就走
                //fLog(0,"Log.txt",train->ID,"AT STATION",curTime);
                if(train->dockTime==train->defaultDockTime){
                    printf("列车 %d 将停靠 %.3f秒\n",train->ID,train->dockTime/1000.0);
                    FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                        fprintf(log,"列车 %d 到站：将停靠 %.3f秒\n",train->ID,train->dockTime/1000.0);
                    fclose(log);
                }

				train->dockTime-=frameDur;

                //printf("还剩%d\n",train->dockTime);
				if(train->dockTime<0) {
                    train->status=RUN;
                    printf("列车 %d 离站\n",train->ID);
                    FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                        fprintf(log,"列车 %d 离站\n",train->ID);
                    fclose(log);
                    //fLog(0,"Log.txt",train->ID,"LEAVE STATION",curTime);
				}
				break;
			}
			//火车驶过一圈，位移与速度异号，修正：
			if(X>0&&train->spd<0) X-=curTrack->length;
			if(X<0&&train->spd>0) X+=curTrack->length;

			train->pos+=abs(X)<abs(x)?X:x;
			train->pos%=curTrack->length;
        }
	}
}

void judgeCommonTrack(CommonTrack* cT,Train* enter[],int ei,clock_t curTime){
    int ii;

    printf("\n时间：%.3f s:列车",
           curTime/(double)CLOCKS_PER_SEC);
    for(ii=0;ii<=ei;ii++){
        printf(" %d",enter[ii]->ID);
        if(ii!=ei) printf(" 和");
    }
    printf(" 在公共轨道%d入口处等待调度\n",cT->ID);

    FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
        fprintf(log,"列车");
        for(ii=0;ii<=ei;ii++){
            fprintf(log," %d",enter[ii]->ID);
            if(ii!=ei) fprintf(log," 和");
        }
        fprintf(log," 在公共轨道%d入口处等待调度\n",cT->ID);

    switch(CTSTG){
                    case ASK:{
                        //showTrain();
                        printf("输入准许进入的列车ID：");
                        int idin; fflush(stdin);scanf("%d",&idin);
                        printf("列车 ID %d 受授权进入公共轨道，其他列车停车等待\n",idin);
                        fprintf(log,"列车 ID %d 受授权进入公共轨道，其他列车停车等待\n",idin);
                        //fLog(0,"Log.txt",idin,"用户准入公共轨道。其他列车停车等待。",curTime);
                        for(;ei>=0;ei--)
                            if(enter[ei]->ID!=idin) {
                                enter[ei]->status=WAIT;
                                trainWaiting[cT->ID]=enter[ei];
                            }
                            else enter[ei]->status=RUN;
                            cT->status=BUSY;
                        break;
                    }

                    case FFI:{
                        Train* tin=abs(enter[0]->spd)>abs(enter[1]->spd)?enter[0]:enter[1];
                        printf("列车 ID %d 速度更快，优先进入公共轨道，其他列车停车等待\n",tin->ID);
                        fprintf(log,"列车 ID %d 速度更快，优先进入公共轨道，其他列车停车等待\n",tin->ID);
                        //fLog(0,"Log.txt",tin->ID,"快速车优先进入公共轨道。其他列车停车等待",curTime);
                        for(;ei>=0;ei--)
                            enter[ei]->status=WAIT;
                        tin->status=RUN;
                        cT->status=BUSY;
                        break;
                    }

                    case RAD:{
                        int ridin=enter[curTime/233%2]->ID;
                        printf("列车 ID %d 被随机选中进入公共轨道，其他列车停车等待\n",ridin);
                        fprintf(log,"列车 ID %d 被随机选中进入公共轨道，其他列车停车等待\n",ridin);
                        //fLog(0,"Log.txt",ridin,"被随机选中进入公共轨道。其他列车停车等待",curTime);
                        for(;ei>=0;ei--)
                            if(enter[ei]->ID!=ridin) enter[ei]->status=WAIT;
                            else enter[ei]->status=RUN;
                        cT->status=BUSY;
                        break;
                    }
    }
    fclose(log);
}

void dealCommonTrack(CommonTrack* cT,Ins ins[],clock_t curTime,clock_t frameDur){
    //printf("[DEBUG]dealCommonTrack ID %d\n Status %s\n",cT->ID,strCommonTrackState(cT->status));
	if(cT->status!=FREE&&cT->status!=ctWAIT) cT->status=FREE;
	if(cT->status==ctWAIT&&(!CTW)) cT->status=FREE;
	int i=trainList.amount;//遍历火车,检查公共轨道状态
	int id=0;
	unsigned long in1=min(cT->track1in,cT->track1out);
	unsigned long out1=max(cT->track1in,cT->track1out);
	unsigned long in2=min(cT->track2in,cT->track2out);
	unsigned long out2=max(cT->track2in,cT->track2out);

	while(i&&(id<MAX_TRAIN_AMOUNT)){
		if(trainList.train[id]!=NULL){
			i--;
			Train* t=trainList.train[id];
			if(t->trackID==cT->track1){
				if(t->pos>=in1&&t->pos<=out1) cT->status=BUSY;
			}
			if(t->trackID==cT->track2){
				if(t->pos>=in2&&t->pos<=out2) cT->status=BUSY;
			}
		}
		id++;
	}

    //fLog(0,"Log.txt",-1,strCommonTrackState(cT->status),curTime);//debug输出：公共轨道状态

	Train* enter[4]; int ei=0;//ei是enter[]的下标
	for(i=0;i<4;i++) enter[i]=NULL;
	//printf("[DEBUG]move.c line M1\n");
	i=trainList.amount;//遍历火车,将所有将要进入cT的火车记到enter[]
	id=0;
	while(i&&(id<MAX_TRAIN_AMOUNT)){
		if(trainList.train[id]!=NULL){
			i--;
			Train* t=trainList.train[id];
			if(t->status==RUN){
				unsigned long cp=t->pos;
				unsigned long np=cp+(t->spd)*frameDur;
				if(t->trackID==cT->track1){
					if(t->spd>0)
						if(cp<in1&&in1<=np){
							enter[ei]=t;
							ei++;
							FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
							fprintf(log,"列车 ID %d 到达公共轨道 %d 入口\n",t->ID,cT->ID);
							fclose(log);
						}
					if(t->spd<0)
                        if(np<=out1&&out1<cp){
							enter[ei]=t;
							ei++;
							FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
							fprintf(log,"列车 ID %d 到达公共轨道 %d 入口\n",t->ID,cT->ID);
							fclose(log);
						}
				}

				if(t->trackID==cT->track2){
					if(t->spd>0)
						if(cp<in2&&in2<=np){
							enter[ei]=t;
							ei++;
							FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
							fprintf(log,"列车 ID %d 到达公共轨道 %d 入口\n",t->ID,cT->ID);
							fclose(log);
						}
					if(t->spd<0)
                        if(np<=out2&&out2<cp){
							enter[ei]=t;
							ei++;
							FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
							fprintf(log,"列车 ID %d 到达公共轨道 %d 入口\n",t->ID,cT->ID);
							fclose(log);
						}
				}
			}
		}
		id++;
	}
	ei--;//ei现在是enter中最后一个车的下标

//	char eis[33];
//	sprintf(eis,"%d",ei);
//    fLog(0,"Log.txt",-1,eis,curTime);
//    if(cT->status==FREE)
//    fLog(0,"Log.txt",-1,"F",curTime);
//    else if(cT->status==ctWAIT)
//        fLog(0,"Log.txt",-1,"ctW",curTime);
//    else if(cT->status==BUSY)
//        fLog(0,"Log.txt",-1,"B",curTime);//debug输出ei和公共轨道状态

    switch(cT->status){
        case BUSY:
            for(;ei>=0;ei--){
                enter[ei]->status=WAIT;//公共轨道忙，想进的不准进
                printf("\n列车 ID %d 到达公共轨道入口,公共轨道有车，停车等待。\n",enter[ei]->ID);
                fLog(0,"Log.txt",enter[ei]->ID,"公共轨道有车，停车等待。",curTime);
            }
            break;

        case FREE:
            if(ei>0)//有2车想进
                judgeCommonTrack(cT,enter,ei,curTime);
            else if(ei==0){
                    if(CTW){
                        enter[ei]->status=WAIT;
                        trainWaiting[cT->ID]=enter[ei];
                        cT->status=ctWAIT;
                        fLog(0,"Log.txt",enter[ei]->ID,"到达公共轨道入口，停车等待",curTime);
                        printf("\n列车 ID %d 到达公共轨道入口，停车等待。\n",enter[ei]->ID);
                    }
                    else{
                        printf("\n%.3f s：列车%d 进入公共轨道 %d\n",
                        curTime/(double)CLOCKS_PER_SEC,enter[ei]->ID,cT->ID);
                        FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                            fprintf(log,"列车%d 进入公共轨道 %d\n",enter[ei]->ID,cT->ID);
                        fclose(log);
                    }
            }
            break;

        case ctWAIT:
            if(ei>=0){
                 ei++;
                 enter[ei]=trainWaiting[cT->ID];
                 judgeCommonTrack(cT,enter,ei,curTime);
                 cT->status=BUSY;
            }
            break;
    }
}

void checkCrash(clock_t curTime,clock_t frameDur){    //判断撞车
int i1 = trainList.amount,i2 = trainList.amount,id1,id2;
int64 x1,x2;
for(id1 = 0;i1&&id1<MAX_TRAIN_AMOUNT;id1++)     //遍历火车
    if(trainList.train[id1] != NULL){
        i1--;
        Train* t1 = trainList.train[id1];
        if(t1->status == RUN)  //找出正在运行的火车
            for(id2 = 0, i2 = trainList.amount;i2&&id2<MAX_TRAIN_AMOUNT;id2++)  //再次遍历火车= =
                if(trainList.train[id2] != NULL){
                    i2--;
                    if(id2 != id1){
                        Train* t2 = trainList.train[id2];
                        if(t1->trackID == t2->trackID){    //找到同一轨道上的火车
                            x1 = (int64)t2->pos - (int64)t1->pos;     //初距离
                            x2 = (int64)t2->pos + t2->spd * frameDur - (int64)t1->pos - t1->spd * frameDur;//单位时间后距离
                            if(t2->status == WAIT || t2->status == STOP)
                                if(abs(x1 * x2) != x1 * x2 || x2 == 0) {
                                    trainIns[t1->ID] = BRK;
                                    printf("列车ID %d 前方有静止列车 ID %d，制动。\n",t1->ID,t2->ID);
                                    fLog(0,"Log.txt",t1->ID,"前方有静止车辆",curTime);
                                }
                            if(t2->status == RUN || t2->status == STATION)
                                if(abs(x1 * x2) != x1 * x2 || x2 ==0)
                                    if(abs(t1->spd * t2->spd) != t1->spd * t2->spd){     //迎面相撞
                                        printf("列车ID %d 和 %d 将迎面相遇，两车制动。\n",t1->ID,t2->ID);
                                        FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                                            fprintf(log,"列车ID %d 和 %d 将迎面相遇，两车制动。\n",t1->ID,t2->ID);
                                        fclose(log);
                                        trainIns[t1->ID] = BRK; trainIns[t2->ID] = BRK;     //两车均制动
                                    }
                                    else{ //追尾
                                        int tid=(abs(t1->spd) > abs(t2->spd)) ? (t1->ID) : (t2->ID);//后车制动
                                        printf("列车 ID %d 将与前车追尾：制动。\n",tid);
                                        fLog(0,"Log.txt",tid,"将与前车追尾",curTime);
                                        trainIns[tid] = BRK;
                                    }
                        }
                    }
                }
    }
}

void moveAllTrain(clock_t curTime,clock_t frameDur)
{
    int i;
    //fLog(1,"Log.txt",-1,"",curTime);//每帧运行日志
	for(i=0;i<MAX_TRAIN_AMOUNT;i++)
		trainIns[i]=HOLD;
	userIns(curTime,frameDur);

	i=commonTrackList.amount;//遍历公共轨道
	int id=0;
	while(i&&(id<MAX_COMMON_TRACK_AMOUNT)){
		if(commonTrackList.commonTrack[id]!=NULL){
			i--;
			dealCommonTrack(commonTrackList.commonTrack[id],trainIns,curTime,frameDur);
		}
		id++;
	}

    checkCrash(curTime,frameDur);
	//下达指令
	i=trainList.amount;
	id=0;
	while(i&&(id<MAX_TRAIN_AMOUNT)){//遍历火车
		if(trainList.train[id]!=NULL){
			i--;
			moveTrain(trainList.train[id],trainIns[id],curTime,frameDur);
		}
		id++;
	}
}
