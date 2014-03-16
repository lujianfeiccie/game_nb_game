#include "WelcomeScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

bool WelcomeScene::init()
{
    if(!CCLayerColor::init()){
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite* pSprite = CCSprite::create("me.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    CCLabelTTF* _label = CCLabelTTF::create("NB GAME","Artial",24);
     // position the sprite on the center of the screen
    _label->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y-pSprite->getContentSize().height*2/3));
    this->addChild(_label, 1);

     CCDelayTime *delaytime = CCDelayTime::create(4);//Í£ÁôÊ±¼ä
     CCCallFuncN *func = CCCallFuncN::create(this,callfuncN_selector(WelcomeScene::backToGame));
     this->runAction(CCSequence::create(delaytime,func,NULL));
    return true;
}
void WelcomeScene::backToGame(CCNode* node){
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

WelcomeScene::~WelcomeScene(){

}
CCScene* WelcomeScene::scene()
{
    CCScene* scene = CCScene::create();
    scene->addChild(WelcomeScene::create());
    return scene;
}

