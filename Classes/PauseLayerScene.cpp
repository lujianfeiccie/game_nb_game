#include "PauseLayerScene.h"

USING_NS_CC;

bool PauseLayerScene::init(){
     if(!CCLayerColor::init()){
         return false;
     }

         CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
          CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
            // add a "close" icon to exit the progress. it's an autorelease object
   
   CCMenuItemFont * fontItem1 = CCMenuItemFont::create("BACK",this,menu_selector(PauseLayerScene::resumeGame));
   fontItem1->setPosition(ccp(origin.x+visibleSize.width/2 ,
   origin.y+visibleSize.height/2+fontItem1->getContentSize().height));

   CCMenuItemFont * fontItem2 = CCMenuItemFont::create("EXIT",this,menu_selector(PauseLayerScene::menuCloseCallback));
   fontItem2->setPosition(ccp(origin.x+visibleSize.width/2 ,
                                 origin.y+visibleSize.height/2 - fontItem2->getContentSize().height));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(fontItem1,fontItem2, NULL);
     pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

        
     return true;
}
void PauseLayerScene::resumeGame(CCObject *obj){
    CCDirector::sharedDirector()->popScene();
}
PauseLayerScene::~PauseLayerScene(){

}

void PauseLayerScene::menuCloseCallback(CCObject* pSender)
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

CCScene* PauseLayerScene::scene(CCRenderTexture *sqr, bool isFlip){
   CCScene *scene = CCScene::create();
  CCSize size = CCDirector::sharedDirector()->getWinSize();

  CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
  _spr->setPosition(ccp(size.width / 2, size.height / 2));
  _spr->setFlipY(isFlip);
  _spr->setColor(ccGRAY);
  scene->addChild(_spr);

  PauseLayerScene* layer = PauseLayerScene::create();
  scene->addChild(layer);

  return scene;
}