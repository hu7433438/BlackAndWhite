
#include "GameOver.h"
#include "Resource.h"
#include "Config.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

CCScene* GameOver::scene()
{
    CCScene *scene = CCScene::create();
    GameOver *gameOver = GameOver::create();
    scene->addChild(gameOver);
    return  scene;
    
}

bool GameOver::init()
{
    if (!CCLayer::init())
	{
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *sp = CCSprite::create(s_bg01);
    sp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    addChild(sp, 0, 1);
    
    CCSprite *logo = CCSprite::create(s_gameOver);
    //logo->setAnchorPoint(ccp(0, 0));
    logo->setPosition(ccp(winSize.width / 2, winSize.height - 60));
    addChild(logo, 10, 1);
    
    CCSprite *playAgainNormal = CCSprite::create(s_menu, CCRectMake(378, 0, 126, 33));
    CCSprite *playAgainSelected = CCSprite::create(s_menu, CCRectMake(378, 33, 126, 33));
    CCSprite *playAgainDisabled = CCSprite::create(s_menu, CCRectMake(378, 33*2, 126, 33));
    
    
    CCMenuItemSprite *playAgain = CCMenuItemSprite::create(playAgainNormal, playAgainSelected, playAgainDisabled, this,
                                                           menu_selector(GameOver::playAgain));
    

    CCMenu *menu = CCMenu::create(playAgain , NULL);
    addChild(menu, 1, 1);
	menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(winSize.width / 2, winSize.height/2 - 60);
    
    int tempScore = Config::sharedConfig()->getScoreValue();
    char score[20];
    char s[32] = "Your score:";
    sprintf(score, "%d", tempScore);
    CCLabelTTF *lb = CCLabelTTF::create(strcat(s, score), "Arial Bold", 64);
    lb->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    //lb->setColor(ccc3(250, 179, 0));
    addChild(lb, 10);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_mainMainMusic, true);
    
    return true;
    
}

void GameOver::playAgain(CCObject *cco)
{
    CCScene *scene = CCScene::create();
    scene->addChild(GameLayer::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, scene));
}

void GameOver::goBack( CCObject *cco )
{
	CCScene *scene = CCScene::create();
	scene->addChild(GameLayer::create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, scene));
}
