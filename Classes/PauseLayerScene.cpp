#include "PauseLayerScene.h"
#include "AboutScene.h"
USING_NS_CC;

bool PauseLayerScene::init(){
     if(!CCLayerColor::init()){
         return false;
     }

         CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
          CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
            // add a "close" icon to exit the progress. it's an autorelease object
   
   CCMenuItemFont * fontItem1 = CCMenuItemFont::create("返回",this,menu_selector(PauseLayerScene::resumeGame));
   fontItem1->setPosition(ccp(origin.x+visibleSize.width/2 ,
   origin.y+visibleSize.height/2+fontItem1->getContentSize().height));

    
   CCMenuItemFont * fontItem2 = CCMenuItemFont::create("关于",this,menu_selector(PauseLayerScene::aboutGame));
    fontItem2->setPosition(ccp(origin.x+visibleSize.width/2 ,
                               fontItem1->getPositionY() - fontItem2->getContentSize().height*2));
    
    
   CCMenuItemFont * fontItem3 = CCMenuItemFont::create("退出",this,menu_selector(PauseLayerScene::menuCloseCallback));
   fontItem3->setPosition(ccp(origin.x+visibleSize.width/2 ,
                                 fontItem2->getPositionY() - fontItem3->getContentSize().height*2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(fontItem1,fontItem2, fontItem3, NULL);
     pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

        
     return true;
}
void PauseLayerScene::resumeGame(CCObject *obj){
    CCDirector::sharedDirector()->popScene();
}

void PauseLayerScene::aboutGame(CCObject *obj){
    CCDirector::sharedDirector()->pushScene(AboutScene::scene());
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

    if(sqr!=NULL){
        sqr->release();
    }
  return scene;
}