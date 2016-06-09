#include"train.h"

void dataInit_StandAlone(){
    int i;
    CTSTG=ASK;
    CTW=1;
    trainList.amount=2;
    for(i=0;i<trainList.amount;i++) trainList.train[i]=(Train*)malloc(sizeof(Train));

    trainList.train[0]->defaultDockTime=3000;
    trainList.train[0]->dockTime=0;
    trainList.train[0]->ID=0;
    trainList.train[0]->pos=0;
    trainList.train[0]->status=STATION;
    trainList.train[0]->trackID=0;
    trainList.train[0]->spd=5;

    trainList.train[1]->defaultDockTime=2000;
    trainList.train[1]->dockTime=0;
    trainList.train[1]->ID=1;
    trainList.train[1]->pos=200;
    trainList.train[1]->status=RUN;
    trainList.train[1]->trackID=1;
    trainList.train[1]->spd=-3;

    trackList.amount=2;
    for(i=0;i<trackList.amount;i++) trackList.track[i]=(Track*)malloc(sizeof(Track));

    trackList.track[0]->cycle=1;
    trackList.track[0]->ID=0;
    trackList.track[0]->length=160000ul;
    trackList.track[0]->stationAmount=1;
    trackList.track[0]->stationPos[0]=5000;

    trackList.track[1]->cycle=1;
    trackList.track[1]->ID=1;
    trackList.track[1]->length=160000ul;
    trackList.track[1]->stationAmount=0;
    trackList.track[1]->stationPos[0]=0;

    commonTrackList.amount=0;
    for(i=0;i<commonTrackList.amount;i++) commonTrackList.commonTrack[i]=(CommonTrack*)malloc(sizeof(CommonTrack));

//    commonTrackList.commonTrack[0]->ID=0;
//    commonTrackList.commonTrack[0]->status=FREE;
//    commonTrackList.commonTrack[0]->track1=0;
//    commonTrackList.commonTrack[0]->track2=1;
//    commonTrackList.commonTrack[0]->track1in=9000ul;
//    commonTrackList.commonTrack[0]->track1out=12000ul;
//    commonTrackList.commonTrack[0]->track2in=4000;
//    commonTrackList.commonTrack[0]->track2out=7000ul;
}
