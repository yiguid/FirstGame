#include "GameMainScene.h"
#include "GameMenuScene.h"
#include "GameHeroBullet.h"
#include "GameEnemyBullet.h"
#include "GameObjEnemy.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
GameMainScene::GameMainScene(void)
{
}


GameMainScene::~GameMainScene(void)
{
}

cocos2d::CCScene* GameMainScene::scene()
{
	CCScene *scene = CCScene::create();

	GameMainScene *layer = GameMainScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameMainScene::init()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();    
	//��������
	m_bg1 = CCSprite::create("back-1.png");
	m_bg1->setScale(1);
	m_bg2 = CCSprite::create("back-2.png");
	m_bg2->setScale(1);
	m_bg1->setAnchorPoint(ccp(0,0));//����ê��
	m_bg2->setAnchorPoint(ccp(0,0));
	m_bg1->setPosition( ccp(0,0) );
	m_bg2->setPosition( ccp(0,size.height) );
	this->addChild(m_bg1, 0);
	this->addChild(m_bg2, 0);
	//��������
	m_hero = new GameObjHero();
	m_hero->setPosition(ccp(size.width/2,-50));
	m_hero->setScale(0.7);
	this->addChild(m_hero,2,1);
	m_hero->runAction(CCMoveBy::create(0.5,ccp(0,150)));

	//��������
	m_enemys = CCArray::createWithCapacity(6);
	for(int i = 0;i < 6;i ++)
	{
		int type = CCRANDOM_0_1() * 4;
		GameObjEnemy* enemy = new GameObjEnemy();
		enemy->setPosition(ccp(size.width/4 * type,size.height + 50));
		float enemyScale = CCRANDOM_0_1() * 0.5 + 0.5;
		enemy->setScale(enemyScale);
		enemy->setType(type);
		m_enemys->addObject(enemy);
		this->addChild(enemy,1);
		enemy->moveStart();
	}
	m_enemys->retain();
	//����Ѫ��ui
	m_blood = 3;
	CCSpriteBatchNode* ui = CCSpriteBatchNode::create("viking.png");
	//CCNode *ui = CCNode::create();
	m_blood1 = CCSprite::createWithTexture(ui->getTexture());
	m_blood1->setPosition(ccp(20,size.height - 20));
	m_blood1->setScale(0.2f);
	ui->addChild(m_blood1);
	m_blood2 = CCSprite::createWithTexture(ui->getTexture());
	m_blood2->setPosition(ccp(50,size.height - 20));
	m_blood2->setScale(0.2f);
	ui->addChild(m_blood2);
	m_blood3 = CCSprite::createWithTexture(ui->getTexture());
	m_blood3->setPosition(ccp(80,size.height - 20));
	m_blood3->setScale(0.2f);
	ui->addChild(m_blood3);
	addChild(ui,4);

	//��ʼ�������ӵ�
 	m_heroBullets = CCArray::createWithCapacity(100);
 	for(size_t i = 0;i < m_heroBullets->capacity();i ++)
 	{
 		GameHeroBullet * mybullet = new GameHeroBullet();
 		mybullet->setIsNotVisable(this);//����û��object�������ᷢ������ʱ����Լ������ԭ��δ֪
 		mybullet->setScale(0.5);
 		m_heroBullets->addObject(mybullet);
 		this->addChild(mybullet,3);
 	}
 	m_heroBullets->retain();//������+1
 	//��ʼ�������ӵ�
 	m_enemyBullets = CCArray::createWithCapacity(10);
 	for(size_t i = 0;i < m_enemyBullets->capacity();i ++)
 	{
 		GameEnemyBullet * mybullet = new GameEnemyBullet();
 		mybullet->setIsNotVisable(this);//����û��object�������ᷢ������ʱ����Լ������ԭ��δ֪
 		mybullet->setScale(0.5);
 		m_enemyBullets->addObject(mybullet);
 		this->addChild(mybullet,3);
 	}
 	m_enemyBullets->retain();
	m_gameMark = new GameMark();
	this->addChild(m_gameMark,4);
	//preload effect music
	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("bullet.mp3").c_str());
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.2);
	SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("enemy_down.mp3").c_str());
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);

	//��ʼ����Ϸ�������弰��ť
	m_gameOver = CCSprite::create("gameover.png");
	m_gameOver->setAnchorPoint(ccp(0.5,0.5));
	m_gameOver->setPosition(ccp(0,0));
	m_gameOver->setPosition(ccp(size.width/2,size.height/2 + 70));
	m_gameOver->setVisible(false);
	m_gameOver->setScale(0.5);
	this->addChild(m_gameOver,5);
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("back.png","back.png",
		this,menu_selector(GameMainScene::menuBackCallback) );
	pCloseItem->setPosition( ccp(size.width/2,size.height/2 - 50) );
	pCloseItem->setScale(0.5);
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,5,25);
	pMenu->setVisible(false);
	pMenu->setEnabled(false);
	//��ͣ��ť
	CCMenuItemImage *pPauseItem = CCMenuItemImage::create("backB.png","backA.png",
		this,menu_selector(GameMainScene::onPause));
	pPauseItem->setPosition(ccp(size.width - 50,size.height - 50));
	pPauseItem->setScale(0.5);
	CCMenu *pPauseMenu = CCMenu::create(pPauseItem,NULL);
	pPauseMenu->setPosition(CCPointZero);
	this->addChild(pPauseMenu,6,26);

	CCMenuItemImage *pResumeItem = CCMenuItemImage::create("backB.png","backA.png",
		this,menu_selector(GameMainScene::onResume));
	pResumeItem->setPosition(ccp(size.width - 50,size.height - 50));
	pResumeItem->setScale(0.5);
	CCMenu *pResumeMenu = CCMenu::create(pResumeItem,NULL);
	pResumeMenu->setPosition(CCPointZero);
	this->addChild(pResumeMenu,6,27);
	pResumeMenu->setVisible(false);
	pResumeMenu->setEnabled(false);

	m_isReduce = false;
	m_isGameOver = false;
	m_isPause = false;
	scheduleUpdate();
	return true;
}

void GameMainScene::onPause( CCObject* pSender )
{
	m_isPause = true;
	CCDirector::sharedDirector()->pause();
	//��ֹ�ƶ�
	this->setTouchEnabled(false);
	//������ť
	CCMenu* pMenu = (CCMenu *)this->getChildByTag(26);
	pMenu->setVisible(false);
	pMenu->setEnabled(false);
	pMenu = (CCMenu *)this->getChildByTag(27);
	pMenu->setVisible(true);
	pMenu->setEnabled(true);
}

void GameMainScene::onResume(CCObject *pSender)
{
	m_isPause = false;
	CCDirector::sharedDirector()->resume();
	this->setTouchEnabled(true);
	//������ť
	CCMenu* pMenu = (CCMenu *)this->getChildByTag(27);
	pMenu->setVisible(false);
	pMenu->setEnabled(false);
	pMenu = (CCMenu *)this->getChildByTag(26);
	pMenu->setVisible(true);
	pMenu->setEnabled(true);
}

void GameMainScene::onEnter()
{
	CCLayer::onEnter();
}

void GameMainScene::onExit()
{
	CCLayer::onExit();
}

void GameMainScene::menuBackCallback( CCObject* pSender )
{
	CCDirector::sharedDirector()->replaceScene(GameMenuScene::scene());
}

void GameMainScene::releaseHeroBullet( int x,int y )
{
	//�����ӵ����飬����ʹ�õ��ӵ��ͷ�
	for(size_t i = 0;i < m_heroBullets->capacity();i ++)
	{
		if(!((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->getIsvisble())
		{
			//����λ�ã�������Ϊ��ʾ
			((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->setPosition(ccp(x,y));
			((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->setIsVisable();
			SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("bullet.mp3").c_str());
			break; 
		}
	}
}

void GameMainScene::update( float time )
{
	//�����ƶ��߼�
	m_bg1->setPosition(ccp(m_bg1->getPosition().x,m_bg1->getPosition().y - 1));
	m_bg2->setPosition(ccp(m_bg2->getPosition().x,m_bg2->getPosition().y - 1));
	if(m_bg2->getPosition().y < 0)
	{
		float temp = m_bg2->getPosition().y + 480;
		m_bg1->setPosition(ccp(m_bg2->getPosition().x,temp));
	}
	if(m_bg1->getPosition().y < 0)
	{
		float temp = m_bg1->getPosition().y + 480;
		m_bg2->setPosition(ccp(m_bg1->getPosition().x,temp));
	}

 	CCPoint hpos = m_hero->getPosition();
 	//���˺��ӵ���ײ���
 	for(size_t i = 0;i < m_enemys->capacity();i ++)
 	{
 		GameObjEnemy * enemy = ((GameObjEnemy *) m_enemys->objectAtIndex(i));
 		CCPoint epos = enemy->getPosition();
 		if(enemy->m_isLife)//�ӵ����е���
 		{
 			for(size_t i = 0;i < m_heroBullets->capacity();i ++)
 			{
 				if(((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->getIsvisble())
 				{
 					if(isHit(((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->getPosition(),epos,5,13,21,28))
 					{
						//play sound
						SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("enemy_down.mp3").c_str());
 						enemy->setDie();
 						m_gameMark->addNumber(200);
 						break;
 					}
 				}
 			}
 		}
		//���˺�Ӣ����ײ
		if(!m_isReduce && enemy->m_isLife && isHit(hpos,epos,21,22.5,21,28))
		{
			SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("enemy_down.mp3").c_str());
			enemy->setDie();
			setHeroHurt();
		}
	}
	//���Ǻ͵����ӵ���ײ
	if(!m_isReduce)
	{
		for(size_t i = 0;i < m_enemyBullets->capacity();i ++)
		{
			if(isHit(hpos,((GameEnemyBullet *)m_enemyBullets->objectAtIndex(i))->getPosition(),21,22.5,5,13))
			{
				SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("enemy_down.mp3").c_str());
				setHeroHurt();
			}
		}
	}
}

void GameMainScene::releaseEnemyBullet( int x,int y )
{
	for(unsigned int i = 0; i<m_enemyBullets->capacity(); i++)
	{
		if(!((GameEnemyBullet*)m_enemyBullets->objectAtIndex(i))->getIsvisble())
		{
			((GameEnemyBullet*)m_enemyBullets->objectAtIndex(i))->setPosition(ccp(x,y));
			((GameEnemyBullet*)m_enemyBullets->objectAtIndex(i))->setIsVisable();
			break; 
		}
	}
}

bool GameMainScene::isHit( CCPoint p1,CCPoint p2,int w1,int h1,int w2,int h2 )
{
	//�ж����������Ƿ���ײ
	if(abs(p1.x - p2.x) < w1 + w2 && abs(p1.y - p2.y) < h1 + h2)
	{
		return true;
	}
	return false;
}

void GameMainScene::setHeroHurt()
{
	//�������ˣ���Ѫ
	m_hero->stopAllActions();
	switch(m_blood)
	{
	case 3:
		m_blood1->setVisible(false);
		m_blood --;
		break;
	case 2:
		m_blood2->setVisible(false);
		m_blood --;
		break;
	case 1:
		m_blood3->setVisible(false);
		m_blood --;
		break;
	case 0:
		if(! m_isGameOver)
		{
			m_isGameOver = true;
			setGameOver();
		}
		break;
	}
 	CCActionInterval*  action = CCBlink::create(3, 6);//5������˸10��
 	m_hero->runAction(action);
	scheduleOnce(schedule_selector(GameMainScene::resetReduce), 5.0f);//5���ִ��һ��
	m_isReduce = true;//5�벻���˺�
}

void GameMainScene::resetReduce( float dt )
{
	m_isReduce = false;//�������ܵ��˺�
}
void GameMainScene::setGameOver()
{
	//������Ϸ����
	CCMenu* pMenu = (CCMenu *)this->getChildByTag(25);
	pMenu->setVisible(true);
	pMenu->setEnabled(true);
	m_gameOver->setVisible(true);
	m_gameOver->setScale(0);
	pMenu->setScale(0);
	pMenu->runAction(CCScaleTo::create(0.5,1));//0.5�����ŵ�������С
	m_gameOver->runAction(CCScaleTo::create(0.5,0.5));//0.5�����ŵ�������С��0.5��
	//�������
	//��������򵥴洢������
	CCUserDefault::sharedUserDefault()->setIntegerForKey("totalScore", m_gameMark->getScore());
	CCUserDefault::sharedUserDefault()->flush();//����һ��Ҫ�ύд��Ŷ�����򲻻��¼��xml�У��´�������Ϸ��ͻ�ȡ����value�ˡ�
	//������㶨��һ��stringΪ����֤���ǵĴ洢
	int totalScore= 0;
	//ȡ�����Ǹմ洢��himi��Ȼ��ֵ��str��֤�£�
	totalScore= CCUserDefault::sharedUserDefault()->getIntegerForKey("totalScore");
	CCLog("totalScore=��%d",totalScore);
}
