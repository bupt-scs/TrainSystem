#include "Train.h"
#include "global.h"
void startShow(){
    char ch;
    FILE* fptr = fopen("file/hello.txt","r");
    while(fscanf(fptr,"%c",&ch)!=EOF)
        printf("%c",ch);
    printf("\n                          ��ӭʹ�����ǵ�С�𳵵���ϵͳ~\n");
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
	trainList.train[ID]->status = STOP; //Ĭ��Ϊ����
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
//���commonTrackList.track[ID],��ΪNULL,������Ϊ�µ�CommonTrack����ռ�,��д���������
//����ΪNULL,����������д�롣 ���������Train��λ��,�ж�ռ�����,��д��commonTrackList.track[ID]->status]

void dataInit()
{
	char s[25],ch;
	int i,j,ID,trackID,pos,spd,length,cycle,stationAmount;
    unsigned long stationPos[MAX_STATION_AMOUNT];
//------------------------------�𳵲���---------------------------------
    for(i=0;i<=MAX_TRAIN_AMOUNT;i++)
    {
        trainList.train[i] = NULL;
    }
	FILE *fptr = fopen("file/trainConfig.txt","r");

	if(fptr==NULL)
	{
		printf("�򿪻���Ϣ�ļ�ʧ��,�����ԡ�");
	}
    //��ȡ����
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

	//�����ǰ״��
    showTrain();
    fclose(fptr);

	printf("�Ƿ���Ҫ����\"С������\"����Ϣ��Y/N:");
    ch = getchar();
    while(ch!='Y'&&ch!='N'&&ch!='y'&&ch!='n')
    {
        printf("������Y��N�����Ƿ��޸�\"С������\"����Ϣ:");
        ch=getchar();
    }
    if(ch=='N'||ch=='n')
        ;
    else
    {
        ID=99999;
        puts(hr);
        printf("����Ϊ���л�,������Ҫ����ʲô������\n1.�����µ�С��\n2.�޸�����С����Ϣ\n3.ɾ��С��\n4.�趨����\n������(1~4):");
        fflush(stdin);
        ch = getchar();
        while(ch!='4')
        {
            switch(ch)
            {
                case '1':
                    printf("�������¼���𳵱��,�ñ��С��%d:",MAX_TRAIN_AMOUNT);
                    scanf("%d",&ID);
                    while(trainList.train[ID]!=NULL||ID>MAX_TRAIN_AMOUNT)
                    {
                        printf("�Ѵ��ڸû𳵻����벻���Ϲ淶�����������룡���ñ��С��%d��:",MAX_TRAIN_AMOUNT);
                        scanf("%d",&ID);
                    }
                    printf("���¼���𳵷��������������:");
                    scanf("%d",&trackID);
                    printf("�������¼���𳵵�����:");
                    scanf("%d",&pos);
                    printf("�������¼�����ٶ�:");
                    scanf("%d",&spd);
                    writeTrain(ID,trackID,pos,spd);

                    break;
                case '2':
                    printf("��������޸ĵĻ𳵱��,�ñ��С��%d:",MAX_TRAIN_AMOUNT);
                    scanf("%d",&ID);
                    while(trainList.train[ID]==NULL||ID>MAX_TRAIN_AMOUNT)
                    {
                        printf("�����ڸû𳵻����벻���Ϲ淶�����������룡���ñ��С��%d��:",MAX_TRAIN_AMOUNT);
                        scanf("%d",&ID);
                    }
                    printf("��������Ҫ�޸ĵĻ𳵱��,�ñ��С��%d:",MAX_TRAIN_AMOUNT);
                    scanf("%d",&ID);
                    printf("�û𳵷��������������:");
                    scanf("%d",&trackID);
                    printf("�û�����Ϊ:");
                    scanf("%d",&pos);
                    printf("�û��ٶ�Ϊ:");
                    scanf("%d",&spd);
                    writeTrain(ID,trackID,pos,spd);
                    break;
                case '3':
                    printf("����Ҫɾ��������:");
                    scanf("%d",&ID);
                    while(trainList.train[ID]==NULL||ID>MAX_TRAIN_AMOUNT)
                    {
                        printf("�����ڸû𳵻����벻���Ϲ淶������������:");
                        scanf("%d",&ID);
                    }
                    free(trainList.train[ID]);
                    trainList.train[ID] = NULL;
                    trainList.amount--;
                    break;
            }
            showTrain();
            puts(hr);
            printf("����Ϊ���л�,������Ҫ����ʲô������\n1.�����µ�С��\n2.�޸�����С����Ϣ\n3.ɾ��С��\n4.�趨����\n������(1~4):");
            fflush(stdin);
            ch = getchar();
        }
        fptr = fopen("file/trainConfig.txt","w");
        fprintf(fptr,"������:\n%d\n",trainList.amount);
        for(i=1;i<=MAX_TRAIN_AMOUNT;i++)
        {
            if(trainList.train[i]!=NULL)
            {
                fprintf(fptr,"\n�г�ID:\n%d\n",trainList.train[i]->ID);
                fprintf(fptr,"���ڹ��:\n%d\n",trainList.train[i]->trackID);
                fprintf(fptr,"����:\n%d\n",trainList.train[i]->pos);
                fprintf(fptr,"�ٶ�:\n%d\n",trainList.train[i]->spd);
            }
        }
        fclose(fptr);
    }
    system("cls");
    startShow();
    printf("�����ѱ���\n");
    showTrain();
    printf("��Ϊ��ǰ����Ϣ,���س���������һ����");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("cls");
//----------------------------------��һ�������---------------------------
    startShow();
	//��ʼ��ָ��
	for(i=0;i<=MAX_TRACK_AMOUNT;i++)
    {
        trackList.track[i] = NULL;
    }

	fptr = fopen("file/trackConfig.txt","r");
	if(fptr==NULL)
	{
		printf("�򿪹����Ϣ�ļ�ʧ��,�����ԡ�");
	}
	fgets(s,1000,fptr);						//�������

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

	printf("�Ƿ���Ҫ����\"�������\"����Ϣ��Y/N:");
    ch = getchar();
    while(ch!='Y'&&ch!='N'&&ch!='y'&&ch!='n')
    {
        printf("������Y��N�����Ƿ��޸�\"�������\"����Ϣ:");
        ch=getchar();
    }
    if(ch=='N'||ch=='n')
        ;
    else
    {
        ID=99999;
        puts(hr);
        printf("����Ϊ���й��,������Ҫ����ʲô������\n1.�����µĹ��\n2.�޸����й����Ϣ\n3.�趨����\n������(1~3):");
        fflush(stdin);
        ch = getchar();
        while(ch!='3')
        {
            switch(ch)
            {
                case '1':
                    printf("�������¼��������,�ñ��С��%d:",MAX_TRACK_AMOUNT);
                    scanf("%d",&ID);
                    while(trackList.track[ID]!=NULL||ID>MAX_TRACK_AMOUNT)
                    {
                        printf("�Ѵ��ڸù�������벻���Ϲ淶�����������룡���ñ��С��%d��:",MAX_TRAIN_AMOUNT);
                        scanf("%d",&ID);
                    }
                    printf("�������Ϊ:");
                    scanf("%d",&length);
                    printf("�Ƿ�·������Ϊ1,��Ϊ0��:");
                    scanf("%d",&cycle);
                    printf("���м�����վ��");
                    scanf("%d",&stationAmount);
                    printf("����վ���꣨ÿ������һ�����꣩:\n");
                    for(i=0;i<stationAmount;i++)
                    {
                        scanf("%d",&stationPos[i]);
                    }
                    writeTrack(ID,length,cycle,stationAmount,stationPos);
                    break;
                case '2':
                    printf("��������޸ĵĹ�����,�ñ��С��%d:",MAX_TRACK_AMOUNT);
                    scanf("%d",&ID);
                    while(trackList.track[ID]==NULL||ID>MAX_TRACK_AMOUNT)
                    {
                        printf("�����ڸù�������벻���Ϲ淶�����������룡���ñ��С��%d��:",MAX_TRAIN_AMOUNT);
                        scanf("%d",&ID);
                    }
                    printf("�������Ϊ:");
                    scanf("%d",&length);
                    printf("�Ƿ�·������Ϊ1,��Ϊ0��:");
                    scanf("%d",&cycle);
                    printf("���м�����վ��");
                    scanf("%d",&stationAmount);
                    printf("����վ���꣨ÿ������һ�����꣩:\n");
                    for(i=0;i<stationAmount;i++)
                    {
                        scanf("%d",&stationPos[i]);
                    }
                    writeTrack(ID,length,cycle,stationAmount,stationPos);
                    break;
            }
            showTrack();
            puts(hr);
            printf("����Ϊ���й��,������Ҫ����ʲô������\n1.�����µĹ��\n2.�޸����й����Ϣ\n3.�趨����\n������(1~3):");
            fflush(stdin);
            ch = getchar();
        }
        fptr = fopen("file/trackConfig.txt","w");
        fprintf(fptr,"�������:\n%d\n",trackList.amount);
        for(i=1;i<=MAX_TRACK_AMOUNT;i++)
        {
            if(trackList.track[i]!=NULL)
            {
                fprintf(fptr,"\n���ID:\n%d\n",trackList.track[i]->ID);
                fprintf(fptr,"�������:\n%u\n",trackList.track[i]->length);
                fprintf(fptr,"�Ƿ�·:\n%d\n",trackList.track[i]->cycle);
                fprintf(fptr,"��վ����:\n%d\n",trackList.track[i]->stationAmount);
                fprintf(fptr,"����վ����:\n");
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
    printf("�����ѱ���\n");
    showTrack();
    printf("��Ϊ��ǰ\"���\"��Ϣ,���س���������һ����");
    fflush(stdin);
    getchar();
    fflush(stdin);
    system("cls");
//-------------------------------------�����������-------------------------------------
    startShow();
    for(i=0;i<=MAX_COMMON_TRACK_AMOUNT;i++)
    {
        commonTrackList.commonTrack[i] = NULL;
    }

	fptr = fopen("file/commontrackConfig.txt","r");
	if(fptr==NULL)
	{
		printf("��\"�������\"��Ϣ�ļ�ʧ��,�����ԡ�");
	}

	fgets(s,1000,fptr);						//�����������
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
	//�����ǰ״��
    showCommonTrack();
    puts(hr);
    printf("��ȷ�Ϲ��������Ϣ,�س�����ʼ���е���ϵͳ��");
    getchar();
    fflush(stdin);
	fclose(fptr);
	system("cls");
	startShow();
	printf("1.�ȵ�ѯ���˹�\n2.�ȵ��쳵����\n3.�ȵ��������\n4.�ȴ�ѯ���˹�\n5.�ȴ��쳵����\n6.�ȴ��������\n\n");
	printf("��ѡ�񹫹�������Ȳ���(����?��ȡ����˵��):");
	ch = getchar();
	fflush(stdin);
	do{
        while((ch<'1'||ch>'6')&&(ch!='?'))
        {
            fflush(stdin);
            printf("����������:");
            ch = getchar();
        }
        if(ch=='?'||ch=='��'){
            printf("\n����˵����\n\t�ȵ�ѯ���˹����ȵ��쳵���ȣ��ȵ�������ԣ�\n\t\t");
            printf("�г����﹫�������ں�ͽ��룬��������һ����Ҫͬʱ���빫�������\n\t\t");
            printf("����������ͬʱ���빫���������ѯ���˹�/�쳵����/�������\n\n\t");
            printf("�ȴ�ѯ���˹����ȴ��쳵���ȣ��ȴ�������ԣ�\n\t\t");
            printf("�г����﹫�������ں�ͣ���ȴ���ֱ������һ����ҲҪ���빫�������\n\t\t");
            printf("��ѯ���˹�/�쳵����/�������\n\n");
            printf("��ѡ�񹫹�������Ȳ���(���룿��ȡ����˵��):");
            ch = getchar();
        }
	}
	while(ch<'1'||ch>'6');

	if(ch<='3') CTW=0;
	else CTW=1;
	 if(CTW) printf("�ȴ�");
    switch(ch){
        case '1':case '4': CTSTG=ASK;printf("ѯ���˹�������ѡ��\n");break;
        case '2':case '5': CTSTG=FFI;printf("�쳵���в�����ѡ��\n");break;
        case '3':case '6': CTSTG=RAD;printf("���������ѡ��\n");break;
    }

}

void showTrain()
{
	int i,j;
	//�����ǰ״��
	puts(hr);
	printf("�г�����Ϊ:%d\nĿǰ���г�״��:\n",trainList.amount);
	for(i=0;i<MAX_TRAIN_AMOUNT;i++)
	{
	    if(trainList.train[i]!=NULL)
        {
            trainList.train[i]->defaultDockTime=(clock_t)3000;
            printf("���Ϊ%d�Ļ�,��ǰ��ʻ�ڵ�%d�����,λ��Ϊ%d,\t�ٶ�Ϊ%d,״̬Ϊ%s,\tվ��ͣ��ʱ��Ϊ%d ms,",
                trainList.train[i]->ID,
                trainList.train[i]->trackID,
                trainList.train[i]->pos,
                abs(trainList.train[i]->spd),
                strTrainState(trainList.train[i]->status),
                trainList.train[i]->defaultDockTime
            );

            if(trainList.train[i]->spd<0)
                printf("��ʱ������\t");
            else
                printf("˳ʱ������\t");
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
	printf("�������Ϊ:%d\n���и��������:\n",trackList.amount);
	for(i=0;i<MAX_TRACK_AMOUNT;i++)
	{
        if(trackList.track[i]!=NULL)
        {
            printf("���Ϊ%d�Ĺ��,�ܳ���Ϊ%u,",
			trackList.track[i]->ID,
			trackList.track[i]->length
            );
            if(trackList.track[i]->cycle==1)
            {
                printf("Ϊ��·,");
            }
            else
            {
                printf("���ǻ�·,");
            }

            if(!trackList.track[i]->stationAmount) printf("�޳�վ");
            else{
                printf("����%d����վ,���ǵ�����ֱ�Ϊ",
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
	fprintf(f,"�������Ϊ:%d\n���и��������:\n",trackList.amount);
	for(i=0;i<MAX_TRACK_AMOUNT;i++)
	{
        if(trackList.track[i]!=NULL)
        {
            fprintf(f,"���Ϊ%d�Ĺ��,�ܳ���Ϊ%u,",
			trackList.track[i]->ID,
			trackList.track[i]->length
            );
            if(trackList.track[i]->cycle==1)
            {
               fprintf(f,"Ϊ��·,");
            }
            else
            {
                fprintf(f,"���ǻ�·,");
            }

            if(!trackList.track[i]->stationAmount) fprintf(f,"�޳�վ");
            else{
                fprintf(f,"����%d����վ,���ǵ�����ֱ�Ϊ",
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
    printf("�������������Ϊ:%d\n���и��������:\n",commonTrackList.amount);
	for(i=0;i<MAX_COMMON_TRACK_AMOUNT;i++)
	{
        if(commonTrackList.commonTrack[i]!=NULL)
        {
            printf("��%d��Ĺ������,Ϊ��%d��%d�Ź���Ĺ�������,",
                commonTrackList.commonTrack[i]->ID,
                commonTrackList.commonTrack[i]->track1,
                commonTrackList.commonTrack[i]->track2
            );
            printf("�ڵ�%d�������,�������Ϊ%d,��������Ϊ%d,",
                commonTrackList.commonTrack[i]->track1,
                commonTrackList.commonTrack[i]->track1in,
                commonTrackList.commonTrack[i]->track1out
            );
            printf("�ڵ�%d�������,�������Ϊ%d,��������Ϊ%d,",
                commonTrackList.commonTrack[i]->track2,
                commonTrackList.commonTrack[i]->track2in,
                commonTrackList.commonTrack[i]->track2out
            );
            printf("Ŀǰ״̬:");
            if(commonTrackList.commonTrack[i]->status ==FREE)
            {
                printf("����\n");
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
                                printf("�ѱ�%dռ��\n",trainList.train[j]->ID);
                        }
                        if(trainList.train[j]->trackID==commonTrackList.commonTrack[i]->track2)
                        {
                            if(trainList.train[j]->pos>commonTrackList.commonTrack[i]->track2in&&
                               trainList.train[j]->pos<commonTrackList.commonTrack[i]->track2out)
                                printf("�ѱ�%dռ��\n",trainList.train[j]->ID);
                        }
                    }
                }
            }
            else
            {
                printf("����Ԥ����\n");
            }
        }
	}
}
void fshowCommonTrack(char* fName)
{
    FILE* f=fopen(fName,"a");
    int i,j;
    fprintf(f,"\n�������������Ϊ:%d\n���и��������:\n",commonTrackList.amount);
	for(i=0;i<MAX_COMMON_TRACK_AMOUNT;i++)
	{
        if(commonTrackList.commonTrack[i]!=NULL)
        {
            fprintf(f,"������� %d ,Ϊ %d �� %d �Ź���Ĺ�������,",
                commonTrackList.commonTrack[i]->ID,
                commonTrackList.commonTrack[i]->track1,
                commonTrackList.commonTrack[i]->track2
            );
            fprintf(f,"�� %d �Ź����,�������Ϊ%d,��������Ϊ%d,",
                commonTrackList.commonTrack[i]->track1,
                commonTrackList.commonTrack[i]->track1in,
                commonTrackList.commonTrack[i]->track1out
            );
            fprintf(f,"�� %d ���������,�������Ϊ%d,��������Ϊ%d\n",
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
	//�����ǰ״��
	if(show){
        fprintf(f,"--------------------------------------------------------------------------\n");

        //fshowCommonTrack(fileName);
        //fprintf(f,"\n");

        fprintf(f," �г�����Ϊ:%d\nĿǰ���г�״��:\n",trainList.amount);
        for(i=0;i<MAX_TRAIN_AMOUNT;i++)
        {
            if(trainList.train[i]!=NULL)
            {
                fprintf(f,"��%d����,��ǰ��ʻ�ڵ�%d�����,λ��Ϊ%d,�ٶ�Ϊ%d,״̬Ϊ%s",
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

	if(trainID>=0) fprintf(f,"�г� %d : ",trainID);
	fputs(msg,f);
	fprintf(f,"\n\n");
	fclose(f);
}

//��moveAllTrain()�е��á�
//���û����г���ָ��д��ָ���б�trainIns[],�����ڰ汾��,����������ļ�����ָ��,����ǰʱ���ָ��д��trainIns[]
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
        printf("ָ���б�:\n");
        printf("1.ACC(����)  2.BRK(ֹͣ)  3.DOCK(ͣ��)  4.SPD(����)  q.�޸Ĳ���  ��������ȡ��ָ��:");
        ch = getchar();
        fflush(stdin);
        switch(ch){
            case '1':
                printf("��������Ҫ�������г����:");
                scanf("%d",&ID);
                if(ID<=0||ID>MAX_TRAIN_AMOUNT)
                {
                    printf("��������!");
                    Sleep(1);
                }
                else
                {
                    inputIns.ins = ACC;
                    inputIns.trainID = ID;
                }
                break;
            case '2':
                printf("��������Ҫֹͣ���г����:");
                scanf("%d",&ID);
                if(ID<=0||ID>MAX_TRAIN_AMOUNT)
                {
                    printf("��������!");
                    Sleep(1);
                }
                else
                {
                    inputIns.ins = BRK;
                    inputIns.trainID = ID;
                }
                break;
            case '3':
                printf("����������һվ��ͣ�����г����:");
                scanf("%d",&ID);
                if(ID<=0||ID>MAX_TRAIN_AMOUNT)
                {
                    printf("��������!");
                    Sleep(1);
                }
                else
                {
                    inputIns.ins = DOCK;
                    inputIns.trainID = ID;
                }
                break;
            case '4':
                printf("��������Ҫ�޸��ٶȵ��г����:");
                scanf("%d",&ID);
                if(ID<=0||ID>MAX_TRAIN_AMOUNT)
                {
                    printf("��������!");
                    Sleep(1);
                }
                else
                {
                    printf("�ٶ�ԭ��Ϊ:%d,�޸�Ϊ:",trainList.train[ID]->spd);
                    scanf("%d",&trainList.train[ID]->spd);
                    printf("�ٶ�������");
                }
                break;
            case 'q':case 'Q':
                printf("1.�ȵ�ѯ���˹�\n2.�ȵ��쳵����\n3.�ȵ��������\n4.�ȴ�ѯ���˹�\n5.�ȴ��쳵����\n6.�ȴ��������\n\n");
                printf("��ѡ�񹫹�������Ȳ���(����?��ȡ����˵��):");
                fflush(stdin);
                ch = getchar();
                do{
                    while((ch<'1'||ch>'6')&&(ch!='?'&&ch!='��'))
                    {
                        fflush(stdin);
                        printf("����������:");
                        ch = getchar();
                    }
                    if(ch=='?'||ch=='��'){
                        printf("\n����˵����\n\t�ȵ�ѯ���˹����ȵ��쳵���ȣ��ȵ�������ԣ�\n\t\t");
                        printf("�г����﹫�������ں�ͽ��룬��������һ����Ҫͬʱ���빫�������\n\t\t");
                        printf("����������ͬʱ���빫���������ѯ���˹�/�쳵����/�������\n\n\t");
                        printf("�ȴ�ѯ���˹����ȴ��쳵���ȣ��ȴ�������ԣ�\n\t\t");
                        printf("�г����﹫�������ں�ͣ���ȴ���ֱ������һ����ҲҪ���빫�������\n\t\t");
                        printf("��ѯ���˹�/�쳵����/�������\n\n");
                        printf("��ѡ�񹫹�������Ȳ���(���룿��ȡ����˵��):");
                        ch = getchar();
                    }
                }
                while(ch<'1'||ch>'6');

                if(ch<='3') CTW=0;
                else CTW=1;
                switch(ch){
                    case '1':case '4': CTSTG=ASK;printf("ASK������ѡ��\n");break;
                    case '2':case '5': CTSTG=FFI;printf("FFI������ѡ��\n");break;
                    case '3':case '6': CTSTG=RAD;printf("RAD������ѡ��\n");break;
                }
                if(CTW) printf("CTW������ѡ��\n");
            default:
                break;
        }
        fflush(stdin);
        ReleaseMutex(hMutex);
	}
}
