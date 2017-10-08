//
// Created by Borna Koruznjak on 08/10/2017.
//

#include "GameScene.h"

USING_NS_CC;

Scene *GameScene::createScene() {
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}

void GameScene::goToPauseScene(cocos2d::Ref *pSender) {
    auto scene = PauseScene::createScene();

    Director::getInstance()->pushScene(scene);
}

void GameScene::goToGameOverScene(cocos2d::Ref *pSender) {
    auto scene = GameOverScene::createScene();

    Director::getInstance()->replaceScene(scene);
}
