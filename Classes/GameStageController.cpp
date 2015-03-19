//
//  GameStageController.cpp
//  SQ
//
//  Created by David Villarreal on 3/11/15.
//
//

#include "GameStageController.h"


void GameStageController::init(std::vector<MySpawner*> spawners){
    this->spawners = spawners;
    highScore = PlayerData::getInstance()->getHighScore();
    stageAt = 0;
    createCombination();
}


void GameStageController::update(float amount){
    gameTime+=amount;
    
    if (!setStage) {
        this->setStageOptions();
        setStage = true;
    }
    
    
    
}

void GameStageController::setStageOptions(){
    
    int combinationNumber = stages.at(stageAt);
    
    int spawnerNumber = combinationNumber%10;
    
    while (spawnerNumber != 0) {
        if (spawnerNumber == 4) {
            spawners[0]->spawnReady = true;
        }else{
            spawners[spawnerNumber]->spawnReady = true;
        }
        
        combinationNumber = combinationNumber/10;
        
        spawnerNumber = combinationNumber%10;
    }
   
}

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

int GameStageController::getGameScore(){
    return gameScore;
}

int GameStageController::getHighScore(){
    if (gameScore>highScore) {
        highScore = gameScore;
        PlayerData::getInstance()->setNewHightScore(gameScore);
    }
    return highScore;
}

bool GameStageController::recordReached(){
 
    if ( gameScore > highScore && !newRecordReached) {
        newRecordReached = true;
        return true;
    }
    
    return false;
    
}


void GameStageController::createCombination(){
    
    /*
     
     r = 4
     u = 1
     b = 2
     l = 3
     
     r-
     u-
     l-
     b-
     
     ur-
     lr-
     br-
     ul-
     ub-
     bl
     
     ulr
     ubr
     blr
     blu
     
     rblu
     
     */
    
    stages.reserve(15);
    
    
    stages.push_back(4);
    stages.push_back(1);
    stages.push_back(2);
    stages.push_back(3);
    
    stages.push_back(14);
    stages.push_back(34);
    stages.push_back(24);
    stages.push_back(13);
    stages.push_back(12);
    stages.push_back(23);
    
    stages.push_back(134);
    stages.push_back(124);
    stages.push_back(234);
    stages.push_back(231);
    
    stages.push_back(1423);
    
}