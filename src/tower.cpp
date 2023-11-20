#include "tower.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include "enemy.hpp"
#include "projectile.hpp"
#include "game.hpp"

static int upgradeCost[4] = {150, 200, 250, 300}; //subject to change

Tower::Tower(sf::Vector2f position)
      : type_("Basic tower"),
        position_(position),
        baseCost_(100), // subject to change
        range_(100.0), // subject to change
        fireRate_(1.0), // subject to change
        currentLvl_(1),
        upgradeCost_(upgradeCost),
        lockedEnemy_(nullptr) {} // initially no locked enemy

int Tower::getUpgradeCost() const { // How we should handle when tower is already at maximum lvl, what interface should display? 
  return upgradeCost_[currentLvl_ - 1];   // Maybe something like "Max level reached"
}

void Tower::upgradeTower() {
  if (currentLvl_ < 5) {
    currentLvl_++;
  }
}
void Tower::lockOn(const Enemy& enemy) {
  lockedEnemy_ = enemy; // We have to make sure lockedEnemy_ is set to nullptr or reference to 
                       // another enemy before enemy is destroyed as this will cause memory leak  
                       // otherwise (referring to a deleted object).
                       // another approach could be not to destroy killed enemies until the end 
                       // of the wave; instead we could not be rendering enemies after they reach 0 hp
}
void Tower::shoot() {
  // This method creates a projectile that flies towards locked enemy
  // This projectile has to be appended to Game::std::list<Projectile> projectiles_.
}

void Tower::update() {
  // Updates tower logic. For example if enemy gets out of range, this method should lockOn to new enemy.
  if (lockedEnemy_ == nullptr) {
    // if no locked enemy looks for an enemy within range
  }
  if (fireTimer_.getElapsedTime().asSeconds() >= 1.0f/fireRate_) {
    shoot();
    fireTimer_.restart();
  }
}