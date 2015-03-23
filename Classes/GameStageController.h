//
//  GameStageController.h
//  SQ
//
//  Created by David Villarreal on 3/11/15.
//
//

#ifndef __SQ__GameStageController__
#define __SQ__GameStageController__

#include <stdio.h>
#include <vector>
#include "PlayerData.h"
#include "MySpawner.h"



class GameStageController {
    
private:
    
    std::vector<MySpawner*> spawners;
    std::vector<int> stages;
    
    float gameTime = 0;
    
    int gameScore = 0;
    int highScore = 0;
    int nextScore = 1;
    int stageAt = 0;
    int nextStage = 40;
    
    bool newRecordReached = false;
    bool setStage = false;
    
public:
    
    void init(std::vector<MySpawner*> spawners);
    
    int increaseScore();
    int increaseScoreByHit();
    
    int getGameScore();
    int getHighScore();
    
    void update(float amount);
    
    bool recordReached();

private:
    void createCombination();
    void setStageOptions();
    void setTotalDifficulty();
    
    
    
    
};

#endif /* defined(__SQ__GameStageController__) */
