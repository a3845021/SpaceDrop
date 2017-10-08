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


    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto menuTitle = MenuItemImage::create("assets/res/MainMenuScene/img_game_title.png",
                                           "assets/res/MainMenuScene/img_game_title.png");

    auto playItem = MenuItemImage::create("assets/res/MainMenuScene/img_button_play.png",
                                          "assets/res/MainMenuScene/img_button_play_clicked.png",
                                          CC_CALLBACK_1(MainMenuScene::goToGameScene,this));

    auto menu = Menu::create(menuTitle,playItem,NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu);

    return true;
}

void MainMenuScene::goToGameScene(cocos2d::Ref *pSender) {
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(scene);
}
