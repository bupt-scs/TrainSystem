#pragma once
#ifndef TRAIN_H
    #define TRAIN_H

#include <cstdio>
#include <cmath>
#include <string.h>
#include <string>
#include <process.h>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <graphics.h>

#define MAX_STATION_AMOUNT 10
#define MAX_TRACK_AMOUNT 10
#define MAX_COMMON_TRACK_AMOUNT 10
#define MAX_TRAIN_AMOUNT 10

#define abs(a) ((a)>0?(a):-(a))
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define hr "-----------------------------------------------------------------------------------\n"
//#define openLog() FILE* log=fopen("Log.txt","a");fprintf(log,"\n[%d ms] ",curTime)

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
	RAD,    //���
	JT      //����
}STG;

typedef struct{
	int ID; //��trackList.track[]���±�
	unsigned long length;//������ȡ����й���ĵ�λ��ͳһ.
	int cycle;//�Ƿ�·
	int stationAmount;//��վ����
	unsigned long stationPos[MAX_STATION_AMOUNT];//����վ�����ꡣ��������������ݵ�ʱ��֤��վ���갴����¼������顣
} Track;

typedef struct{
	int ID;					//��trainList.train[]����±�
	int trackID; 			//���ڹ��ID
	unsigned long pos; 		//�ڹ���ϵ�����
	int spd; 				//�ٶ�(�ɷ���)
	clock_t dockTime;
	long defaultDockTime;
	TrainState status;
}Train;

typedef struct{
	int ID; //��commonTrackList.commonTrack[]����±�
	int track1;
	int track2;//����֮ID
	unsigned long track1in;
	unsigned long track2in;
	unsigned long track1out;
	unsigned long track2out;
    CommonTrackState status;
    Train* lastUser;//�ϴ�׼��Ļ�
} CommonTrack;

typedef struct TrackList_name{
	int amount;
	Track* track[MAX_TRACK_AMOUNT];
} TrackList;

typedef struct{
	int amount;
	CommonTrack* commonTrack[MAX_COMMON_TRACK_AMOUNT];
} CommonTrackList;

typedef struct{
	int amount;
	Train* train[MAX_TRAIN_AMOUNT];
} TrainList;

typedef struct{
    Ins ins;
    int trainID;
}InputIns;

typedef signed long long int int64;

//static Ins trainIns[MAX_TRAIN_AMOUNT];//ָ���б�
//static Train* trainWaiting[MAX_COMMON_TRACK_AMOUNT];//������������ڵȴ������Ļ𳵡��±��ǹ������ID
//static STG CTSTG;//�����������
//static char CTW;//�г����﹫��������ʱ���Ƿ���Ҫ�ȴ���������֮���پ���˭�ߡ���!CTW��ֻ�ڹ������ͬʱ����2��Ҫ��ʱ���о�����
//static HANDLE hMutex;
//static clock_t startTime;
//-----------------------------------------------------------------------

void freeLists(void);
//free����list
void dataInit_StandAlone();

//enum.cpp
//ö��ת��Ϊ�ַ���
char* strTrainState(TrainState sta);
char* strCommonTrackState(CommonTrackState sta);
char* strIns(Ins ins);
//�ַ���ת��Ϊö��
CommonTrackState enumCommonTrackState(char* a);
Ins enumIns(char* a);
TrainState enumTrainState(char* a);

//IO.cpp
//DWORD WINAPI insDuringRun(LPVOID pPararneter);
void fLog(char show,char* fileName,int trainID,char* msg,clock_t curTime);
void showTrain();
void showTrack();
void showCommonTrack();

void dataInit();

void writeTrain(int ID,int trackID,unsigned long pos,int spd);
////���trainList.train[ID]����ΪNULL��������Ϊ�µ�Train����ռ䣬��д�������������ΪNULL������������д�롣
//
void writeTrack(int ID,unsigned long length,int cycle,
			int stationAmount,unsigned long stationPos[]);
////���trackList.track[ID]����ΪNULL��������Ϊ�µ�Track����ռ䣬��д�������������ΪNULL������������д�롣
//
void writeCommonTrack(int ID,int track1,int track2,
			int track1in,int track2in,int track1out,int track2out);
////���commonTrackList.track[ID]����ΪNULL��������Ϊ�µ�CommonTrack����ռ䣬��д���������
////����ΪNULL������������д�롣 ���������Train��λ�ã��ж�ռ���������д��commonTrackList.track[ID]->status

void fshowTrack(char* fName);
void fshowCommonTrack(char* fName);

void dataInit();//���ļ��ж�ȡ���ݣ����޸�

void startShow();

void userIns(clock_t curTime,clock_t frameDur);
//��moveAllTrain()�е��á�
//���û����г���ָ��д��ָ���б�Ins[],�����ڰ汾�У�����������ļ�����ָ�����ǰʱ���ָ��д��Ins[]


//debug.cpp
void dataInit_StandAlone();

//  move.cpp
unsigned long findNextStation(Train* train);
void moveTrain(Train* train,Ins ins,clock_t curTime,clock_t frameDur);
void judgeCommonTrack(CommonTrack* cT,Train* enter[],int ei,clock_t curTime);
void dealCommonTrack(CommonTrack* cT,Ins ins[],clock_t curTime,clock_t frameDur);
void checkCrash(clock_t curTime,clock_t frameDur);
void moveAllTrain(clock_t curTime,clock_t frameDur);
//��������commonTrack��train������״����ÿ��train����moveTrain()������ָ��.

//------------------------ͼ�λ�����
struct AniObj
{
    int trainID;
    int dir;//����,0Ϊ���ң�1Ϊ����
	float x, y;
};

void insByMouse(mouse_msg msg,int *trainID);
DWORD WINAPI printGraph(LPVOID pPararneter);

void printTrainInformation();
void printCommonTrackInformation();
void printStation();
void printCheckPoint();
void choiceTactics(mouse_msg msg);
void printTrain();
int askForPass(int train1, int train2);
#endif
