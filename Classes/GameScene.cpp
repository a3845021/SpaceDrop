//
// Created by Borna Koruznjak on 08/10/2017.
//

#include "GameScene.h"

//debug printing

USING_NS_CC;

Scene *GameScene::createScene() {
    auto scene = GameScene::createWithPhysics();
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
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
    auto playerSpriteBody = PhysicsBody::createCircle(playerSprite->getContentSize().width / 2);
    playerSpriteBody->setContactTestBitmask(true);
    playerSpriteBody->setDynamic(true);
    playerSprite->setPhysicsBody(playerSpriteBody);
    playerSprite->setPosition(Point(visibleSize.width / 2 + origin.x,
                                    pauseItem->getPosition().y - (pauseItem->
                                            getContentSize().height / 2) - (playerSprite->
                                            getContentSize().height / 2)));
    this->addChild(playerSprite, -1);

    this->scheduleUpdate();

    this->schedule(schedule_selector(GameScene::spawnAsteroid), 1.0);

    //handle touch input
    auto touchListener = EventListenerTouchOneByOne::create();
    //prevent layers underneath from where the touch occurred to detect the touch
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

    //enable event detection
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    isTouching = false;
    touchPosition = 0;

    //collision detection
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    //preload audio
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
            "assets/res/audio/effect_crash.wav");

    return true;
}

void GameScene::goToPauseScene(cocos2d::Ref *pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
            "assets/res/audio/effect_button_click.wav");
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

    //handle player touch inputs
    if (isTouching) {
        //check which half of the screen is being touched
        if (touchPosition < (visibleSize.width / 2 + origin.x)) {
            //move the player sprite left
            playerSprite->setPositionX(
                    playerSprite->getPosition().x -
                    (0.5 * (visibleSize.width + origin.x) * deltaTime));
            //check to prevent the player sprite from going off the screen (left side)
            if (playerSprite->getPosition().x <=
                origin.x + (playerSprite->getContentSize().width / 2)) {
                playerSprite->setPositionX(playerSprite->getContentSize().width / 2 + origin.x);
            }
        } else {
            //move the player sprite right
            playerSprite->setPositionX(
                    playerSprite->getPosition().x +
                    (0.5 * (visibleSize.width + origin.x) * deltaTime));
            //check to prevent the player sprite from going off the screen (right side)
            if (playerSprite->getPosition().x >=
                (visibleSize.width + origin.x) - (playerSprite->getContentSize().width / 2)) {
                playerSprite->setPositionX(
                        (visibleSize.width + origin.x) -
                        (playerSprite->getContentSize().width / 2));
            }
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
    auto asteroidPhysicsBody = PhysicsBody::createCircle(
            asteroidVector[asteroidVector.size() - 1]->getContentSize().width / 2);
    asteroidPhysicsBody->setContactTestBitmask(true);
    asteroidPhysicsBody->setDynamic(true);
    asteroidVector[asteroidVector.size() - 1]->setPhysicsBody(asteroidPhysicsBody);
    this->addChild(asteroidVector[asteroidVector.size() - 1], -1);
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    isTouching = true;
    touchPosition = touch->getLocation().x;
    __android_log_print(ANDROID_LOG_DEBUG, "TestOne", "position : %f", touchPosition);
    //touch event consumed, no more propagation
    return true;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
    //not used at the moment
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
    isTouching = false;
}

void GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event) {
    onTouchEnded(touch, event);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {
    __android_log_print(ANDROID_LOG_DEBUG, "TestOne", "collision detected");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
            "assets/res/audio/effect_crash.wav");
    goToGameOverScene(this);
    return true;
}

