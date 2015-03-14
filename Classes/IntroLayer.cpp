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
                auto star = spawner->spawnStar(481);
                this->addChild(star);
                timePassed = 0;
                boxesIn.pushBack(star);
                spawnCount++;
                
            }else{
                auto box = spawner->introSpawnBox(Size(15, 15), 481);
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
    star->getPhysicsBody()->setContactTestBitmask(false);
    star->getPhysicsBody()->setCollisionBitmask(0);
    star->getPhysicsBody()->setCategoryBitmask(0);
    boxesIn.eraseObject(star);
    star->removeFromParent();
    moveCount = 0;
}

void IntroLayer::handleCircleBoxCol(Node * box){
    box->getPhysicsBody()->setContactTestBitmask(false);
    box->getPhysicsBody()->setCollisionBitmask(0);
    box->getPhysicsBody()->setCategoryBitmask(0);
    
    if (!circle->isPowerActive) {
        this->pausePhysics();
        this->createCircleSwitchAni();
        this->createBoxExplo(circle, true);
        
    }else{
        this->createBoxExplo(box, false);
        box->removeFromParent();
        boxesIn.eraseObject(box);
        moveCount = 0;
        
    }
    
}

void IntroLayer::createBoxExplo(cocos2d::Node *box, bool isCircle){
    
    for (int i = 0; i < 8; i++) {
        Sprite* miniBox;
        
        if (isCircle) {
            miniBox = Sprite::create("circle.png");
            miniBox->setScale(circle->getScale()/6);
            
        }else{
            miniBox = Sprite::create();
            miniBox->setTextureRect(Rect(0, 0, box->getBoundingBox().size.width/4, box->getBoundingBox().size.height/4));
        }
        
        
        miniBox->setColor(box->getColor());
        miniBox->setPosition(Vec2(box->getPosition().x, box->getPosition().y));
        
        auto moveTo = MoveTo::create(.7, this->getExploPoint(i, box->getPosition()));
        
        auto end1 = CallFunc::create([&, miniBox](){
            miniBox->removeFromParent();
            
        });
        
        auto end2 = CallFunc::create([&, miniBox](){
            miniBox->removeFromParent();
            if (noMoreLifes) {
                this->endIntro();
            }
        });
        
        if (i == 7) {
            auto seq = Sequence::createWithTwoActions(moveTo, end2);
            miniBox->runAction(seq);
        }else{
            auto seq = Sequence::createWithTwoActions(moveTo, end1);
            miniBox->runAction(seq);
        }
        
        this->addChild(miniBox);
    }
}

Vec2 IntroLayer::getExploPoint(int i, Vec2 startPosition){
    float x = 0;
    float y = 0;
    
    switch (i) {
        case 0:
            x = startPosition.x;
            y = this->getBoundingBox().size.height;
            break;
            
        case 1:
            
            x = this->getBoundingBox().size.width;
            y = startPosition.y;
            break;
            
        case 2:
            
            x = startPosition.x;
            y = 0;
            break;
            
        case 3:
            x = 0;
            y = startPosition.y;
            break;
            
        case 4:
            if (this->getBoundingBox().size.width - startPosition.x < this->getBoundingBox().size.height - startPosition.y ) {
                x = this->getBoundingBox().size.width;
                y = startPosition.y + this->getBoundingBox().size.width - startPosition.x;
            }else{
                x = startPosition.x + this->getBoundingBox().size.height - startPosition.y ;
                y = this->getBoundingBox().size.height;
            }
            break;
            
        case 5:
           
            if (this->getBoundingBox().size.width - startPosition.x < startPosition.y ) {
                x = this->getBoundingBox().size.width;
                y = startPosition.y - (this->getBoundingBox().size.width - startPosition.x);
            }else{
                x = startPosition.x + startPosition.y;
                y = 0;
            }
            
            break;
            
        case 6:
            if (startPosition.x < startPosition.y ) {
                x = 0;
                y = startPosition.y - startPosition.x;
            }else{
                x = startPosition.x - startPosition.y;
                y = 0;
            }
            
            break;
            
        case 7:
           
            if (startPosition.x < this->getBoundingBox().size.height - startPosition.y ) {
                x = 0;
                y = startPosition.y + startPosition.x;
            }else{
                x = startPosition.x - (this->getBoundingBox().size.height - startPosition.y);
                y = this->getBoundingBox().size.height;
            }
            
            break;
    }
    
    return Vec2(x, y);
    
}

void IntroLayer::pausePhysics(){
    
    this->unscheduleUpdate();
    circle->stopAllActions();
    
    for (int i = 0; i < boxesIn.size(); i++) {
        boxesIn.at(i)->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
}

void IntroLayer::resumesPhysics(){
    this->scheduleUpdate();
    for (int i = 0; i < boxesIn.size(); i++) {
        boxesIn.at(i)->getPhysicsBody()->setVelocity(Vec2(-481, 0));
    }
}

void IntroLayer::createCircleSwitchAni(){
    LivesLayer * livesl =  (LivesLayer *)this->getChildByTag(LivesLayer::LIVE_LAYER);
    
    Vec2 post = livesl->getCurrentChildPostion();
    Color3B nextColor = livesl->getCurrentColor();
    circle->setVisible(false);
    int left = livesl->decreaseLives();
    
    if (left == 0) {
        noMoreLifes = true;
        return;
    }
    
    auto sprite = Sprite::create("circle.png");
    this->scaleCorrectly(.15, sprite);
    sprite->setPosition(Vec2(livesl->getPosition().x + post.x, livesl->getPosition().y + post.y));
    sprite->setColor(nextColor);
    
    auto moveTo = MoveTo::create(1.5, Vec2(circle->getPosition().x, circle->getPosition().y));
    auto scaleUp = ScaleTo::create(1.5, circle->getScale());
    
    auto spawn = Spawn::createWithTwoActions(moveTo, scaleUp);
    
    auto callBack = CallFunc::create([&,sprite, nextColor](){
        circle->setColor(nextColor);
        circle->setVisible(true);
        sprite->removeFromParent();
        
        
        this->resumesPhysics();
        
    });
    
    auto seq = Sequence::create(spawn,callBack, NULL);
    
    sprite->runAction(seq);
    this->addChild(sprite);
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
    liveLayer->buildLives(.1);
    liveLayer->setPosition(Vec2(this->getContentSize().width - liveLayer->getContentSize().width, this->getContentSize().height - liveLayer->getContentSize().height));
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
    
    circle->setColor( Color3B(255, 255, 255));
    
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