#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"
#include "GameScene.h"

class GameOverScene : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

    void goToGameScene(cocos2d::Ref *pSender);

    void goToMainMenuScene(cocos2d::Ref *pSender);
};

#endif // __GAME_OVER_SCENE_H__
