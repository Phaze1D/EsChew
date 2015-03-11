//
//  GamePlayLayer.h
//  SQ
//
//  Created by David Villarreal on 3/11/15.
//
//

#ifndef __SQ__GamePlayLayer__
#define __SQ__GamePlayLayer__

#include <stdio.h>
#include <vector>
#include "cocos2d.h"
#include "MySpawner.h"
#include "Circle.h"
#include "SquareBox.h"
#include "GameStageController.h"


class GamePlayLayer: public cocos2d::LayerColor{
    
private:

    std::vector<MySpawner*> spawners;

    Circle* circle;
    
    
    
public:
    
    static GamePlayLayer* create(const cocos2d::Color4B &color);
    
    void update(float) override;
    
private:
    
    void buildGameLayer();
    
    void createSpawners();
    void deleteSpawners();
    
    void addTouchHandlers();
    
    void createCircle();
    
};

#endif /* defined(__SQ__GamePlayLayer__) */
