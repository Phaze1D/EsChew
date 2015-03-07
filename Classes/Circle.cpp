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
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


void Circle::createPhysicsBody(){
    
    auto phyBody = PhysicsBody::createCircle(this->getBoundingBox().size.height/2);
    phyBody->setDynamic(false);
    this->setPhysicsBody(phyBody);
    
}