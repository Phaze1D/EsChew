//
//  Circle.h
//  SQ
//
//  Created by David Villarreal on 3/5/15.
//
//

#ifndef __SQ__Circle__
#define __SQ__Circle__

#include <stdio.h>
#include "cocos2d.h"
#include "SquareBox.h"

class Circle: public cocos2d::Sprite {
    
public:
    static const int CIRCLE_TAG = 64;
    static const int CIRCLE_CAT = 32;
    
    
    bool isPowerActive = false;
    
public:
   static Circle* createWithFile(const std::string& filename);
    
    void createPhysicsBody();
    
    void runStarPowerAnimation();
    
    void circleHitAnimation();
    
    
};

#endif /* defined(__SQ__Circle__) */
