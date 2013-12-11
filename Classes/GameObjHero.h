#ifndef _GameObjHero_h
#define _GameObjHero_h

#include "cocos2d.h"
USING_NS_CC;

class GameObjHero:public CCNode, public CCTargetedTouchDelegate
{
public:
	GameObjHero(void);
	~GameObjHero(void);

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	
	CCRect rect();//Ó¢ÐÛ·¶Î§
	bool containsTouchLocation(CCTouch* touch);//ÊÇ·ñ´¥Ãþµ½Ó¢ÐÛ
	void releasebullet(float dt);
	CREATE_FUNC(GameObjHero);
	bool m_allowTouch;
private:
	
	bool m_isControl;
	CCPoint m_offset;
	CCSprite* m_leftHand;
	CCSprite* m_rightHand;
};
#endif

