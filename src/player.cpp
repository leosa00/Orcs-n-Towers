#include "player.hpp"
#include "resource_container.hpp"

int Player::getWallet() const {
    return wallet_;
}

int Player::getHP() const {
    return hp_;
}

/*std::string Player::getName() const {
    return name_;
}*/

int Player::getLevel() const {
    return level_;
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

/*void Player::addToScore(int amount) {
    score_ += amount;
}*/

void Player::levelUp(){
    level_++;
}

// 
/*void Player::reachedCastle (std::shared_ptr<Enemy>& enemy) {

    if(this->getGlobalBounds().intersects(enemy->getGlobalBounds())){
        enemy->kill(); //this should kill the enemy (at least i hope so :)
        removeHP(10);//should different enemies affect affect differently
    }
}*/

/*std::list<std::shared_ptr<Enemy>> Player::increaseLevel(ResourceContainer<Textures::EnemyID, sf::Texture>& enemytextures, path& path){
    // Increase level, spawn corresponding enemies
    std::list<std::shared_ptr<Enemy>> newround;
    // Create enemies depending on the number of levels
    // NOTE: Probably best to eventually create multiple specific types of enemies in for loops
    // These could also be separate functions which take amount of enemies to be created as an input
    switch (++level_)
    {
    case 1:
    {
        Enemy test(1, 100, EnemyType::Ground, 10, path.getWaypoints());
        test.setPosition(100, 100);
        test.setTexture(enemytextures.get(Textures::Enemy1));

        newround.push_back(std::make_shared<Enemy>(test));

        Enemy test2(30, 60, EnemyType::Flying, 10, path.getWaypoints());
        test2.setPosition(100, 50);
        test2.setTexture(enemytextures.get(Textures::Enemy1));
        newround.push_back(std::make_shared<Enemy>(test2));

        Enemy test3(900, 30, EnemyType::Ground, 10, path.getWaypoints());
        test3.setPosition(100, 70);
        test3.setTexture(enemytextures.get(Textures::Enemy1));
        newround.push_back(std::make_shared<Enemy>(test3));
        break;
    }    
    case 2:
    {
        Enemy test(1, 100, EnemyType::Ground, 10, path.getWaypoints());
        test.setPosition(100, 100);
        test.setTexture(enemytextures.get(Textures::Enemy1));

        newround.push_back(std::make_shared<Enemy>(test));

        Enemy test2(30, 60, EnemyType::Flying, 10, path.getWaypoints());
        test2.setPosition(100, 50);
        test2.setTexture(enemytextures.get(Textures::Enemy1));
        newround.push_back(std::make_shared<Enemy>(test2));

        Enemy test3(900, 30, EnemyType::Ground, 10, path.getWaypoints());
        test3.setPosition(100, 70);
        test3.setTexture(enemytextures.get(Textures::Enemy1));
        newround.push_back(std::make_shared<Enemy>(test3));
        break;
    }
    default:
        break;
    }

    return newround;
    // Create list of shared_ptr<enemy>
    // Push enemies 
}
/*void Player::buyTower (int cost, Textures::TowerID towerID) {
    
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
        /* add to towers_ 
        removeMoney(cost);
        break;

    case Textures::Tower2 :
        /* call right constructor 
        removeMoney(cost);
        break;

    case Textures::Tower3 :
        /* call right constructor 
        removeMoney(cost);
        break;

    case Textures::Tower4 :
        /* call right constructor 
        removeMoney(cost);
        break;
    
    case Textures::Tower5 :
        /* call right constructor 
        removeMoney(cost);
        break;
    
    default:
        /* infrom player of error 
        break;
    }
}

void Player::sellTower(Tower& tower){
    auto it_erase = towers_.end();

    for(auto i = towers_.begin(); i != towers_.end(); i++){
        //if pointer of i and addr of tower match -> same object
        if(*i == std::addressof(tower)){
            //find same object, add its cost to wallet (full cost or only partial?), delete object and remove it from the vector
            wallet_ += (*i)->getBaseCost();
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
}*/

/*void Player::updateCastlePosition(sf::Vector2f position){
    position_ = position;
    this->setPosition(position);
}*/