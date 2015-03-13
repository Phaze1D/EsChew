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
    
    
    if (!isPaused) {
        
        this->spawnBall(deltaTime);
        
        gameTime += deltaTime;
    
        
    }
}

void GamePlayLayer::spawnBall(float deltaTime){
    
    for (int i = 0; i < spawners.size(); i++) {
        SquareBox * box = spawners.at(i)->spawnBox(Size(16, 16), 200);
        
        if (box) {
            this->addChild(box);
        }
        
        spawners.at(i)->timePassed+= deltaTime;
    }
}

bool GamePlayLayer::onContactBegin(cocos2d::PhysicsContact &contact){
    
    
    
    Node* circle = nullptr;
    Node* star = nullptr;
    Node* box = nullptr;
    
    if (contact.getShapeA()->getBody()->getNode()->getTag() == Circle::CIRCLE_TAG) {
        circle = contact.getShapeA()->getBody()->getNode();
    }else if (contact.getShapeA()->getBody()->getNode()->getTag() == StarPower::STAR_TAG) {
        star = contact.getShapeA()->getBody()->getNode();
    }else{
        box = contact.getShapeA()->getBody()->getNode();
    }
    
    if (contact.getShapeB()->getBody()->getNode()->getTag() == Circle::CIRCLE_TAG) {
        circle = contact.getShapeB()->getBody()->getNode();
    }else if (contact.getShapeB()->getBody()->getNode()->getTag() == StarPower::STAR_TAG) {
        star = contact.getShapeB()->getBody()->getNode();
    }else{
        box = contact.getShapeB()->getBody()->getNode();
    }
    

    
    if (circle && box ) {
        
        box->removeFromParent();
    }
    
    
    return true;
}


void GamePlayLayer::buildGameLayer(){
    this->createSpawners();
    this->createCircle();
    this->addTouchHandlers();
    
   
    
    
    this->scheduleUpdate();
    
}

void GamePlayLayer::createSpawners(){
    spawners.reserve(4);
    
    MySpawner * spawner1 = new MySpawner();
    spawner1->createSpawner(UPPER, this->getBoundingBox());
    spawner1->spawnRate = 1/2.0;
    spawner1->spawnReady = false;
    spawners.push_back(spawner1);
    
    MySpawner * spawner2 = new MySpawner();
    spawner2->createSpawner(RIGHT, this->getBoundingBox());
    spawner2->spawnRate = 1/20.0;
    spawner2->spawnReady = true;
    spawners.push_back(spawner2);
    
    MySpawner * spawner3 = new MySpawner();
    spawner3->createSpawner(LOWER, this->getBoundingBox());
    spawner3->spawnRate = 1/2.0;
    spawners.push_back(spawner3);
    
    MySpawner * spawner4 = new MySpawner();
    spawner4->createSpawner(LEFT, this->getBoundingBox());
    spawner4->spawnRate = 1/2.0;
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
    circle->setPosition(circle->getBoundingBox().size.height, this->getBoundingBox().size.height/2);
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
        
        circle->setPosition(touch->getLocation());
        return true;
    };
    
    listener->onTouchMoved = [&](Touch* touch, Event* event){
       
        circle->setPosition(touch->getLocation());
        
    };
    
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        // your code
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GamePlayLayer::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    
}












