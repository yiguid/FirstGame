#ifndef _GameHeroBullet_h
#define _GameHeroBullet_h

#include "cocos2d.h"
using namespace cocos2d;

class GameHeroBullet : public CCNode
{
public:
	GameHeroBullet(void);
	virtual ~GameHeroBullet(void);
	void setIsVisable();
	void setIsNotVisable(CCNode* pSender);
	bool getIsvisble();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(GameHeroBullet)

private:
	bool m_isVisable;
};
#endif

