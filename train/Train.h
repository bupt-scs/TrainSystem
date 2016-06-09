#include <stdio.h>
#include <math.h>
#include <string.h>
#include <process.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_STATION_AMOUNT 10
#define MAX_TRACK_AMOUNT 10
#define MAX_COMMON_TRACK_AMOUNT 10
#define MAX_TRAIN_AMOUNT 10

#define abs(a) ((a)>0?(a):-(a))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define hr "-----------------------------------------------------------------------------------\n"
#define openLog() FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime)

/****************************************************************************
*****************************************************************************
**															               **
**		   ����ÿ����������ĸ����д ��							           **
**		   �����ͺ�������ĸСд���Ժ�ÿһ����������ĸ��д ��			   **
**															               **
*****************************************************************************
****************************************************************************/




//��״̬
typedef enum{
	STOP, 	//ֹͣ
	STATION,//ͣ��
	RUN	,	//����
	WAIT	//�ȴ������������
}TrainState;

//�������״̬
typedef enum{
	FREE,	//����
	BUSY,	//��ռ��
	ctWAIT
}CommonTrackState;

//��ָ��
typedef enum{
	HOLD,   //����
	BRK,	//�ƶ�
	ACC,	//����
	DOCK,	//ͣ��
}Ins;

//�����������
typedef enum{
	FFI,	//����
	ASK,	//ѯ��
	RAD	    //���
}STG;

typedef struct{
	int ID; //��trackList.track[]���±�
	unsigned long length;//������ȡ����й���ĵ�λ��ͳһ.
	char cycle;//�Ƿ�·
	int stationAmount;//��վ����
	unsigned long stationPos[MAX_STATION_AMOUNT];//����վ�����ꡣ��������������ݵ�ʱ��֤��վ���갴����¼������顣
} Track;

typedef struct{
	int ID; //��commonTrackList.commonTrack[]����±�
	int track1;
	int track2;//����֮ID
	unsigned long track1in;
	unsigned long track2in;
	unsigned long track1out;
	unsigned long track2out;
    CommonTrackState status;
} CommonTrack;

typedef struct{
	int ID;					//��trainList.train[]����±�
	int trackID; 			//���ڹ��ID
	unsigned long pos; 		//�ڹ���ϵ�����
	int spd; 				//�ٶ�(�ɷ���)
	clock_t dockTime;
	long defaultDockTime;
	TrainState status;
}Train;

typedef struct TrackList_name{
	int amount;
	Track* track[MAX_TRACK_AMOUNT];
} TrackList;
TrackList trackList;//����Ψһȫ�ֱ���

typedef struct{
	int amount;
	CommonTrack* commonTrack[MAX_COMMON_TRACK_AMOUNT];
} CommonTrackList;
CommonTrackList commonTrackList;//����Ψһȫ�ֱ���

typedef struct{
	int amount;
	Train* train[MAX_TRAIN_AMOUNT];
} TrainList;
TrainList trainList;//����Ψһȫ�ֱ���

typedef struct{
    Ins ins;
    int trainID;
}InputIns;
InputIns inputIns;//����Ψһȫ�ֱ���

typedef signed long long int int64;

Ins trainIns[MAX_TRAIN_AMOUNT];//ָ���б�
Train* trainWaiting[MAX_COMMON_TRACK_AMOUNT];//������������ڵȴ������Ļ𳵡��±��ǹ������ID
STG CTSTG;//�����������
char CTW;//�г����﹫��������ʱ���Ƿ���Ҫ�ȴ���������֮���پ���˭�ߡ���!CTW��ֻ�ڹ������ͬʱ����2��Ҫ��ʱ���о�����
HANDLE hMutex;
clock_t startTime;
//-----------------------------------------------------------------------

//int writeTrain(int ID,int trackID,unsigned long pos,int spd);
////���trainList.train[ID]����ΪNULL��������Ϊ�µ�Train����ռ䣬��д�������������ΪNULL������������д�롣
//
//int writeTrack(int ID,unsigned long length,int cycle,
//			int stationAmount,unsigned long stationPos[]);
////���trackList.track[ID]����ΪNULL��������Ϊ�µ�Track����ռ䣬��д�������������ΪNULL������������д�롣
//
//int writeCommonTrack(int ID,Track* track1,Track* track2,
//			int track1in,int track2in,int track1out,int track2out);
////���commonTrackList.track[ID]����ΪNULL��������Ϊ�µ�CommonTrack����ռ䣬��д���������
////����ΪNULL������������д�롣 ���������Train��λ�ã��ж�ռ���������д��commonTrackList.track[ID]->status

void fshowTrack(char* fName);
void fshowCommonTrack(char* fName);
void moveAllTrain(clock_t curTime,clock_t frameDur);
//��������commonTrack��train������״����ÿ��train����moveTrain()������ָ��.

void dataInit();//���ļ��ж�ȡ���ݣ����޸�
void dataInit_StandAlone();//debug�ã�dataInit���޽����汾

void startShow();

void userIns(clock_t curTime,clock_t frameDur);
//��moveAllTrain()�е��á�
//���û����г���ָ��д��ָ���б�Ins[],�����ڰ汾�У�����������ļ�����ָ�����ǰʱ���ָ��д��Ins[]

void freeLists(void);
//free����list

//ö��ת��Ϊ�ַ���
char* strTrainState(TrainState sta);
char* strCommonTrackState(CommonTrackState sta);
char* strIns(Ins ins);
//�ַ���ת��Ϊö��
CommonTrackState enumCommonTrackState(char* a);
Ins enumIns(char* a);
TrainState enumTrainState(char* a);

DWORD WINAPI insDuringRun(LPVOID pPararneter);
void fLog(char show,char* fileName,int trainID,char* msg,clock_t curTime);
