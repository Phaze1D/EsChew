//
//  LivesLayer.cpp
//  SQ
//
//  Created by David Villarreal on 3/5/15.
//
//

#include "LivesLayer.h"
USING_NS_CC;


LivesLayer* LivesLayer::create(const cocos2d::Color4B &color){
    
    LivesLayer * layer = new (std::nothrow) LivesLayer();
    if(layer && layer->initWithColor(color))
    {
        layer->autorelease();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
    
}

void LivesLayer::buildLives(float scale){
    
    Color3B color = Color3B(255, 102, 0);
    
    Sprite* live1 = Sprite::create("circle.png");
    live1->setColor(color);
    live1->setAnchorPoint(Vec2(0, 0));
    live1->setTag(LIVE1_TAG);
    live1->setPosition(offset, offset);
    this->scaleCorrectly(scale, live1);
    this->addChild(live1);
    
   Color3B color2 = Color3B(255, 72, 0);
    
    
    Sprite* live2 = Sprite::create("circle.png");
    live2->setColor(color2);
    live2->setTag(LIVE2_TAG);
    live2->setAnchorPoint(Vec2(0, 0));
    live2->setPosition(offset*2 + live1->getBoundingBox().size.width, offset);
    this->scaleCorrectly(scale, live2);
    this->addChild(live2);
    
    Color3B color3 = Color3B(255, 42, 0);
    
    Sprite* live3 = Sprite::create("circle.png");
    live3->setColor(color3);
    live3->setAnchorPoint(Vec2(0, 0));
    live3->setTag(LIVE3_TAG);
    live3->setPosition(offset*3 +live1->getBoundingBox().size.width*2, offset);
    this->scaleCorrectly(scale, live3);
    this->addChild(live3);

    this->resize();
}

void LivesLayer::decreaseLives(){
    
}

void LivesLayer::resize(){
    
    float reWidth = this->getChildByTag(LIVE1_TAG)->getBoundingBox().size.width*3 + offset*4;
    float reHeight = this->getChildByTag(LIVE1_TAG)->getBoundingBox().size.height + offset*2;
    this->setContentSize(Size(reWidth, reHeight));
}

void LivesLayer::scaleCorrectly(float scale, Sprite * sprite){
    sprite->getTexture()->generateMipmap();
    cocos2d::Texture2D::TexParams texpar = {GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(texpar);
    sprite->setScale(scale);
}