
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
	//控制变颜色
	bool isChange;
    int m_state;
    int m_time;
	int m_balkTime;
    CCSize winSize;
    Ship *m_ship;
    CCSprite * m_backSky;
	//死亡后调用菜单
	CCMenu *dieMenu;
	//暂停技能菜单
	CCMenu *pcMenu;
	//技能按钮
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
	//加载敌机
    void updateEnemy(float dt);
	//加载障碍
	void updateBalk(float dt);
    Ship* getShip();
	//检查各个对象碰撞并删除屏幕外对象
    void checkIsCollide();
	//删除没血的敌机和敌机子弹、飞船和飞船子弹
    void removeInactiveUnit(float dt);
	//检查是否复活
    void checkIsReborn();
	//各个对象碰撞，由checkIsCollide调用
    bool collide(UnitSprite *a, UnitSprite *b);
    void updateUI();
	//按钮调用函数
	void gameBegin(CCObject* pSender);
	void gameAbout(CCObject* pSender);
	void gameOptions(CCObject* pSender);
	void gameContinue(CCObject* pSender);
    void gameOver(CCObject* pSender);
    void gamePause(CCObject *pSender);
	void gameChange(CCObject *pSender);
	//回复颜色
	void resetColChange();
	//回复按钮
	void resetBtnChange();
	//延迟暂停
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
