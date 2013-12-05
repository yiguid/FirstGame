﻿#include "GameAboutScene.h"
#include "GameMenuScene.h"
USING_NS_CC;

GameAboutScene::GameAboutScene(void)
{
}


GameAboutScene::~GameAboutScene(void)
{
}

cocos2d::CCScene* GameAboutScene::scene()
{
	CCScene* scene = CCScene::create();
	GameAboutScene* layer = GameAboutScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameAboutScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();    
	//初始化背景
	CCSprite* bg = CCSprite::create("bg.png");
	bg->setScale(0.5);
	bg->setPosition( ccp(size.width/2, size.height/2) );
	this->addChild(bg, 0,0);
	
    //初始化背景
	CCSprite*bgstar = CCSprite::create("moon.png");
	bgstar->setAnchorPoint(ccp(0.5,0));
	bgstar->setScale(0.5);
	bgstar->setPosition(ccp(size.width/3 * 1, 0));
	this->addChild(bgstar,1,1);

	//初始化关于框
	CCSprite*kuang = CCSprite::create("tb.png");
	kuang->setScale(0.5);
	kuang->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(kuang,2,2);
	char inf[256];
	sprintf(inf,"游戏名称:喵星战争\n\n作者:李颖\n\n公司:拓比\n\n使用工具:cocos2D-x");
	CCLabelTTF * myjineng = CCLabelTTF::create(inf,"Marker Felt",40,CCSizeMake(400,400),kCCTextAlignmentLeft);
	myjineng->setAnchorPoint(ccp(0,1));
	myjineng->setColor(ccc3(255,200,0));
	myjineng->setPosition(ccp(50,600));
	kuang->addChild(myjineng);

	//初始化关于标题
	CCSprite*abouttitle = CCSprite::create("about.png");
	abouttitle->setScale(0.5);
	abouttitle->setPosition(ccp(size.width/2, size.height - 20));
	this->addChild(abouttitle,3,3);
	//初始化返回按钮
	CCMenuItemImage *back = CCMenuItemImage::create("backA.png", "backB.png",this,menu_selector(GameAboutScene::menuBackCallback));
	back->setScale(0.5);
	back->setPosition(ccp(size.width - 20,size.height - 20));
	back->setEnabled(false);
	CCMenu* mainmenu = CCMenu::create(back,NULL);
	mainmenu->setPosition(ccp(0,0));
	this->addChild(mainmenu,3,4);
	return true;
}

void GameAboutScene::onEnter()
{
	 CCLayer::onEnter();
	  //菜单进入后，菜单项点击有效
	 CCSize size = CCDirector::sharedDirector()->getWinSize();
	 CCNode* mainmenu = this->getChildByTag(4);
	 mainmenu->setPositionX(-100);
	 mainmenu->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveBy::create(0.5,ccp(100,0))),CCCallFuncN::create(this, callfuncN_selector(GameAboutScene::menuEnter)),NULL));
	 //加速度动作
	 CCNode* title = this->getChildByTag(3);
	 title->setPositionY(size.height+20);
	 title->runAction(CCEaseElasticIn::create(CCMoveBy::create(0.5,ccp(0,-40))));

	 CCNode*bgstar = this->getChildByTag(1);
	 bgstar->setPositionX(size.width/3 * 2);
	 bgstar->runAction(CCMoveBy::create(0.5,ccp(-size.width/3,0)));

	 CCNode*kuang = this->getChildByTag(2);
	 kuang->setPositionX(-200);
	 kuang->runAction(CCEaseElasticIn::create(CCMoveTo::create(0.5,ccp(size.width/2,size.height/2))));
}

void GameAboutScene::onExit()
{
	CCLayer::onExit();
}

void GameAboutScene::menuBackCallback( CCObject* pSender )
{
	 CCDirector::sharedDirector()->replaceScene(GameMenuScene::scene());
}

void GameAboutScene::menuEnter( CCNode* pSender )
{
	//菜单进入后，菜单项点击有效
	CCNode* back = this->getChildByTag(4);
	CCArray* temp = back->getChildren();
	((CCMenuItemImage *)temp->objectAtIndex(0))->setEnabled(true);
}