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
    if (timePassed >= defaultSpawnRate && !stopIntro) {
        
        if (spawnCount == 5) {
            auto star = spawner->spawnStar(Vec2(481,0));
            this->addChild(star);
            timePassed = 0;
            boxesIn.pushBack(star);
            spawnCount++;
            
        }else{
            auto box = spawner->introSpawnBox(Size(15, 15), Vec2(481,0));
            this->addChild(box);
            boxesIn.pushBack(box);
            timePassed = 0;
            spawnCount++;
        }
    }
    
    for (int i = 0; i < boxesIn.size(); i++) {
        Node * front = boxesIn.at(i);
        if ( (front->getPosition().x - front->getBoundingBox().size.width/2) <= 0 || front->getPosition().y <= 0 || front->getPosition().y >= this->getContentSize().height) {
            front->removeFromParent();
            boxesIn.eraseObject(front);
            moveCount = 0;
        }
    }
    
    if (boxesIn.size() > 2) {
        this->moveCircle();
    }
    
    if (spawnCount >= 15) {
        stopIntro = true;
        if (boxesIn.size() == 0) {
            this->endIntro();
        }
    }

    timePassed += timeTook;
}

void IntroLayer::moveCircle(){
    
    
    if (boxesIn.at(moveCount+1)->getTag() != StarPower::STAR_TAG) {
        if (boxesIn.at(moveCount)->getPosition().x < circle->getPosition().x) {
            movedCircle = false;
            moveCount++;
        }
    }
    
    if (!movedCircle) {
        if (circle->isPowerActive) {
            float x = random(circle->getBoundingBox().size.height, getContentSize().width/5);
            auto moveto = MoveTo::create(.2, Vec2(x, boxesIn.at(moveCount)->getPosition().y));
            circle->runAction(moveto);
            movedCircle = true;
        }else{
            if (circle->getPosition().y != boxesIn.at(moveCount+1)->getPosition().y) {
                float x = random(circle->getBoundingBox().size.height, getContentSize().width/5);
                auto moveto = MoveTo::create(.2, Vec2(x, boxesIn.at(moveCount+1)->getPosition().y));
                circle->runAction(moveto);
                movedCircle = true;
            }
        }
    }
}

void IntroLayer::buildIntro(){
    defaultSpawnRate = 1/2.0;
    boxesIn = Vector<Node*>();
    this->buildCrossButton();
    this->buildLives();
    this->buildIntroAnimation();
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(IntroLayer::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    this->scheduleUpdate();
    
}

void IntroLayer::endIntro(){
    this->unscheduleUpdate();
    delete this->spawner;
    circle->stopAllActions();
    this->stopAllActions();
    this->boxesIn.clear();
    this->crossClicked();
}


bool IntroLayer::onContactBegin(PhysicsContact& contact){
   
    Node* circle = nullptr;
    Node* star = nullptr;
    Node* box = nullptr;
    
    if (contact.getShapeA()->getBody()->getNode()->getTag() == Circle::CIRCLE_TAG) {
        circle = contact.getShapeA()->getBody()->getNode();
    }else if (contact.getShapeA()->getBody()->getNode()->getTag() == StarPower::STAR_TAG) {
        star = contact.getShapeA()->getBody()->getNode();
    }else{
        box = contact.getShapeA()->getBody()->getNode();
    }
    
    if (contact.getShapeB()->getBody()->getNode()->getTag() == Circle::CIRCLE_TAG) {
        circle = contact.getShapeB()->getBody()->getNode();
    }else if (contact.getShapeB()->getBody()->getNode()->getTag() == StarPower::STAR_TAG) {
        star = contact.getShapeB()->getBody()->getNode();
    }else{
        box = contact.getShapeB()->getBody()->getNode();
    }
    
    if (circle && star) {
        this->handleCircleStarCol(star);
    }
    
    if (circle && box ) {
        this->handleCircleBoxCol(box);
    }
    
    return true;
}

void IntroLayer::handleCircleStarCol(Node * star){
    circle->runStarPowerAnimation();
    boxesIn.eraseObject(star);
    star->removeFromParent();
    moveCount = 0;
}

void IntroLayer::handleCircleBoxCol(Node * box){
    
    if (circle->isPowerActive) {
        
        box->removeFromParent();
        boxesIn.eraseObject(box);
        moveCount = 0;
        
    }else{
        LivesLayer * livesl =  (LivesLayer *)this->getChildByTag(LIVE_LAYER);
        livesl->decreaseLives();
        circle->setColor(livesl->getCurrentColor());
    }
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
            this->endIntro();
           
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
    
    spawner->ballSize = circle->getBoundingBox().size;
    
    
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