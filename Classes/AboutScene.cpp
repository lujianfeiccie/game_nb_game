#include "AboutScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;
bool AboutScene::init()
{
    if(CCLayerColor::initWithColor(ccc4(0,0,0,255))){

        
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
       

        _me = CCSprite::create("me.png");
        _me->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
        this->addChild(_me);
        _me->retain();
        
        
        _label = CCLabelTTF::create("Author :John","Artial",40);
        _label->setPosition(ccp(visibleSize.width/2,_me->getPositionY()-_me->getContentSize().height));
        this->addChild(_label);
        _label->retain();
        
        _fontItem1 = CCMenuItemFont::create("OK",this,menu_selector(AboutScene::backToGame));
        _fontItem1->setPosition(ccp(origin.x+visibleSize.width/2 ,_label->getPositionY()-_label->getContentSize().height));
        _fontItem1->retain();
        
        // create menu, it's an autorelease object
        _menu = CCMenu::create(_fontItem1, NULL);
        _menu->setPosition(CCPointZero);
        _menu->retain();
        
        this->addChild(_menu);
        
        return true;
    }
    return false;
}
void AboutScene::backToGame(CCNode* node){
    CCDirector::sharedDirector()->popScene();
}

CCScene* AboutScene::scene()
{
    CCScene *scene = CCScene::create();
    
    AboutScene *layer = AboutScene::create();
    scene->addChild(layer);
    return scene;
}

AboutScene::~AboutScene(){
    CCLog("~AboutScene");
    if(_label!=NULL){
        _label->release();
    }
    if(_me != NULL){
        _me->release();
    }
    if(_fontItem1!=NULL){
        _fontItem1->release();
    }
    if(_menu!=NULL){
        _menu->release();
    }
}