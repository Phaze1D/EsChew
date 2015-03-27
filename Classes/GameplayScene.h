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


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "AdMobCPP.h"
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AndroidAdHelper.h"
#endif



class GameplayScene: public cocos2d::Scene {
    
    
public:

    static GameplayScene * createWithPhysics();
   
    typedef std::function<void()> HomeCallBack;
    HomeCallBack homeClick;
    
    void pauseGamePlayLayer();
    void resumeGamePlayLayer();
    
    IntroLayer * intro;
    CountDownLayer * countLayer;
    GamePlayLayer * gameLayer;
    GameOverLayer * gameOver;
    
private:
    void buildScene();
    void createBackground();
    void createIntroLayer();
    void createCountDown();
    void createGamePlayLayer();
    void createGameOverLayer(int score, int highScore);
    
    bool playing = false;

};

#endif /* defined(__SQ__GameplayScene__) */
