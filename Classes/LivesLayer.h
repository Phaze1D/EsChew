//
//  LivesLayer.h
//  SQ
//
//  Created by David Villarreal on 3/5/15.
//
//

#ifndef __SQ__LivesLayer__
#define __SQ__LivesLayer__

#include <stdio.h>
#include "cocos2d.h"

class LivesLayer: public cocos2d::LayerColor {
    
public:
    static const int LIVE1_TAG = 12;
    static const int LIVE2_TAG = 15;
    static const int LIVE3_TAG = 16;
    static const int LIVE_LAYER = 21;
    
    int livesLeft = 4;
    
private:
    float offset = 6;
    
public:
    static LivesLayer* create(const cocos2d::Color4B &color);
    
    void buildLives(float scale);
    int decreaseLives();
    
    cocos2d::Color3B getCurrentColor();
    
    cocos2d::Vec2 getCurrentChildPostion();
    
private:
    //Only works with texture size of power of 2
    void scaleCorrectly(float scale, cocos2d::Sprite* sprite);
    
    void resize();
};

#endif /* defined(__SQ__LivesLayer__) */
