#include "Train.h"
#include "global.h"
#define FRAME_COUNT 10 //每这么多帧输出一下


using namespace std;

int main(void)
{
    int i;
    startShow();
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

    if(CTW) for(i=0;i<MAX_COMMON_TRACK_AMOUNT;i++)
                trainWaiting[i]=NULL;

    HANDLE hThread1;
	hMutex=CreateMutex(NULL,FALSE,NULL);
	hThread1=CreateThread(NULL,0,insDuringRun,NULL ,0,NULL);
	CloseHandle(hThread1);

    startTime = clock();
    fflush(stdin);
	while(1)
	{
	    WaitForSingleObject(hMutex,INFINITE);
		lastTime = currentTime;

		moveAllTrain(currentTime-startTime,frameDur);

		if(!frameCount)
		{
		    system("cls");
		    startShow();
			printf("\n程序已运行时间 %.3fs\t", (double)(currentTime-startTime)/CLOCKS_PER_SEC);
			printf("FPS=%.3f\n", (double)CLOCKS_PER_SEC/frameDur);

            switch(CTSTG){
                case ASK:printf("询问人工策略\n");break;
                case FFI:printf("快车先行策略\n");break;
                case RAD:printf("随机策略\n");break;
            }

			//fflush(stdout);
			showTrain();
			puts(hr);
			showCommonTrack();
			printf("%d\n",startTime);

			printf("请按回车键输入指令:");
			frameCount = FRAME_COUNT;

            fLog(1,"Log.txt",-1,"",currentTime-startTime);
		}
		while(currentTime-lastTime<frameDur)
		currentTime = clock();
		frameCount--;
		ReleaseMutex(hMutex);
	}
	freeLists();
	return 0;
}
