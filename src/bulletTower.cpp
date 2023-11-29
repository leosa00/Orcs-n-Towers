#include "bulletTower.hpp"
#include "bulletProjectile.hpp"
#include "tower.hpp"
#include <cmath>
#include <memory>

BulletTower::BulletTower(sf::Vector2f position)
    : Tower(position, "Bullet Tower", 200, 100.0f, 0.5f, 15, 1, 300, CanDamage::Both, nullptr, sf::Clock(), false) {}
                                // tbd ^    ^      ^     ^      ^      ^

BulletProjectile& BulletTower::shoot() {
    sf::Vector2f direction = getPosition() - getLockedEnemy()->getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    BulletProjectile* bulletProjectile = new BulletProjectile(normalizedDirection, getPosition(), getDamage());
    return *bulletProjectile;
}