#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::CCLayerColor
{   
public:
    cocos2d::CCLabelTTF *_label ;
    virtual bool init();
    void setEffect(int effect);
    ~GameOverScene();
     // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    void backToGame(CCNode* node);
     // implement the "static node()" method manually
    CREATE_FUNC(GameOverScene);
};
#endif