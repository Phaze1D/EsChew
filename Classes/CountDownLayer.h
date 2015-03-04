//
//  CountDownLayer.h
//  SQ
//
//  Created by David Villarreal on 3/3/15.
//
//

#ifndef __SQ__CountDownLayer__
#define __SQ__CountDownLayer__

#include <stdio.h>
#include "cocos2d.h"
#include <vector>

class CountDownLayer: public cocos2d:: LayerColor {
    
private:
    cocos2d::Size boxSize;
    
    int boxOffset;
    
    std::vector<cocos2d::Vec2> onePosition;
    std::vector<cocos2d::Vec2> twoPosition;
    std::vector<cocos2d::Vec2> threePosition;
    
    float timePassed;
    
    bool didCreateOne = false;
    bool didCreateTwo = false;
    bool didCreateThree = false;
    
public:
   static CountDownLayer* create(const cocos2d::Color4B &color);
    
    void beginCountDown();
    
    void createCountDown();
    
    void setBoxSize(const cocos2d::Size size);
    
    void update(float) override;
    
private:
    std::vector<int> getBitmapNumber(int number);
    
    void resize();
    
    std::vector<cocos2d::Vec2> calculatePosition(std::vector<int> array);
    
    void createBoxes(std::vector<cocos2d::Vec2> positionVec);
    
    cocos2d::Color3B getRandomBrightColor();
    
    void moveToOutter();
    
    cocos2d::Vec2 getRandomOuterPosition();
    
};

#endif /* defined(__SQ__CountDownLayer__) */
