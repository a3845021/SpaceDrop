#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PauseScene.h"
#include "GameOverScene.h"

class GameScene : public cocos2d::Scene
{
public:
    cocos2d::Sprite *backgroundSpriteArray[2];
    cocos2d::Sprite *playerSprite;

    std::vector<cocos2d::Sprite *> asteroidVector;

    static cocos2d::Scene* createScene();

    virtual bool init();

    void goToPauseScene(cocos2d::Ref *pSender);

    void goToGameOverScene(cocos2d::Ref *pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    void update(float deltaTime);

    void spawnAsteroid(float deltaTime);

};

#endif // __GAME_SCENE_H__
