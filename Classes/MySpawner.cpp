//
//  MySpawner.cpp
//  SQ
//
//  Created by David Villarreal on 3/4/15.
//
//

#include "MySpawner.h"
USING_NS_CC;

void MySpawner::createSpawner(SpawnerPosition position, Rect sceneRect){
    this->sceneRect = sceneRect;
    this->position = position;
}


SquareBox* MySpawner::spawnBox(Size boxSize, Vec2 velocity){
    
    SquareBox * box = SquareBox::create();
    box->setTextureRect(Rect(0, 0,boxSize.width, boxSize.height));
    box->setColor(this->createRandomBrightColor());
    box->setPosition(this->getRandomPosition());
    box->createPhysicsBody(boxSize);
    
    this->getFinalVelocity(&velocity);
    box->getPhysicsBody()->setVelocity(velocity);
    
    return box;
}

void MySpawner::getFinalVelocity(cocos2d::Vec2 *velocity){
    
    if (position == RIGHT) {
        velocity->x = velocity->x * -1;
        
    }else if (position == LEFT){
        
        
    }else if(position == UPPER){
        velocity->y = velocity->y * -1;
        
    }else if(position == LOWER){
        
    }
}

Vec2 MySpawner::getRandomPosition(){
    
    float x = 0;
    float y = 0;
    
    if (position == RIGHT) {
        x = sceneRect.size.width;
        y = random((float)0,sceneRect.size.height);
        
    }else if (position == LEFT){
        x = 0;
        y = random((float)0,sceneRect.size.height);
        
    }else if(position == UPPER){
        x = random((float)0, sceneRect.size.width);
        y = sceneRect.size.height;
        
    }else if(position == LOWER){
        x = random((float)0, sceneRect.size.width);
        y = 0;
    }
    
    return Vec2(x, y);
}


Color3B MySpawner::createRandomBrightColor(){
    
    Color3B color = Color3B(random(0, 255), random(0, 255), random(0, 255));
    
    int ave = (color.r + color.g + color.b)/3;
    
    if (ave < 80) {
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