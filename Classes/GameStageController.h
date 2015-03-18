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

class GameStageController {
    
private:
    float gameTime = 0;
    int gameScore = 0;
    int highScore = 10;
    
    int next = 1;
    
    bool newRecordReached = false;
    
public:
    
    int increaseScore();
    int increaseScoreByHit();
    
    int getGameScore();
    int getHighScore();
    
    void increaseGameTime(float amount);
    
    bool recordReached();
    
    
};

#endif /* defined(__SQ__GameStageController__) */
