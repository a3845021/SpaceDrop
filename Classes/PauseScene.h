#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "GameScene.h"

class PauseScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(PauseScene);

    void resume(cocos2d::Ref *pSender);

    void goToMainMenuScene(cocos2d::Ref *pSender);

    void retry(cocos2d::Ref *pSender);
};

#endif // __PAUSE_SCENE_H__
