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
    
    bool isPaused = false;
    bool noMoreLifes = false;
    bool isSwitching = false;
    
    int test = 0;
    
    cocos2d::Label* pointsLabel;
    
    GameStageController * gameCon;
    
public:
    
    typedef std::function<void(int score, int highScore)> gameOverCallBack;
    gameOverCallBack gameOverCall;
    
    static GamePlayLayer* create(const cocos2d::Color4B &color);
    
    void update(float) override;
    
    void pauseLayer();
    void resumeLayer();
    
private:
    
    void buildGameLayer();
    
    void createSpawners();
    void deleteSpawners();
    
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    void addTouchHandlers();
    
    void deleteNodesIn();
    
    void createLivesLayer();
    void createCircle();
    void createPointLabel();
    
    void handleCircleBoxCol(cocos2d::Node*box);
    void handleCircleStarCol(cocos2d::Node*star);
    
    void spawnBall(float deltaTime);
    void spawnStar(float deltaTime);
    
    void updatePointsLabel(int amount);
    void checkBoxIn();
    
    void createBoxExplo(cocos2d::Node* box, bool isCircle);
    
    void pausePhysics();
    void resumePhysics();
    void createCircleSwitchAni();
    
    void createNewRecordAni();
    
    void scaleCorrectly(float scale, cocos2d::Sprite * sprite);
    
    void updateSpawnRate();
    
    cocos2d::Vec2 getExploPoint(int i, cocos2d::Vec2 startPosition);
    
    void saveDataAndDelete();
    
    void deleteAll();
    
};

#endif /* defined(__SQ__GamePlayLayer__) */
