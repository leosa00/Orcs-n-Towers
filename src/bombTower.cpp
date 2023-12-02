#include "bombTower.hpp"
#include "bombProjectile.hpp"
#include "enemy.hpp"
#include <cmath>
#include <memory>
#include <iostream>

BombTower::BombTower(sf::Vector2f position)
    : Tower(position, "Bomb Tower", 300, 500.0f, 0.4f, 15, 1, 450, CanDamage::Ground, nullptr, sf::Clock(), false) {}
                            //tbd    ^   ^      ^     ^       ^
//since BombTower can only lock on Ground units, update() method has to be overriden

void BombTower::update(std::list<std::shared_ptr<Enemy>> &enemies) {
    auto lockedEnemy = getLockedEnemy();
    if (lockedEnemy == nullptr) {
        for (auto& enemy : enemies) {
            if (enemyWithinRange(enemy) && enemy->type() == EnemyType::Ground) {
                setLockedEnemy(enemy);
                std::cout << "Some enemy was locked" << std::endl;
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
                    std::cout << "Some enemy was locked" << std::endl;
                    break;
                }
            }
        }
    }
}
BombProjectile& BombTower::shoot() {
    sf::Vector2f direction = getLockedEnemy()->getPosition() - getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    BombProjectile* bombProjectile = new BombProjectile(normalizedDirection, getPosition(), getDamage());//, getLockedEnemy())
    // Constructor for BombProjectile does not accept shared_ptr<Enemy> as input...
    return *bombProjectile;    
}

std::shared_ptr<Tower> BombTower::getClassObject()
{
    sf::Vector2f defaultPosition(0.0f, 0.0f);  // You can change the default position as needed
    std::shared_ptr<Tower> obj = std::make_shared<BombTower>(defaultPosition);

    return obj;
}