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

    auto pauseItem = MenuItemImage::create("assets/res/GameScene/img_button_pause.png",
                                           "assets/res/GameScene/img_button_pause_clicked.png",
                                           CC_CALLBACK_1(GameScene::goToPauseScene, this));


    int pauseWidth = pauseItem->getContentSize().width;
    int pauseHeight = pauseItem->getContentSize().height;
    int quarterPauseWidth = pauseItem->getContentSize().width / 4;
    int quarterPauseHeight = pauseItem->getContentSize().height / 4;

    int pauseButtonX = pauseWidth - quarterPauseWidth + origin.x;
    int pauseButtonY = visibleSize.height - pauseHeight + quarterPauseHeight + origin.y;

    pauseItem->setPosition(Point(pauseButtonX, pauseButtonY));

    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    return true;
}

void GameScene::goToPauseScene(cocos2d::Ref *pSender) {
    auto scene = PauseScene::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(1.0,scene));
}

void GameScene::goToGameOverScene(cocos2d::Ref *pSender) {
    auto scene = GameOverScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}
