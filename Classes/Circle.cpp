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