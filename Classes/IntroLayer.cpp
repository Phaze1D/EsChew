//
//  IntroLayer.cpp
//  SQ
//
//  Created by David Villarreal on 3/2/15.
//
//

#include "IntroLayer.h"

USING_NS_CC;

IntroLayer* IntroLayer::create(const cocos2d::Color4B &color){
    
    IntroLayer * layer = new (std::nothrow) IntroLayer();
    if(layer && layer->initWithColor(color))
    {
        layer->autorelease();
        layer->addEvents();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
    
}

void IntroLayer::update(float timeTook){
    
    //Spawn Box
    if (timePassed >= defaultSpawnRate) {
        auto box = spawner->spawnBox(Size(11, 11), Vec2(181,0));
        this->addChild(box);
        boxesIn.pushBack(box);
        timePassed = 0;
        
    }
    
    for (int i = 0; i < boxesIn.size(); i++) {
        SquareBox * front = boxesIn.at(i);
        if (front->getPosition().x <= 0 || front->getPosition().y <= 0 || front->getPosition().y >= this->getContentSize().height) {
            front->removeFromParent();
            boxesIn.eraseObject(front);
        }
    }
    
    timePassed += timeTook;
}

void IntroLayer::buildIntro(){
    defaultSpawnRate = 1/1.0;
    boxesIn = Vector<SquareBox*>();
    this->buildCrossButton();
    this->buildLives();
    this->buildIntroAnimation();
    this->scheduleUpdate();
    
}

void IntroLayer::buildCrossButton(){
    
    auto crossButton = Sprite::create("cross.png");
    this->scaleCorrectly(.3, crossButton);
    crossButton->setAnchorPoint(Vec2(0.5, 0.5));
    crossButton->setPosition(Vec2(0, this->getContentSize().height));
    this->addChild(crossButton);
   
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&, crossButton](Touch* touch, Event* event){
        
        Rect rect = crossButton->getBoundingBox();
        Vec2 point = touch->getLocation();
        rect.size.height = rect.size.height*5;
        rect.size.width = rect.size.width*5;
        
        if (rect.containsPoint(point)) {
            this->unscheduleUpdate();
            delete this->spawner;
            this->boxesIn.clear();
            this->crossClicked();
            return true;
        }
        
        return false;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event){
        // your code
    };
    
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        // your code
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, crossButton);
}

void IntroLayer::buildLives(){
    LivesLayer * liveLayer = LivesLayer::create(Color4B(255, 255, 255, 0));
    liveLayer->buildLives(.15);
    liveLayer->setPosition(Vec2(this->getContentSize().width - liveLayer->getContentSize().width, this->getContentSize().height - liveLayer->getContentSize().height));
    liveLayer->setTag(LIVE_LAYER);
    this->addChild(liveLayer);
    
    
}

void IntroLayer::buildIntroAnimation(){
    this->buildSpawner();
    this->buildCircle();
   
    
}

void IntroLayer::buildSpawner(){
    spawner = new MySpawner();
    spawner->createSpawner(RIGHT, this->getBoundingBox());
    
    
}

void IntroLayer::buildCircle(){
    circle = Circle::createWithFile("circle.png");
    circle->setScale(.25);
    circle->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    circle->createPhysicsBody();
    circle->setColor( ((LivesLayer *)this->getChildByTag(LIVE_LAYER))->getCurrentColor() );
    auto moveTo = MoveTo::create(.7, Vec2(circle->getBoundingBox().size.height, circle->getPosition().y));
    circle->runAction(moveTo);
    
    
    this->addChild(circle);

}

void IntroLayer::scaleCorrectly(float scale, Sprite * sprite){
    sprite->getTexture()->generateMipmap();
    cocos2d::Texture2D::TexParams texpar = {GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(texpar);
    sprite->setScale(scale);
}

void IntroLayer::addEvents(){
    
}