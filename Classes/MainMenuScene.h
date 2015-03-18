//
//  MainMenuScene.h
//  SQ
//
//  Created by David Villarreal on 2/26/15.
//
//

#ifndef __SQ__MainMenuScene__
#define __SQ__MainMenuScene__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "LabelBoxesLayer.h"

class MainMenuScene : public cocos2d::Scene {
  
//Variables
public:
    LabelBoxesLayer * labelLayer;
    
//Methods
public:
    
    //Initializes the Scene -- Write code in here ---
    virtual bool init();
    
    
    
    //Creates the create() function
    CREATE_FUNC(MainMenuScene);
    
    void createBackgroundLayer();
    void createPlayBoxesLayer();
    void createRemoveAdsButton();
    
    void clearDelete();
    
};

#endif /* defined(__SQ__MainMenuScene__) */
