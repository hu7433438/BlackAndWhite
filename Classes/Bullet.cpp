
#include "Bullet.h"
#include "Resource.h"
#include "Config.h"


Bullet::Bullet():m_active(true),m_velocityx(0),m_velocityy(200),m_power(1),m_Hp(1),m_zOrder(1)
{
    
}
/**子弹构造器，可以用create重写下，懒的写了*/
Bullet::Bullet(int speed, const char *weapon)
{
    m_active = true;
    m_velocityx = 0;
    m_power = 1;
    m_Hp = 1;
	m_zOrder = 1;
    
    m_velocityy = -speed;

//     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_bullet_plist);
//     this->initWithSpriteFrameName(weapon);
	CCTexture2D * bulletTextureCache = CCTextureCache::sharedTextureCache()->addImage(weapon);
	this->initWithTexture(bulletTextureCache);
//     ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
//     this->setBlendFunc(cbl);

}

void Bullet::update(float dt)
{
    CCPoint position = this->getPosition();
    position.x -= m_velocityx * dt;
    position.y -= m_velocityy * dt;
    setPosition(position);
    if (m_Hp <= 0) 
	{
        m_active = false;
    }

// 	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
// 
// 	if (position.y<-64||position.y>winSize.height/2+64)
// 	{
// 		m_active = false;
// 	}

}
bool Bullet::init()
{
    return true;
}

void Bullet::hurt()
{
    m_Hp--;
}

void Bullet::destroy(bool isScore , bool isEffect)
{
    CCSprite *explode;
    // 子弹爆炸特效
	if (isEffect)
	{
		explode = CCSprite::create(s_hit);
		ccBlendFunc cb = {GL_SRC_ALPHA, GL_ONE };
		explode->setBlendFunc(cb);
		explode->setPosition(this->getPosition());
		explode->setRotation(CCRANDOM_0_1() * 360);
		explode->setScale(0.75);
		getParent()->addChild(explode, 3);
	}

	play_bullet->removeObject(this);
	enemy_bullet->removeObject(this);
    this->removeFromParent();
    
	if (isEffect)
	{
		CCCallFuncN *removeExplode =  CCCallFuncN::create(explode, callfuncN_selector(Bullet::removeExplode));
		explode->runAction(CCScaleBy::create(0.3f, 2, 2));
		explode->runAction(CCSequence::create(CCFadeOut::create(0.3f), removeExplode, NULL));
	}
    
}

void Bullet::removeExplode(CCNode *pSender)
{
    pSender->removeFromParent();
}
bool Bullet::isActive()
{
    return m_active;
}

CCRect Bullet::collideRect()
{
	CCSize size = getContentSize();
	CCPoint pos = getPosition();
	return CCRectMake(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height / 2);
}

int Bullet::getZorder()
{
	return m_zOrder;
}


