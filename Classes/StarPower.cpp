//
//  StarPower.cpp
//  SQ
//
//  Created by David Villarreal on 3/9/15.
//
//

#include "StarPower.h"

USING_NS_CC;


StarPower* StarPower::createWithFile(const std::string& filename){
    
    StarPower*sprite = new (std::nothrow) StarPower();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        sprite->setTag(STAR_TAG);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
    
}

void StarPower::createPhysicsBody(){
    
    auto phyBody = PhysicsBody::createBox(this->getBoundingBox().size);
    phyBody->setDynamic(true);
    phyBody->setContactTestBitmask(true);
    phyBody->setCategoryBitmask(true);
    //phyBody->setAngularVelocity(8);
    this->setPhysicsBody(phyBody);
        
}

void StarPower::runAnimation(){
    auto delay = DelayTime::create(.2);
    
    auto callBack = CallFunc::create([&](){
        this->setColor(Color3B(random(0, 255), random(0, 255), random(0, 255)));
    });
    
    auto seq = Sequence::create(callBack,delay, NULL);
    
    this->runAction(RepeatForever::create(seq));
    
}