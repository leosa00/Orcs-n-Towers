#include "freezingTower.hpp"
#include <iostream>

FreezingTower::FreezingTower(sf::Vector2f position)
    : Tower(position, "Freezing Tower", 350, 300.f, sf::seconds(2), 0, 1, 475, nullptr, false) {}

void FreezingTower::update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) {
    updateFireTimer(time);
    lockedEnemies_.clear();
    setLockedEnemy(nullptr);
    for (std::shared_ptr<Enemy> enemy : enemies) {
        if (enemyWithinRange(enemy)) {
            lockedEnemies_.push_back(enemy);
        }
    }
    if (!lockedEnemies_.empty()) {
        setLockedEnemy(*(lockedEnemies_.begin()));
    }
}

Projectile* FreezingTower::shoot() {
    for (std::shared_ptr<Enemy> enemy : lockedEnemies_) {
        enemy->applySlowed(sf::seconds(1.5), slowCoefficient_);
    }
    return nullptr;
}

void FreezingTower::upgradeTower() {
    int currentLvl = getCurrentLvl();
    if (currentLvl == 1) {
        setLevel(2);
        slowCoefficient_ = 1.5 * slowCoefficient_;
        setMaxLevelFlag();
    }
}