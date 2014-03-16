#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "PauseLayerScene.h"
#include "SimpleAudioEngine.h"  
using namespace CocosDenshion;
USING_NS_CC;


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
    if ( !CCLayerColor::initWithColor(ccc4(191,191,191,255)))
    {
        return false;
    }
    _fire = new CCArray;
    _monster = new CCArray;
    count= 0;
    CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
     CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite *sprite = CCSprite::create("Player.png");
    sprite->setPosition(ccp(30,screenSize.height/2));


    this->addChild(sprite);

     // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::exitDialog));
    
     pCloseItem->setPosition(ccp(origin.x + screenSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    this->schedule(schedule_selector(HelloWorld::gameLogic),4);//ÿ������ִ��һ��
    this->schedule(schedule_selector(HelloWorld::update));//ÿһִ֡��һ��
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);



    return true;
}

HelloWorld::~HelloWorld(){
    if(_fire != NULL){
        _fire->release();
    }

    if(_monster != NULL){
        _monster->release();
    }
}
void HelloWorld::exitDialog(CCObject *obj){
  //  CCDirector::sharedDirector()->stopAnimation();
   CCSize size = CCDirector::sharedDirector()->getVisibleSize();

    CCRenderTexture* renderTexture = CCRenderTexture::create(size.width, size.height);
    renderTexture->retain();
    CCScene *s = CCDirector::sharedDirector()->getRunningScene();

    renderTexture->begin();
    s->visit();
    renderTexture->end();
    CCScene* pause = PauseLayerScene::scene(renderTexture, true);
  //  CCScene *pause = GameOverScene::scene();
    CCDirector::sharedDirector()->pushScene(pause);
}
void HelloWorld::update(float delta){
    CCObject *fire,*monster;

    CCArray *fire_to_del = new CCArray;
    CCArray *monster_to_del= new CCArray;


    CCARRAY_FOREACH(_fire,fire){//����fire����
        CCSprite *fireSprite = (CCSprite*)fire;
        CCRect fireZone = CCRectMake(fireSprite->getPositionX(),
                fireSprite->getPositionY(),
                fireSprite->getContentSize().width,
                fireSprite->getContentSize().height);

        CCARRAY_FOREACH(_monster,monster){//����monster����
            CCSprite *monsterSprite = (CCSprite*)monster;
                CCRect monsterZone = CCRectMake(monsterSprite->getPositionX(),
                monsterSprite->getPositionY(),
                monsterSprite->getContentSize().width,
                monsterSprite->getContentSize().height);

                if(fireZone.intersectsRect(monsterZone)){
                     SimpleAudioEngine::sharedEngine()->playEffect("kill.wav");   //���Ŵ�����Ч 
                    if(++count>=5){ //�㶨5������Ӯ��
                      
                        CCScene* scene = GameOverScene::scene();
                        GameOverScene *layer = (GameOverScene*)scene->getChildByTag(100);//ͨ��TAG��ȡ����
                        layer->_label->setString("You won!");
                        layer->setEffect(1);//1:win����Ч
                        CCDirector::sharedDirector()->replaceScene(scene);
                    }
                    fire_to_del->addObject(fireSprite);
                    monster_to_del->addObject(monsterSprite);
                }
        }//end ����monster����
    }//end ����fire����

      CCARRAY_FOREACH(fire_to_del,fire){//����Ҫɾ����fire���ϣ����Ӳ����Ƴ�
          _fire->removeObject(fire);
          CCSprite* fireSprite = (CCSprite*)fire;
          fireSprite->removeFromParentAndCleanup(true);
      }
       CCARRAY_FOREACH(monster_to_del,monster){//����Ҫɾ����monster���ϣ����Ӳ����Ƴ�
          _monster->removeObject(monster);
          CCSprite* monsterSprite = (CCSprite*)monster;
          monsterSprite->removeFromParentAndCleanup(true);
      }

       fire_to_del->release();//�ͷ���Դ
       monster_to_del->release();
}
void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
    CCLog("touch ended");
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint point = touch->getLocationInView();
    CCPoint loc  = CCDirector::sharedDirector()->convertToGL(point);
    if(loc.x<30){
        return;
    }
   
    CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();

    float startx,starty;
    float endx,endy;
    float xside,yside;
    startx = 30;
    starty = screenSize.height/2;
 
    xside = (loc.x-startx);
    yside = (loc.y-starty);

    CCSprite *fire = CCSprite::create("Projectile.png");
    this->addChild(fire);

    SimpleAudioEngine::sharedEngine()->playEffect("fire.wav");   //���ſ�����Ч 

     _fire->addObject(fire);//���뵽������
     fire->setTag(2);//���ñ��2�����ڵ�
    fire->setPosition(ccp(startx,starty));

    float D = sqrt(screenSize.width * screenSize.width + screenSize.height * screenSize.height);
    float d = sqrt(xside*xside + yside*yside);

    float ratio = D/d;

    endx = startx + xside * ratio;
    endy = starty + yside * ratio;

    CCMoveTo *move = CCMoveTo::create(2,ccp(endx,endy));//�ƶ�
    CCCallFuncN *disappear = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::myDisappear));//��ʧ
    CCSequence *action = CCSequence::create(move,disappear,NULL);//���ᶯ��

    fire->runAction(action);
}
void HelloWorld::gameLogic(float num){
    this->createTarget();
}

void HelloWorld::createTarget(){
     CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSprite *target = CCSprite::create("Target.png");
    int y = rand()%(int)screenSize.height;//���λ��
    target->setPosition(ccp(screenSize.width-20,y));
    this->addChild(target);
    _monster->addObject(target);//���뵽������,Ϊ��ײ�����׼��
    target->setTag(1);//���ñ��Ϊ1,�������
     CCMoveTo *move = CCMoveTo::create(2,ccp(30,y));//�ƶ�
     CCCallFuncN *disappear = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::myDisappear));//��ʧ
     CCSequence *action = CCSequence::create(move,disappear,NULL);//���ᶯ��
     target->runAction(action);
}

void HelloWorld::myDisappear(CCNode *who){
    int flag = who->getTag();
    switch(flag){
    case 1:{//�Ƴ�����
        _monster->removeObject(who);
        CCScene* scene = GameOverScene::scene();
         GameOverScene *layer = (GameOverScene*)scene->getChildByTag(100);
         layer->_label->setString("You failed!");
        layer->setEffect(2);//1:lose����Ч
         CCDirector::sharedDirector()->replaceScene(scene);
      }
           break;
    case 2:{//�Ƴ��ڻ�
        _fire->removeObject(who);
      }
           break;
    }
    who->removeFromParentAndCleanup(true);//��ʧ
}
void HelloWorld::keyBackClicked()
{
    exitDialog(NULL);
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
