#include "tower.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include "enemy.hpp"
#include "projectile.hpp"
#include "game.hpp"
#include <cmath>
// upgradeCost list is redundant if we limit max lvl to be 2
// static int upgradeCost[4] = {150, 200, 250, 300}; //subject to change

Tower::Tower(sf::Vector2f position)
      : type_("Basic"),
        position_(position),
        baseCost_(100), // subject to change
        range_(100.0), // subject to change
        fireRate_(1.0), // subject to change
        damage_(10), // subject to change
        currentLvl_(1),
        upgradeCost_(150), // subject to change, maybe 1.5 * baseCost_?
        damageType_(DamageType::Both),
        lockedEnemy_(nullptr), // initially no locked enemy
        fireTimer_() {}

int Tower::getUpgradeCost() const { // How we should handle when tower is already at maximum lvl, what interface should display? 
  return upgradeCost_[currentLvl_ - 1];   // Maybe something like "Max level reached"
}

void Tower::upgradeTower() { 
  if (currentLvl_ = 1) {
    currentLvl_++;
    damage_ = 1.5 * damage_;
  }
}
// lockOn is redundant in current implementation, will save it up for now. 
void Tower::lockOn(std::shared_ptr<Enemy> enemy) {
  lockedEnemy_ = enemy; 
                       // We have to make sure lockedEnemy_ is set to nullptr or reference to 
                       // another enemy before enemy is destroyed as this will cause memory leak  
                       // otherwise (referring to a deleted object).
                       // another approach could be not to destroy killed enemies until the end 
                       // of the wave; instead we could not be rendering enemies after they reach 0 hp
}

bool Tower::enemyWithinRange(std::shared_ptr<Enemy> enemy) {
  return range_ >= std::sqrt(std::pow((position_.x - enemy->getPosition().x), 2) + std::pow((position_.y - enemy->getPosition().y), 2));
}
Projectile Tower::shoot() {
  /* Assuming speed is 100.0
   * Velocity is calculated in following steps:
   * 1. sf::Vector2f direction = this->position_ - lockedEnemy_->getPosition(); 
   * 2. Next we normalize direction: 
   * 2.1. float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
   * 2.2. sf::Vector2f normalizedDirection = direction / length;
   * 3. sf::Vector2f velocity = normalizedDirection * projectileSpeed;
   * */
  float speed = 100.0; 
  int damage = 10;
  sf::Vector2f direction = this->position_ - lockedEnemy_->getPosition();
  float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  sf::Vector2f normalizedDirection = direction / length;
  sf::Vector2f velocity = normalizedDirection * speed;
  return Projectile(speed, velocity, this->position_, this, this->type_, damage, this->lockedEnemy_);
  /* Prototype implementation for shoot method. 
   * Projectile class has to be adjusted a little bit in order to 
   * finish implementation of shoot(). */
}

/*void Tower::update() { // Redundant in current implementation, will save it up for now
  // Updates tower logic. For example if enemy gets out of range, this method should lockOn to new enemy.
  if (lockedEnemy_ == nullptr) {
    // if no locked enemy looks for an enemy within range
  }
  if (fireTimer_.getElapsedTime().asSeconds() >= 1.0f/fireRate_) {
    shoot();
    fireTimer_.restart();
  }
}*/
void Tower::update(std::list<std::shared_ptr<Enemy>> &enemies, std::list<Projectile> &projectiles) {

}