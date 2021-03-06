#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"  
using namespace CocosDenshion;
USING_NS_CC;
bool GameOverScene::init()
{
    if(CCLayerColor::initWithColor(ccc4(0,0,0,255))){

        _label = CCLabelTTF::create("word","Artial",40);
        CCSize size = CCDirector::sharedDirector()->getVisibleSize();
        _label->setPosition(ccp(size.width/2,size.height/2));
        this->addChild(_label);
        _label->retain(); //œ‡Õ¨µƒ…˙√¸÷‹∆⁄ 

        CCDelayTime *delaytime = CCDelayTime::create(4);//Õ£¡Ù ±º‰
        CCCallFuncN *func = CCCallFuncN::create(this,callfuncN_selector(GameOverScene::backToGame));
        this->runAction(CCSequence::create(delaytime,func,NULL));
        return true;
    }
    return false;
}
void GameOverScene::backToGame(CCNode* node){
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void GameOverScene::setEffect(int effect)
{
    switch(effect){
    case 1:
        {
        _label->setString("你赢了，高富帅!");
        SimpleAudioEngine::sharedEngine()->playEffect("win.wav");
        }
       break;
    case 2:
        {
        _label->setString("你输了，你个屌丝!");
        SimpleAudioEngine::sharedEngine()->playEffect("lose.wav");
        }
        break;
    }
}
CCScene* GameOverScene::scene()
{
    CCScene *scene = CCScene::create();
    GameOverScene *layer = GameOverScene::create();
        layer->setTag(100);
    scene->addChild(layer);
    return scene;
}

GameOverScene::~GameOverScene(){
    CCLog("~~GameOverScene");
    if(_label!=NULL){
        _label->release();
    }
}