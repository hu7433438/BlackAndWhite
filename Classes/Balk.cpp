
#include "Balk.h"
#include "Resource.h"
#include "SimpleAudioEngine.h"
#include "Effect.h"

using namespace CocosDenshion;

Balk::Balk():m_active(true),m_velocityx(0),m_velocityy(200),m_zOrder(0),m_HP(1)
{
    
}
Balk::~Balk()
{
    
}

/**�Լ���create��������ΪҪ���������Ǹ��ӵ���Ҳ������ôд*/
Balk* Balk::create(int speed, const char *weapon, int attactMode)
{
    Balk *pRet = new Balk();
    if (pRet && pRet->balkInit(speed,weapon,attactMode)) {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

/**�Լ���init����*/
bool Balk::balkInit(int speed, const char *weapon, int attactMode)
{
    if ( !CCSprite::init() )
    {
        return false;
    }
	m_active = true;
	m_velocityx = 0;
	m_HP = 1;

	m_velocityy = -speed;
	m_attackMode = attactMode;

	CCTexture2D * balkTextureCache = CCTextureCache::sharedTextureCache()->addImage(weapon);
	this->initWithTexture(balkTextureCache);
    
    return true;
}

void Balk::update(float dt)
{
	CCPoint position = this->getPosition();
	position.x -= m_velocityx * dt;
	position.y -= m_velocityy * dt;
	setPosition(position);
	if (m_HP <= 0) 
	{
		m_active = false;
	}
}

void Balk::destroy(bool isScore , bool isEffect)
{
    // �л���ը���ӵл�����ɾ��
    balk_items->removeObject(this);
    
    // ɾ������
    this->removeFromParent();
	
}

CCRect Balk::collideRect()
{
    CCSize size = getContentSize();
    CCPoint pos = getPosition();
    
    return CCRectMake(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height / 2);
}

void Balk::hurt()
{
	m_HP--;
}

bool Balk::isActive()
{
	return m_active;
}

int Balk::getZorder()
{
	return m_zOrder;
}






// void Enemy::sharedEnemy()
// {
//     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_Enemy_plist, s_enemy);
// }