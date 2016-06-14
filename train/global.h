#include"Train.h"
#ifndef GLOBAL_H
#define GLOBAL_H
extern HANDLE hMutex;

extern Train* trainWaiting[MAX_COMMON_TRACK_AMOUNT];//各公共轨道正在等待来车的火车。下标是公共轨道ID
extern STG CTSTG;//公共轨道策略
extern char CTW;//有车到达公共轨道入口时，是否需要等待对面来车之后再决定谁走。若!CTW，只在公共轨道同时将有2车要入时进行决定。

extern clock_t startTime;

extern TrackList trackList;//此类唯一全局变量
extern CommonTrackList commonTrackList;//此类唯一全局变量
extern TrainList trainList;//此类唯一全局变量

extern InputIns inputIns;//此类唯一全局变量
extern Ins trainIns[MAX_TRAIN_AMOUNT];//指令列表
#endif
