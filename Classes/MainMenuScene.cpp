//
//  MainMenuScene.cpp
//  SQ
//
//  Created by David Villarreal on 2/26/15.
//
//

#include "MainMenuScene.h"


USING_NS_CC;

bool MainMenuScene::init(){
    
    if (!Scene::init()) {
        return false;
    }
    
    this->createBackgroundLayer();
    this->createPlayBoxesLayer();
    
    //If player has not removed ads
   
    
    
    return true;
}

void MainMenuScene::createBackgroundLayer(){
    
    BackgroundLayer * backLayer = BackgroundLayer::create();
    this->addChild(backLayer);
    
}

void MainMenuScene::createPlayBoxesLayer(){
    
    labelLayer = LabelBoxesLayer::create(Color4B(255, 255, 255, 0));
    labelLayer->boxSize = Size(5, 3);
    labelLayer->buildLabel("PLAY");
    labelLayer->setPosition(this->getContentSize().width/2 - labelLayer->getContentSize().width/2, this->getContentSize().height/2 - labelLayer->getContentSize().height/2);    
    labelLayer->moveBoxesToFinal();
    this->addChild(labelLayer);
    
    
    labelLayer->addRemoveAdL = [&](){
        if (true) {
            if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
                this->createRemoveAdsButton();
            }
        }
    };
    
}

void MainMenuScene::createRemoveAdsButton(){
    
    auto removeAdLabel = Label::createWithTTF("Remove Ads", "fonts/arial.ttf", 24);
    removeAdLabel->setAnchorPoint(Vec2(0,0));
    removeAdLabel->setPosition(Vec2(30,30));
    removeAdLabel->setColor(Color3B(70,70,70));
    removeAdLabel->setTag(12);
    this->addChild(removeAdLabel);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [removeAdLabel](Touch* touch, Event* event){
        
        Rect rect = removeAdLabel->getBoundingBox();
        Vec2 point = touch->getLocation();
        rect.size.height = rect.size.height*2;
        rect.size.width = rect.size.width*2;
        
        if (rect.containsPoint(point)) {
            CCLOG("ads touch");
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
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, removeAdLabel);
    
    
    
}

void MainMenuScene::clearDelete(){
    labelLayer = nullptr;
}