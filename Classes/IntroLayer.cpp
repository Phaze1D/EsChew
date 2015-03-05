//
//  IntroLayer.cpp
//  SQ
//
//  Created by David Villarreal on 3/2/15.
//
//

#include "IntroLayer.h"

USING_NS_CC;

IntroLayer* IntroLayer::create(const cocos2d::Color4B &color){
    
    IntroLayer * layer = new (std::nothrow) IntroLayer();
    if(layer && layer->initWithColor(color))
    {
        layer->autorelease();
        layer->addEvents();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
    
}

void IntroLayer::update(float timeTook){
    
    //Spawn Box
    if (timePassed >= defaultSpawnRate) {
        this->addChild(spawner->spawnBox());
        
    }
    
    //Remove Box if box is out of layer bound
    
}

void IntroLayer::buildIntro(){
    defaultSpawnRate = 1/5.0;
    this->buildCrossButton();
    this->buildLives();
    this->buildIntroAnimation();
    //this->scheduleUpdate();
    
}

void IntroLayer::buildCrossButton(){
    
    auto crossButton = Sprite::create("cross.png");
    crossButton->setScale(.2);
    crossButton->setAnchorPoint(Vec2(0.5, 0.5));
    crossButton->setPosition(Vec2(0, this->getContentSize().height));
    this->addChild(crossButton);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&, crossButton](Touch* touch, Event* event){
        
        Rect rect = crossButton->getBoundingBox();
        Vec2 point = touch->getLocation();
        rect.size.height = rect.size.height*5;
        rect.size.width = rect.size.width*5;
        
        if (rect.containsPoint(point)) {
            //this->unscheduleUpdate();
            delete this->spawner;
            this->crossClicked();
            return true;
        }
        
        return false;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        // your code
    };
    
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        // your code
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, crossButton);
}

void IntroLayer::buildLives(){
    LivesLayer * liveLayer = LivesLayer::create(Color4B(255, 255, 255, 0));
    liveLayer->buildLives();
    
    this->addChild(liveLayer);
    
    
}

void IntroLayer::buildIntroAnimation(){
    this->buildSpawner();
    this->buildCircle();
    
}

void IntroLayer::buildSpawner(){
    spawner = new MySpawner();
    spawner->createSpawner(RIGHT, this->getContentSize().height);
    
}

void IntroLayer::buildCircle(){
    
}

void IntroLayer::addEvents(){
    
}