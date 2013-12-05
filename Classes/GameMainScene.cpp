#include "GameMainScene.h"
#include "GameMenuScene.h"
#include "GameHeroBullet.h"
#include "GameEnemyBullet.h"
#include "GameObjEnemy.h"

USING_NS_CC;
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
	//创建背景
	m_bg1 = CCSprite::create("bg.png");
	m_bg1->setScale(0.5);
	m_bg2 = CCSprite::create("bg.png");
	m_bg2->setScale(0.5);
	m_bg1->setAnchorPoint(ccp(0,0));//设置锚点
	m_bg2->setAnchorPoint(ccp(0,0));
	m_bg1->setPosition( ccp(0,0) );
	m_bg2->setPosition( ccp(0,size.height) );
	this->addChild(m_bg1, 0);
	this->addChild(m_bg2, 0);
	//创建主角
	m_hero = new GameObjHero();
	m_hero->setPosition(ccp(size.width/2,-50));
	m_hero->setScale(0.5);
	this->addChild(m_hero,2,1);
	m_hero->runAction(CCMoveBy::create(0.5,ccp(0,150)));

	//创建敌人
	m_enemys = CCArray::createWithCapacity(3);
	for(int i = 0;i < 3;i ++)
	{
		int type = i + 1;
		GameObjEnemy* enemy = new GameObjEnemy();
		enemy->setPosition(ccp(size.width/4 * type,size.height + 50));
		enemy->setScale(0.5);
		enemy->setType(type);
		m_enemys->addObject(enemy);
		this->addChild(enemy,1);
		enemy->moveStart();
	}
	m_enemys->retain();
	//创建血量ui
	m_blood = 3;
	CCSpriteBatchNode* ui = CCSpriteBatchNode::create("cat.png");
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

	//初始化主角子弹
 	m_heroBullets = CCArray::createWithCapacity(30);
 	for(size_t i = 0;i < m_heroBullets->capacity();i ++)
 	{
 		GameHeroBullet * mybullet = new GameHeroBullet();
 		mybullet->setIsNotVisable(this);//若是没加object参数，会发生运行时调用约定错误，原因未知
 		mybullet->setScale(0.5);
 		m_heroBullets->addObject(mybullet);
 		this->addChild(mybullet,3);
 	}
 	m_heroBullets->retain();//计数器+1
 	//初始化敌人子弹
 	m_enemyBullets = CCArray::createWithCapacity(10);
 	for(size_t i = 0;i < m_enemyBullets->capacity();i ++)
 	{
 		GameEnemyBullet * mybullet = new GameEnemyBullet();
 		mybullet->setIsNotVisable(this);//若是没加object参数，会发生运行时调用约定错误，原因未知
 		mybullet->setScale(0.5);
 		m_enemyBullets->addObject(mybullet);
 		this->addChild(mybullet,3);
 	}
 	m_enemyBullets->retain();
	m_gameMark = new GameMark();
	this->addChild(m_gameMark,4);
	
	//初始化游戏结束弹板及按钮
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
	m_isReduce = false;
	m_isGameOver = false;
	scheduleUpdate();
	return true;
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
	//遍历子弹数组，不在使用的子弹释放
	for(size_t i = 0;i < m_heroBullets->capacity();i ++)
	{
		if(!((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->getIsvisble())
		{
			//设置位置，并设置为显示
			((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->setPosition(ccp(x,y));
			((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->setIsVisable();
			break; 
		}
	}
}

void GameMainScene::update( float time )
{
	//背景移动逻辑
	m_bg1->setPosition(ccp(m_bg1->getPosition().x,m_bg1->getPosition().y - 2));
	m_bg2->setPosition(ccp(m_bg2->getPosition().x,m_bg2->getPosition().y - 2));
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
 	//敌人和子弹碰撞检测
 	for(size_t i = 0;i < m_enemys->capacity();i ++)
 	{
 		GameObjEnemy * enemy = ((GameObjEnemy *) m_enemys->objectAtIndex(i));
 		CCPoint epos = enemy->getPosition();
 		if(enemy->m_isLife)//子弹击中敌人
 		{
 			for(size_t i = 0;i < m_heroBullets->capacity();i ++)
 			{
 				if(((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->getIsvisble())
 				{
 					if(isHit(((GameHeroBullet *)m_heroBullets->objectAtIndex(i))->getPosition(),epos,5,13,21,28))
 					{
 						enemy->setDie();
 						m_gameMark->addNumber(200);
 						break;
 					}
 				}
 			}
 		}
		//敌人和英雄碰撞
		if(!m_isReduce && enemy->m_isLife && isHit(hpos,epos,21,22.5,21,28))
		{
			enemy->setDie();
			setHeroHurt();
		}
	}
	//主角和敌人子弹碰撞
	if(!m_isReduce)
	{
		for(size_t i = 0;i < m_enemyBullets->capacity();i ++)
		{
			if(isHit(hpos,((GameEnemyBullet *)m_enemyBullets->objectAtIndex(i))->getPosition(),21,22.5,5,13))
			{
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
	//判断两个矩形是否碰撞
	if(abs(p1.x - p2.x) < w1 + w2 && abs(p1.y - p2.y) < h1 + h2)
	{
		return true;
	}
	return false;
}

void GameMainScene::setHeroHurt()
{
	//主角受伤，减血
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
 	CCActionInterval*  action = CCBlink::create(3, 6);//5秒内闪烁10次
 	m_hero->runAction(action);
	scheduleOnce(schedule_selector(GameMainScene::resetReduce), 5.0f);//5秒后执行一次
	m_isReduce = true;//5秒不受伤害
}

void GameMainScene::resetReduce( float dt )
{
	m_isReduce = false;//重新能收到伤害
}
void GameMainScene::setGameOver()
{
	//设置游戏结束
	CCMenu* pMenu = (CCMenu *)this->getChildByTag(25);
	pMenu->setVisible(true);
	pMenu->setEnabled(true);
	m_gameOver->setVisible(true);
	m_gameOver->setScale(0);
	pMenu->setScale(0);
	pMenu->runAction(CCScaleTo::create(0.5,1));//0.5秒缩放到正常大小
	m_gameOver->runAction(CCScaleTo::create(0.5,0.5));//0.5秒缩放到正常大小的0.5倍
}
