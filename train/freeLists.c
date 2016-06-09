#include"Train.h"
void freeLists(void){
        int i;
        for(i = 0;i < MAX_TRAIN_AMOUNT;i++){
                if(trainList.train[i] == NULL)        continue;
                else        free(trainList.train[i]);
        }
        for(i = 0;i < MAX_TRACK_AMOUNT;i++){
                if(trackList.track[i] == NULL)        continue;
                else        free(trackList.track[i]);
        }
        for(i = 0;i < MAX_COMMON_TRACK_AMOUNT;i++){
                if(commonTrackList.commonTrack[i] == NULL)        continue;
                else        free(commonTrackList.commonTrack[i]);
        }
}
