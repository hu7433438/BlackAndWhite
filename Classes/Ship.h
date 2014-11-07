
#ifndef __MoonWarriorsx__Ship__
#define __MoonWarriorsx__Ship__

#include "cocos2d.h"
#include "UnitSprite.h"
USING_NS_CC;

class Ship : public UnitSprite{
private:
    
    // �ӵ��ٶ�
    int m_bulletSpeed;
    
    // ����ֵ
    int m_HP;
    
    
    // �ӵ�����
    int m_bulletPowerValue;
    
    
    // �Ƿ�ɱ�����
    bool m_canBeAttack;
    
    int m_zOrder;
    
    // ���ֵĳ�ʼλ��
    bool m_active;
	CCSize winSize;
    
public:
    Ship();
    ~Ship();
    
    // ������ʹ��
    void makeAttack(CCNode *pSender);
    
    // ����
    virtual void update(float dt);
    
    // ���
    void shoot(float dt);
    
    // ��ʼ��
    virtual bool init();
    
    // ������������
    virtual void hurt();
    
    // ���ٷɴ�
    virtual void destroy(bool isScore , bool isEffect);

    
    // ��ȡ����״̬
    virtual bool isActive();
    
    // ��ײ����
    virtual CCRect collideRect();
    int getZorder();
    
    // ������
    CREATE_FUNC(Ship);
};

#endif /* defined(__MoonWarriorsx__Ship__) */
