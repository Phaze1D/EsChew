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

class Circle: public cocos2d::Sprite {
    
    
public:
   static Circle* createWithFile(const std::string& filename);
    
    void createPhysicsBody();
    
    
};

#endif /* defined(__SQ__Circle__) */
