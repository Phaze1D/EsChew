//
//  IntroLayer.h
//  SQ
//
//  Created by David Villarreal on 3/2/15.
//
//

#ifndef __SQ__IntroLayer__
#define __SQ__IntroLayer__

#include <stdio.h>
#include "cocos2d.h"

class IntroLayer: public cocos2d::LayerColor {
    
    
public:
    
    //Create method with parameters
    static IntroLayer* create(const cocos2d::Color4B &color);
    
    typedef std::function<void()> crossClickCallBack;
    crossClickCallBack crossClicked;
    
    void buildIntro();
    
private:
    
    void addEvents();
    
};

#endif /* defined(__SQ__IntroLayer__) */
