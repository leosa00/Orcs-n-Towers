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

int Projectile::getDamage() const {
    return damage_;
}

sf::Vector2f Projetile::getShootDir() const {
    return shootDirection;
}

bool Projectile::distToTower() {
    sf::Vector2f currPos = this.getPosition(); //function from transformable class

    double dist = sqrt(pow((position_.x - currPos.x),2) + pow((position_.y - currPos.y),2))

    if(dist >= maxDistance_) //need to determine some reasonable distance from the tower
    {
        return true;
    }
    return false;
}

/*void Projectile::shootDirection() {
    sf::Vector2f direction = targetEnemy_.getPosition() - position_;

    //need to normalise the directional vector to control the speed
    float len = sqrt(pow(direction.x,2)+ pow(direction.y,2));
    if(len != 0){
        direction.x = direction.x / len;
        direction.y = direction.y / len;
    }

    direction *= velocity_;

    shootDirection_ = direction;
}

sf::Vector2f Projectile::getDirection(){
    return shootDirection_;
}*/