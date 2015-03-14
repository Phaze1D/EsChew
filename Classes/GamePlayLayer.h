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
#include <list>
#include "cocos2d.h"
#include "MySpawner.h"
#include "Circle.h"
#include "SquareBox.h"
#include "GameStageController.h"
#include "LivesLayer.h"


class GamePlayLayer: public cocos2d::LayerColor{
    
private:

    std::vector<MySpawner*> spawners;
    std::list<SquareBox*> nodesIn;

    Circle* circle;
    
    float gameTime = 0;
    
    bool isPaused = false;
    bool noMoreLifes = false;
    
    int test = 0;
public:
    
    static GamePlayLayer* create(const cocos2d::Color4B &color);
    
    void update(float) override;
    
private:
    
    void buildGameLayer();
    
    void createSpawners();
    void deleteSpawners();
    
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    void addTouchHandlers();
    
    void deleteNodesIn();
    
    void createLivesLayer();
    
    void createCircle();
    
    void handleCircleBoxCol(cocos2d::Node*box);
    void handleCircleStarCol(cocos2d::Node*star);
    
    void spawnBall(float deltaTime);
    void spawnStar(float deltaTime);
    void checkBoxIn();
    
    void createBoxExplo(cocos2d::Node* box, bool isCircle);
    
    void pausePhysics();
    void resumePhysics();
    void createCircleSwitchAni();
    
    void scaleCorrectly(float scale, cocos2d::Sprite * sprite);
    
    cocos2d::Vec2 getExploPoint(int i, cocos2d::Vec2 startPosition);
    
};

#endif /* defined(__SQ__GamePlayLayer__) */
