#include "projectile.hpp"
#include <cmath>

double Projectile::getSpeed() const {
    return speed_;
}

sf::Vector2f Projectile::getVelocity() const {
    return velocity_,;
}

Tower* Projectile::getOwner() const{
    return owner_;
}

std::string& Projectile::getType() const {
    return type_;
}

void Projectile::dealDamage(Enemy& enemy){
    //get access to enemies hp and reduct projectiles damage
}

void Projectile::distToTower() {
    sf::Vector2f pPos = this.getPosition(); //function from transformable class
    sf::Vector2f tPos = owner_.getPosition();

    double dist = sqrt(pow((tPos.x - pPos.x),2) + pow((tPos.y - pPos.y),2))

    if(dist > 10) //need to determine some reasonable distance from the tower
    {
        delete this;
    }
}