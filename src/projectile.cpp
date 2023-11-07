#include "projectile.hpp"

double Projectile::getSpeed() const {
    return speed_;
}

sf::Vector2f Projectile::getVelocity() const {
    return velocity_,;
}

Tower* Projectile::getOwner() const{
    return owner_;
}

std::string& getType() const {
    return type_;
}

void Projectile::dealDamage(Enemy* enemy){
    //get access to enemies hp and reduct projectiles damage
}