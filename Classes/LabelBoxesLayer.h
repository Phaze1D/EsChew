//
//  LabelBoxesLayer.h
//  SQ
//
//  Created by David Villarreal on 2/26/15.
//
//

#ifndef __SQ__LabelBoxesLayer__
#define __SQ__LabelBoxesLayer__

#include "cocos2d.h"
#include <vector>

USING_NS_CC;

class LabelBoxesLayer: public cocos2d::LayerColor {
    
public:
    cocos2d::Size boxSize;
    
private:
    float boxOffset;
    
    int lettersLength;
    int letterArrayHeight;
    int letterArrayWidth;
    
    bool didFinishEntrance = false;
    
    std::vector<cocos2d::Vec2> finalPositions;
    
    
public:
    
    //Callback function called when the layer is touch
    typedef std::function<void()> playClickedCallback;
    playClickedCallback playClicked;
    
    typedef std::function<void()> introFinished;
    introFinished addRemoveAdL;
    
    //Create method with parameters
    static LabelBoxesLayer* create(const cocos2d::Color4B &color);
    
    //Build a label from a string
    void buildLabel(std::string letters);
    
    //Moves the boxes to the final position
    void moveBoxesToFinal();

    
private:
    std::vector<int> getArray(char letter);
    
    void createBox(int row, int column, int letterNum, cocos2d::Color3B color);
    
    void resizeLayer();
    
    void addEvents();
    
    Vec2 getRandomOuterPosition();
    
    Color3B getRandomBrightColor();
    
    void moveBoxesOut();
};

#endif /* defined(__SQ__LabelBoxesLayer__) */
