//
//  GameStageController.cpp
//  SQ
//
//  Created by David Villarreal on 3/11/15.
//
//

#include "GameStageController.h"


int GameStageController::increaseScore(){
    
    if ((int)gameTime == next) {
        gameScore+= 1;
        next+= 1;
        return gameScore;
    }
    
    return 0;
}

int GameStageController::increaseScoreByHit(){
    gameScore += 5;
    return gameScore;
}

void GameStageController::increaseGameTime(float amount){
    gameTime+=amount;
    
}

int GameStageController::getGameScore(){
    return gameScore;
}

int GameStageController::getHighScore(){
    return highScore;
}

bool GameStageController::recordReached(){
 
    if ( gameScore > highScore && !newRecordReached) {
        newRecordReached = true;
        return true;
    }
    
    return false;
    
}