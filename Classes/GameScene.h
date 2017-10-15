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

    //touch commands
    bool isTouching;
    float touchPosition;
    //returns true if the touch is consumed and false if it will keep propagating
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
    // Detects when a touch event has ended but not by the user; for example, a system alert.
    // The general practice is to call the onTouchEnded method to run the same code, as it can be considered the same event for most games
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event);
};

#endif // __GAME_SCENE_H__
