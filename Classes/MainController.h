//
//  MainController.h
//  SQ
//
//  Created by David Villarreal on 2/26/15.
//
//

#ifndef __SQ__MainController__
#define __SQ__MainController__

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "GameplayScene.h"
#include "HelloWorldScene.h"

class MainController{
    
private:
    bool gameSceneCreate =false;
    
    
public:
        
    //Called when AppDelegate didFinishingLaunching
    void begin();
    
    //Called when AppDelegate didEnterBackground
    void pause();
    
    //Called when AppDelegate didEnterForeground
    void resume();
    
    //Called when application closes
    void end();
    
    //Creates the Main Menu Scene
    void createMainMenuScene();
    
    //Creates the gameplay Scene
    void createGameplayScene();

    
private:
    
};

#endif /* defined(__SQ__MainController__) */
