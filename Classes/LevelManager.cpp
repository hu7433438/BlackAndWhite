
#include "LevelManager.h"
#include "Balk.h"
#include "Effect.h"
#include "Enemy.h"
#include "GameLayer.h"

using namespace cocos2d;

LevelManager::LevelManager(CCLayer *gameLayer)
{
    CCAssert(gameLayer != NULL, "game layer must be non-null");
    m_gameLayer = gameLayer;
    m_enemies = Config::sharedConfig()->getEnemise();
    m_enemyType = Config::sharedConfig()->getEnemyType();
}
LevelManager::~LevelManager()
{
    
}


void LevelManager::loadLevelBalkResource( int dt )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	Balk *balk1 = Balk::create(-200, "balk.png", 1);
	Balk *balk2 = Balk::create(-200, "balk.png", 1);

	float shipW = ((GameLayer*)m_gameLayer)->getShip()->getContentSize().width/2;

	CCPoint enemyPos1 = ccp(winSize.width/4 - shipW - (winSize.width/4)* CCRANDOM_0_1() , winSize.height + balk1->getContentSize().height);
	CCPoint enemyPos2 = ccp(winSize.width/4*3 + shipW + (winSize.width/4) * CCRANDOM_0_1(), winSize.height + balk2->getContentSize().height);
	
	balk_items->addObject(balk1);
	balk_items->addObject(balk2);
	
	m_gameLayer->addChild(balk1, balk1->getZorder(), 900);
	m_gameLayer->addChild(balk2, balk1->getZorder(), 900);
	
	balk1->setPosition(enemyPos1);
	balk2->setPosition(enemyPos2);
	
	if (CCRANDOM_0_1()>0.5)
	{
		Effect::changeColorb(balk1);
		Effect::changeColorb(balk2);
	}
	else
	{
		Effect::changeColor(balk1);
		Effect::changeColor(balk2);
	}

}

void LevelManager::loadLevelResource(int dt)
{
	int score =  Config::sharedConfig()->getScoreValue();
    for (vector<EnemyInfo>::iterator iter = m_enemies.begin(); iter != m_enemies.end(); ++iter) 
	{
        if (iter->showType == 0) 
		{
            if (dt % iter->showTime == 0) 
			{
				// 数组长度
				for (int i = 0; i != 1; ++i) 
				{
					addEnemyToGameLayer(iter->types[i]);
				}
			}
        }
		if (score>=30)
		{
			if (iter->showType == 1) 
			{
				if (dt % iter->showTime == 0) 
				{
					// 数组长度
					for (int i = 0; i != 1; ++i) 
					{
						addEnemyToGameLayer(iter->types[i]);
					}
				}
			}
		}
		if (score>=90)
		{
			if (iter->showType == 2) 
			{
				if (dt % iter->showTime == 0) 
				{
					// 数组长度
					for (int i = 0; i != 1; ++i) 
					{
						addEnemyToGameLayer(iter->types[i]);
					}
					
				}
			}
		}
		if (score>=180)
		{
			if (iter->showType == 3) 
			{
				if (dt % iter->showTime == 0) 
				{
					// 数组长度
					for (int i = 0; i != 1; ++i) 
					{
						addEnemyToGameLayer(iter->types[i]);
					}

				}
			}
		}
		if (score>=270)
		{
			if (iter->showType == 4) 
			{
				if (dt % iter->showTime == 0) 
				{
					// 数组长度
					for (int i = 0; i != 1; ++i) 
					{
						addEnemyToGameLayer(iter->types[i]);
					}
				}
			}
		}
		if (score>=360)
		{
			if (iter->showType == 5) 
			{
				if (dt % iter->showTime == 0) 
				{
					// 数组长度
					for (int i = 0; i != 1; ++i) 
					{
						addEnemyToGameLayer(iter->types[i]);
					}
				}
			}
		}
		//boss
		if (dt==120)
		{
			if (iter->showType == 6) 
			{
				// 数组长度
				for (int i = 0; i != 1; ++i) 
				{
					addEnemyToGameLayer(iter->types[i]);
				}
			}
		}
		if (dt==120)
		{
			if (iter->showType == 7) 
			{
				// 数组长度
				for (int i = 0; i != 1; ++i) 
				{
					addEnemyToGameLayer(iter->types[i]);
				}
			}
		}
		if (dt==120)
		{
			if (iter->showType == 8) 
			{
				// 数组长度
				for (int i = 0; i != 1; ++i) 
				{
					addEnemyToGameLayer(iter->types[i]);
				}
			}
		}
		if (dt==120)
		{
			if (iter->showType == 9) 
			{
				// 数组长度
				for (int i = 0; i != 1; ++i) 
				{
					addEnemyToGameLayer(iter->types[i]);
				}
			}
		}
    }
}

void LevelManager::addEnemyToGameLayer(int type)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    EnemyType enemyType = m_enemyType[type];
    Enemy * enemy = Enemy::create(enemyType);
    
	CCSize eSize = enemy->getContentSize();
    CCPoint enemyPos = ccp(eSize.width/2 + (winSize.width - eSize.width) * CCRANDOM_0_1(), winSize.height + eSize.height/2);
    
    
    CCPoint offset; //= ((GameLayer*)m_gameLayer)->getShip()->getPosition();
    CCAction *tempAction; //= CCMoveTo::create(1, offset);
    CCMoveBy *a0;
    CCMoveBy *a1;
    CCCallFuncN *onComplete;
	float newX;
    
    switch (enemy->getMoveType()) 
	{
        case 0:
			//一直往前走，不要停
			enemy->setPosition(enemyPos);
			offset = ccp(0, -winSize.height*2);
			tempAction = CCMoveBy::create(5, offset);
			break;

		case 1:
			//快速一直往前走，不要停
			enemy->setPosition(enemyPos);
			offset = ccp(0, -winSize.height*2);
			tempAction = CCMoveBy::create(3, offset);
			break;

		case 2:
			//横向移动
			newX = CCRANDOM_0_1()>0.5 ? winSize.width + eSize.width/2 : - eSize.width/2;
			enemy->setPosition(ccp(newX , winSize.height/3 + winSize.height/2*CCRANDOM_0_1()));
			offset = ccp( newX > 0 ? - winSize.width - eSize.width : winSize.width + eSize.width , 0);
			tempAction = CCMoveBy::create(4, offset);
			break;
            
		case 3:
			//斜下
			newX = CCRANDOM_0_1()>0.5 ? winSize.width + eSize.width: - eSize.width/2;
			enemy->setPosition(ccp(newX , winSize.height));
			offset = ccp(newX > 0 ? - winSize.width*3/2 :winSize.width*3/2 , -winSize.height*3/2);
			tempAction = CCMoveBy::create(5, offset);
			break;

        case 4:
			//闪电移动
			newX = CCRANDOM_0_1()>0.5 ? winSize.width : 0;
			enemy->setPosition(ccp( newX, winSize.height + eSize.height/2));
			newX = newX > 1 ? - winSize.width*2/3 : winSize.width*2/3;
			a0 = CCMoveBy::create(3, ccp(newX, -winSize.height/2));
			a1 = CCMoveBy::create(2, ccp(-newX*2/3 , -400));
			tempAction = CCSequence::create(a0, a1,CCMoveBy::create(1 , ccp(0 , -winSize.height - eSize.height/2)) , NULL);  
			break;

        case 5:
			//后方出现
			newX = ((GameLayer*)m_gameLayer)->getShip()->getPosition().x;
			enemy->setPosition(ccp(newX , -eSize.height/2));
			a0 = CCMoveBy::create(3 , ccp(0 , winSize.height/3 + winSize.height/2 * CCRANDOM_0_1()));
			a1 = CCMoveBy::create(2 , ccp(0 , 0));
			tempAction = CCSequence::create(a0, a1, CCMoveBy::create(1 , ccp(0 , -winSize.height-eSize.height/2)), NULL);
			break;

		case 6:
			//前进，然后重复横向移动
			enemy->setPosition(ccp(winSize.width/2 , winSize.height + eSize.height/2));
			offset = ccp(0,-winSize.height/3);
			a0 = CCMoveBy::create(3, offset);
			a1 = CCMoveBy::create(1, ccp(-50 - 100 * CCRANDOM_0_1(), 0));

			onComplete =  CCCallFuncN::create(enemy, callfuncN_selector(LevelManager::repeatAction));
			tempAction = CCSequence::create(a0, a1, onComplete, NULL);
			break;
		case 7:
			//前进，然后重复横向移动
			enemy->setPosition(enemyPos);
			offset = ccp(0, -100 - 200 * CCRANDOM_0_1());
			a0 = CCMoveBy::create(0.5, offset);
			a1 = CCMoveBy::create(1, ccp(-50 - 100 * CCRANDOM_0_1(), 0));

			onComplete =  CCCallFuncN::create(enemy, callfuncN_selector(LevelManager::repeatAction));
			tempAction = CCSequence::create(a0, a1, onComplete, NULL);
			break;
		case 8:
			//前进，然后重复横向移动
			enemy->setPosition(enemyPos);
			offset = ccp(0, -100 - 200 * CCRANDOM_0_1());
			a0 = CCMoveBy::create(0.5, offset);
			a1 = CCMoveBy::create(1, ccp(-50 - 100 * CCRANDOM_0_1(), 0));

			onComplete =  CCCallFuncN::create(enemy, callfuncN_selector(LevelManager::repeatAction));
			tempAction = CCSequence::create(a0, a1, onComplete, NULL);
			break;
		case 9:
			//前进，然后重复横向移动
			enemy->setPosition(enemyPos);
			offset = ccp(0, -100 - 200 * CCRANDOM_0_1());
			a0 = CCMoveBy::create(0.5, offset);
			a1 = CCMoveBy::create(1, ccp(-50 - 100 * CCRANDOM_0_1(), 0));

			onComplete =  CCCallFuncN::create(enemy, callfuncN_selector(LevelManager::repeatAction));
			tempAction = CCSequence::create(a0, a1, onComplete, NULL);
			break;

    }
    
    Effect::changeColorb(enemy);
    m_gameLayer->addChild(enemy,enemy->getZorder(), 1000);
    enemy_items->addObject(enemy);
    enemy->runAction(tempAction);
}

void LevelManager::repeatAction(CCNode *pSender)
{
    CCDelayTime *delay =  CCDelayTime::create(1);
    CCMoveBy *mv = CCMoveBy::create(1, ccp(100 + 100 * CCRANDOM_0_1(), 0));
    CCFiniteTimeAction *seq = CCSequence::create(delay, mv, delay->copy(), mv->reverse(), NULL);
    pSender->runAction(CCRepeatForever::create((CCActionInterval*)seq));
}

