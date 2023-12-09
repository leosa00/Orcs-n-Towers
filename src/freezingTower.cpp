#include "freezingTower.hpp"
#include <iostream>

FreezingTower::FreezingTower(sf::Vector2f position)
    : Tower(position, "Freezing Tower", 350, 300.f, 0.4f, 5, 1, 475, CanDamage::Both, nullptr, sf::Clock(), false) {}

void FreezingTower::update(std::list<std::shared_ptr<Enemy>> &enemies) {
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
        enemy->takeDamage(getDamage());
        enemy->applySlowed(5000); // argument needs to be changed (most likely)
    }
    return nullptr;
}