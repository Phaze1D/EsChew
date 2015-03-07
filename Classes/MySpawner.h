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

enum SpawnerPosition {
    UPPER,
    LOWER,
    RIGHT,
    LEFT,
};

class MySpawner {
    
private:
    cocos2d::Rect sceneRect;
    SpawnerPosition position;
    
public:
    
    void createSpawner(SpawnerPosition position, cocos2d::Rect sceneRect);
    
    SquareBox* spawnBox(cocos2d::Size boxSize, cocos2d::Vec2 velocity);
    
    SquareBox* introSpawnBox(cocos2d::Size boxSize, cocos2d::Vec2 velocity);
  
private:
    cocos2d::Color3B createRandomBrightColor();
    cocos2d::Vec2 getRandomPosition();
    void getFinalVelocity(cocos2d::Vec2* velocity);
};


#endif /* defined(__SQ__MySpawner__) */
