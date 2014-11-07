
#ifndef __MoonWarriorsx__Balk__
#define __MoonWarriorsx__Balk__

#include "cocos2d.h"
#include "Config.h"
#include "UnitSprite.h"

USING_NS_CC;

class Balk : public UnitSprite {
private:
	bool m_active;
	int m_HP;
	int m_velocityx;
	int m_velocityy;
    int m_zOrder;
	int m_attackMode;
    
public:
    Balk();
    ~Balk();
    bool balkInit(int speed, const char *weapon, int attactMode);
    virtual void update(float dt);
    virtual void hurt();
    virtual void destroy(bool isScore , bool isEffect);
    virtual CCRect collideRect();
    virtual bool isActive();
    int getZorder();
    //static void sharedEnemy();
    static Balk* create(int speed, const char *weapon, int attactMode);
    
};
#endif /* defined(__MoonWarriorsx__Balk__) */
