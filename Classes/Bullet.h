
#ifndef __MoonWarriorsx__Bullet__
#define __MoonWarriorsx__Bullet__

#include "cocos2d.h"
#include "UnitSprite.h"
USING_NS_CC;

class Bullet : public UnitSprite {
private:
    float m_velocityx;
    float m_velocityy;
    int m_power;
    int m_Hp;
	int m_zOrder;

public:
    bool m_active;
    Bullet();
    Bullet(int speed, const char* weapon);
    virtual bool init();
    virtual void update(float dt);
    virtual void hurt();
    virtual void destroy(bool isScore , bool isEffect);

    virtual CCRect collideRect();
    virtual bool isActive();
    int getZorder();

    void removeExplode(CCNode *pSender);
    CREATE_FUNC(Bullet);
};

#endif /* defined(__MoonWarriorsx__Bullet__) */
