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
    intro = IntroLayer::create(Color4B(148,0,211,50));
    intro->setContentSize(Size(winSize.width - 180, winSize.height - 150));
    intro->setPosition(winSize.width/2 - intro->getContentSize().width/2, winSize.height/2 - intro->getContentSize().height/2);
    intro->buildIntro();
    intro->setTag(234);
    this->addChild(intro);
  
    intro->crossClicked = [&](){
        this->createCountDown();
        intro->removeAllChildren();
        intro->removeFromParent();

    };
}

void GameplayScene::createCountDown(){
    
    Size winSize = Director::getInstance()->getWinSize();
    
    countLayer = CountDownLayer::create(Color4B(255, 255, 255, 0));
    countLayer->setBoxSize(Size(6, 6));
    countLayer->createCountDown();
    countLayer->setPosition(winSize.width/2 - countLayer->getContentSize().width/2, winSize.height/2 - countLayer->getContentSize().height/2);
    countLayer->beginCountDown();
    this->addChild(countLayer);
    
    countLayer->countFinishedCall = [&](){
    	this->createGamePlayLayer();
        countLayer->removeAllChildren();
        countLayer->removeFromParent();
        
    };




}


void GameplayScene::createGamePlayLayer(){
    
    gameLayer = GamePlayLayer::create(Color4B(255, 255, 255, 0));
    
    
    gameLayer->gameOverCall = [&](int score, int highScore){
        this->createGameOverLayer(score, highScore);
        gameLayer->removeFromParent();
    };
    
    playing = true;
    this->addChild(gameLayer);
    
    
}

void GameplayScene::pauseGamePlayLayer(){
    if (playing) {
        gameLayer->pauseLayer();

    }
    
}

void GameplayScene::resumeGamePlayLayer(){
    
    if (playing) {
    
        Size winSize = Director::getInstance()->getWinSize();
        
        countLayer = CountDownLayer::create(Color4B(255, 255, 255, 0));
        countLayer->setBoxSize(Size(6, 6));
        countLayer->createCountDown();
        countLayer->setPosition(winSize.width/2 - countLayer->getContentSize().width/2, winSize.height/2 - countLayer->getContentSize().height/2);
        countLayer->beginCountDown();
        this->addChild(countLayer);
        
        
        
        countLayer->countFinishedCall = [&](){
        	gameLayer->resumeLayer();
        	countLayer->removeAllChildren();
            countLayer->removeFromParent();
            

        };
    }
}

void GameplayScene::createGameOverLayer(int score, int highScore){
   
    #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
     gene::AdMobCPP admob = gene::AdMobCPP();
     admob.showAd();
    #endif

	#if  CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        AndroidAdHelper::showAd();
	#endif
    
     playing = false;
    
    gameOver = GameOverLayer::create();
    gameOver->buildLayer(score, highScore);
    this->addChild(gameOver);
    
    gameOver->homeClicked = [&](){
        this->homeClick();
    };

    
    gameOver->restartClicked = [&](){
    	 this->createCountDown();
    	gameOver->removeAllChildren();
        gameOver->removeFromParent();

    };
    
    
    
}


