#ifndef _GameObjEnemy_h
#define _GameObjEnemy_h

#include "cocos2d.h"
USING_NS_CC;

class GameObjEnemy:public CCNode, public CCTargetedTouchDelegate
{
public:
	GameObjEnemy(void);
	~GameObjEnemy(void);

	virtual void onEnter();
	virtual void onExit();
	
	void moveStart();
	void reStart(CCNode* pSender);
	void reBorn(CCNode* pSender);
	void setDie();
	void setType(int type);
	void releaseBullet(float dt);
	CREATE_FUNC(GameObjEnemy)

	float m_shootInterval;
	bool m_isLife;
private:
	CCSprite* m_mainBody;
	CCSprite* m_boom;
	int m_type;
};
#endif

