#include"Train.h"
#ifndef GLOBAL_H
#define GLOBAL_H
extern HANDLE hMutex;

extern Train* trainWaiting[MAX_COMMON_TRACK_AMOUNT];//������������ڵȴ������Ļ𳵡��±��ǹ������ID
extern STG CTSTG;//�����������
extern char CTW;//�г����﹫��������ʱ���Ƿ���Ҫ�ȴ���������֮���پ���˭�ߡ���!CTW��ֻ�ڹ������ͬʱ����2��Ҫ��ʱ���о�����

extern clock_t startTime;
extern clock_t currentTime;
extern clock_t lastTime;

extern TrackList trackList;//����Ψһȫ�ֱ���
extern CommonTrackList commonTrackList;//����Ψһȫ�ֱ���
extern TrainList trainList;//����Ψһȫ�ֱ���

extern InputIns inputIns;//����Ψһȫ�ֱ���
extern Ins trainIns[MAX_TRAIN_AMOUNT];//ָ���б�

extern PIMAGE backGround;
extern PIMAGE trainPic;
extern PIMAGE button;
extern PIMAGE checkPointGreen;
extern PIMAGE checkPointRed;
extern int tacticsOrIns;

extern AniObj obj[MAX_TRAIN_AMOUNT]; //�����������

extern clock_t mouseFlag;
#endif
