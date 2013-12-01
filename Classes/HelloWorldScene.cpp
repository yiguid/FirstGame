#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCNode *anode = CCNode::create();
    this->addChild(anode,0);
    //anode->setPosition(ccp(50,50));
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    anode->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 70) );

    // add the label as a child to this layer
    anode->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld-568h@2x.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    anode->addChild(pSprite, 0);
    
    //add a sprite
    hero = CCSprite::create("grossini.png");
    hero->setPosition(ccp(size.width/8,size.height/2));
    anode->addChild(hero,0);
    setTouchEnabled(true);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelloWorld::ccTouchBegan(CCTouch* touch, CCEvent *event)
{
    CCPoint heropos = hero->getPosition();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    if (location.x > heropos.x - 42.5 && location.x < heropos.x + 42.5 && location.y > heropos.y - 60.5 && location.y < heropos.y + 60.5) {
        isControl = true;
        deltax = location.x - heropos.x;
        deltay = location.y - heropos.y;
    }
    return true;
}

void HelloWorld::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
    if(isControl)
    {
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        float x = location.x - deltax;
        float y = location.y - deltay;
        hero->setPosition(ccp(x, y));
    }
}

void HelloWorld::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    isControl = false;
}

void HelloWorld::ccTouchCancelled(CCTouch *touch, CCEvent *event)
{
    isControl = false;
}



