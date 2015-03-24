//
//  GameplayScene.cpp
//  SQ
//
//  Created by David Villarreal on 3/2/15.
//
//

#include "GameplayScene.h"

USING_NS_CC;


GameplayScene* GameplayScene::createWithPhysics(){
    GameplayScene *ret = new (std::nothrow) GameplayScene();
    if (ret && ret->initWithPhysics()){
        ret->autorelease();
        ret->buildScene();
        return ret;
    }
    else{
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void GameplayScene::buildScene(){
    this->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
    
    this->createBackground();
    
    //Player has not seen intro
    if (true) {
        this->createIntroLayer();
    }else{
        
    }
}

void GameplayScene::createBackground(){
    BackgroundLayer * backLayer = BackgroundLayer::create();
    this->addChild(backLayer);
}

void GameplayScene::createIntroLayer(){
    Size winSize = Director::getInstance()->getWinSize();
    IntroLayer * intro = IntroLayer::create(Color4B(148,0,211,50));
    intro->setContentSize(Size(winSize.width - 180, winSize.height - 150));
    intro->setPosition(winSize.width/2 - intro->getContentSize().width/2, winSize.height/2 - intro->getContentSize().height/2);
    intro->buildIntro();
    this->addChild(intro);
  
    intro->crossClicked = [&, intro](){
        intro->removeAllChildren();
        intro->removeFromParent();
        
        this->createCountDown();
    };
}

void GameplayScene::createCountDown(){
    
    Size winSize = Director::getInstance()->getWinSize();
    
    CountDownLayer * countLayer = CountDownLayer::create(Color4B(255, 255, 255, 0));
    countLayer->setBoxSize(Size(6, 6));
    countLayer->createCountDown();
    countLayer->setPosition(winSize.width/2 - countLayer->getContentSize().width/2, winSize.height/2 - countLayer->getContentSize().height/2);
    countLayer->beginCountDown();
    this->addChild(countLayer);
    
    
    
    countLayer->countFinishedCall = [&, countLayer](){
        countLayer->removeAllChildren();
        countLayer->removeFromParent();
        
        this->createGamePlayLayer();
    };
}


void GameplayScene::createGamePlayLayer(){
    
    GamePlayLayer * gameLayer = GamePlayLayer::create(Color4B(255, 255, 255, 0));
    gameLayer->setTag(GAME_LAYER_TAG);
    
    
    gameLayer->gameOverCall = [&,gameLayer](int score, int highScore){
        gameLayer->removeFromParent();
        this->createGameOverLayer(score, highScore);
        
    };
    
    this->addChild(gameLayer);
    
    
}

void GameplayScene::pauseGamePlayLayer(){
    if (this->getChildByTag(GAME_LAYER_TAG)) {
        GamePlayLayer* glayer = (GamePlayLayer*)(this->getChildByTag(GAME_LAYER_TAG));
        glayer->pauseLayer();

    }
    
}

void GameplayScene::resumeGamePlayLayer(){
    
    if (this->getChildByTag(GAME_LAYER_TAG)) {
    
        Size winSize = Director::getInstance()->getWinSize();
        
        CountDownLayer * countLayer = CountDownLayer::create(Color4B(255, 255, 255, 0));
        countLayer->setBoxSize(Size(6, 6));
        countLayer->createCountDown();
        countLayer->setPosition(winSize.width/2 - countLayer->getContentSize().width/2, winSize.height/2 - countLayer->getContentSize().height/2);
        countLayer->beginCountDown();
        this->addChild(countLayer);
        
        
        
        countLayer->countFinishedCall = [&, countLayer](){
            countLayer->removeAllChildren();
            countLayer->removeFromParent();
            GamePlayLayer* glayer = (GamePlayLayer*)(this->getChildByTag(GAME_LAYER_TAG));
            glayer->resumeLayer();
            
        };
    }
}

void GameplayScene::createGameOverLayer(int score, int highScore){
   
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        gene::AdMobCPP admob = gene::AdMobCPP();
        admob.showAd();
    }
    
    
    
    GameOverLayer * gameOver = GameOverLayer::create();
    gameOver->buildLayer(score, highScore);
    this->addChild(gameOver);
    
    gameOver->homeClicked = [&, gameOver](){
        gameOver->removeAllChildren();
        gameOver->removeFromParent();
        this->homeClick();
    };
    
    
    gameOver->restartClicked = [&, gameOver](){
        gameOver->removeAllChildren();
        gameOver->removeFromParent();
        this->createCountDown();
    };
    
    
    
}


