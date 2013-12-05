#ifndef _GameMenuScene_h
#define _GameMenuScene_h

#include "cocos2d.h"

class GameMenuScene :public cocos2d::CCLayer
{
public:
	GameMenuScene(void);
	~GameMenuScene(void);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	virtual void onEnter();

	virtual void onExit();
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	void menuNewGameCallback(CCObject* pSender);

	void menuContinueCallback(CCObject* pSender);

	void menuAboutCallback(CCObject* pSender);

	void menuSoundCallback(CCObject* pSender);

	void menuEnter(CCNode* pSender);
	CREATE_FUNC(GameMenuScene);

private:
	 bool m_isSound;
	 cocos2d::CCMenuItemImage* m_soundItem;
};

#endif
