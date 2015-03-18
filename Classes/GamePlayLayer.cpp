//
//  GamePlayLayer.cpp
//  SQ
//
//  Created by David Villarreal on 3/11/15.
//
//

#include "GamePlayLayer.h"
USING_NS_CC;


GamePlayLayer* GamePlayLayer::create(const cocos2d::Color4B &color){
    
    GamePlayLayer * layer = new (std::nothrow) GamePlayLayer();
    if(layer && layer->initWithColor(color))
    {
        layer->autorelease();
        layer->buildGameLayer();
        
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
    
}

void GamePlayLayer::update(float deltaTime){
    
    
    if (!isPaused) {
        
        this->spawnBall(deltaTime);
        this->checkBoxIn();
        
        if (test == 10) {
            this->spawnStar(deltaTime);
        }
        
        gameCon->increaseGameTime(deltaTime);
        
        this->updatePointsLabel(gameCon->increaseScore());
        
        if (gameCon->recordReached()) {
            this->createNewRecordAni();
        }
        
    }
}

void GamePlayLayer::spawnBall(float deltaTime){
    
    for (int i = 0; i < spawners.size(); i++) {
        SquareBox * box = spawners.at(i)->spawnBox(Size(16, 16), 200);
        
        if (box) {
            box->retain();
            this->addChild(box);
            nodesIn.push_back(box);
            test++;
        }
        
        spawners.at(i)->timePassed+= deltaTime;
    }
}

void GamePlayLayer::spawnStar(float deltaTime){
    auto star = spawners[random(0, 3)]->spawnStar(400);
    this->addChild(star);
    test++;
    
}

void GamePlayLayer::updatePointsLabel(int amount){
    
    if (amount > 0) {
        pointsLabel->setString(std::to_string(amount));
    }

}

void GamePlayLayer::checkBoxIn(){
    
    for (auto it = nodesIn.cbegin(); it != nodesIn.cend(); it++) {
        
        if ((*it)->getReferenceCount() == 2) {
            bool isInside = (*it)->getPosition().x < 0 || (*it)->getPosition().x > this->getContentSize().width || (*it)->getPosition().y < 0 || (*it)->getPosition().y > this->getContentSize().height;
            
            if (isInside){
                (*it)->removeFromParent();
                (*it)->release();
                nodesIn.erase(it);
            }
        }else if( (*it)->getReferenceCount() == 1){
            (*it)->release();
            nodesIn.erase(it);
        }
        
    }
}

bool GamePlayLayer::onContactBegin(cocos2d::PhysicsContact &contact){
    
    
    
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
    

    
    if (circle && box ) {
        this->handleCircleBoxCol(box);
    }
    
    if (circle && star) {
        this->handleCircleStarCol(star);
    }
    
    
    return true;
}

void GamePlayLayer::handleCircleBoxCol(Node* box){
    
    box->getPhysicsBody()->setContactTestBitmask(false);
    box->getPhysicsBody()->setCollisionBitmask(0);
    box->getPhysicsBody()->setCategoryBitmask(0);
    
    if (!circle->isPowerActive) {
        isSwitching = true;
        this->pausePhysics();
        this->createCircleSwitchAni();
        this->createBoxExplo(circle, true);
        
    }else{
        this->updatePointsLabel(gameCon->increaseScoreByHit());
        this->createBoxExplo(box, false);
        box->removeFromParent();
        
    }

}

void GamePlayLayer::handleCircleStarCol(Node*star){
    circle->runStarPowerAnimation();
    star->getPhysicsBody()->setContactTestBitmask(false);
    star->getPhysicsBody()->setCollisionBitmask(0);
    star->getPhysicsBody()->setCategoryBitmask(0);
    star->removeFromParent();
}

void GamePlayLayer::createBoxExplo(cocos2d::Node *box, bool isCircle){
    
    for (int i = 0; i < 8; i++) {
        Sprite* miniBox;
        
        
        
        if (isCircle) {
            miniBox = Sprite::create("circle.png");
            miniBox->setScale(circle->getScale()/6);
            
        }else{
            miniBox = Sprite::create();
            miniBox->setTextureRect(Rect(0, 0, box->getBoundingBox().size.width/4, box->getBoundingBox().size.height/4));
            
            Label * plus5 = Label::createWithTTF("+5", "fonts/arial.ttf", 28);
            plus5->setPosition(box->getPosition().x, box->getPosition().y);
            plus5->setColor(box->getColor());
            auto scaleUp = ScaleTo::create(.7, 2);
            
            auto callBac = CallFunc::create([plus5](){
                plus5->removeFromParent();
            });
            
            plus5->runAction(Sequence::createWithTwoActions(scaleUp, callBac));
            this->addChild(plus5);
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
                int highScore = this->gameCon->getHighScore();
                int score = this->gameCon->getGameScore();
                this->deleteAll();
                this->gameOverCall(score, highScore);
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

void GamePlayLayer::createCircleSwitchAni(){
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
        isSwitching = false;
        this->resumePhysics();
        
    });
    
    auto seq = Sequence::create(spawn,callBack, NULL);
    
    sprite->runAction(seq);
    this->addChild(sprite);
}

void GamePlayLayer::createNewRecordAni(){
    
}

void GamePlayLayer::pausePhysics(){
    
    this->unscheduleUpdate();
    circle->stopAllActions();
    
    for (auto it = nodesIn.cbegin(); it != nodesIn.cend(); it++) {
       (*it)->pausePhysics();
    }
}

void GamePlayLayer::resumePhysics(){
    this->scheduleUpdate();
    for (auto it = nodesIn.cbegin(); it != nodesIn.cend(); it++) {
        (*it)->resumePhysics();
    }
}

Vec2 GamePlayLayer::getExploPoint(int i, Vec2 startPosition){
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



void GamePlayLayer::buildGameLayer(){
    
    gameCon = new GameStageController();
    
    this->createSpawners();
    this->createCircle();
    this->createLivesLayer();
    this->createPointLabel();
    this->addTouchHandlers();
    
    
    this->scheduleUpdate();
    
}

void GamePlayLayer::createLivesLayer(){
    LivesLayer * liveLayer = LivesLayer::create(Color4B(255, 255, 255, 0));
    liveLayer->buildLives(.15);
    liveLayer->setPosition(Vec2(this->getContentSize().width - liveLayer->getContentSize().width, this->getContentSize().height - liveLayer->getContentSize().height));
    this->addChild(liveLayer);
}

void GamePlayLayer::createSpawners(){
    spawners.reserve(4);
    
    MySpawner * spawner1 = new MySpawner();
    spawner1->createSpawner(UPPER, this->getBoundingBox());
    spawner1->spawnRate = 1/1;
    //spawner1->spawnReady = true;
    spawners.push_back(spawner1);
    
    MySpawner * spawner2 = new MySpawner();
    spawner2->createSpawner(RIGHT, this->getBoundingBox());
    spawner2->spawnRate = 1/5.0;
    spawner2->spawnReady = true;
    spawners.push_back(spawner2);
    
    MySpawner * spawner3 = new MySpawner();
    spawner3->createSpawner(LOWER, this->getBoundingBox());
    spawner3->spawnRate = 1/1;
    //spawner3->spawnReady = true;
    spawners.push_back(spawner3);
    
    MySpawner * spawner4 = new MySpawner();
    spawner4->createSpawner(LEFT, this->getBoundingBox());
    spawner4->spawnRate = 1/1;
    //spawner4->spawnReady = true;
    spawners.push_back(spawner4);
}

void GamePlayLayer::createPointLabel(){
    
    Vec2 liveLayerP = this->getChildByTag(LivesLayer::LIVE_LAYER)->getPosition();
    
    pointsLabel = Label::createWithTTF(" 0", "fonts/Titillium-Light.otf", 43);
    pointsLabel->setColor(Color3B::WHITE);
    pointsLabel->setAnchorPoint(Vec2(0.5, 0.5));
    pointsLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    pointsLabel->setPosition(this->getContentSize().width/2, this->getContentSize().height - pointsLabel->getContentSize().height);
    this->addChild(pointsLabel);
    
    
}

void GamePlayLayer::deleteSpawners(){
    for (int i = 0; i < spawners.size(); i++) {
        delete spawners[i];
    }
    spawners.clear();
}

void GamePlayLayer::createCircle(){
    
    circle = Circle::createWithFile("circle.png");
    circle->setScale(.25);
    circle->setPosition(circle->getBoundingBox().size.height, this->getBoundingBox().size.height/2);
    circle->createPhysicsBody();
    circle->setColor( Color3B(255, 255, 255));
    for (int i = 0; i < spawners.size(); i++) {
        spawners[i]->ballSize = circle->getBoundingBox().size;
    }
    
    this->addChild(circle);
    
}

void GamePlayLayer::deleteNodesIn(){
    
    for (auto it = nodesIn.cbegin(); it != nodesIn.cend(); it++) {
        if ( (*it) -> getReferenceCount() > 1) {
            (*it)->release();
        }
    }
    nodesIn.clear();
    
    delete gameCon;
}

void GamePlayLayer::deleteAll(){
    this->deleteNodesIn();
    this->deleteSpawners();
    this->removeAllChildren();
}

void GamePlayLayer::scaleCorrectly(float scale, Sprite * sprite){
    sprite->getTexture()->generateMipmap();
    cocos2d::Texture2D::TexParams texpar = {GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(texpar);
    sprite->setScale(scale);
}

void GamePlayLayer::addTouchHandlers(){
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        
        if (!isSwitching) {
            circle->setPosition(touch->getLocation());
        }
        return true;
    };
    
    listener->onTouchMoved = [&](Touch* touch, Event* event){
       
        if (!isSwitching) {
            circle->setPosition(touch->getLocation());
        }
        
    };
    
    
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        // your code
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GamePlayLayer::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    
}












