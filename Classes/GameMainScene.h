#ifndef _GameMainScene_h
#define _GameMainScene_h

#include "GameObjHero.h"
#include "GameMark.h"

#include "cocos2d.h"
USING_NS_CC;
class GameMainScene :public cocos2d::CCLayer
{
public:
	GameMainScene(void);
	~GameMainScene(void);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	virtual void onEnter();

	virtual void onExit();
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	void menuBackCallback(CCObject* pSender);
	virtual void update(float time);
	CREATE_FUNC(GameMainScene);

	void releaseHeroBullet(int x,int y);
	void releaseEnemyBullet(int x,int y);
	bool isHit(CCPoint p1,CCPoint p2,int w1,int h1,int w2,int h2);
	void setHeroHurt();
	void setGameOver();
	void resetReduce(float dt);
	void onPause(CCObject *pSender);
	void onResume(CCObject *pSender);

	bool m_isGameOver;//游戏结束，不在接受触屏事件
	bool m_isReduce;    //不受伤害
	bool m_isPause; //是否暂停中
	
private:
	CCSprite* m_blood1;
	CCSprite* m_blood2;
	CCSprite* m_blood3;
	CCSprite* m_bg1;
	CCSprite* m_bg2;
	CCSprite* m_gameOver;
	
	GameObjHero* m_hero;
	GameMark* m_gameMark;//游戏分数
	
	CCArray* m_enemys;
	CCArray* m_heroBullets;
	CCArray* m_enemyBullets;
	int m_blood;//命数
};
#endif

