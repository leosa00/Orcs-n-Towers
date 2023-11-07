#include "player.hpp"

int Player::getWallet() const {
    return wallet_;
}

int Player::getHP() const {
    return hp_;
}

std::string& Player::getName() const {
    return name_;
}

void Player::addMoney(int amount) {
    wallet_ += amount;
}

void Player::removeMoney(int cost) {
    wallet_ -= cost;
}

void Player::removeHP(int amount) {
    hp_ -= amount;
}

void Player::addToScore(int amount) {
    score_ += amount;
}