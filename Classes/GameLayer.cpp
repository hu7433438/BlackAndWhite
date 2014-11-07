
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"
#include "Resource.h"
#include "Config.h"
#include "Enemy.h"
#include "Effect.h"
#include "GameOver.h"
#include "PauseLayer.h"
#include "About.h"


using namespace cocos2d;
using namespace CocosDenshion;


bool isPaused = false;

GameLayer::GameLayer():isChange(true),m_state(statePause),m_time(0),m_balkTime(0),m_ship(NULL),m_backSky(NULL),m_lbScore(NULL),m_tempScore(0)
{
    
}
GameLayer::~GameLayer()
{
    if (m_levelManager) {
        delete m_levelManager;
    }
    
    play_bullet->release();
    enemy_bullet->release();
    enemy_items->release();
	balk_items->release();
}

bool GameLayer::init()
{
    if (!CCLayer::init())
	{
        return false;
    }
    // 开启触摸
    this->setTouchEnabled(true);
    
    // 创建数组，需要retain一下
    play_bullet = CCArray::create();
    play_bullet->retain();
    
    enemy_bullet = CCArray::create();
    enemy_bullet->retain();
    
    enemy_items = CCArray::create();
    enemy_items->retain();

	balk_items = CCArray::create();
	balk_items->retain();
    
    m_state = statePause;
    
    //Enemy::sharedEnemy();
    Effect::sharedExplosion();
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    m_levelManager = new LevelManager(this);
    
    //初始化背景
	m_backSky = CCSprite::create(s_bg01);
	m_backSky->setPosition(ccp(winSize.width/2, winSize.height/2));
	m_backSky->setScaleY(winSize.height/m_backSky->getContentSize().height);
	addChild(m_backSky, -1);

	//主菜单按钮
	CCSprite* newGameNormal = CCSprite::create(s_menu, CCRectMake(0, 0, 126, 33));
	CCSprite* newGameSelected = CCSprite::create(s_menu, CCRectMake(0, 33, 126, 33));
	CCSprite* newGameDisabled = CCSprite::create(s_menu, CCRectMake(0, 33*2, 126, 33));

	CCSprite* aboutNormal = CCSprite::create(s_menu, CCRectMake(252, 0, 126, 33));
	CCSprite* aboutSelected = CCSprite::create(s_menu, CCRectMake(252, 33, 126, 33));
	CCSprite* aboutDesabled = CCSprite::create(s_menu, CCRectMake(252, 33*2, 126, 33));


	CCMenuItemSprite* newGame = CCMenuItemSprite::create(newGameNormal, newGameSelected, newGameDisabled, this, 
		menu_selector(GameLayer::gameBegin));

	CCMenuItemSprite* about = CCMenuItemSprite::create(aboutNormal, aboutSelected, aboutDesabled, this, 
		menu_selector(GameLayer::gameAbout));

	//音乐控制
	CCMenuItemFont::setFontName("Arial Bold");
	CCMenuItemFont::setFontSize(26);

	CCMenuItemFont *menuTitle = CCMenuItemFont::create("Sound");
	menuTitle->setEnabled(false);

	CCMenuItemToggle *toggle = CCMenuItemToggle::createWithTarget(this, menu_selector(GameLayer::gameOptions), CCMenuItemFont::create("On"),CCMenuItemFont::create("Off"), NULL);

	int selectId = Config::sharedConfig()->getAudioState()? 0 : 1;
	toggle->setSelectedIndex(selectId);

	// 最后一个参数要是NULL
	CCMenu* mainMenu = CCMenu::create(newGame, about, menuTitle, toggle, NULL);
	mainMenu->alignItemsVerticallyWithPadding(20);
	this->addChild(mainMenu, 4, 2);
	mainMenu->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 80));


	//功能按钮初始为不可见，游戏开始后变为可见
	CCMenuItemImage *pause = CCMenuItemImage::create("pause.png", "pause.png", this, menu_selector(GameLayer::gamePause));
	pause->setAnchorPoint(ccp(1, 0));
	pause->setPosition(ccp(winSize.width, 0));

	change = CCMenuItemImage::create("pause.png", "pause.png", this, menu_selector(GameLayer::gameChange));
	change->setAnchorPoint(ccp(1, 0));
	change->setPosition(ccp(50, 0));

	pcMenu = CCMenu::create(pause,change, NULL);
	pcMenu->setAnchorPoint(ccp(0, 0));
	this->addChild(pcMenu, 4, 10);
	pcMenu->setPosition(CCPointZero);
	pcMenu->setVisible(false);
	
	//玩家死亡对话框
	CCSprite* gameContinueNormal = CCSprite::create(s_menu, CCRectMake(0, 0, 126, 33));
	CCSprite* gameContinueSelected = CCSprite::create(s_menu, CCRectMake(0, 33, 126, 33));
	CCSprite* gameContinueDisabled = CCSprite::create(s_menu, CCRectMake(0, 33*2, 126, 33));

	CCSprite* gameOverNormal = CCSprite::create(s_menu, CCRectMake(126, 0, 126, 33));
	CCSprite* gameOverNSelected = CCSprite::create(s_menu, CCRectMake(126, 33, 126, 33));
	CCSprite* gameOverDesabled = CCSprite::create(s_menu, CCRectMake(126, 33*2, 126, 33));

	CCMenuItemSprite* gameContinue = CCMenuItemSprite::create(gameContinueNormal, gameContinueSelected, gameContinueDisabled, this, 
		menu_selector(GameLayer::gameContinue));

	CCMenuItemSprite* gameOver = CCMenuItemSprite::create(gameOverNormal, gameOverNSelected, gameOverDesabled, this, 
		menu_selector(GameLayer::gameOver));

	// 最后一个参数要是NULL
	dieMenu = CCMenu::create(gameContinue, gameOver, NULL);
	dieMenu->alignItemsHorizontallyWithPadding(20);
	this->addChild(dieMenu, 4, 10);
	dieMenu->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 80));
	dieMenu->setVisible(false);

    m_screenRec = CCRectMake(-64, -64,  winSize.width + 64, winSize.height*3/2);
    
    // 调 update函数
    scheduleUpdate();
    // 每秒调一次 scoreCounter函数
    schedule(schedule_selector(GameLayer::updateEnemy), 0.5);
	//schedule(schedule_selector(GameLayer::updateBalk),3);
    
    if (Config::sharedConfig()->getAudioState())
	{
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_bgMusic, true);
    }
    return true;
}



void GameLayer::update(float dt)
{
	checkIsCollide();
	removeInactiveUnit(dt);
    if (m_state == statePlaying) 
	{
		if (isChange)
		{
			Effect::changeColor(m_ship);
		}
		else
		{
			Effect::changeColorb(m_ship);
		}
		checkIsReborn();
		updateUI();
    }
}

void GameLayer::updateEnemy(float dt)
{
    if (m_state == statePlaying)
	{
        m_time++;
        m_levelManager->loadLevelResource(m_time);
    }
}


void GameLayer::updateBalk( float dt )
{
	if (m_state == statePlaying)
	{
		m_balkTime++;
		m_levelManager->loadLevelBalkResource(m_balkTime);
	}
}


void GameLayer::checkIsCollide()
{
    CCObject *enemys;
    CCObject *bullets;
    CCObject *enemybs;
	CCObject *balks;
    CCARRAY_FOREACH(enemy_items, enemys)
    {
        UnitSprite *enemy = dynamic_cast<UnitSprite*>(enemys);

        CCARRAY_FOREACH(play_bullet, bullets)
        {
            UnitSprite *bullet = dynamic_cast<UnitSprite*>(bullets);
            if (collide(enemy, bullet))
			{
				if (enemy->getColor().r!=bullet->getColor().r)
				{
					enemy->hurt();
					bullet->hurt();
				}
            }
			if (bullet)
			{
				if (!(m_screenRec.intersectsRect(bullet->boundingBox()))) 
				{
					bullet->destroy(false,false);
				}
			}
        }
        if (collide(enemy, m_ship)) 
		{
            if (m_ship->isActive()) 
			{
				if (m_ship->getColor().r!=enemy->getColor().r)
				{
					//enemy->hurt();
					m_ship->hurt();
				}
            }
        }
		if (enemy)
		{
			if (!(m_screenRec.intersectsRect(enemy->boundingBox()))) 
			{
				enemy->destroy(false,false);
			}
		}
    }
    
    CCARRAY_FOREACH(enemy_bullet, enemybs)
    {
        UnitSprite *enemyb = dynamic_cast<UnitSprite*>(enemybs);
        if (enemyb) 
		{
            if (collide(enemyb, m_ship)) 
			{
                if (m_ship->isActive())
				{
					if (m_ship->getColor().r!=enemyb->getColor().r)
					{
						m_ship->hurt();
						enemyb->hurt();
					}
					
                }
            }
			if (enemyb)
			{
				if (!m_screenRec.intersectsRect(enemyb->boundingBox())) 
				{
					enemyb->destroy(false,false);
				}
			}
        }
    }

	CCARRAY_FOREACH(balk_items, balks)
	{
		UnitSprite *blak = dynamic_cast<UnitSprite*>(balks);
		CCARRAY_FOREACH(play_bullet, bullets)
		{
			UnitSprite *bullet = dynamic_cast<UnitSprite*>(bullets);
			if (collide(blak, bullet))
			{
				if (blak->getColor().r!=bullet->getColor().r)
				{
					//blak->hurt();
					bullet->hurt();
				}

			}
			if (bullet)
			{
				if (!(m_screenRec.intersectsRect(bullet->boundingBox()))) 
				{
					bullet->destroy(false,false);
				}
			}
		}
		CCARRAY_FOREACH(enemy_bullet, enemybs)
		{
			UnitSprite *enemyb = dynamic_cast<UnitSprite*>(enemybs);
			if (collide(blak, enemyb))
			{
				if (blak->getColor().r!=enemyb->getColor().r)
				{
					//blak->hurt();
					enemyb->hurt();
				}

			}
			if (enemyb)
			{
				if (!(m_screenRec.intersectsRect(enemyb->boundingBox()))) 
				{
					enemyb->destroy(false,false);
				}
			}
		}
		if (blak) 
		{
			if (collide(blak, m_ship)) 
			{
				if (m_ship->isActive())
				{
					if (m_ship->getColor().r!=blak->getColor().r)
					{
						m_ship->hurt();
					}
				}
			}
			if (blak)
			{
				if (!m_screenRec.intersectsRect(blak->boundingBox())) 
				{
					blak->destroy(false,false);
				}
			}
		}
	}
}

void GameLayer::removeInactiveUnit(float dt)
{
        
    CCArray *children = this->getChildren();
    for (unsigned int i = 0; i < children->count(); ++i)
	{
        CCSprite *selChild =  dynamic_cast<CCSprite*>(children->objectAtIndex(i));
        if (selChild)
		{
            selChild->update(dt);
            int tag = selChild->getTag();
            if (( tag == 900) || (tag == 901 )|| (tag == 1000))
			{
                if (!((UnitSprite*)selChild)->isActive())
				{
                    ((UnitSprite*)selChild)->destroy(true,true);
                }
            }
        }
    }
    
    if (m_ship) {
        if (!m_ship->isActive())
		{
            m_ship->destroy(true , true);
            m_ship = NULL;
        }
    }
}

void GameLayer::checkIsReborn()
{    
    if (Config::sharedConfig()->getLifeCount() <= 0)
	{
		m_state = statePause;
		m_ship = NULL;
		pcMenu->setVisible(false);
		dieMenu->setVisible(true);
		CCCallFunc *ccDelayPause = CCCallFunc::create(this, callfunc_selector(GameLayer::delayPause));
		this->runAction(CCSequence::create(CCDelayTime::create(1.05f), ccDelayPause, NULL));

    }
    else if (Config::sharedConfig()->getLifeCount() > 0 )
	{
		if (!m_ship)
		{
			m_ship = Ship::create();
			this->addChild(m_ship, m_ship->getZorder(), 1001);
		}
    }
}

void GameLayer::gameBegin(CCObject* pSender)
{
	removeChildByTag(2);
	CCDirector::sharedDirector()->resume();

	// score
	m_lbScore = CCLabelBMFont::create("Score:0", s_arial14_fnt);
	m_lbScore->setAlignment(kCCTextAlignmentRight);
	addChild(m_lbScore, 4);
	m_lbScore->setScale(3);
	m_lbScore->setPosition(winSize.width/2, winSize.height-20);

	pcMenu->setVisible(true);
	Config::sharedConfig()->resetConfig();
	// ship
	m_ship = Ship::create();
	addChild(m_ship, m_ship->getZorder(), 1001);
	m_state = statePlaying;
}

void GameLayer::gameAbout( CCObject* pSender )
{
	CCScene *scene = About::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, scene));
}

void GameLayer::gameOptions( CCObject* pSender )
{
	bool tmpSound = Config::sharedConfig()->getAudioState();
	Config::sharedConfig()->updateAudioState(!tmpSound);

	if (Config::sharedConfig()->getAudioState())
	{
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

void GameLayer::gameContinue( CCObject* pSender )
{
	m_state = statePlaying;
	CCDirector::sharedDirector()->resume();

	pcMenu->setVisible(true);
	dieMenu->setVisible(false);
	Config::sharedConfig()->setLifeCount(1);
	m_ship = Ship::create();
	this->addChild(m_ship, m_ship->getZorder(), 1001);
}

void GameLayer::gameOver( CCObject* pSender )
{
	CCDirector::sharedDirector()->resume();
    CCScene * scene = GameOver::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, scene));
}

void GameLayer::gamePause(CCObject *pSender)
{
    CCDirector::sharedDirector()->pause();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    PauseLayer *pauseLayer = PauseLayer::create();
    addChild(pauseLayer,9999);
}

void GameLayer::gameChange( CCObject *pSender )
{
	isChange = false;
	change->setEnabled(false);
	CCCallFunc *ccResetColChange = CCCallFunc::create(this, callfunc_selector(GameLayer::resetColChange));
	this->runAction(CCSequence::create(CCDelayTime::create(2), ccResetColChange, NULL));

	CCCallFunc *ccResetBtnChange = CCCallFunc::create(this, callfunc_selector(GameLayer::resetBtnChange));
	this->runAction(CCSequence::create(CCDelayTime::create(4), ccResetBtnChange, NULL));

}

void GameLayer::delayPause()
{
	if (m_state == statePause)
	{
		CCDirector::sharedDirector()->pause();
	}
}

void GameLayer::resetColChange()
{
	isChange=true;
}

void GameLayer::resetBtnChange()
{
	change->setEnabled(true);
}

Ship* GameLayer::getShip()
{
    return m_ship;
}

void GameLayer::draw()
{
	//绘制一条线，参数为起始点和终点的坐标  
	//glEnable(GL_LINE_SMOOTH);
	glLineWidth(4);
	if (m_ship)
	{
		ccDrawLine(ccp(winSize.width/2,0),ccp(winSize.width/2,winSize.height));  

		if (m_ship->getPositionX()>winSize.width/2+m_ship->getContentSize().width/2)
		{
			ccDrawColor4B(255, 255, 255, 255);
		}
		if (m_ship->getPositionX()<winSize.width/2-m_ship->getContentSize().width/2)
		{
			ccDrawColor4B(0, 0, 0, 255);
		}
	}
}

bool GameLayer::collide(UnitSprite *a, UnitSprite *b)
{
	if(!a || !b)
	{
		return false;
	}
	CCRect aRect = a->collideRect();
	CCRect bRect = b->collideRect();
	if (aRect.intersectsRect(bRect)) 
	{
		return true;
	}
	return false;
}

void GameLayer::updateUI()
{
	if (m_tempScore < Config::sharedConfig()->getScoreValue()) {
		m_tempScore += 1;
	}
	char score[20];
	char s[27] = "Score:";
	sprintf(score, "%d", m_tempScore);
	m_lbScore->setString(strcat(s, score));
	//     char lifecount[2];
	//     sprintf(lifecount, "%d",Config::sharedConfig()->getLifeCount());
	//     m_lifeCount->setString(lifecount);

}

void GameLayer::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayer::onEnter();
}

void GameLayer::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}


bool GameLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	//    CCLog("touch began!");
	return true;
}

void GameLayer::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
	if ((m_state == statePlaying) && m_ship) 
	{
		CCPoint pos = touch->getDelta();
		CCPoint currentPos = m_ship->getPosition();
		currentPos = ccpAdd(currentPos, pos);
		currentPos = ccpClamp(currentPos, ccp(m_ship->getContentSize().width/2,m_ship->getContentSize().height/2), 
			ccp(winSize.width - m_ship->getContentSize().width/2, winSize.height-m_ship->getContentSize().height/2));
		m_ship->setPosition(currentPos);
	}
}

void GameLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
	//    CCLog("touch end!");
}
