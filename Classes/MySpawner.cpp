//
//  MySpawner.cpp
//  SQ
//
//  Created by David Villarreal on 3/4/15.
//
//

#include "MySpawner.h"
USING_NS_CC;

void MySpawner::createSpawner(SpawnerPosition position, Size sceneSize){
    this->sceneSize = sceneSize;
    this->position = position;
}


SquareBox* MySpawner::spawnBox(){
    
    
    return nullptr;
}


Color3B MySpawner::createRandomBrightColor(){
    
    Color3B color = Color3B(random(0, 255), random(0, 255), random(0, 255));
    
    int ave = (color.r + color.g + color.b)/3;
    
    if (ave < 70) {
        int rannum = random(1, 3);
        if (rannum == 1) {
            color.r += 40;
        }else if(rannum == 2){
            color.g += 40;
        }else{
            color.b += 40;
        }
    }
    return color;
}