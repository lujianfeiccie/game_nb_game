#ifndef PAUSELAYERSCENE_H
#define PAUSELAYERSCENE_H

#include "cocos2d.h"
class PauseLayerScene : public cocos2d::CCLayerColor
{
public:
     virtual bool init();
    ~PauseLayerScene();
    void resumeGame(CCObject *obj);
     // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene(cocos2d::CCRenderTexture *sqr, bool isFlip);

    void menuCloseCallback(CCObject* pSender);
     // implement the "static node()" method manually
    CREATE_FUNC(PauseLayerScene);
};
#endif