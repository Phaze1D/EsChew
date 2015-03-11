//
//  GamePlayLayer.cpp
//  SQ
//
//  Created by David Villarreal on 3/11/15.
//
//

#include "GamePlayLayer.h"
USING_NS_CC;


GamePlayLayer* GamePlayLayer::create(const cocos2d::Color4B &color){
    
    GamePlayLayer * layer = new (std::nothrow) GamePlayLayer();
    if(layer && layer->initWithColor(color))
    {
        layer->autorelease();
        layer->buildGameLayer();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
    
}

void GamePlayLayer::update(float deltaTime){
    
}


void GamePlayLayer::buildGameLayer(){
    this->createSpawners();
    this->createCircle();
    
}

void GamePlayLayer::createSpawners(){
    spawners.reserve(4);
    
    MySpawner * spawner1 = new MySpawner();
    spawner1->createSpawner(UPPER, this->getBoundingBox());
    spawners.push_back(spawner1);
    
    MySpawner * spawner2 = new MySpawner();
    spawner2->createSpawner(RIGHT, this->getBoundingBox());
    spawners.push_back(spawner2);
    
    MySpawner * spawner3 = new MySpawner();
    spawner3->createSpawner(LOWER, this->getBoundingBox());
    spawners.push_back(spawner3);
    
    MySpawner * spawner4 = new MySpawner();
    spawner4->createSpawner(LEFT, this->getBoundingBox());
    spawners.push_back(spawner4);
}

void GamePlayLayer::deleteSpawners(){
    for (int i = 0; i < spawners.size(); i++) {
        delete spawners[i];
    }
    spawners.clear();
}

void GamePlayLayer::createCircle(){
    
    circle = Circle::createWithFile("circle.png");
    circle->setScale(.25);
    circle->setPosition(circle->getBoundingBox().size.height, circle->getPosition().y);
    circle->createPhysicsBody();
    circle->setColor( Color3B(255, 255, 255));
    for (int i = 0; i < spawners.size(); i++) {
        spawners[i]->ballSize = circle->getBoundingBox().size;
    }
    
    this->addChild(circle);
    
}

void GamePlayLayer::addTouchHandlers(){
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        
        return false;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        // your code
        
    };
    
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        // your code
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    
}












