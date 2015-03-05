//
//  GameplayScene.h
//  SQ
//
//  Created by David Villarreal on 3/2/15.
//
//

#ifndef __SQ__GameplayScene__
#define __SQ__GameplayScene__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "IntroLayer.h"
#include "CountDownLayer.h"

class GameplayScene: public cocos2d::Scene {
    
    
public:

    static GameplayScene * createWithPhysics();
    
    
private:
    
    void createBackground();
    void createIntroLayer();
    void createCountDown();
    
    
};

#endif /* defined(__SQ__GameplayScene__) */
