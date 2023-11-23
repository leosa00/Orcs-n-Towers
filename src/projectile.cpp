#include "projectile.hpp"
#include <cmath>

float Projectile::getSpeed() const {
    return speed_;
}

sf::Vector2f Projectile::getVelocity() const {
    // This implementation mimics calculating of velocity in Tower::shoot()
    // Assumes the direction vector is normalized
    return shootDirection_ * speed_;
}

Tower& Projectile::getOwner() const{
    return owner_;
}

//std::string& Projectile::getType() const {
//    return type_;
//}

int Projectile::getDamage() const {
    return damage_;
}

sf::Vector2f Projectile::getShootDir() const {
<<<<<<< Updated upstream
    return shootDirection_;
=======
    return shootDirection;
>>>>>>> Stashed changes
}

bool Projectile::distToTower() {
    sf::Vector2f currPos = getPosition(); //function from transformable class
    // Inheriting both transformable and sprite leads to conflicts according to my editor, as both classes have getPosition()
    // I am not sure why or how this even happeens as sprite inherits the method from transformable -Otto

    double dist = sqrt(pow((position_.x - currPos.x),2) + pow((position_.y - currPos.y),2));

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