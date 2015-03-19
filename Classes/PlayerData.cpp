//
//  PlayerData.cpp
//  SQ
//
//  Created by David Villarreal on 3/2/15.
//
//

#include "PlayerData.h"
USING_NS_CC;


static PlayerData* shareInstance = nullptr;

PlayerData* PlayerData::getInstance(){
    
    if(!shareInstance){
        shareInstance = new PlayerData();
        shareInstance->init();
    }
    
    return shareInstance;
    
}

void PlayerData::init(){
    highScore = UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE_KEY);
    
}

void PlayerData::savedData(){
    UserDefault::getInstance()->setIntegerForKey(HIGH_SCORE_KEY, highScore);
    UserDefault::getInstance()->flush();
}

int PlayerData::getHighScore(){
    return highScore;
}

void PlayerData::setNewHightScore(int newHigh){
    highScore = newHigh;
}