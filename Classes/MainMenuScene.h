#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);

    void goToGameScene(cocos2d::Ref *pSender);
};

#endif // __MAIN_MENU_SCENE_H__
