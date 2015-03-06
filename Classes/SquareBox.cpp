//
//  SquareBox.cpp
//  SQ
//
//  Created by David Villarreal on 3/5/15.
//
//

#include "SquareBox.h"

USING_NS_CC;

void SquareBox::createPhysicsBody(Size size){
    PhysicsBody * phyBody = PhysicsBody::createBox(size);
    phyBody->setDynamic(true);
    phyBody->setLinearDamping(0);
    this->setPhysicsBody(phyBody);
    
}