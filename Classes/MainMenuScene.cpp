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
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto menuTitle = MenuItemImage::create("assets/res/MainMenuScene/img_game_title.png",
                                           "assets/res/MainMenuScene/img_game_title.png");

    auto playItem = MenuItemImage::create("assets/res/MainMenuScene/img_button_play.png",
                                          "assets/res/MainMenuScene/img_button_play_clicked.png",
                                          CC_CALLBACK_1(MainMenuScene::goToGameScene, this));

    auto menu = Menu::create(menuTitle, playItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu);

    auto backgroundImage = Sprite::create("assets/res/MainMenuScene/img_background_port.png");
    //lets make it scale nicely http://discuss.cocos2d-x.org/t/solved-background-image-is-not-covering-full-screen-on-android-device-in-coco2dx-v3-3/19376/6
    float scale = MAX(visibleSize.width / backgroundImage->getContentSize().width, visibleSize.height / backgroundImage->getContentSize().height);
    backgroundImage->setScale(scale);
    backgroundImage->setPosition(
            Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundImage, -1);

    return true;
}

void MainMenuScene::goToGameScene(cocos2d::Ref *pSender) {
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}
