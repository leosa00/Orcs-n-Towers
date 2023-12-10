#include "bulletTower.hpp"
#include "bulletProjectile.hpp"
#include "tower.hpp"
#include <cmath>
#include <memory>

BulletTower::BulletTower(sf::Vector2f position)
    : Tower(position, "Bullet Tower", 200, 300.f, sf::seconds(1), 15, 1, 300, nullptr, false) {}
                                // tbd ^    ^      ^     ^      ^      ^
                                //          range should be somewhat concise with BulletProjectile's maxDistance.
BulletProjectile* BulletTower::shoot() {
    sf::Vector2f direction = getLockedEnemy()->getPosition() - getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    BulletProjectile* bulletProjectile = new BulletProjectile(normalizedDirection, getPosition(), getDamage(), getRange() + 20);
    return bulletProjectile;
}
