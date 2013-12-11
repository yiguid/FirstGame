#include "GameObjHero.h"
#include "GameMainScene.h"

GameObjHero::GameObjHero(void)
{
}


GameObjHero::~GameObjHero(void)
{
}

void GameObjHero::onEnter()
{
	CCNode::onEnter();
	this->setContentSize(CCSizeMake(100,100));
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite *mainsprite = CCSprite::create("viking.png");
	//���嶯��
	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("viking.png");
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	mainsprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	this->addChild(mainsprite);
	//β��
	//CCSprite *tail = CCSprite::create("catTail.png");
 	//tail->setAnchorPoint(ccp(0.5,1));
 	//tail->setPosition(ccp(-5,-29));
	//tail->setScale(0.5);
	//tail->setRotation(20);
	//tail->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCRotateBy::create(0.5,-40),CCRotateBy::create(0.5,40),NULL)));
	//this->addChild(tail);
	//��
	//m_leftHand = CCSprite::create("catHand1.png");
	//m_leftHand->setAnchorPoint(ccp(1,0.5));
	//m_leftHand->setPosition(ccp(-18,-20));
	//this->addChild(m_leftHand);
	//m_rightHand = CCSprite::create("catHand2.png");
	//m_rightHand->setPosition(ccp(18,-20));
	//m_rightHand->setAnchorPoint(ccp(0,0.5));
	//this->addChild(m_rightHand);
	m_offset = ccp(0,0);
	m_isControl = false;
	schedule(schedule_selector(GameObjHero::releasebullet), 0.2f);
}

void GameObjHero::onExit()
{
	CCNode::onExit();
}

CCRect GameObjHero::rect()
{
	CCSize s = CCSizeMake(100,100);
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	//�����½ǵ����Ͻǵľ�������
}

bool GameObjHero::containsTouchLocation(CCTouch* touch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool GameObjHero::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
 	if(((GameMainScene *)this->getParent())->m_isGameOver)//��Ϸ���������ڽ��ܴ����¼�
	{
 		return false;
	}
	if(((GameMainScene *)this->getParent())->m_isPause)//��Ϸ��ͣ�����ڽ��ܴ����¼�
	{
		return false;
	}
	if(! containsTouchLocation(touch))//���������û����Ӣ��ͼƬ�ľ�����
	{
		return false; 
	}
	else//��ô���ƫ��λ��
	{
		m_isControl = true;
		CCPoint touchPoint = touch->getLocationInView();
		touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
		m_offset.x = touchPoint.x - this->getPosition().x;
		m_offset.y = touchPoint.y - this->getPosition().y;
	}
	return true;   
}

void GameObjHero::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	if(m_isControl)
	{
		CCPoint touchPoint = touch->getLocationInView();
		touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
		//��������������
		float x = touchPoint.x - m_offset.x; 
		float y = touchPoint.y - m_offset.y;
		//if(x < this->getPosition().x)
		//{
		//	m_leftHand->setFlipY(true);//��������
		//	m_rightHand->setFlipY(false);
		//}
		//else
		//{
		//	m_leftHand->setFlipY(false);
		//	m_rightHand->setFlipY(true); 
		//}
		this->setPosition(x,y);
	}
}

void GameObjHero::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	if(m_isControl)
	{
		m_isControl = false;
		//m_leftHand->setFlipY(false);
		//m_rightHand->setFlipY(false); 
	}
}

void GameObjHero::releasebullet( float dt )
{
	if(m_isControl)//�ͷ��ӵ�
	{
		CCPoint pos = this->getPosition(); 
		GameMainScene *p = (GameMainScene*) this->getParent();
		p->releaseHeroBullet(pos.x,pos.y + 30);
	}
}