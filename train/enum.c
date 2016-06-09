#include "Train.h"

char* strTrainState(TrainState sta){
	switch(sta){
		case STOP: return "STOP";
		case STATION: return "STATION";
		case RUN: return "RUN";
		case WAIT: return "WAIT";
	}
}

TrainState enumTrainState(char* a){
    if(strcmp(a,"STOP")==0)
		return STOP;
	else if(strcmp(a,"STATION")==0)
		return STATION;
	else if(strcmp(a,"RUN")==0)
		return RUN;
	else if(strcmp(a,"WAIT")==0)
		return WAIT;
	else
	{
		printf("ERROR！请检查火车状态！");
		exit(0);
	}
}

char* strCommonTrackState(CommonTrackState sta){
	switch(sta){
		case FREE: return "FREE";
		case BUSY: return "BUSY";
		case ctWAIT: return "ctWAIT";
	}
}

CommonTrackState enumCommonTrackState(char* a){
	if(strcmp(a,"FREE")==0)
		return FREE;
	else if(strcmp(a,"BUSY")==0)
		return BUSY;
	else
	{
		printf("ERROR！请检查公共轨道状态！");
		exit(0);
	}
}

char* strIns(Ins ins){
	switch(ins){
		case HOLD: return "HOLD";
		case BRK: return "BRK";
		case ACC: return "ACC";
		case DOCK: return "DOCK";
	}
}

Ins enumIns(char* a){
    if(strcmp(a,"HOLD")==0)
        return HOLD;
	else if(strcmp(a,"BRK")==0)
		return BRK;
	else if(strcmp(a,"ACC")==0)
		return ACC;
	else if(strcmp(a,"DOCK")==0)
		return DOCK;
	else
	{
		printf("ERROR！请检查指令信息！");
		exit(0);
	}
}
