//
//  MySpawner.cpp
//  SQ
//
//  Created by David Villarreal on 3/4/15.
//
//

#include "MySpawner.h"
USING_NS_CC;

void MySpawner::createSpawner(SpawnerPosition position, Rect sceneRect){
    this->sceneRect = sceneRect;
    this->position = position;
    
}
SquareBox* MySpawner::spawnBox(Size boxSize, float velocity){
    
    if (timePassed >= spawnRate && spawnReady) {
        
        SquareBox * box = SquareBox::create();
        box->setTextureRect(Rect(0, 0,boxSize.width, boxSize.height));
        box->setColor(this->createRandomBrightColor());
        box->setPosition(this->getRandomPosition());
        box->createPhysicsBody(boxSize);
        this->getFinalVelocity(velocity);
        box->velocity = this->getFinalVelocity(velocity);
        box->getPhysicsBody()->setVelocity(box->velocity);
        box->getPhysicsBody()->setCategoryBitmask(true);
        box->getPhysicsBody()->setCollisionBitmask(this->getBoxCat());
        
        timePassed = 0;
        return box;
    }
    
    return nullptr;
    
}

int MySpawner::getBoxCat(){
    
    if (this->position == RIGHT) {
        return SquareBox::BOX_RIGHT;
    }
    
    if (this->position == LEFT) {
        return SquareBox::BOX_LEFT;
    }
    
    if (this->position == UPPER) {
        return SquareBox::BOX_UPPER;
    }
    
    if (this->position == LOWER) {
        return SquareBox::BOX_LOWER;
    }
    
    return 0;
    
}

SquareBox* MySpawner::introSpawnBox(Size boxSize, float velocity){
    
    SquareBox * box = SquareBox::create();
    box->setTextureRect(Rect(0, 0,boxSize.width, boxSize.height));
    box->setColor(this->createRandomBrightColor());
    
    box->setPosition(this->getRandomIntroPosition());
    passIntroY = box->getPosition().y;
    box->createPhysicsBody(boxSize);
    box->getPhysicsBody()->setVelocity(this->getFinalVelocity(velocity));
    
    return box;
}

StarPower* MySpawner::spawnStar(float velocity){
    
    StarPower * star = StarPower::createWithFile("starPower2.png");
    this->scaleCorrectly(.15, star);
    star->setPosition(this->getRandomPosition());
    star->createPhysicsBody();
    star->getPhysicsBody()->setVelocity(this->getFinalVelocity(velocity));
    star->runAnimation();
    
    return star;
    
}

void MySpawner::scaleCorrectly(float scale, Sprite * sprite){
    sprite->getTexture()->generateMipmap();
    cocos2d::Texture2D::TexParams texpar = {GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    sprite->getTexture()->setTexParameters(texpar);
    sprite->setScale(scale);
}


Vec2 MySpawner::getRandomIntroPosition(){
    float x = sceneRect.size.width;
    float y = 10;
    
    do{
        y = random(ballSize.height/2,sceneRect.size.height - ballSize.height/2);
        
    }while (y > (passIntroY - ballSize.width) && y < (passIntroY + ballSize.width) );
    
    return Vec2(x, y);
}


Vec2 MySpawner::getFinalVelocity(float velocity){
    
    Vec2 vect;
    
    if (position == RIGHT) {
        vect = Vec2(-1*velocity, 0);
        
    }else if (position == LEFT){
        vect = Vec2(velocity, 0);
        
    }else if(position == UPPER){
        vect = Vec2(0,-1*velocity);
        
    }else if(position == LOWER){
        vect = Vec2(0,velocity);
    }
    return vect;
}

Vec2 MySpawner::getRandomPosition(){
    
    float x = 0;
    float y = 0;
    
    if (position == RIGHT) {
        x = sceneRect.size.width;
        y = random((float)0,sceneRect.size.height);
        
    }else if (position == LEFT){
        x = 0;
        y = random((float)0,sceneRect.size.height);
        
    }else if(position == UPPER){
        x = random((float)0, sceneRect.size.width);
        y = sceneRect.size.height;
        
    }else if(position == LOWER){
        x = random((float)0, sceneRect.size.width);
        y = 0;
    }
    
    return Vec2(x, y);
}


Color3B MySpawner::createRandomBrightColor(){
    
    Color3B color = Color3B(random(0, 255), random(0, 255), random(0, 255));
    
    int ave = (color.r + color.g + color.b)/3;
    
    if (ave < 150) {
        int rannum = random(1, 3);
        if (rannum == 1) {
            color.r += 10;
        }else if(rannum == 2){
            color.g += 10;
        }else{
            color.b += 10;
        }
    }
    return color;
}