#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"

class AboutScene : public cocos2d::CCLayerColor
{   
public:
    cocos2d::CCLabelTTF *_label ;
    cocos2d::CCSprite *_me;
    cocos2d::CCMenuItemFont *_fontItem1;
    cocos2d::CCMenu* _menu;
    virtual bool init();
    ~AboutScene();
     // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    void backToGame(CCNode* node);
     // implement the "static node()" method manually
    CREATE_FUNC(AboutScene);
};
#endif