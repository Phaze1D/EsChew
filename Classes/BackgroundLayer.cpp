//
//  BackgroundLayer.cpp
//  SQ
//
//  Created by David Villarreal on 2/26/15.
//
//

#include "BackgroundLayer.h"

USING_NS_CC;

bool BackgroundLayer::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    this->createParticles();
    
    return true;
}


void BackgroundLayer::createParticles(){
    auto size = Director::getInstance()->getWinSize();
    
    
    ParticleSystemQuad * m_emitter = ParticleSystemQuad::createWithTotalParticles(50);
    m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("star.jpg"));
    m_emitter->setDuration(-1);
    m_emitter->setGravity(Point(0, 0));  // in Cocos2d-x-2.x CCPoint(0, -240) is used
    m_emitter->setAngle(90);
    m_emitter->setAngleVar(360);
    m_emitter->setRadialAccel(0);
    m_emitter->setRadialAccelVar(0);
    m_emitter->setTangentialAccel(0);
    m_emitter->setTangentialAccelVar(0);
    m_emitter->setPosition(Point(size.width / 2, size.height/2));
    m_emitter->setPosVar(Point(size.width/2, size.height/2));
    m_emitter->setLife(3);
    m_emitter->setLifeVar(1);
    m_emitter->setStartSpin(30);
    m_emitter->setStartSpinVar(60);
    m_emitter->setEndSpin(0);
    m_emitter->setEndSpinVar(0);
    m_emitter->setStartColor(Color4F(1,1,1,1));
    m_emitter->setStartColorVar(Color4F(0,0,0,0));
    m_emitter->setEndColor(Color4F(1,1,1,1));
    m_emitter->setEndColorVar(Color4F(0,0,0,0));
    m_emitter->setStartSize(2);
    m_emitter->setStartSizeVar(13);
    m_emitter->setEndSize(0);
    m_emitter->setEndSizeVar(0);
    m_emitter->setEmissionRate(3);
    this->addChild(m_emitter);

}