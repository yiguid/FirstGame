#ifndef _GameEnemyBullet_h
#define _GameEnemyBullet_h

#include "cocos2d.h"
using namespace cocos2d;

class GameEnemyBullet : public CCNode
{
public:

	GameEnemyBullet(void);
	~GameEnemyBullet(void);
	void setIsVisable();
	void setIsNotVisable(CCNode* pSender);
	bool getIsvisble();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(GameEnemyBullet)

private:
	bool m_isVisable;
};


#endif
