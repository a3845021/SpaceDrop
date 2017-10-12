//
// Created by Borna Koruznjak on 08/10/2017.
//

#include "PauseScene.h"

USING_NS_CC;

Scene *PauseScene::createScene() {
    return PauseScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOverScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PauseScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto resumeItem = MenuItemImage::create("assets/res/PauseScene/img_button_resume.png",
                                            "assets/res/PauseScene/img_button_resume_clicked.png",
                                            CC_CALLBACK_1(PauseScene::resume, this));

    auto retryItem = MenuItemImage::create("assets/res/PauseScene/img_button_retry.png",
                                           "assets/res/PauseScene/img_button_retry_clicked.png",
                                           CC_CALLBACK_1(PauseScene::retry, this));

    auto mainMenuItem = MenuItemImage::create("assets/res/PauseScene/img_button_menu.png",
                                              "assets/res/PauseScene/img_button_menu_clicked.png",
                                              CC_CALLBACK_1(PauseScene::goToMainMenuScene, this));

    auto menu = Menu::create(resumeItem, retryItem, mainMenuItem, NULL);

    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu);

    auto backgroundImage = Sprite::create("assets/res/PauseScene/img_background_port.png");
    float scale = MAX(visibleSize.width / backgroundImage->getContentSize().width,
                      visibleSize.height / backgroundImage->getContentSize().height);
    backgroundImage->setScale(scale);

    backgroundImage->setPosition(Point(origin.x + visibleSize.width / 2,
                                       origin.y + visibleSize.height / 2));

    this->addChild(backgroundImage, -1);

    return true;
}

void PauseScene::goToMainMenuScene(cocos2d::Ref *pSender) {
    auto scene = MainMenuScene::createScene();

    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}


void PauseScene::resume(cocos2d::Ref *pSender) {
    //todo implement your own transition fade for pop method
    Director::getInstance()->popScene();

}

void PauseScene::retry(cocos2d::Ref *pSender) {
    auto scene = GameScene::createScene();

    Director::getInstance()->popScene();
    Director::getInstance()->replaceScene(scene);
}