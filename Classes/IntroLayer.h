//
//  IntroLayer.h
//  SQ
//
//  Created by David Villarreal on 3/2/15.
//
//

#ifndef __SQ__IntroLayer__
#define __SQ__IntroLayer__

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
    
    cocos2d::Vector<cocos2d::Node *> boxesIn;
    
    bool movedCircle = false;
    bool stopIntro = false;
    bool noMoreLifes = false;
    
    int moveCount = 0;
    int spawnCount = 0;
    
public:
    
    //Create method with parameters
    static IntroLayer* create(const cocos2d::Color4B &color);
    
    typedef std::function<void()> crossClickCallBack;
    crossClickCallBack crossClicked;
    
    void buildIntro();
    
    void update(float) override;
    
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
private:
    
    void buildCrossButton();
    void buildLives();
    void buildIntroAnimation();
    void buildSpawner();
    void buildCircle();
    void moveCircle();
    void moveToStar();
    void scaleCorrectly(float scale, cocos2d::Sprite*sprite);
    void handleCircleStarCol(Node * star);
    void handleCircleBoxCol(Node * box);
    
    void pausePhysics();
    void resumesPhysics();
    
    void createCircleSwitchAni();
    void createBoxExplo(Node* box, bool isCircle);
    
    cocos2d::Vec2 getExploPoint(int i, cocos2d::Vec2 startPosition);
    
    
    void endIntro();
    
    void addEvents();
    
};

#endif /* defined(__SQ__IntroLayer__) */
