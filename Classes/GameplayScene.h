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
#include "GamePlayLayer.h"
#include "GameOverLayer.h"

class GameplayScene: public cocos2d::Scene {
    
    
public:
    
    static const int GAME_LAYER_TAG = 23;
    
    static GameplayScene * createWithPhysics();
   
    typedef std::function<void()> HomeCallBack;
    HomeCallBack homeClick;
    
    void pauseGamePlayLayer();
    void resumeGamePlayLayer();
    
private:
    void buildScene();
    void createBackground();
    void createIntroLayer();
    void createCountDown();
    void createGamePlayLayer();
    void createGameOverLayer(int score, int highScore);
    
};

#endif /* defined(__SQ__GameplayScene__) */
