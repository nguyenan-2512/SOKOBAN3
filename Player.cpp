#include "Player.h"
#include <iostream>

Player::Player(int x, int y, int tileSize) : GameObject(x, y, tileSize),
currentDirection(PlayerDirection::IDLE), isMoving(false) {
    loadAnimations();
}

Player::~Player() {
}

bool Player::loadAnimations() {
    // Load idle animation
    if (!idleAnimation.loadSpriteSheet("images/player_idle.png")) {
        std::cerr << "Failed to load player idle animation" << std::endl;
        return false;
    }
    idleAnimation.addFrame(0, 0, 32, 32); // Chỉ 1 frame cho idle
    idleAnimation.setFrameTime(1.0f);
    idleAnimation.setLoop(true);

    // Load walk animations
    if (!walkDownAnimation.loadSpriteSheet("images/player_walk_down.png")) {
        std::cerr << "Failed to load player walk down animation" << std::endl;
        return false;
    }
    walkDownAnimation.addFrameRow(0, 0, 32, 32, 4); // 4 frames ngang
    walkDownAnimation.setFrameTime(0.2f);
    walkDownAnimation.setLoop(true);

    if (!walkUpAnimation.loadSpriteSheet("images/player_walk_up.png")) {
        std::cerr << "Failed to load player walk up animation" << std::endl;
        return false;
    }
    walkUpAnimation.addFrameRow(0, 0, 32, 32, 4);
    walkUpAnimation.setFrameTime(0.2f);
    walkUpAnimation.setLoop(true);

    if (!walkLeftAnimation.loadSpriteSheet("images/player_walk_left.png")) {
        std::cerr << "Failed to load player walk left animation" << std::endl;
        return false;
    }
    walkLeftAnimation.addFrameRow(0, 0, 32, 32, 4);
    walkLeftAnimation.setFrameTime(0.2f);
    walkLeftAnimation.setLoop(true);

    if (!walkRightAnimation.loadSpriteSheet("images/player_walk_right.png")) {
        std::cerr << "Failed to load player walk right animation" << std::endl;
        return false;
    }
    walkRightAnimation.addFrameRow(0, 0, 32, 32, 4);
    walkRightAnimation.setFrameTime(0.2f);
    walkRightAnimation.setLoop(true);

    // Set initial animation
    setAnimation(&idleAnimation);
    return true;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::update() {
    GameObject::update(); // Gọi update animation của parent
}

void Player::move(int dx, int dy) {
    setPosition(getX() + dx, getY() + dy);

    // Determine direction và set animation
    if (dx > 0) {
        setDirection(PlayerDirection::RIGHT);
    }
    else if (dx < 0) {
        setDirection(PlayerDirection::LEFT);
    }
    else if (dy > 0) {
        setDirection(PlayerDirection::DOWN);
    }
    else if (dy < 0) {
        setDirection(PlayerDirection::UP);
    }

    setMoving(true);
}

void Player::setDirection(PlayerDirection direction) {
    if (currentDirection == direction) return;

    currentDirection = direction;

    switch (direction) {
    case PlayerDirection::IDLE:
        setAnimation(&idleAnimation);
        break;
    case PlayerDirection::UP:
        setAnimation(&walkUpAnimation);
        break;
    case PlayerDirection::DOWN:
        setAnimation(&walkDownAnimation);
        break;
    case PlayerDirection::LEFT:
        setAnimation(&walkLeftAnimation);
        break;
    case PlayerDirection::RIGHT:
        setAnimation(&walkRightAnimation);
        break;
    }
}

void Player::setMoving(bool moving) {
    isMoving = moving;
    if (!moving) {
        setDirection(PlayerDirection::IDLE);
    }
}