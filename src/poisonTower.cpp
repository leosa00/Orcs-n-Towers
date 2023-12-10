#include "poisonTower.hpp"
#include <iostream>

PoisonTower::PoisonTower(sf::Vector2f position)
    : Tower(position, "Poison Tower", 350, 300.f, sf::seconds(2.2), 3, 1, 475, CanDamage::Both, nullptr, false) {}

void PoisonTower::update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) {
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

Projectile* PoisonTower::shoot() {
    for (std::shared_ptr<Enemy> enemy : lockedEnemies_) {
        enemy->applyPoison(3, getDamage());
    }
    return nullptr;
}