#include "MainMenuScene.h"

USING_NS_CC;

Scene *MainMenuScene::createScene() {
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }
    return true;
}

void MainMenuScene::goToGameScene(cocos2d::Ref *pSender) {
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(scene);
}
