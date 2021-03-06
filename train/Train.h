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
**		   类名每个单词首字母都大写 ！							           **
**		   变量和函数首字母小写，以后每一个单词首字母大写 ！			   **
**															               **
*****************************************************************************
****************************************************************************/

//火车状态
typedef enum{
	STOP, 	//停止
	STATION,//停靠
	RUN	,	//运行
	WAIT	//等待公共轨道空闲
}TrainState;

//公共轨道状态
typedef enum{
	FREE,	//空闲
	BUSY,	//已占用
	ctWAIT
}CommonTrackState;

//火车指令
typedef enum{
	HOLD,   //保持
	BRK,	//制动
	ACC,	//加速
	DOCK,	//停靠
}Ins;

//公共轨道策略
typedef enum{
	FFI,	//快先
	ASK,	//询问
	RAD,    //随机
	JT      //交替
}STG;

typedef struct{
	int ID; //在trackList.track[]的下标
	unsigned long length;//轨道长度。所有轨道的单位都统一.
	int cycle;//是否环路
	int stationAmount;//车站总数
	unsigned long stationPos[MAX_STATION_AMOUNT];//各车站的坐标。在最初读入轨道数据的时候保证车站坐标按升序录入此数组。
} Track;

typedef struct{
	int ID;					//在trainList.train[]里的下标
	int trackID; 			//所在轨道ID
	unsigned long pos; 		//在轨道上的坐标
	int spd; 				//速度(可非正)
	clock_t dockTime;
	long defaultDockTime;
	TrainState status;
}Train;

typedef struct{
	int ID; //在commonTrackList.commonTrack[]里的下标
	int track1;
	int track2;//两轨之ID
	unsigned long track1in;
	unsigned long track2in;
	unsigned long track1out;
	unsigned long track2out;
    CommonTrackState status;
    Train* lastUser;//上次准入的火车
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

//static Ins trainIns[MAX_TRAIN_AMOUNT];//指令列表
//static Train* trainWaiting[MAX_COMMON_TRACK_AMOUNT];//各公共轨道正在等待来车的火车。下标是公共轨道ID
//static STG CTSTG;//公共轨道策略
//static char CTW;//有车到达公共轨道入口时，是否需要等待对面来车之后再决定谁走。若!CTW，只在公共轨道同时将有2车要入时进行决定。
//static HANDLE hMutex;
//static clock_t startTime;
//-----------------------------------------------------------------------

void freeLists(void);
//free三个list
void dataInit_StandAlone();

//enum.cpp
//枚举转换为字符串
char* strTrainState(TrainState sta);
char* strCommonTrackState(CommonTrackState sta);
char* strIns(Ins ins);
//字符串转换为枚举
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
////检查trainList.train[ID]，若为NULL，在这里为新的Train申请空间，并写入各参数。若不为NULL，将参数覆盖写入。
//
void writeTrack(int ID,unsigned long length,int cycle,
			int stationAmount,unsigned long stationPos[]);
////检查trackList.track[ID]，若为NULL，在这里为新的Track申请空间，并写入各参数。若不为NULL，将参数覆盖写入。
//
void writeCommonTrack(int ID,int track1,int track2,
			int track1in,int track2in,int track1out,int track2out);
////检查commonTrackList.track[ID]，若为NULL，在这里为新的CommonTrack申请空间，并写入各参数。
////若不为NULL，将参数覆盖写入。 最后检查所有Train的位置，判断占用情况，并写入commonTrackList.track[ID]->status

void fshowTrack(char* fName);
void fshowCommonTrack(char* fName);

void dataInit();//从文件中读取数据，并修改

void startShow();

void userIns(clock_t curTime,clock_t frameDur);
//在moveAllTrain()中调用。
//将用户对列车的指令写入指令列表Ins[],在早期版本中，这个函数从文件读入指令，将当前时间的指令写入Ins[]


//debug.cpp
void dataInit_StandAlone();

//  move.cpp
unsigned long findNextStation(Train* train);
void moveTrain(Train* train,Ins ins,clock_t curTime,clock_t frameDur);
void judgeCommonTrack(CommonTrack* cT,Train* enter[],int ei,clock_t curTime);
void dealCommonTrack(CommonTrack* cT,Ins ins[],clock_t curTime,clock_t frameDur);
void checkCrash(clock_t curTime,clock_t frameDur);
void moveAllTrain(clock_t curTime,clock_t frameDur);
//遍历所有commonTrack和train，根据状况对每个train调用moveTrain()，传达指令.

//------------------------图形化内容
struct AniObj
{
    int trainID;
    int dir;//方向,0为左右，1为上下
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
