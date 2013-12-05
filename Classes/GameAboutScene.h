#ifndef _GameAboutScene_h
#define _GameAboutScene_h

#include "cocos2d.h"
class GameAboutScene:public cocos2d::CCLayer
{
public:
	GameAboutScene(void);
	~GameAboutScene(void);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	virtual void onEnter();

	virtual void onExit();
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	void menuBackCallback(CCObject* pSender);
	void menuEnter(CCNode* pSender);

	CREATE_FUNC(GameAboutScene);
};

#endif
