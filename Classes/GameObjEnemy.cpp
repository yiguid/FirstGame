#include "GameObjEnemy.h"
#include "GameMainScene.h"
#define ENEMY_IMG "enemy.png"

GameObjEnemy::GameObjEnemy(void)
{
	m_shootInterval = CCRANDOM_0_1() * 2 + 2;
}


GameObjEnemy::~GameObjEnemy(void)
{
}

void GameObjEnemy::onEnter()
{
	CCNode::onEnter();

	this->setContentSize(CCSizeMake(100,100));
	m_mainBody = CCSprite::create(ENEMY_IMG);
	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName(ENEMY_IMG);
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	m_mainBody->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	this->addChild(m_mainBody);
	m_boom = CCSprite::create("boom1.png");
	this->addChild(m_boom);
	m_boom->setVisible(false);
	m_isLife = true;
}

void GameObjEnemy::onExit()
{
	CCNode::onExit();
}

void GameObjEnemy::moveStart()
{
	m_isLife = true;
	int type = CCRANDOM_0_1() * 4;
	ccBezierConfig bezier2;
	int bezierRandom = CCRANDOM_0_1() * 150 + 300;
	bezier2.controlPoint_1 = CCPointMake(this->getPosition().x - bezierRandom,330);
	bezier2.controlPoint_2 = CCPointMake(this->getPosition().x + bezierRandom,280);
	bezier2.endPosition = CCPointMake(this->getPosition().x,-70);
	CCBezierTo * bezierBy2 = CCBezierTo::create(6, bezier2);
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = CCPointMake(this->getPosition().x + bezierRandom,330);
	bezier1.controlPoint_2 = CCPointMake(this->getPosition().x - bezierRandom,280);
	bezier1.endPosition = CCPointMake(this->getPosition().x,-70);
	CCBezierTo * bezierBy1 = CCBezierTo::create(6, bezier1);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int duration = CCRANDOM_0_1() * 3 + 5;
	switch(type)
	{
	case 0:
	case 1:
		this->runAction(CCSequence::create(CCMoveBy::create(duration,ccp(0,-size.height)),CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::reStart)),NULL));
		break;
	case 2:
		this->runAction(CCSequence::create(bezierBy2,CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::reStart)),NULL));
		break;
	case 3:
		this->runAction(CCSequence::create(bezierBy1,CCCallFuncN::create(this, callfuncN_selector(GameObjEnemy::reStart)),NULL));
		break;
	}
	schedule(schedule_selector(GameObjEnemy::releaseBullet), m_shootInterval);
}

void GameObjEnemy::reStart( CCNode* pSender )
{
	m_mainBody->setVisible(true);
	m_boom->setVisible(false);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->setPosition(ccp(size.width/4 * (m_type + 1) + 50,size.height + 50));
	m_isLife = true;
	if(m_shootInterval - 0.02 > 0)
		m_shootInterval -= 0.02;
	this->moveStart();
}

void GameObjEnemy::setDie()
{
	m_isLife = false;
	m_mainBody->setVisible(false);
	m_boom->setVisible(true);
	this->stopAllActions();
	//±¬Õ¨¶¯»­
	CCAnimation* boomAnimation = CCAnimation::create();
	boomAnimation->addSpriteFrameWithFileName("boom1.png");
	boomAnimation->addSpriteFrameWithFileName("boom2.png");
	boomAnimation->addSpriteFrameWithFileName("boom3.png");
	boomAnimation->addSpriteFrameWithFileName("boom4.png");
	boomAnimation->addSpriteFrameWithFileName("boom5.png");
	boomAnimation->setDelayPerUnit(0.1f);
	boomAnimation->setRestoreOriginalFrame(true);
	m_boom->runAction(CCSequence::create(CCAnimate::create(boomAnimation),CCCallFuncN::create(this, 
	  callfuncN_selector(GameObjEnemy::reStart)),NULL));
}

void GameObjEnemy::setType( int type )
{
	m_type = type;
}

void GameObjEnemy::releaseBullet( float dt )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = this->getPosition();
	if(pos.y > 20 && pos.y < size.height && m_isLife)
	{
		GameMainScene *p = (GameMainScene *) this->getParent();
		p->releaseEnemyBullet(pos.x,pos.y - 30);
	}
}