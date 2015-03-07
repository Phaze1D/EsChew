//
//  IntroLayer.h
//  SQ
//
//  Created by David Villarreal on 3/2/15.
//
//

#ifndef __SQ__IntroLayer__
#define __SQ__IntroLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "MySpawner.h"
#include "Circle.h"
#include "LivesLayer.h"
#include "SquareBox.h"


class IntroLayer: public cocos2d::LayerColor {
    
public:
    static const int LIVE_LAYER = 101;
    
private:
    MySpawner * spawner;
    
    Circle * circle;
    
    float defaultSpawnRate;
    float timePassed = 0;
    
    //float deltaTime;
    
    cocos2d::Vector<SquareBox *> boxesIn;
    
public:
    
    //Create method with parameters
    static IntroLayer* create(const cocos2d::Color4B &color);
    
    typedef std::function<void()> crossClickCallBack;
    crossClickCallBack crossClicked;
    
    void buildIntro();
    
    void update(float) override;
    
private:
    
    void buildCrossButton();
    void buildLives();
    void buildIntroAnimation();
    void buildSpawner();
    void buildCircle();

    void scaleCorrectly(float scale, cocos2d::Sprite*sprite);
    
    void addEvents();
    
};

#endif /* defined(__SQ__IntroLayer__) */
