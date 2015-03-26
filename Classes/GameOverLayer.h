//
//  GameOverLayer.h
//  SQ
//
//  Created by David Villarreal on 3/16/15.
//
//

#ifndef __SQ__GameOverLayer__
#define __SQ__GameOverLayer__

#include <stdio.h>
#include <sstream>
#include <string>
#include "cocos2d.h"

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

class GameOverLayer: public cocos2d::Layer{
    
private:
    static const int RESET_B = 43;
    static const int HOME_B = 42;
    
    int highScore = 0;
    int score = 0;
    
    
public:
    CREATE_FUNC(GameOverLayer);
    void buildLayer(int score,int highScore);
    
    typedef std::function<void()> HomeCallBack;
    HomeCallBack homeClicked;
    
    typedef std::function<void()> RestartCallBack;
    RestartCallBack restartClicked;
    
private:
    void createResetButton();
    void createHomeButton();
    void createHighScore();
    void createScore();
    
    void scaleCorrectly(float scale, cocos2d::Sprite*sprite);
    
    void addEvents();
    
    
};

#endif /* defined(__SQ__GameOverLayer__) */
