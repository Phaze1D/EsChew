//
//  SquareBox.h
//  SQ
//
//  Created by David Villarreal on 3/5/15.
//
//

#ifndef __SQ__SquareBox__
#define __SQ__SquareBox__

#include <stdio.h>
#include "cocos2d.h"

class SquareBox: public cocos2d::Sprite{
    
public:
    static const int BOX_RIGHT = 2;
    static const int BOX_LEFT = 4;
    static const int BOX_UPPER = 8;
    static const int BOX_LOWER = 16;
    
    cocos2d::Vec2 velocity;
    
    
public:
    
    CREATE_FUNC(SquareBox);
    
    void createPhysicsBody(cocos2d::Size size);
    void pausePhysics();
    void resumePhysics();
    
    
};

#endif /* defined(__SQ__SquareBox__) */
