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

    for (int index = 0; index < 2; index++) {
        backgroundSpriteArray[index] = Sprite::create(
                "assets/res/GameScene/img_background_port.png");
        float scale = MAX(visibleSize.width / backgroundSpriteArray[index]->getContentSize().width,
                          visibleSize.height /
                          backgroundSpriteArray[index]->getContentSize().height);
        backgroundSpriteArray[index]->setScale(scale);
        backgroundSpriteArray[index]->setPosition(
                Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(backgroundSpriteArray[index], -2);
    }

    playerSprite = Sprite::create("assets/res/GameScene/img_space_pod_port.png");
    playerSprite->setPosition(Point(visibleSize.width / 2 + origin.x,
                                    pauseItem->getPosition().y - (pauseItem->
                                            getContentSize().height / 2) - (playerSprite->
                                            getContentSize().height / 2)));
    this->addChild(playerSprite, -1);

    this->scheduleUpdate();

    this->schedule(schedule_selector(GameScene::spawnAsteroid), 1.0);
    return true;
}

void GameScene::goToPauseScene(cocos2d::Ref *pSender) {
    auto scene = PauseScene::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(1.0, scene));
}

void GameScene::goToGameOverScene(cocos2d::Ref *pSender) {
    auto scene = GameOverScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene));
}

void GameScene::update(float deltaTime) {

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //due to background scroll we need to reset background once it left the screen
    for (int index = 0; index < 2; index++) {
        if (backgroundSpriteArray[index]->getPosition().y >=
            visibleSize.height + (visibleSize.height / 2) - 1) {
            backgroundSpriteArray[index]->setPosition(Point((visibleSize.width / 2) + origin.x,
                                                            (-1 * visibleSize.height) +
                                                            (visibleSize.height / 2)));
        }
    }


    for (int index = 0; index < 2; index++) {
        backgroundSpriteArray[index]->setPosition(
                Point(backgroundSpriteArray[index]->getPosition().x,
                      backgroundSpriteArray[index]->getPosition().y +
                      (0.75 * visibleSize.height * deltaTime)));
    }

    //asteroid spawn & update logic
    for (int index = 0; index < asteroidVector.size(); index++) {
        asteroidVector[index]->setPosition(Point(asteroidVector[index]->getPosition().x,
                                                 asteroidVector[index]->getPosition().y +
                                                 (0.75 * visibleSize.height * deltaTime)));

        if (asteroidVector[index]->getPosition().y > visibleSize.height * 2) {
            this->removeChild(asteroidVector[index]);
            asteroidVector.erase(asteroidVector.begin() + index);
        }
    }
}

void GameScene::spawnAsteroid(float deltaTime) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    int asteroidIndex = (arc4random() % 3) + 1;
    __String *asteroidString = __String::createWithFormat(
            "assets/res/GameScene/img_asteroid_%i_port.png", asteroidIndex);

    Sprite *tempAsteroid = Sprite::create(asteroidString->getCString());
    //min 2 seconds max 10
    int randomRotateDuration = (arc4random() % 8) + 2;
    auto twoSecondFullRotate = RotateBy::create(randomRotateDuration, 360);
    auto foreverRotateAction = RepeatForever::create(twoSecondFullRotate);
    *tempAsteroid->runAction(foreverRotateAction);

    int xRandomPosition = (arc4random() %
                           (int) (visibleSize.width - (tempAsteroid->getContentSize().width / 2))) +
                          (tempAsteroid->getContentSize().width / 2);

    tempAsteroid->setPosition(
            Point(xRandomPosition + origin.x, -tempAsteroid->getContentSize().height + origin.y));
    asteroidVector.push_back(tempAsteroid);
    this->addChild(asteroidVector[asteroidVector.size() - 1], -1);
}
