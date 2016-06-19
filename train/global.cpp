#include "global.h"

HANDLE hMutex;

Train* trainWaiting[MAX_COMMON_TRACK_AMOUNT];//各公共轨道正在等待来车的火车。下标是公共轨道ID
STG CTSTG;//公共轨道策略
char CTW;//有车到达公共轨道入口时，是否需要等待对面来车之后再决定谁走。若!CTW，只在公共轨道同时将有2车要入时进行决定。

clock_t startTime;
clock_t currentTime;
clock_t lastTime;

TrackList trackList;//此类唯一全局变量
CommonTrackList commonTrackList;//此类唯一全局变量
TrainList trainList;//此类唯一全局变量

InputIns inputIns;//此类唯一全局变量
Ins trainIns[MAX_TRAIN_AMOUNT];//指令列表

PIMAGE backGround;
PIMAGE trainPic;
PIMAGE button;

PIMAGE checkPointGreen;
PIMAGE checkPointRed;

int tacticsOrIns;
AniObj obj[MAX_TRAIN_AMOUNT]; //定义对象数组

clock_t mouseFlag;
