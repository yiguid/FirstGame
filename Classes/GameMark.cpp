#include "GameMark.h"


GameMark::GameMark(void)
{
}


GameMark::~GameMark(void)
{
}

void GameMark::onEnter()
{
	CCNode::onEnter();
	CCSize size = CCDirector::sharedDirector()->getWinSize(); 
	this->setContentSize(size);
	m_bits = CCArray::createWithCapacity(5);
	//��������
	CCSprite *title = CCSprite::create("score.png");
	title->setPosition(ccp(size.width/2 + 40,size.height - 15));
	title->setScale(0.5);
	this->addChild(title);
	//���ְ�λ����
	for(int i = 0;i < 5;i ++)
	{
		CCSprite * shu = CCSprite::create("shu.png");
		m_ui = shu->getTexture();
		shu->setScale(0.5);
		shu->setTextureRect(CCRectMake(234,0,26,31));
		shu->setPosition(ccp(size.width - 15 - i * 15,size.height - 15));
		m_bits->addObject(shu);
		addChild(shu);
	}
	m_bits->retain();
	m_score = 0;
}

void GameMark::onExit()
{
	CCNode::onExit();
}

void GameMark::addNumber( int var )
{
	//��������λ��������
	m_score += var;
	int temp = m_score % 10;//��λ�ϵ�����
	if(temp > 0)//������Ӧ����1-9
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(0))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31)); 
	}
	else//0
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(0))->setTextureRect(CCRectMake(234,0,26,31)); 
	}
	temp = (m_score % 100) / 10;//ʮλ�ϵ�����
	if(temp > 0)
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(1))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31));  

	}
	else
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(1))->setTextureRect(CCRectMake(234,0,26,31)); 
	}
	temp = (m_score % 1000) / 100;//��λ�ϵ�����
	if(temp > 0)
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(2))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31)); 
	}
	else
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(2))->setTextureRect(CCRectMake(234,0,26,31));
	}
	temp = (m_score % 10000) / 1000;//ǧλ�ϵ�����
	if(temp > 0)
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(3))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31)); 

	}
	else
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(3))->setTextureRect(CCRectMake(234,0,26,31)); 
	}
	temp = m_score / 10000;//��λ�ϵ�����
	if(temp > 0)
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(4))->setTextureRect(CCRectMake((temp - 1) * 26,0,26,31));  

	}
	else
	{
		((CCSprite *)m_bits->objectAtIndex(0))->setTexture(m_ui);
		((CCSprite *)m_bits->objectAtIndex(4))->setTextureRect(CCRectMake(234,0,26,31));
	}
}