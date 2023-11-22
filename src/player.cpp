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

void Player::reachedCastle (std::shared_ptr<Enemy> enemy) {

    if(this.getGlobalBounds().intersects(enemy.getGlobalBounds())){
        removeHP(10) //should different enemies affect affect differently
    }

    if(hp_ <= 0){
        //gameover
    }
}

void Player::buyTower (int cost, Textures::TowerID towerID) {
    
    //cost can maybe be determined from towerID?
    if(cost > wallet_){
        //inform player somehow that they can't afford
        return;
    }

    //call constructor for selected type
    //add tower to list of towers they own
    //enum towerID could be used for this

    switch (towerID)
    {
    case Textures::Tower1 :
        /* call right constructor */
        /* add to towers_ */
        removeMoney(cost);
        break;

    case Textures::Tower2 :
        /* call right constructor */
        removeMoney(cost);
        break;

    case Textures::Tower3 :
        /* call right constructor */
        removeMoney(cost);
        break;

    case Textures::Tower4 :
        /* call right constructor */
        removeMoney(cost);
        break;
    
    case Textures::Tower5 :
        /* call right constructor */
        removeMoney(cost);
        break;
    
    default:
        /* infrom player of error */
        break;
    }
}

void Player::sellTower(Tower& tower){
    auto it_erase = towers_.end();

    for(auto i = towers_.begin(); i != towers_.end(); i++){
        //if pointer of i and addr of tower match -> same object
        if(*i == std::addressof(tower)){
            //find same object, add its cost to wallet (full cost or only partial?), delete object and remove it from the vector
            wallet_ += i->getBaseCost();
            it_erase = i;
            delete *i;
            break;
        }
    }

    towers_.erase(it_erase);
}

void Player::upgradeTower(Tower& tower){
    if(tower.getUpgradeCost() > wallet_){
        //infrom player can't afford
        return;
    }

    wallet_ -= tower.getUpgradeCost();
    tower.upgradeTower();
}

void Player::updateCastlePosition(sf::Vector2f position){
    position_ = position;
}