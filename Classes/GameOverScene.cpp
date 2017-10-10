//
// Created by Borna Koruznjak on 08/10/2017.
//

#include "GameOverScene.h"

USING_NS_CC;

Scene *GameOverScene::createScene() {
    return GameOverScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOverScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOverScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto gameOverTitle = MenuItemImage::create("assets/res/GameOverScene/img_game_over.png",
                                               "assets/res/GameOverScene/img_game_over.png");

    auto retryItem = MenuItemImage::create("assets/res/GameOverScene/img_button_retry.png",
                                           "assets/res/GameOverScene/img_button_retry_clicked.png",
                                           CC_CALLBACK_1(GameOverScene::goToGameScene, this));

    auto mainMenuItem = MenuItemImage::create("assets/res/GameOverScene/img_button_menu.png",
                                              "assets/res/GameOverScene/img_button_menu_clicked.png",
                                              CC_CALLBACK_1(GameOverScene::goToMainMenuScene,
                                                            this));

    auto menu = Menu::create(gameOverTitle, retryItem, mainMenuItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu);
    return true;
}

void GameOverScene::goToGameScene(cocos2d::Ref *pSender) {
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(scene);
}

void GameOverScene::goToMainMenuScene(cocos2d::Ref *pSender) {
    auto scene = MainMenuScene::createScene();

    Director::getInstance()->replaceScene(scene);
}

