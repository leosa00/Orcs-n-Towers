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

void Player::buyTower (int cost, std::string type) {
    if(cost > wallet_){
        //inform player somehow that they can't afford
        return;
    }

    //call constructor for selected type
    //add tower to list of towers they own

    switch (type)
    {
    case :
        /* code */
        break;
    
    default:
        break;
    }
}

void Player::sellTower(Tower& tower){
    for(auto i = towers_.begin(); i != towers_.end(); i++){
        //if pointer of i and addr of tower match -> same object
        if(*i == std::addressof(tower)){
            //find same object, add its cost to wallet, delete object and remove it from the vector
            wallet_ += i->getBaseCost();
            delete *i;
            towers_.erase(i);
        }
    }
}

void Player::upgradeTower(Tower& tower){
    if(tower.getUpgradeCost() > wallet_){
        //infrom player can't afford
        return;
    }

    wallet_ -= tower.getUpgradeCost();
    tower.upgradeTower();
}