#include "tower.hpp"
#include <SFML/System/Vector2.hpp>

static int upgradeCost[4] = {150, 200, 250, 300}; //subject to change

Tower::Tower(sf::Vector2f position)
      : type_("Basic tower"),
        position_(position),
        baseCost_(100), // subject to change
        range_(100.0), // subject to change
        fireRate_(1.0), // subject to change
        currentLvl_(1),
        upgradeCost_(upgradeCost),
        lockedEnemy_(nullptr) {}

int Tower::getUpgradeCost() const { // How we should handle when tower is already at maximum lvl, what interface should display? 
  return upgradeCost_[currentLvl_ - 1];   // Maybe something like "Max level reached"
}

void Tower::upgradeTower() {
  if (currentLvl_ < 5) {
    currentLvl_++;
  }
}
void Tower::lockOn(const Enemy& enemy) {
  lockedEnemy_(enemy); // We have to make sure lockedEnemy_ is set to nullptr or reference to 
                       // another enemy before enemy is destroyed as this will cause memory leak  
                       // otherwise (referring to a deleted object).
}
void Tower::shoot() {
  // Ch
}