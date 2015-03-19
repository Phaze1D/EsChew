//
//  PlayerData.h
//  SQ
//
//  Created by David Villarreal on 3/2/15.
//
//

#ifndef __SQ__PlayerData__
#define __SQ__PlayerData__

#include <stdio.h>
#include "cocos2d.h"

class PlayerData {
    
private:
    const char* HIGH_SCORE_KEY = "HIGH";
    
    int highScore;
    
    
public:
    
    static PlayerData* getInstance();
    
    void savedData();
    
    int getHighScore();
    void setNewHightScore(int newHigh);
    
private:
    PlayerData(){};
    void init();
    
};

#endif /* defined(__SQ__PlayerData__) */
