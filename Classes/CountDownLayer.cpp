//
//  CountDownLayer.cpp
//  SQ
//
//  Created by David Villarreal on 3/3/15.
//
//

#include "CountDownLayer.h"

USING_NS_CC;

CountDownLayer* CountDownLayer::create(const cocos2d::Color4B &color){
    
    CountDownLayer * layer = new (std::nothrow) CountDownLayer();
    if(layer && layer->initWithColor(color))
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
    
}


void CountDownLayer::beginCountDown(){

    timePassed = 0;
    this->scheduleUpdate();
 
}

void CountDownLayer::update(float timeTook){
    
    
    
    if ((int)timePassed == 0 && !didCreateOne) {
        createBoxes(threePosition);
        didCreateOne = true;
    }else if ((int)timePassed == 1 && !didCreateTwo){
        createBoxes(twoPosition);
        didCreateTwo = true;
    }else if((int)timePassed == 2 && !didCreateThree){
        createBoxes(onePosition);
        didCreateThree = true;
    }
    
    if ((int)timePassed >= 3) {
        this->unscheduleUpdate();
        this->moveToOutter();
    }
    
    timePassed += timeTook;

    
}

void CountDownLayer::moveToOutter(){
    auto move = MoveTo::create(.8, this->getRandomOuterPosition());
    
    auto callBack = CallFunc::create([&](){
        this->removeAllChildren();
      
        
    });
    
    auto seq = Sequence::create(move, callBack, NULL);
    
    for (int i = 0; i < this->getChildren().size(); i++) {
        auto move = MoveTo::create(.8, this->getRandomOuterPosition());
        
        this->getChildren().at(i)->setColor(this->getRandomBrightColor());
        
        if (i == 0) {
            this->getChildren().at(i)->runAction(seq);
        }else{
            this->getChildren().at(i)->runAction(move);
        }
    }

}

Vec2 CountDownLayer::getRandomOuterPosition(){
    
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

Color3B CountDownLayer::getRandomBrightColor(){
    
    
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


void CountDownLayer::createBoxes(std::vector<cocos2d::Vec2> positionVec){
    
    Vector<Node *> childern = this->getChildren();
    Color3B color = this->getRandomBrightColor();
    
    for (int i = 0; i < positionVec.size(); i++) {
        
        if (i < childern.size()) {
            //Use exciting box
            childern.at(i)->setPosition(positionVec[i]);
            childern.at(i)->setColor(color);
            
        }else{
            Sprite*box = Sprite::create();
            box->setTextureRect(Rect(0, 0, boxSize.width, boxSize.height));
            box->setColor(color);
            box->setAnchorPoint(Vec2(0, 0));
            box->setPosition(positionVec[i]);
            this->addChild(box);
        }
    }
    
    for (int i  = positionVec.size(); i < childern.size(); i++) {
        //Remove extra childern
        childern.at(i)->removeFromParent();
    }
    
}

void CountDownLayer::createCountDown(){
    
    boxOffset = 3;
    
    onePosition = this->calculatePosition(this->getBitmapNumber(1));
    twoPosition = this->calculatePosition(this->getBitmapNumber(2));
    threePosition = this->calculatePosition(this->getBitmapNumber(3));
    
    
    this->resize();
}

std::vector<int> CountDownLayer::getBitmapNumber(int number){
    
    switch (number) {
        case 1:
        {
            int myints[] = {0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2,
                            1,0,1,0,0,1,1,1,2,
                            1,0,0,0,0,1,1,1,2,
                            1,1,0,0,0,1,1,1,2,
                            1,1,1,0,0,1,1,1,2};
            
            std::vector<int> vect(myints, myints + sizeof(myints) / sizeof(int));
            
            return vect;
        }
            
            
        case 2:
        {
            int myints[] = {0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,1,1,1,1,1,1,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            1,1,1,1,1,1,0,0,2,
                            1,1,1,1,1,1,0,0,2,
                            1,1,1,1,1,1,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,0,2};
            
            std::vector<int> vect(myints, myints + sizeof(myints) / sizeof(int));
            
            return vect;
        }
            
        case 3:
        {
            int myints[] = {0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            1,1,1,1,1,1,0,0,2,
                            1,1,1,1,1,1,0,0,2,
                            1,1,0,0,0,0,0,0,2,
                            1,1,0,0,0,0,0,0,2,
                            1,1,1,1,1,1,0,0,2,
                            1,1,1,1,1,1,0,0,2,
                            0,0,1,1,1,1,0,0,2,
                            0,0,0,0,0,0,0,0,2,
                            0,0,0,0,0,0,0,0,2};
            
            std::vector<int> vect(myints, myints + sizeof(myints) / sizeof(int));
            
            return vect;
        }
    }
    
    std::vector<int> vect;
    
    return vect;
}


std::vector<Vec2> CountDownLayer::calculatePosition(std::vector<int> array){
    
    std::vector<Vec2> vect;
    vect.reserve(100);
    
    int row = 0;
    int column = 0;
    
    for (int i = 0; i < array.size(); i++) {
        if (array[i] == 0) {
            vect.push_back(Vec2( (boxOffset + boxSize.width)*column, (boxOffset + boxSize.height)*row) );
        }
        column++;
        if(array[i] == 2){
            row++;
            column = 0;
        }
    }
    
    vect.shrink_to_fit();
    
    return vect;
    
}

void CountDownLayer::setBoxSize(const cocos2d::Size size){
    boxSize = size;
}

void CountDownLayer::resize(){
    
    float reWidth = (8 * (boxOffset + boxSize.width));
    float reHeight = 12*(boxOffset + boxSize.height);
    
    this->setContentSize(Size(reWidth, reHeight));
    
}




