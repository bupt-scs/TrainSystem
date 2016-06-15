#include "Train.h"
#include "global.h"
//��trainǰ���ĵ�һ����վλ��
unsigned long findNextStation(Train* train){
	unsigned long nextPos;//�������
	Track* curTrack=trackList.track[train->trackID];
	unsigned long pos=train->pos;
	unsigned long length=curTrack->length;


	if( (train->spd)>0 ){
		int i=0;
		for(;i<curTrack->stationAmount;i++)
			if(curTrack->stationPos[i]>=pos) break;
		if(pos>curTrack->stationPos[i])//�������һ��վ֮��
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
		else if(i==0)//���ڵ�һ��վ��֮ǰ
				if(curTrack->cycle)
					nextPos=curTrack->stationPos[curTrack->stationAmount-1];
				else nextPos=0;
			 else nextPos=curTrack->stationPos[i-1];
		return nextPos;
	}
}

//��ָ�����г�����insָ��г�����ins���Լ���status����һ���ж�������任��֡ʱ��frameDur�йء�
void moveTrain(Train* train,Ins ins,clock_t curTime,clock_t frameDur)
{
    switch(ins){
        case DOCK:
            fLog(0,"Log.txt",train->ID,"����ָ�� DOCK(��վ)",curTime);
            printf("\n�г� ID %d ������DOCK(��վ)ָ��\n",train->ID);
            break;
        case BRK:
            fLog(0,"Log.txt",train->ID,"����ָ�� BRK(�ƶ�)",curTime);
            printf("\n�г� ID %d ������BRK(�ƶ�)ָ��\n",train->ID);
            break;
        case ACC:
            fLog(0,"Log.txt",train->ID,"����ָ�� ACC(ǰ��)",curTime);
            printf("\n�г� ID %d ������ACC(ǰ��)ָ��\n",train->ID);
            break;
    }
	//״̬ת��
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

			int i=commonTrackList.amount;//�����������,�ҵ��Լ��ġ����FREE�˾�RUN
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
                                fprintf(log,"�г�ID %d �ȴ��Ĺ������%d�ѿ��У��г�������\n",
                                        train->ID,ct->ID);
                            fclose(log);
                            //fLog(0,"Log.txt",train->ID,"��������ѿ��Խ���,����",curTime);
                            printf("\n�г�ID %d �ȴ��Ĺ�������ѿ��У��г�������\n",train->ID);
						}
						if((train->spd>0&&cp<=ctin2&&ctin2<=np)||(train->spd<0&&cp>=ctout2&&ctout2>=np))
						if(ct->track2==train->trackID&&ct->status==FREE){
                            train->status=RUN;
                            trainWaiting[ct->ID]=NULL;
                            FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                                fprintf(log,"�г�ID %d �ȴ��Ĺ������%d�ѿ��У��г�������\n",
                                        train->ID,ct->ID);
                            fclose(log);
                            //fLog(0,"Log.txt",train->ID,"��������ѿ��Խ���,����",curTime);
                            printf("\n�г�ID %d �ȴ��Ĺ�������ѿ��У��г�������\n",train->ID);
						}
					}
				}
				id++;
			}
			break;
	}

	int x=(train->spd)*frameDur;
	Track* curTrack=trackList.track[train->trackID];

	switch(train->status){//��������
		case RUN:
			if(curTrack->cycle){
				train->pos=(train->pos+x+curTrack->length)%(curTrack->length);
				break;
			}
			else{//�ǻ�·����ͷ��ͣ
				if(train->spd>0)
					train->pos=min((train->pos+x),(curTrack->length-1));
				else
					train->pos=max((train->pos+x),0);
				break;
			}

		case STATION://��վ��ͣ�������ߡ��ǻ�·�Ĺ��������վ
        {
            unsigned long nextStation=findNextStation(train);
			long X=nextStation-train->pos;
			char s[255];
			//sprintf(s,"\nnext %u \nX %d \nx %d\n",nextStation,X,x);
            //fLog(0,"Log.txt",train->ID,s,curTime);
			if(X==0){//��վ��ͣ��ʱ�����
                //fLog(0,"Log.txt",train->ID,"AT STATION",curTime);
                if(train->dockTime==train->defaultDockTime){
                    printf("�г� %d ��ͣ�� %.3f��\n",train->ID,train->dockTime/1000.0);
                    FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                        fprintf(log,"�г� %d ��վ����ͣ�� %.3f��\n",train->ID,train->dockTime/1000.0);
                    fclose(log);
                }

				train->dockTime-=frameDur;

                //printf("��ʣ%d\n",train->dockTime);
				if(train->dockTime<0) {
                    train->status=RUN;
                    printf("�г� %d ��վ\n",train->ID);
                    FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                        fprintf(log,"�г� %d ��վ\n",train->ID);
                    fclose(log);
                    //fLog(0,"Log.txt",train->ID,"LEAVE STATION",curTime);
				}
				break;
			}
			//��ʻ��һȦ��λ�����ٶ���ţ�������
			if(X>0&&train->spd<0) X-=curTrack->length;
			if(X<0&&train->spd>0) X+=curTrack->length;

			train->pos+=abs(X)<abs(x)?X:x;
			train->pos%=curTrack->length;
        }
	}
}

void judgeCommonTrack(CommonTrack* cT,Train* enter[],int ei,clock_t curTime){
    int ii;

    printf("\nʱ�䣺%.3f s:�г�",
           curTime/(double)CLOCKS_PER_SEC);
    for(ii=0;ii<=ei;ii++){
        printf(" %d",enter[ii]->ID);
        if(ii!=ei) printf(" ��");
    }
    printf(" �ڹ������%d��ڴ��ȴ�����\n",cT->ID);

    FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
        fprintf(log,"�г�");
        for(ii=0;ii<=ei;ii++){
            fprintf(log," %d",enter[ii]->ID);
            if(ii!=ei) fprintf(log," ��");
        }
        fprintf(log," �ڹ������%d��ڴ��ȴ�����\n",cT->ID);

    switch(CTSTG){
                    case ASK:{
                        //showTrain();
                        printf("����׼�������г�ID��");
                        int idin; fflush(stdin);scanf("%d",&idin);
                        printf("�г� ID %d ����Ȩ���빫������������г�ͣ���ȴ�\n",idin);
                        fprintf(log,"�г� ID %d ����Ȩ���빫������������г�ͣ���ȴ�\n",idin);
                        //fLog(0,"Log.txt",idin,"�û�׼�빫������������г�ͣ���ȴ���",curTime);
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
                        printf("�г� ID %d �ٶȸ��죬���Ƚ��빫������������г�ͣ���ȴ�\n",tin->ID);
                        fprintf(log,"�г� ID %d �ٶȸ��죬���Ƚ��빫������������г�ͣ���ȴ�\n",tin->ID);
                        //fLog(0,"Log.txt",tin->ID,"���ٳ����Ƚ��빫������������г�ͣ���ȴ�",curTime);
                        for(;ei>=0;ei--)
                            enter[ei]->status=WAIT;
                        tin->status=RUN;
                        cT->status=BUSY;
                        break;
                    }

                    case RAD:{
                        int ridin=enter[curTime/233%2]->ID;
                        printf("�г� ID %d �����ѡ�н��빫������������г�ͣ���ȴ�\n",ridin);
                        fprintf(log,"�г� ID %d �����ѡ�н��빫������������г�ͣ���ȴ�\n",ridin);
                        //fLog(0,"Log.txt",ridin,"�����ѡ�н��빫������������г�ͣ���ȴ�",curTime);
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
	int i=trainList.amount;//������,��鹫�����״̬
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

    //fLog(0,"Log.txt",-1,strCommonTrackState(cT->status),curTime);//debug������������״̬

	Train* enter[4]; int ei=0;//ei��enter[]���±�
	for(i=0;i<4;i++) enter[i]=NULL;
	//printf("[DEBUG]move.c line M1\n");
	i=trainList.amount;//������,�����н�Ҫ����cT�Ļ𳵼ǵ�enter[]
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
							fprintf(log,"�г� ID %d ���﹫����� %d ���\n",t->ID,cT->ID);
							fclose(log);
						}
					if(t->spd<0)
                        if(np<=out1&&out1<cp){
							enter[ei]=t;
							ei++;
							FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
							fprintf(log,"�г� ID %d ���﹫����� %d ���\n",t->ID,cT->ID);
							fclose(log);
						}
				}

				if(t->trackID==cT->track2){
					if(t->spd>0)
						if(cp<in2&&in2<=np){
							enter[ei]=t;
							ei++;
							FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
							fprintf(log,"�г� ID %d ���﹫����� %d ���\n",t->ID,cT->ID);
							fclose(log);
						}
					if(t->spd<0)
                        if(np<=out2&&out2<cp){
							enter[ei]=t;
							ei++;
							FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
							fprintf(log,"�г� ID %d ���﹫����� %d ���\n",t->ID,cT->ID);
							fclose(log);
						}
				}
			}
		}
		id++;
	}
	ei--;//ei������enter�����һ�������±�

//	char eis[33];
//	sprintf(eis,"%d",ei);
//    fLog(0,"Log.txt",-1,eis,curTime);
//    if(cT->status==FREE)
//    fLog(0,"Log.txt",-1,"F",curTime);
//    else if(cT->status==ctWAIT)
//        fLog(0,"Log.txt",-1,"ctW",curTime);
//    else if(cT->status==BUSY)
//        fLog(0,"Log.txt",-1,"B",curTime);//debug���ei�͹������״̬

    switch(cT->status){
        case BUSY:
            for(;ei>=0;ei--){
                enter[ei]->status=WAIT;//�������æ������Ĳ�׼��
                printf("\n�г� ID %d ���﹫��������,��������г���ͣ���ȴ���\n",enter[ei]->ID);
                fLog(0,"Log.txt",enter[ei]->ID,"��������г���ͣ���ȴ���",curTime);
            }
            break;

        case FREE:
            if(ei>0)//��2�����
                judgeCommonTrack(cT,enter,ei,curTime);
            else if(ei==0){
                    if(CTW){
                        enter[ei]->status=WAIT;
                        trainWaiting[cT->ID]=enter[ei];
                        cT->status=ctWAIT;
                        fLog(0,"Log.txt",enter[ei]->ID,"���﹫�������ڣ�ͣ���ȴ�",curTime);
                        printf("\n�г� ID %d ���﹫�������ڣ�ͣ���ȴ���\n",enter[ei]->ID);
                    }
                    else{
                        printf("\n%.3f s���г�%d ���빫����� %d\n",
                        curTime/(double)CLOCKS_PER_SEC,enter[ei]->ID,cT->ID);
                        FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                            fprintf(log,"�г�%d ���빫����� %d\n",enter[ei]->ID,cT->ID);
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

void checkCrash(clock_t curTime,clock_t frameDur){    //�ж�ײ��
int i1 = trainList.amount,i2 = trainList.amount,id1,id2;
int64 x1,x2;
for(id1 = 0;i1&&id1<MAX_TRAIN_AMOUNT;id1++)     //������
    if(trainList.train[id1] != NULL){
        i1--;
        Train* t1 = trainList.train[id1];
        if(t1->status == RUN)  //�ҳ��������еĻ�
            for(id2 = 0, i2 = trainList.amount;i2&&id2<MAX_TRAIN_AMOUNT;id2++)  //�ٴα�����= =
                if(trainList.train[id2] != NULL){
                    i2--;
                    if(id2 != id1){
                        Train* t2 = trainList.train[id2];
                        if(t1->trackID == t2->trackID){    //�ҵ�ͬһ����ϵĻ�
                            x1 = (int64)t2->pos - (int64)t1->pos;     //������
                            x2 = (int64)t2->pos + t2->spd * frameDur - (int64)t1->pos - t1->spd * frameDur;//��λʱ������
                            if(t2->status == WAIT || t2->status == STOP)
                                if(abs(x1 * x2) != x1 * x2 || x2 == 0) {
                                    trainIns[t1->ID] = BRK;
                                    printf("�г�ID %d ǰ���о�ֹ�г� ID %d���ƶ���\n",t1->ID,t2->ID);
                                    fLog(0,"Log.txt",t1->ID,"ǰ���о�ֹ����",curTime);
                                }
                            if(t2->status == RUN || t2->status == STATION)
                                if(abs(x1 * x2) != x1 * x2 || x2 ==0)
                                    if(abs(t1->spd * t2->spd) != t1->spd * t2->spd){     //ӭ����ײ
                                        printf("�г�ID %d �� %d ��ӭ�������������ƶ���\n",t1->ID,t2->ID);
                                        FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime);
                                            fprintf(log,"�г�ID %d �� %d ��ӭ�������������ƶ���\n",t1->ID,t2->ID);
                                        fclose(log);
                                        trainIns[t1->ID] = BRK; trainIns[t2->ID] = BRK;     //�������ƶ�
                                    }
                                    else{ //׷β
                                        int tid=(abs(t1->spd) > abs(t2->spd)) ? (t1->ID) : (t2->ID);//���ƶ�
                                        printf("�г� ID %d ����ǰ��׷β���ƶ���\n",tid);
                                        fLog(0,"Log.txt",tid,"����ǰ��׷β",curTime);
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
    //fLog(1,"Log.txt",-1,"",curTime);//ÿ֡������־
	for(i=0;i<MAX_TRAIN_AMOUNT;i++)
		trainIns[i]=HOLD;
	userIns(curTime,frameDur);

	i=commonTrackList.amount;//�����������
	int id=0;
	while(i&&(id<MAX_COMMON_TRACK_AMOUNT)){
		if(commonTrackList.commonTrack[id]!=NULL){
			i--;
			dealCommonTrack(commonTrackList.commonTrack[id],trainIns,curTime,frameDur);
		}
		id++;
	}

    checkCrash(curTime,frameDur);
	//�´�ָ��
	i=trainList.amount;
	id=0;
	while(i&&(id<MAX_TRAIN_AMOUNT)){//������
		if(trainList.train[id]!=NULL){
			i--;
			moveTrain(trainList.train[id],trainIns[id],curTime,frameDur);
		}
		id++;
	}
}
