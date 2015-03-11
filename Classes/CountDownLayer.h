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

USING_NS_CC;

class CountDownLayer: public cocos2d:: LayerColor {
    
private:
    cocos2d::Size boxSize;
    
    int boxOffset;
    
    std::vector<Vec2*> onePosition;
    std::vector<Vec2*> twoPosition;
    std::vector<Vec2*> threePosition;
    
    float timePassed;
    
    bool didCreateOne = false;
    bool didCreateTwo = false;
    bool didCreateThree = false;
    
public:
   static CountDownLayer* create(const Color4B &color);
    
    void beginCountDown();
    
    void createCountDown();
    
    void setBoxSize(const cocos2d::Size size);
    
    void update(float) override;
    
    typedef std::function<void()> countFinshCallBack;
    countFinshCallBack countFinishedCall;
    
private:
    std::vector<int> getBitmapNumber(int number);
    
    void resize();
    
    std::vector<Vec2*> calculatePosition(std::vector<int> array);
    
    void createBoxes(std::vector<Vec2*> positionVec);
    
    Color3B getRandomBrightColor();
    
    void moveToOutter();
    
    Vec2 getRandomOuterPosition();
        
};

#endif /* defined(__SQ__CountDownLayer__) */
