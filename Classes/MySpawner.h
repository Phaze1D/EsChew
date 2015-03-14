//
//  MySpawner.h
//  SQ
//
//  Created by David Villarreal on 3/4/15.
//
//

#ifndef __SQ__MySpawner__
#define __SQ__MySpawner__

#include <stdio.h>
#include "cocos2d.h"
#include "SquareBox.h"
#include "StarPower.h"

enum SpawnerPosition {
    UPPER,
    LOWER,
    RIGHT,
    LEFT,
};

class MySpawner {
    
public:
    cocos2d::Size ballSize;
    
    float timePassed = 0;
    float spawnRate = 1;
    
    bool spawnReady = false;
    
    
private:
    cocos2d::Rect sceneRect;
    SpawnerPosition position;
    
    float passIntroY = 0;
    
public:
    
    void createSpawner(SpawnerPosition position, cocos2d::Rect sceneRect);
    
    SquareBox* spawnBox(cocos2d::Size boxSize, float velocity);
    
    SquareBox* introSpawnBox(cocos2d::Size boxSize, float velocity);
    
    StarPower * spawnStar(float velocity);
  
private:
    cocos2d::Color3B createRandomBrightColor();
    
    cocos2d::Vec2 getRandomPosition();
    cocos2d::Vec2 getRandomIntroPosition();
    cocos2d::Vec2 getFinalVelocity(float velocity);
    
    void scaleCorrectly(float scale, cocos2d::Sprite * sprite);
    
    int getBoxCat();
    
};


#endif /* defined(__SQ__MySpawner__) */
