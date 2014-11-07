
#include "Effect.h"
#include "Resource.h"
#include <string>
USING_NS_CC;
using namespace std;

Effect::Effect()
{
}

Effect::~Effect()
{
}

Effect* Effect::create()
{
    Effect* effect = new Effect();
    if (effect) {
        effect->autorelease();
        return effect;
    }else{
        delete effect;
        effect = NULL;
        return NULL;
    }
}

void Effect::flareEffect(CCNode *parent, CCCallFunc *callback)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    // ��ЧͼƬ
    CCSprite *flare = CCSprite::create(s_flare);
    
    // ���û��ģʽ
    ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
    flare->setBlendFunc(cbl);
    
    // ��ӵ����ڵ�
    parent->addChild(flare, 3);
    
    // ���ó�ʼ͸����
    flare->setOpacity(0);
    
    // ���ó�ʼλ��
    flare->setPosition(ccp(-30, winSize.height - 130));
    
    // ���ó�ʼ�Ƕ�
    flare->setRotation(-120);
    
    // ���ó�ʼ�Ŵ�ϵ��
    flare->setScale(0.2f);
    
    // ͸���Ƚ���
    CCActionInterval *opacityAnim = CCFadeTo::create(0.5, 255);
    CCActionInterval *opacDim = CCFadeTo::create(1, 0);
    
    // ��С����
    CCActionInterval *bigAnim = CCScaleBy::create(0.7f, 1.2f, 1.2f);
    
    // �����ٶ�
    CCEaseSineOut *biggerEase = CCEaseSineOut::create(bigAnim);
    CCActionInterval *moveAnim = CCMoveBy::create(0.5, ccp(328, 0));
    CCEaseSineOut *moveEase = CCEaseSineOut::create(moveAnim);
    
    // �Ƕ���ת
    CCActionInterval *roteAnim = CCRotateBy::create(2.5, 90);
    
    // �Ƕ���ת�ٶȣ�ָ���仯
    CCEaseExponentialOut * rotateEase = CCEaseExponentialOut::create(roteAnim);
    
    // �Ŵ�ԭ��С
	//
    CCScaleTo *bigger = CCScaleTo::create(0.5, 1);
    
    // ������ɺ�ص�����,�ɵ�����
    CCCallFuncN *removeFunc =  CCCallFuncN::create(flare, callfuncN_selector(Effect::killSprite));
    
    // ִ�ж����ͻص�����
    flare->runAction(CCSequence::create(opacityAnim, biggerEase, opacDim, removeFunc, callback,  NULL));
    flare->runAction(moveEase);
    flare->runAction(rotateEase);
    flare->runAction(bigger);

}

void Effect::explode(CCNode *parent, CCPoint pos)
{
    // ��һ֡
    //CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("explosion_01.png");
	CCSpriteFrame *pFrame = CCSpriteFrame::create("explosion_01.png",CCRectMake(0, 0, 128, 128));
    CCSprite *explosion = CCSprite::createWithSpriteFrame(pFrame);
    parent->addChild(explosion);
    explosion->setPosition(pos);
    
    CCSize cs = explosion->getContentSize();
    
    // ���֮��Ļص�
    CCCallFuncN *removeFunc =  CCCallFuncN::create(explosion, callfuncN_selector(Effect::killSprite));
    
    // ��ը����
    CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("Explosion");
    explosion->runAction(CCSequence::create(CCAnimate::create(animation), removeFunc, NULL));
    
}

// ���⶯��
void Effect::spark(CCPoint pos, CCNode *parent, float scale, float duration)
{
    // spark ����
    CCSprite *one = CCSprite::create(s_explode1);
    CCSprite *two = CCSprite::create(s_explode2);
    CCSprite *three = CCSprite::create(s_explode3);
    
    // ���ģʽ
    ccBlendFunc cb = { GL_SRC_ALPHA, GL_ONE };
    one->setBlendFunc(cb);
    two->setBlendFunc(cb);
    three->setBlendFunc(cb);
    
    one->setPosition(pos);
    two->setPosition(pos);
    three->setPosition(pos);
    
    //���Ϊʲô���ӣ�����ȥ�о�̫���˰�
//    parent->addChild(one);
    parent->addChild(two);
    parent->addChild(three);
    
    one->setScale(scale);
    two->setScale(scale);
    three->setScale(scale);
    
    three->setRotation(CCRANDOM_0_1() * 360);
    
    CCRotateBy *left = CCRotateBy::create(duration, -45);
    CCRotateBy *right = CCRotateBy::create(duration, 45);
    CCScaleBy *scaleBy = CCScaleBy::create(duration, 3);
    CCFadeOut *fadeOut = CCFadeOut::create(duration);
    

    //JSд����ط�����ˬ������ȴҪд3���ص���3������
    CCCallFuncN *removeOne =  CCCallFuncN::create(this, callfuncN_selector(Effect::killSprite));
    CCCallFuncN *removeTwo =  CCCallFuncN::create(this, callfuncN_selector(Effect::killSprite));
    CCCallFuncN *removeThree =  CCCallFuncN::create(this, callfuncN_selector(Effect::killSprite));
    CCAction *seqOne = CCSequence::create(fadeOut, removeOne, NULL);
    CCAction *seqTwo = CCSequence::create((CCFadeOut*)fadeOut->copy(), removeTwo, NULL);
    CCAction *seqThree = CCSequence::create((CCFadeOut*)fadeOut->copy(), removeThree, NULL);
    
    one->runAction(left);
    two->runAction(right);
    
    one->runAction(scaleBy);
    two->runAction((CCScaleBy*)scaleBy->copy());
    three->runAction((CCScaleBy*)scaleBy->copy());
    
    one->runAction(seqOne);
    two->runAction(seqTwo);
    three->runAction(seqThree);
    
    
}

//�������뻺��
void Effect::sharedExplosion()
{
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_explosion_plist);
    CCArray *animFrames = CCArray::create();
    
    char str[64] = {0};
    
    // ���sprintf���ĺ�ǿ��
    for (int i = 1; i < 35; ++i) {
        sprintf(str, "explosion_%02d.png", i);
        CCLOG("%s",str);
        //CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		CCSpriteFrame *frame = CCSpriteFrame::create(str,CCRectMake(0, 0, 128, 128));
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.03f);
    
    // ֡��������
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "Explosion");
    
}

void Effect::killSprite(CCNode *pSender)
{
//    CCLOG("remove effect");
    pSender->removeFromParent();
}

void Effect::changeColor( UnitSprite *temp )
{
	if (temp)
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		if (temp->getPositionX()>=winSize.width/2)
		{
			temp->setColor(ccc3(0, 0, 0));
		}
		else if (temp->getPositionX()<winSize.width/2)
		{
			temp->setColor(ccc3(255, 255, 255));
		}

	}

}

void Effect::changeColorb( UnitSprite *temp )
{
	if (temp)
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		if (temp->getPositionX()>=winSize.width/2)
		{
			temp->setColor(ccc3(255, 255, 255));
		}
		else if (temp->getPositionX()<winSize.width/2)
		{
			temp->setColor(ccc3(0, 0, 0));
		}
	}
}



