//
//  StarPower.h
//  SQ
//
//  Created by David Villarreal on 3/9/15.
//
//

#ifndef __SQ__StarPower__
#define __SQ__StarPower__

#include <stdio.h>
#include "cocos2d.h"

class StarPower: public cocos2d::Sprite  {
    
public:
    static const int STAR_TAG = 68;
    
public:

    static StarPower* createWithFile(const std::string& filename);
    
    void createPhysicsBody();
    void runAnimation();
};

#endif /* defined(__SQ__StarPower__) */
