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

bool Projectile::distToTower() {
    sf::Vector2f pPos = this.getPosition(); //function from transformable class
    sf::Vector2f tPos = owner_.getPosition();

    double dist = sqrt(pow((tPos.x - pPos.x),2) + pow((tPos.y - pPos.y),2))

    if(dist > 10) //need to determine some reasonable distance from the tower
    {
        delete this;
        return true;
    }
    return false;
}

bool Projectile::collision() {

    if(this.getGlobalBounds().intersects(targetEnemy_.getGlobalBounds())){
        targetEnemy_.takeDamage(this.getDamage());
        //Player::addToWallet() //send enemy worth as param
        delete this;
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

void Projectile::update(float dt){
    //only move the projectile if it hasn't collided or gone out of range
    if(!collision()){
        if(!distToTower()){
            this.move(shootDirection_.x * speed_ * dt, shootDirection_.y * speed_ * dt);
            //shootDirection dictates towards where, speed how fast, dt makes it consistent across framerates
        }
    }
}