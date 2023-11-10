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

void Player::reachedCastle (Enemy& enemy) {
    sf::FloatRect castleBB = this.getGlobalBounds();
    sf::FloatRect enemyBB = enemy.getGlobalBounds();

    if(castleBB.intersects(enemyBB)){
        removeHP(10) //should different enemies affect affect differently
    }

    if(hp_ <= 0){
        //gameover
    }
}