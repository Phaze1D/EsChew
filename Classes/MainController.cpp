//
//  MainController.cpp
//  SQ
//
//  Created by David Villarreal on 2/26/15.
//
//

#include "MainController.h"

USING_NS_CC;

void MainController::begin(){
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("SQ");
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    this->createMainMenuScene();
    
}

void MainController::pause(){
    Director::getInstance()->stopAnimation();
    PlayerData::getInstance()->savedData();
    
    if (gameSceneCreate) {
        GameplayScene* scene = (GameplayScene*)Director::getInstance()->getRunningScene();
        scene->pauseGamePlayLayer();
    }
    
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void MainController::resume(){
    Director::getInstance()->startAnimation();
    
    if (gameSceneCreate) {
        GameplayScene* scene = (GameplayScene*)Director::getInstance()->getRunningScene();
        scene->resumeGamePlayLayer();
    }

    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void MainController::end(){
    
}

void MainController::createMainMenuScene(){
    
    
    auto mainMenuScene = MainMenuScene::create();
    Director* director = Director::getInstance();
    
    if (director->getRunningScene()) {
        director->replaceScene(mainMenuScene);
        
    }else{
        director->runWithScene(mainMenuScene);
        
    }
    gameSceneCreate = false;
    
    
    mainMenuScene->labelLayer->playClicked = [&, mainMenuScene](){
        mainMenuScene->removeAllChildren();
        this->createGameplayScene();
        
    };
    
    
}

void MainController::createGameplayScene(){
    
    auto gameplayScene = GameplayScene::createWithPhysics();
    Director::getInstance()->replaceScene(gameplayScene);
    
    gameSceneCreate = true;
    
    gameplayScene->homeClick = [&, gameplayScene](){
        gameplayScene->removeAllChildren();
        this->createMainMenuScene();
       
    };
    
    
    
}


