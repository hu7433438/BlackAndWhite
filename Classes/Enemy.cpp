
#include "Enemy.h"
#include "Resource.h"
#include "Bullet.h"
#include "Config.h"
#include "SimpleAudioEngine.h"
#include "Effect.h"

using namespace CocosDenshion;

Enemy::Enemy():m_active(true),m_isShoot(true),m_bulletSpeed(-200),m_HP(15),m_bulletPowerValure(1),m_moveType(0),m_scoreValue(200),m_zOrder(2),m_shootTime(1),m_attackMode(1)
{
    
}
Enemy::~Enemy()
{
    
}

/**自己的create函数，因为要带参数，那个子弹类也可以这么写*/
Enemy* Enemy::create(EnemyType type)
{
    Enemy *pRet = new Enemy();
    if (pRet && pRet->enemyInit(type)) {
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

/**自己的init函数*/
bool Enemy::enemyInit(EnemyType type)
{
    if ( !CCSprite::init() )
    {
        return false;
    }
    
    
    m_HP          = type.hp;
    m_moveType    = type.moveType;
    m_scoreValue  = type.scoreValue;
	m_bulletSpeed = type.bulletSpeed;
	m_shootTime   = type.shootTime;
	m_isShoot     = type.isShoot;
	m_attackMode  = type.attackMode;
    
	CCTexture2D * enemyTextureCache = CCTextureCache::sharedTextureCache()->addImage(type.textureName.c_str());
	this->initWithTexture(enemyTextureCache);
    //this->initWithSpriteFrameName(type.textureName.c_str());
	if (m_isShoot)
	{
		this->schedule(schedule_selector(Enemy::shoot),m_shootTime);
	}
    
    return true;
}

void Enemy::update(float dt)
{
    if (m_HP < 0) {
        m_active = false;
    }
}

void Enemy::shoot(float dt)
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	if (this->getPositionY()>=this->getContentSize().height/2&&this->getPositionY()<=winsize.height-this->getContentSize().height/2
		&&this->getPositionX()>=this->getContentSize().width/2&&this->getPositionX()<=winsize.width-this->getContentSize().width/2)
	{
		CCPoint pos = this->getPosition();
		CCSize cos = this->getContentSize();
		Bullet *bullet = new Bullet(m_bulletSpeed, "W2.png");
		switch (m_attackMode)
		{
		case 1:
			bullet->autorelease();
			enemy_bullet->addObject(bullet);
			getParent()->addChild(bullet, bullet->getZorder(), 900);
			bullet->setPosition(ccp(pos.x, pos.y - cos.height/2));
			Effect::changeColorb(bullet);
			break;
		case 2:
			bullet->autorelease();
			enemy_bullet->addObject(bullet);
			getParent()->addChild(bullet, m_zOrder, 900);
			bullet->setPosition(ccp(pos.x, pos.y - getContentSize().height * 0.2));
			Effect::changeColorb(bullet);
			break;
		case 3:
			bullet->autorelease();
			enemy_bullet->addObject(bullet);
			getParent()->addChild(bullet, m_zOrder, 900);
			bullet->setPosition(ccp(pos.x, pos.y - getContentSize().height * 0.2));
			Effect::changeColorb(bullet);
			break;
		case 4:
			bullet->autorelease();
			enemy_bullet->addObject(bullet);
			getParent()->addChild(bullet, m_zOrder, 900);
			bullet->setPosition(ccp(pos.x, pos.y - getContentSize().height * 0.2));
			Effect::changeColorb(bullet);
			break;
		}
	}
}

void Enemy::hurt()
{
    m_HP--;
}

void Enemy::destroy(bool isScore , bool isEffect)
{
	if (isScore)
	{
		// 更新分数
		Config::sharedConfig()->setScoreValue(m_scoreValue );
	}

	if (isEffect)
	{
		// 爆炸特效和闪光特效
		Effect *effect = Effect::create();

		effect->explode(this->getParent(), getPosition());

		effect->spark(this->getPosition(),this->getParent(), 1.2f, 0.7f);
	}
	
    
    // 敌机爆炸，从敌机数组删除
    enemy_items->removeObject(this);
    
    // 删除精灵
    this->removeFromParent();
    
	if (isEffect)
	{
		// 声音
		if (Config::sharedConfig()->getAudioState())
		{
			SimpleAudioEngine::sharedEngine()->playEffect(s_explodeEffect);
		}
	}
	
}

CCRect Enemy::collideRect()
{
    CCSize size = getContentSize();
    CCPoint pos = getPosition();
    
    return CCRectMake(pos.x - size.width / 2, pos.y - size.height / 4, size.width, size.height / 2);
}

int Enemy::getMoveType()
{
	return m_moveType;
}
bool Enemy::isActive()
{
    return  m_active;
}

int Enemy::getZorder()
{
	return m_zOrder;
}



// void Enemy::sharedEnemy()
// {
//     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_Enemy_plist, s_enemy);
// }