#include "bombTower.hpp"
#include "bombProjectile.hpp"
#include "enemy.hpp"
#include <cmath>
#include <memory>

BombTower::BombTower(sf::Vector2f position)
    : Tower(position, "Bomb Tower", 300, 50.0f, 0.4f, 15, 1, 450, CanDamage::Ground, nullptr, sf::Clock(), false) {}
                            //tbd    ^   ^      ^     ^       ^
//since BombTower can only lock on Ground units, update() method has to be overriden

void BombTower::update(std::list<std::shared_ptr<Enemy>> &enemies) {
    auto lockedEnemy = getLockedEnemy();
    if (lockedEnemy == nullptr) {
        for (auto& enemy : enemies) {
            if (enemyWithinRange(enemy) && enemy->type() == EnemyType::Ground) {
                setLockedEnemy(enemy);
                break;
            }

        }
    }
    else {
        if (lockedEnemy->hp() <= 0 || !enemyWithinRange(lockedEnemy)) {
            setLockedEnemy(nullptr);
            for (auto& enemy : enemies) {
                if (enemyWithinRange(enemy) && enemy->type() == EnemyType::Ground) {
                    setLockedEnemy(enemy);
                    break;
                }
            }
        }
    }
}
BombProjectile& BombTower::shoot() {
    sf::Vector2f direction = getPosition() - getLockedEnemy()->getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    BombProjectile* bombProjectile = new BombProjectile(normalizedDirection, getPosition(), getDamage(), getLockedEnemy());
    return *bombProjectile;    
}