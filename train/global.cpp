#include "global.h"

HANDLE hMutex;

Train* trainWaiting[MAX_COMMON_TRACK_AMOUNT];//������������ڵȴ������Ļ𳵡��±��ǹ������ID
STG CTSTG;//�����������
char CTW;//�г����﹫��������ʱ���Ƿ���Ҫ�ȴ���������֮���پ���˭�ߡ���!CTW��ֻ�ڹ������ͬʱ����2��Ҫ��ʱ���о�����

clock_t startTime;

TrackList trackList;//����Ψһȫ�ֱ���
CommonTrackList commonTrackList;//����Ψһȫ�ֱ���
TrainList trainList;//����Ψһȫ�ֱ���

InputIns inputIns;//����Ψһȫ�ֱ���
Ins trainIns[MAX_TRAIN_AMOUNT];//ָ���б�