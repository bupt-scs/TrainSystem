#include "Train.h"
#include "global.h"

#define FRAME_COUNT 10 //每这么多帧输出一下

using namespace std;

int main(void)
{
    int i;
	dataInit();
    //dataInit_StandAlone();

    FILE* f=fopen("Log.txt","w");fclose(f);
    fshowTrack("Log.txt");
    fshowCommonTrack("Log.txt");
    //初始化日志

	clock_t currentTime = clock();
	clock_t lastTime = clock();
	int frameCount = FRAME_COUNT;
    const clock_t frameDur=40;

    if(CTW)
        for(i=0;i<MAX_COMMON_TRACK_AMOUNT;i++)
            trainWaiting[i]=NULL;

    setinitmode(INIT_ANIMATION);
    initgraph(900,675);

    //获得背景图片
    backGround = newimage();
    getimage(backGround,"img/background.png");
    trainPic = newimage();
    getimage(trainPic,"img/train.png");
    button = newimage();
    getimage(button,"img/button/acc_0.png");
    //鼠标监视线程
    HANDLE hThread1;
    //图形输出线程
    HANDLE hThread2;

	hMutex=CreateMutex(NULL,FALSE,NULL);

	hThread1=CreateThread(NULL,0,printGraph,NULL ,0,NULL);
	CloseHandle(hThread1);

    startTime = clock();
	while(1)
	{
	    WaitForSingleObject(hMutex,INFINITE);
		lastTime = currentTime;

		moveAllTrain(currentTime-startTime,frameDur);

		if(!frameCount)
		{
			frameCount = FRAME_COUNT;

            fLog(1,"Log.txt",-1,"",currentTime-startTime);
		}
		while(currentTime-lastTime<frameDur)
		currentTime = clock();
		frameCount--;

		ReleaseMutex(hMutex);
	}
	freeLists();
//	closegraph();
	return 0;
}
