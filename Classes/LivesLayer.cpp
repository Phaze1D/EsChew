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
        layer->setTag(LIVE_LAYER);
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
    
}

void LivesLayer::buildLives(float scale){
    
    Color3B color = Color3B(255, 255, 255);
    
    Sprite* live1 = Sprite::create("circle.png");
    live1->setColor(color);
    live1->setAnchorPoint(Vec2(0, 0));
    live1->setTag(LIVE1_TAG);
    live1->setPosition(offset, offset);
    this->scaleCorrectly(scale, live1);
    this->addChild(live1);
    
    Sprite* live2 = Sprite::create("circle.png");
    live2->setColor(color);
    live2->setTag(LIVE2_TAG);
    live2->setAnchorPoint(Vec2(0, 0));
    live2->setPosition(offset*2 + live1->getBoundingBox().size.width, offset);
    this->scaleCorrectly(scale, live2);
    this->addChild(live2);
    
    Sprite* live3 = Sprite::create("circle.png");
    live3->setColor(color);
    live3->setAnchorPoint(Vec2(0, 0));
    live3->setTag(LIVE3_TAG);
    live3->setPosition(offset*3 +live1->getBoundingBox().size.width*2, offset);
    this->scaleCorrectly(scale, live3);
    this->addChild(live3);

    this->resize();
}

int LivesLayer::decreaseLives(){
    livesLeft--;
    
    if (livesLeft == 3) {
        this->getChildByTag(LIVE1_TAG)->removeFromParent();
        this->resize();
    }else if(livesLeft == 2){
        this->getChildByTag(LIVE2_TAG)->removeFromParent();
        this->resize();
    }else if(livesLeft == 1){
        this->getChildByTag(LIVE3_TAG)->removeFromParent();
        this->resize();
    }
    
    return livesLeft;
}

Color3B LivesLayer::getCurrentColor(){
    
    if (this->getChildByTag(LIVE1_TAG)) {
        return this->getChildByTag(LIVE1_TAG)->getColor();
    }else if(this->getChildByTag(LIVE2_TAG)){
        return this->getChildByTag(LIVE2_TAG)->getColor();
    }else if(this->getChildByTag(LIVE3_TAG)){
        return this->getChildByTag(LIVE3_TAG)->getColor();
    }
    
    return Color3B(255, 255, 255);
}

Vec2 LivesLayer::getCurrentChildPostion(){
    if (this->getChildByTag(LIVE1_TAG)) {
        return this->getChildByTag(LIVE1_TAG)->getPosition();
    }else if(this->getChildByTag(LIVE2_TAG)){
        return this->getChildByTag(LIVE2_TAG)->getPosition();
    }else if(this->getChildByTag(LIVE3_TAG)){
        return this->getChildByTag(LIVE3_TAG)->getPosition();
    }
    return Vec2(0,0);
}


void LivesLayer::resize(){
    
    if (this->getChildren().size() >0) {
        float reWidth = this->getChildren().at(0)->getBoundingBox().size.width*this->getChildren().size() + offset*(this->getChildren().size()+1);
        float reHeight = this->getChildren().at(0)->getBoundingBox().size.height + offset*2;
        this->setContentSize(Size(reWidth, reHeight));
    }
    
}

void LivesLayer::scaleCorrectly(float scale, Sprite * sprite){
    sprite->getTexture()->generateMipmap();
    cocos2d::Texture2D::TexParams texpar = {GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(texpar);
    sprite->setScale(scale);
}