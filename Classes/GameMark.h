#ifndef _GameMark_h
#define _GameMark_h

#include "cocos2d.h"
USING_NS_CC;

class GameMark : public CCNode
{
public:
	GameMark(void);
	~GameMark(void);

	virtual void onEnter();
	virtual void onExit();
	void addNumber(int var);
	CREATE_FUNC(GameMark);
private:
	int m_score;
	CCTexture2D* m_ui;
	CCArray* m_bits;
};

#endif