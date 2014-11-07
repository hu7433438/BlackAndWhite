
#ifndef __MoonWarriorsx__GameLayer__
#define __MoonWarriorsx__GameLayer__

#include "cocos2d.h"
#include "Ship.h"
#include "LevelManager.h"
USING_NS_CC;

enum Sate{
    statePause   = 0,
    statePlaying = 1,
};


class GameLayer : public CCLayer {
    
private:
	//���Ʊ���ɫ
	bool isChange;
    int m_state;
    int m_time;
	int m_balkTime;
    CCSize winSize;
    Ship *m_ship;
    CCSprite * m_backSky;
	//��������ò˵�
	CCMenu *dieMenu;
	//��ͣ���ܲ˵�
	CCMenu *pcMenu;
	//���ܰ�ť
	CCMenuItemImage *change;
    CCLabelBMFont *m_lbScore;
    //CCLabelTTF *m_lifeCount;
    CCRect m_screenRec;
    LevelManager *m_levelManager;
    int m_tempScore;
public:
    GameLayer();
    ~GameLayer();
    virtual bool init();
    virtual void update(float dt);
	//���صл�
    void updateEnemy(float dt);
	//�����ϰ�
	void updateBalk(float dt);
    Ship* getShip();
	//������������ײ��ɾ����Ļ�����
    void checkIsCollide();
	//ɾ��ûѪ�ĵл��͵л��ӵ����ɴ��ͷɴ��ӵ�
    void removeInactiveUnit(float dt);
	//����Ƿ񸴻�
    void checkIsReborn();
	//����������ײ����checkIsCollide����
    bool collide(UnitSprite *a, UnitSprite *b);
    void updateUI();
	//��ť���ú���
	void gameBegin(CCObject* pSender);
	void gameAbout(CCObject* pSender);
	void gameOptions(CCObject* pSender);
	void gameContinue(CCObject* pSender);
    void gameOver(CCObject* pSender);
    void gamePause(CCObject *pSender);
	void gameChange(CCObject *pSender);
	//�ظ���ɫ
	void resetColChange();
	//�ظ���ť
	void resetBtnChange();
	//�ӳ���ͣ
	void delayPause();
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void draw();
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__MoonWarriorsx__GameLayer__) */
