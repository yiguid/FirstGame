#include "GameHeroBullet.h"

GameHeroBullet::GameHeroBullet(void)
{
	m_isVisable = false;
}

GameHeroBullet::~GameHeroBullet(void)
{
}
void GameHeroBullet::setIsVisable()
{
	this->setVisible(true);
	m_isVisable = true;
	this->runAction(CCSequence::create(CCMoveTo::create((-this->getPosition().y + 550)/150,ccp(this->getPosition().x,550)),CCCallFuncN::create(this, callfuncN_selector(GameHeroBullet::setIsNotVisable)),NULL));;
}
void GameHeroBullet::setIsNotVisable(CCNode* pSender)
{
	this->setVisible(false);
	m_isVisable = false;
	this->stopAllActions();
}
bool GameHeroBullet::getIsvisble(){
	return m_isVisable;
}
void GameHeroBullet::onEnter()
{
	CCNode::onEnter();

	this->setContentSize(CCSizeMake(21,52));
	CCSprite *mainbody = CCSprite::create("YuGuZD.png");
	this->addChild(mainbody);
}
void GameHeroBullet::onExit()
{
	CCNode::onExit();
}