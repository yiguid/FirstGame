#include "GameMenuScene.h"
#include "GameAboutScene.h"
#include "GameMainScene.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

#define GAMEBACKGROUNDMUSIC "music.mp3"

GameMenuScene::GameMenuScene(void)
{
	m_isSound = false;
}


GameMenuScene::~GameMenuScene(void)
{
}

bool GameMenuScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	 //初始化背景
	CCSprite* back = CCSprite::create("bg.png");
	back->setScale(0.25);
	back->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(back,0,0);

	//初始化背景星球
	CCSprite* bgstar = CCSprite::create("moon.png");
	bgstar->setAnchorPoint(ccp(0.5,0));
	bgstar->setScale(0.5);
	bgstar->setPosition(ccp(size.width/3 * 2, 0));
	this->addChild(bgstar,1,1);

	//init score
	int totalScore = 0;
	//取出我们刚存储的score
	totalScore= CCUserDefault::sharedUserDefault()->getIntegerForKey("totalScore");
	CCString *score = CCString::createWithFormat("%d",totalScore);
	CCLabelTTF *pHighScore = CCLabelTTF::create(score->getCString(),"微软雅黑",20);
	pHighScore->setPosition(ccp(size.width/2+50,size.height/2 + 100));
	this->addChild(pHighScore);
	CCLabelTTF *pHighLabel = CCLabelTTF::create("High Score: ","微软雅黑",20);
	pHighLabel->setPosition(ccp(size.width/2-50,size.height/2 + 100));
	this->addChild(pHighLabel);

	//初始化标题
	CCNode* title = CCNode::create();
	title->setContentSize(CCSizeMake(0,0));
	CCSprite* ptmLabel = CCSprite::create("meowstar.png");
	ptmLabel->setScale(0.5);
	ptmLabel->setPosition(ccp(0,30));
	title->addChild(ptmLabel);
	CCSprite *ptbLabel = CCSprite::create("battle.png");
	ptbLabel->setScale(0.5);
	ptbLabel->setPosition( ccp(0,-30) );
	title->addChild(ptbLabel);
	title->setPosition(ccp(size.width / 2, size.height - 80));
	this->addChild(title,2,2);

	//初始化按钮
	CCMenuItemImage *newGameItem = CCMenuItemImage::create("newGameA.png", "newGameB.png",this,menu_selector(GameMenuScene::menuNewGameCallback));
	newGameItem->setScale(0.5);
	newGameItem->setPosition(ccp(size.width / 2,size.height / 2 - 20));
	newGameItem->setEnabled(false);
	//CCMenuItemImage *continueItem = CCMenuItemImage::create("continueA.png", "continueB.png",this,menu_selector(GameMenuScene::menuContinueCallback));
	//continueItem->setScale(0.5);
	//continueItem->setPosition(ccp(size.width / 2,size.height / 2 - 80));
	//continueItem->setEnabled(false);
	CCMenuItemImage *aboutItem = CCMenuItemImage::create("aboutA.png", "aboutB.png",this,menu_selector(GameMenuScene::menuAboutCallback));
	aboutItem->setScale(0.5);
	aboutItem->setPosition(ccp(size.width / 2,size.height / 2 - 100));
	aboutItem->setEnabled(false);
	m_soundItem = CCMenuItemImage::create("sound-on-A.png", "sound-on-B.png",this,menu_selector(GameMenuScene::menuSoundCallback));
	m_soundItem->setScale(0.5);
	m_soundItem->setEnabled(false);
	m_soundItem->setPosition(ccp(40,40));

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameMenuScene::menuCloseCallback));
	pCloseItem->setPosition(ccp(size.width - 20, 20));
	//使用按钮创建菜单
	CCMenu* mainmenu = CCMenu::create(newGameItem,aboutItem,m_soundItem,pCloseItem,NULL);
	mainmenu->setPosition(ccp(0,0));
	this->addChild(mainmenu,1,3);

	m_isSound = true;//是否开启声音参数
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( CCFileUtils::sharedFileUtils()->fullPathForFilename(GAMEBACKGROUNDMUSIC).c_str() );
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename(GAMEBACKGROUNDMUSIC).c_str(), true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
	return true;
}

void GameMenuScene::onEnter()
{
	CCLayer::onEnter();
	//进入主菜单动画
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCNode* mainmenu = this->getChildByTag(3);
	mainmenu->setPositionX(-200);
	mainmenu->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveTo::create(0.5,ccp(0,0))),CCCallFuncN::create(this, callfuncN_selector(GameMenuScene::menuEnter)),NULL));

	CCNode* title = this->getChildByTag(2);
	title->setPositionY(size.height + 20);
	title->runAction(CCEaseElasticIn::create(CCMoveBy::create(0.5,ccp(0,-100))));

	CCNode* bgstar = this->getChildByTag(1);
	bgstar->setPositionX(size.width/3);
	bgstar->runAction(CCMoveBy::create(0.5,ccp(size.width/3,0)));
}

void GameMenuScene::onExit()
{
	CCLayer::onExit();
}
void GameMenuScene::menuEnter( CCNode* pSender )
{
	//启用按钮
	CCNode* mainmenu = this->getChildByTag(3);
	CCArray* temp = mainmenu->getChildren();
	for(unsigned int i = 0;i < temp->count();i ++)
	{
		((CCMenuItemImage *)temp->objectAtIndex(i))->setEnabled(true);
	}
}
cocos2d::CCScene* GameMenuScene::scene()
{
	CCScene* scene = CCScene::create();
	GameMenuScene* layer = GameMenuScene::create();
	scene->addChild(layer);
	return scene;
}

void GameMenuScene::menuCloseCallback( CCObject* pSender )
{
	CCDirector::sharedDirector()->end();
}

void GameMenuScene::menuNewGameCallback( CCObject* pSender )
{
	CCDirector::sharedDirector()->replaceScene(GameMainScene::scene());
}

void GameMenuScene::menuContinueCallback( CCObject* pSender )
{
	CCDirector::sharedDirector()->replaceScene(GameMainScene::scene());
}

void GameMenuScene::menuAboutCallback( CCObject* pSender )
{
	CCDirector::sharedDirector()->replaceScene(GameAboutScene::scene());
}

void GameMenuScene::menuSoundCallback( CCObject* pSender )
{
	if(!m_isSound)
	{
		m_soundItem->setNormalImage(CCSprite::create("sound-on-A.png"));
		m_soundItem->setDisabledImage(CCSprite::create("sound-on-B.png"));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename(GAMEBACKGROUNDMUSIC).c_str(), true);
		m_isSound = true;
	}
	else
	{
		m_soundItem->setNormalImage(CCSprite::create("sound-off-A.png"));
		m_soundItem->setDisabledImage(CCSprite::create("sound-off-B.png"));
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		m_isSound = false;
	}
}
