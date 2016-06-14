#include "Train.h"
#include "global.h"
#define FRAME_COUNT 10 //ÿ��ô��֡���һ��


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
    //��ʼ����־

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
			printf("\n����������ʱ�� %.3fs\t", (double)(currentTime-startTime)/CLOCKS_PER_SEC);
			printf("FPS=%.3f\n", (double)CLOCKS_PER_SEC/frameDur);

            switch(CTSTG){
                case ASK:printf("ѯ���˹�����\n");break;
                case FFI:printf("�쳵���в���\n");break;
                case RAD:printf("�������\n");break;
            }

			//fflush(stdout);
			showTrain();
			puts(hr);
			showCommonTrack();
			printf("%d\n",startTime);

			printf("�밴�س�������ָ��:");
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
