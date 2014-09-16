#include "HelloWorldScene.h"
#include "AppMacros.h"

USING_NS_CC;
static int ticket;
static pthread_t pidrun;
static pthread_t pidgo;
static pthread_mutex_t mutex;


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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // press test pthread:
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    pLabel->runAction(CCRotateTo::create(500, 30000));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setVisible(false);

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    for(int i = 0;i < 1;i++)
    {
        Student *temp=new Student(std::string("zhycheng"),23,std::string("male"));
        pthread_mutex_init(&mutex,NULL);
        pthread_create(&pidrun,NULL,th_run,temp);//启动线程
        pthread_create(&pidgo,NULL,th_go,0);
        pthread_join(pidrun, NULL);
        pthread_join(pidgo, NULL);
        pthread_mutex_destroy(&mutex);
        printf("\n ---------------%d----------------- \n",i);
    }
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    Student *temp=new Student(std::string("kaitiren"),23,std::string("male"));
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&pidrun,NULL,th_run,temp);//启动线程
    pthread_create(&pidgo,NULL,th_go,0);
    pthread_join(pidrun, NULL);
    pthread_join(pidgo, NULL);
    pthread_mutex_destroy(&mutex);
}


void* HelloWorld::th_run(void *r)
{
    ticket = 100;
    Student *s=(Student*)(r);
    CCLog("name is %s,and age is %d,sex is %s",s->name.c_str(),s->age,s->sex.c_str());
    delete s;
    while(true)
    {
        pthread_mutex_lock(&mutex);
        if(ticket>0)
        {
            CCLog("thread run sell %d",ticket);
            ticket--;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    pthread_exit(0);
}


void* HelloWorld::th_go(void *r)
{
    
    while(true)
    {
        pthread_mutex_lock(&mutex);
        if(ticket>0)
        {
            CCLog("thread go sell %d",ticket);
            ticket--;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            break;
            
        }
        
    }
    pthread_exit(0);
}




