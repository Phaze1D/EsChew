//
//  GameOverLayer.cpp
//  SQ
//
//  Created by David Villarreal on 3/16/15.
//
//

#include "GameOverLayer.h"
USING_NS_CC;



void GameOverLayer::buildLayer(int score, int highScore){
    this->score = score;
    this->highScore = highScore;
    this->createHighScore();
    this->createScore();
    this->createResetButton();
    this->createHomeButton();
    this->addEvents();
}

void GameOverLayer::createResetButton(){
    
    Sprite * resetB = Sprite::create("restartB.png");
    this->scaleCorrectly(.2, resetB);
    resetB->setAnchorPoint(Vec2(1, 0));
    resetB->setPosition(this->getContentSize().width/2 - this->getChildByTag(5)->getContentSize().width/2, this->getChildByTag(6)->getContentSize().height*2);
    resetB->setColor(Color3B::WHITE);
    resetB->setTag(RESET_B);
    this->addChild(resetB);
    
}

void GameOverLayer::createHomeButton(){
    
    Sprite * homeB = Sprite::create("homeB.png");
    this->scaleCorrectly(.2, homeB);
    homeB->setAnchorPoint(Vec2(0, 0));
    homeB->setPosition(this->getContentSize().width/2 + this->getChildByTag(5)->getContentSize().width/2, this->getChildByTag(6)->getContentSize().height*2);
    homeB->setColor(Color3B::WHITE);
    homeB->setTag(HOME_B);
    this->addChild(homeB);
    
}

void GameOverLayer::createHighScore(){
    
    Label * highL = Label::createWithTTF("Best Score", "fonts/Titillium-Light.otf", 40);
    highL->setHorizontalAlignment(TextHAlignment::CENTER);
    highL->setAnchorPoint(Vec2(.5, .5));
    highL->setTag(5);
    highL->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    this->addChild(highL);
    
    Label * highLI = Label::createWithTTF(std::to_string(highScore), "fonts/Titillium-Light.otf", 38);
    highLI->setHorizontalAlignment(TextHAlignment::CENTER);
    highLI->setTag(4);
    highLI->setAnchorPoint(Vec2(.5, .5));
    highLI->setPosition(this->getContentSize().width/2, this->getContentSize().height/2 - highL->getBoundingBox().size.height);
    this->addChild(highLI);
    
}

void GameOverLayer::createScore(){
    
    Label * scoreL = Label::createWithTTF("Score", "fonts/Titillium-Light.otf", 50);
    scoreL->setHorizontalAlignment(TextHAlignment::CENTER);
    scoreL->setAnchorPoint(Vec2(.5, 1));
    scoreL->setTag(6);
    scoreL->setPosition(this->getContentSize().width/2, this->getContentSize().height - scoreL->getContentSize().height*2);
    this->addChild(scoreL);
    
    Label * scoreLI = Label::createWithTTF(std::to_string(score), "fonts/Titillium-Light.otf", 48);
    scoreLI->setHorizontalAlignment(TextHAlignment::CENTER);
    scoreLI->setAnchorPoint(Vec2(.5, 1));
    scoreLI->setColor(Color3B::ORANGE);
    scoreLI->setTag(7);
    scoreLI->setPosition(this->getContentSize().width/2, this->getContentSize().height - scoreL->getContentSize().height*3 );
    this->addChild(scoreLI);
    
}

void GameOverLayer::scaleCorrectly(float scale, Sprite * sprite){
    sprite->getTexture()->generateMipmap();
    cocos2d::Texture2D::TexParams texpar = {GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(texpar);
    sprite->setScale(scale);
}

void GameOverLayer::addEvents(){
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        
        
        Rect rectR = this->getChildByTag(RESET_B)->getBoundingBox();
        Rect rectH = this->getChildByTag(HOME_B)->getBoundingBox();
        
        Vec2 point = touch->getLocation();
        
        if (rectR.containsPoint(point)) {
            this->getChildByTag(RESET_B)->setColor(Color3B::YELLOW);
            return true;
        }
        
        if (rectH.containsPoint(point)) {
            this->getChildByTag(HOME_B)->setColor(Color3B::YELLOW);
            return true;
        }
        
        
        return true;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        // your code
    };
    
    
    listener->onTouchEnded = [&](Touch* touch, Event* event){
        Rect rectR = this->getChildByTag(RESET_B)->getBoundingBox();
        Rect rectH = this->getChildByTag(HOME_B)->getBoundingBox();
        this->getChildByTag(RESET_B)->setColor(Color3B::WHITE);
        this->getChildByTag(HOME_B)->setColor(Color3B::WHITE);
        
        Vec2 point = touch->getLocation();
        
        if (rectR.containsPoint(point)) {
            
            this->restartClicked();
        }
        
        if (rectH.containsPoint(point)) {
            
            this->homeClicked();
        }
        
        

    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
}






