#include "bombTower.hpp"
#include "bombProjectile.hpp"
#include "enemy.hpp"
#include <cmath>
#include <memory>
#include <iostream>

BombTower::BombTower(sf::Vector2f position)
    : Tower(position, "Bomb Tower", 300, 200.0f, sf::seconds(1.5), 15, 1, 450, nullptr, false) {}
                            //tbd    ^   ^      ^     ^       ^
//since BombTower can only lock on Ground units, update() method has to be overriden

void BombTower::update(std::list<std::shared_ptr<Enemy>> &enemies, sf::Time time) {
    updateFireTimer(time);
    auto lockedEnemy = getLockedEnemy();
    if (lockedEnemy == nullptr || lockedEnemy->dead() || !enemyWithinRange(lockedEnemy)) {
        setLockedEnemy(nullptr);
        float highestSpeed = 0.f;
        for (std::shared_ptr<Enemy>& enemy : enemies) {
            if (enemyWithinRange(enemy) && enemy->type() == EnemyType::Ground && !enemy->dead()) {
                highestSpeed = enemy->speed();
                setLockedEnemy(enemy);
                std::cout << "Some enemy was locked" << std::endl;
            }
        }
    }   
}
BombProjectile* BombTower::shoot() {
    sf::Vector2f direction = getLockedEnemy()->getPosition() - getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    BombProjectile* bombProjectile = new BombProjectile(normalizedDirection, getPosition(), getDamage(), getRange()/2);
    return bombProjectile;    
}
