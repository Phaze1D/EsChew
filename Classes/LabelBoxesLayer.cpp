//
//  LabelBoxesLayer.cpp
//  SQ
//
//  Created by David Villarreal on 2/26/15.
//
//

#include "LabelBoxesLayer.h"


LabelBoxesLayer* LabelBoxesLayer::create(const cocos2d::Color4B &color){
    
    LabelBoxesLayer * layer = new (std::nothrow) LabelBoxesLayer();
    if(layer && layer->initWithColor(color))
    {
        layer->autorelease();
        layer->addEvents();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
    
}


void LabelBoxesLayer::buildLabel(std::string letters){
    const char* charArray  = letters.c_str();
    boxOffset = 2;
    lettersLength = (int)letters.length();
    letterArrayHeight = 12;
    letterArrayWidth = 8;
    
    finalPositions.reserve(100);
    
    Color3B color = this->getRandomBrightColor();
    
    for (int i = 0; i < letters.length(); i++) {
        std::vector<int> vectorArray = getArray(charArray[i]);
        
        int row = 0;
        int column = 0;
        
        for (int j = 0; j < vectorArray.size() ; j++) {
        
            if (vectorArray[j] == 0) {
                this->createBox(row, column, i, color);
            }
            
            column++;
            
            if(vectorArray[j] == 2){
                row++;
                column = 0;
            }
        }
    }
    this->resizeLayer();
}

Color3B LabelBoxesLayer::getRandomBrightColor(){
    
    
    Color3B color = Color3B(random(0, 255), random(0, 255), random(0, 255));
    
    int ave = (color.r + color.g + color.b)/3;
    
    if (ave < 70) {
        int rannum = random(1, 3);
        if (rannum == 1) {
            color.r += 40;
        }else if(rannum == 2){
            color.g += 40;
        }else{
            color.b += 40;
        }
    }
    
    return color;
    
}


std::vector<int> LabelBoxesLayer::getArray(char letter){
    
    switch (letter) {
        case 'P':
        {
            int myints[] = {0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,0,0,0,0,0,1,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,1,2};
            
            std::vector<int> vect(myints, myints + sizeof(myints) / sizeof(int));
           
            return vect;
        }
            
            
        case 'L':
        {
            int myints[] = {0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2};
            
            std::vector<int> vect(myints, myints + sizeof(myints) / sizeof(int));
            
            return vect;
        }
            
        case 'A':
        {
            int myints[] = {0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,0,2};
            
            std::vector<int> vect(myints, myints + sizeof(myints) / sizeof(int));
            
            return vect;
        }

            
        case 'Y':
        {
            int myints[] = {1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,0,0,0,0,1,1,2,
                            1,0,0,1,1,0,0,1,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2};
            
            std::vector<int> vect(myints, myints + sizeof(myints) / sizeof(int));
            
            return vect;
        }
    }
    
    std::vector<int> vect;
    
    return vect;
    
    
}


void LabelBoxesLayer::createBox(int row, int column, int letterNum, Color3B color){
    
    Sprite*box = Sprite::create();
    box->setTextureRect(Rect(0, 0, boxSize.width, boxSize.height));
    box->setColor(color);
    box->setAnchorPoint(Vec2(0, 0));
    
    finalPositions.push_back(Vec2( (boxOffset + boxSize.width)*column + (letterNum * ((boxSize.width+boxOffset) * letterArrayWidth + boxOffset*2) ), (boxOffset + boxSize.height)*row) );
    
    box->setPosition(this->getRandomOuterPosition());
    
    this->addChild(box);
}

Vec2 LabelBoxesLayer::getRandomOuterPosition(){
    
    Size winSize = Director::getInstance()->getWinSize();
    Vec2 position;
    
    int ran = random(1, 4);
    
    if (ran == 1) {
        position = Vec2(-winSize.width, random( -(int)winSize.height, (int)winSize.height) );
        
    }else if (ran == 2){
        position = Vec2(winSize.width, random( -(int)winSize.height, (int)winSize.height) );
        
    }else if (ran == 3){
        position = Vec2(random(-(int)winSize.width, (int)winSize.width), -winSize.height );
    }else{
        position = Vec2(random(-(int)winSize.width, (int)winSize.width), winSize.height );
    }

    return position;
    
}

void LabelBoxesLayer::resizeLayer(){
    
    finalPositions.shrink_to_fit();
    
    float reWidth = (letterArrayWidth* (boxOffset + boxSize.width))* lettersLength + boxOffset*2*(lettersLength-1);
    float reHeight = letterArrayHeight*(boxOffset + boxSize.height);
    
    this->setContentSize(Size(reWidth, reHeight));
}

void LabelBoxesLayer::moveBoxesToFinal(){
    
    
    auto move = MoveTo::create(3, finalPositions.at(0));
    
    auto callBack = CallFunc::create([&](){
        this->addRemoveAdL();
        didFinishEntrance = true;
        
    });
    
    auto seq = Sequence::create(move, callBack, NULL);
    
    for (int i = 0; i < finalPositions.size(); i++) {
        auto move = MoveTo::create(3, finalPositions.at(i));
        
        if (i == 0) {
            this->getChildren().at(i)->runAction(seq);
        }else{
            this->getChildren().at(i)->runAction(move);
        }
        
    }

    finalPositions.clear();
}

void LabelBoxesLayer::moveBoxesOut(){
    
    auto move = MoveTo::create(2, this->getRandomOuterPosition());
    
    auto callBack = CallFunc::create([&](){
        this->removeAllChildren();
        this->playClicked();
        
    });
    
    auto seq = Sequence::create(move, callBack, NULL);
    
    for (int i = 0; i < this->getChildren().size(); i++) {
        auto move = MoveTo::create(3, this->getRandomOuterPosition());
        
        if (i == 0) {
            this->getChildren().at(i)->runAction(seq);
        }else{
            this->getChildren().at(i)->runAction(move);
        }
    }
    
}

void LabelBoxesLayer::addEvents(){
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch* touch, Event* event){
        
        if (didFinishEntrance) {
  
            Rect rect = this->getBoundingBox();
            Vec2 point = touch->getLocation();
            
            
            if (rect.containsPoint(point)) {
                
                if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
                    this->getScene()->getChildByTag(12)->removeFromParent();
                }
                Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
                this->moveBoxesOut();
                return true;
            }
            
        }
    
        return false;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        // your code
    };
    
   
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        // your code
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
   
}














