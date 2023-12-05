#include "tower.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include "enemy.hpp"
#include "projectile.hpp"
#include "game.hpp"
#include <cmath>
#include <memory>
#include <iostream>
// upgradeCost list is redundant if we limit max lvl to be 2
// static int upgradeCost[4] = {150, 200, 250, 300}; //subject to change

/*Tower::Tower(const std::string& type = "Basic", sf::Vector2f position, int baseCost = 100, float range = 100.0, float fireRate = 1.0,
              int damage = 10, int currentLvl = 1, int upgradeCost = 150, CanDamage damageType = CanDamage::Both, std::shared_ptr<Enemy> lockedEnemy = nullptr,
              sf::Clock fireTimer, bool maxLevelReached = false)
              : type_(type), 
                position_(position),
                baseCost_(baseCost),
                range_(range),
                fireRate_(fireRate),
                damage_(damage),
                currentLvl_(currentLvl),
                upgradeCost_(upgradeCost),
                damageType_(damageType),
                lockedEnemy_(lockedEnemy),
                fireTimer_(fireTimer),
                maxLevelReached_(maxLevelReached) {} */

Tower::Tower(sf::Vector2f position, const std::string& type,  int baseCost, float range, float fireRate,
          int damage, int currentLvl, int upgradeCost, CanDamage damageType, std::shared_ptr<Enemy> lockedEnemy,
          sf::Clock fireTimer, bool maxLevelReached)
      : type_(type),
        baseCost_(baseCost), // subject to change
        range_(range), // subject to change
        fireRate_(fireRate), // subject to change
        damage_(damage), // subject to change
        currentLvl_(currentLvl),
        upgradeCost_(upgradeCost), // subject to change, maybe 1.5 * baseCost_?
        damageType_(damageType),
        lockedEnemy_(lockedEnemy), // initially no locked enemy
        fireTimer_(fireTimer),
        maxLevelReached_(maxLevelReached) {
          setPosition(position);
        }

/*int Tower::getUpgradeCost() const { // How we should handle when tower is already at maximum lvl, what interface should display? 
  return upgradeCost_[currentLvl_ - 1];   // Maybe something like "Max level reached"
}*/

// upgradeTower()
void Tower::upgradeTower() { 
  if (currentLvl_ == 1) {
    currentLvl_++;
    damage_ = 1.5 * damage_;
    if (currentLvl_ == TOWER_MAX_LVL) {
      maxLevelReached_ = true;
    }
  }
}


bool Tower::enemyWithinRange(std::shared_ptr<Enemy> enemy) {
  //std::cout << "enemyWithinRange is called" << std::endl;
  //std::cout << range_ << std::endl;
  //std::cout << std::sqrt(std::pow((position_.x - enemy->getPosition().x), 2) + std::pow((position_.y - enemy->getPosition().y), 2)) << std::endl;
  
  // LINE UNDER USES GLOBAL POS
  //return range_ >= std::sqrt(std::pow((position_.x - enemy->getPosition().x), 2) + std::pow((position_.y - enemy->getPosition().y), 2));

  return range_ >= std::sqrt(std::pow((getPosition().x - enemy->getPosition().x), 2) + std::pow((getPosition().y - enemy->getPosition().y), 2));
}
/* Projectile& Tower::shoot() {
     Assuming speed is 100.0
   * Velocity is calculated in following steps:
   * 1. sf::Vector2f direction = this->position_ - lockedEnemy_->getPosition(); 
   * 2. Next we normalize direction: 
   * 2.1. float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
   * 2.2. sf::Vector2f normalizedDirection = direction / length;
   * 3. sf::Vector2f velocity = normalizedDirection * projectileSpeed;
   * 
  sf::Vector2f direction = this->position_ - lockedEnemy_->getPosition();
  float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  sf::Vector2f normalizedDirection = direction / length; //I am assuming here you want normalized direction
  Projectile* projectile = new Projectile(normalizedDirection, position_, *this, damage_);
  return *projectile;
     Prototype implementation for shoot method. 
   * Projectile class has to be adjusted a little bit in order to 
   * finish implementation of shoot(). 
} */

void Tower::update(std::list<std::shared_ptr<Enemy>> &enemies) { 
    auto lockedEnemy = getLockedEnemy();
    if (lockedEnemy == nullptr || lockedEnemy->dead() || !enemyWithinRange(lockedEnemy)) {
        setLockedEnemy(nullptr);
        float highestSpeed = 0.f; //added logic for prioritazing enemies moving at higher speeds
        for (std::shared_ptr<Enemy>& enemy : enemies) {
            if (enemyWithinRange(enemy) && !enemy->dead()) {
                if (highestSpeed < enemy->speed()) {
                  highestSpeed = enemy->speed();
                  setLockedEnemy(enemy);
                  std::cout << "Some enemy was locked" << std::endl;
                }
            }
        }
    }
  /*auto lockedEnemy = getLockedEnemy();
  if (lockedEnemy == nullptr) {
    for (auto& enemy : enemies) {
      if (enemyWithinRange(enemy) && !enemy->dead()) {
        setLockedEnemy(enemy);
        std::cout << "Some enemy was locked" << std::endl;
        break;
      }
    }
  }
  else {
    if (lockedEnemy->dead() || !enemyWithinRange(lockedEnemy)) {
      setLockedEnemy(nullptr);
      for (auto& enemy : enemies) {
        if (enemyWithinRange(enemy) && !enemy->dead()) {
          setLockedEnemy(enemy);
          std::cout << "Some enemy was locked" << std::endl;
          break;
        }
      }
    }
  } */
}


bool Tower::isActive()
{
    return HUDactive;
}

void Tower::activateHUD()
{
    HUDactive = true;
}

void Tower::unactiveHUD()
{
    HUDactive = false;
}

void Tower::build()
{
    builded = true;
}

sf::Vector2f Tower::getSize()
{
    sf::Vector2f size;
    size.x = this->getGlobalBounds().width;
    size.y = this->getGlobalBounds().height;
    return size;
}
