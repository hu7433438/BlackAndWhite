
#include "About.h"
#include "Resource.h"
#include "GameLayer.h"

CCScene* About::scene()
{
    CCScene *scene = CCScene::create();
    About *about = About::create();
    scene->addChild(about);
    return scene;
}

bool About::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *sp = CCSprite::create(s_bg01);
    sp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    addChild(sp, 0, 1);
    
    CCTexture2D *imageCache = CCTextureCache::sharedTextureCache()->addImage(s_menuTitle);
    CCSprite *title = CCSprite::createWithTexture(imageCache, CCRectMake(0, 36, 100, 34));
    title->setPosition(ccp(winSize.width/2, winSize.height - 60));
    addChild(title);
    
    CCLabelTTF *about = CCLabelTTF::create("   Thanks to cocos2d!", "Arial Bold", 32, CCSizeMake(winSize.width * 0.85, 320), kCCTextAlignmentLeft);
    about->setPosition(ccp(winSize.width / 2, winSize.height / 2 ));
    addChild(about);
    
    
    CCLabelBMFont *backLb = CCLabelBMFont::create("Go Back", s_font);
    CCMenuItemLabel *goBack = CCMenuItemLabel::create(backLb, this, menu_selector(About::goBack));
    goBack->setScale(0.6f);
    CCActionInterval *fadeIn = CCFadeTo::create(1, 80);
    CCActionInterval *fadeOut = CCFadeTo::create(1, 255);
    CCEaseSineInOut *ease1 = CCEaseSineInOut::create(fadeIn);
    CCEaseSineInOut *ease2 = CCEaseSineInOut::create(fadeOut);
    CCFiniteTimeAction *seq = CCSequence::create(ease1, ease2, NULL);
    // 参数必须要强转，不然ndk编译不过
    goBack->runAction(CCRepeatForever::create((CCActionInterval*)seq));
    
    CCMenu *menu = CCMenu::create(goBack, NULL);
    menu->setPosition(winSize.width / 2, winSize.height/2 - 60);
    addChild(menu);
    
    return  true;
}

void About::goBack(CCObject *cco)
{
	CCScene *pScene = CCScene::create();
	pScene->addChild(GameLayer::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f, pScene));
}

