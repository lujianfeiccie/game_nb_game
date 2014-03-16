#ifndef WELCOME_H
#define WELCOME_H

#include "cocos2d.h"

class WelcomeScene: public cocos2d::CCLayerColor{
public:
    ~WelcomeScene();
    void backToGame(CCNode* node);
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(WelcomeScene);
};
#endif