//
//  Circle.cpp
//  SQ
//
//  Created by David Villarreal on 3/5/15.
//
//

#include "Circle.h"
USING_NS_CC;


Circle* Circle::createWithFile(const std::string& filename){
    Circle*sprite = new (std::nothrow) Circle();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        sprite->setTag(CIRCLE_TAG);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


void Circle::createPhysicsBody(){
    
    auto phyBody = PhysicsBody::createCircle(this->getBoundingBox().size.height/2.2);
    phyBody->setDynamic(false);
    phyBody->setContactTestBitmask(true);
    this->setPhysicsBody(phyBody);
    
}

void Circle::runStarPowerAnimation(){
    Color3B color = this->getColor();
    this->isPowerActive = true;
    
    auto delay = DelayTime::create(.2);
    auto callBack = CallFunc::create([&](){
        this->setColor(Color3B(random(0, 255), random(0, 255), random(0, 255)));
    });
    auto seq = Sequence::create(callBack,delay, NULL);
    auto finish = CallFunc::create([&, color](){
        this->setColor(color);
        this->isPowerActive = false;
    });
    auto seq2 = Sequence::create(Repeat::create(seq, 50), finish, NULL);
    this->runAction(seq2);
    
}

void Circle::circleHitAnimation(){
    
}