#include "missileTower.hpp"
#include "missileProjectile.hpp"
#include "tower.hpp"
#include <cmath>
#include <memory>

MissileTower::MissileTower(sf::Vector2f position)
    : Tower(position, "Missile Tower", 200, 1000.0f, 0.2f, 30, 1, 300, CanDamage::Both, nullptr, sf::Clock(), false) {}

MissileProjectile& MissileTower::shoot() {
    sf::Vector2f direction = getLockedEnemy()->getPosition() - getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = direction / length;
    MissileProjectile* missileProjectile = new MissileProjectile(getPosition(), getDamage(), getLockedEnemy());
    return *missileProjectile;
}

std::shared_ptr<Tower> MissileTower::getClassObject()
{
    sf::Vector2f defaultPosition(0.0f, 0.0f);
    std::shared_ptr<Tower> obj = std::make_shared<MissileTower>(defaultPosition);

    return obj;
}