#include "GameEnemyBullet.h"


GameEnemyBullet::GameEnemyBullet(void)
{
}


GameEnemyBullet::~GameEnemyBullet(void)
{
}

void GameEnemyBullet::onEnter()
{
	CCNode::onEnter();
	this->setContentSize(CCSizeMake(21,62));
	CCSprite *mainbody = CCSprite::create("DrDogZD.png");
	mainbody->runAction(CCRepeatForever::create(CCRotateBy::create(1,360)));
	addChild(mainbody);
}

bool GameEnemyBullet::getIsvisble()
{
	return m_isVisable;
}

void GameEnemyBullet::onExit()
{
	CCNode::onExit();
}

void GameEnemyBullet::setIsVisable()
{
	this->setVisible(true);
	m_isVisable = true;
	this->runAction(CCRepeatForever::create(CCRotateBy::create(1,360)));
	this->runAction(CCSequence::create(CCMoveTo::create((this->getPosition().y + 50)/150,ccp(this->getPosition().x,-50)),CCCallFuncN::create(this, callfuncN_selector(GameEnemyBullet::setIsNotVisable)),NULL));;
}

void GameEnemyBullet::setIsNotVisable(CCNode* pSender)
{
	this->setVisible(false);
	m_isVisable = false;
	this->stopAllActions();
}