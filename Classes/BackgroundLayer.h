//
//  BackgroundLayer.h
//  SQ
//
//  Created by David Villarreal on 2/26/15.
//
//

#ifndef __SQ__BackgroundLayer__
#define __SQ__BackgroundLayer__

#include "cocos2d.h"

class BackgroundLayer: public cocos2d::Layer {
    
    
public:
    CREATE_FUNC(BackgroundLayer);
    
    virtual bool init();
    
    
private:
    void createParticles();
};

#endif /* defined(__SQ__BackgroundLayer__) */
