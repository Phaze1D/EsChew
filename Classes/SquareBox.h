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
    
private:
    cocos2d::Vec2 velocity;
    
    
public:
    
    CREATE_FUNC(SquareBox);
    
    void createPhysicsBody(cocos2d::Size size);
    
    void boxHitAnimation();
    
};

#endif /* defined(__SQ__SquareBox__) */
