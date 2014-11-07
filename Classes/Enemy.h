
#ifndef __MoonWarriorsx__Enemy__
#define __MoonWarriorsx__Enemy__

#include "cocos2d.h"
#include "Config.h"
#include "UnitSprite.h"

USING_NS_CC;

class Enemy : public UnitSprite {
private:
    bool m_active;
	bool m_isShoot;
    int m_bulletSpeed;
    int m_HP;
    int m_bulletPowerValure;
    int m_moveType;
    int m_scoreValue;
    int m_zOrder;
	int m_attackMode;
    float m_shootTime;
    
public:
    Enemy();
    ~Enemy();
    bool enemyInit(EnemyType type);
    virtual void update(float dt);
    void shoot(float dt);
    virtual void hurt();
    virtual void destroy(bool isScore , bool isEffect);
    virtual CCRect collideRect();
    virtual bool isActive();
    int getZorder();

    //static void sharedEnemy();
    static Enemy* create(EnemyType type);
    int getMoveType();
    
};
#endif /* defined(__MoonWarriorsx__Enemy__) */
