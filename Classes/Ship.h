
#ifndef __MoonWarriorsx__Ship__
#define __MoonWarriorsx__Ship__

#include "cocos2d.h"
#include "UnitSprite.h"
USING_NS_CC;

class Ship : public UnitSprite{
private:
    
    // 子弹速度
    int m_bulletSpeed;
    
    // 生命值
    int m_HP;
    
    
    // 子弹威力
    int m_bulletPowerValue;
    
    
    // 是否可被攻击
    bool m_canBeAttack;
    
    int m_zOrder;
    
    // 出现的初始位置
    bool m_active;
	CCSize winSize;
    
public:
    Ship();
    ~Ship();
    
    // 被攻击使能
    void makeAttack(CCNode *pSender);
    
    // 更新
    virtual void update(float dt);
    
    // 射击
    void shoot(float dt);
    
    // 初始化
    virtual bool init();
    
    // 被攻击，受伤
    virtual void hurt();
    
    // 销毁飞船
    virtual void destroy(bool isScore , bool isEffect);

    
    // 获取生存状态
    virtual bool isActive();
    
    // 碰撞矩形
    virtual CCRect collideRect();
    int getZorder();
    
    // 构造器
    CREATE_FUNC(Ship);
};

#endif /* defined(__MoonWarriorsx__Ship__) */
