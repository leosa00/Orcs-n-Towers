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

/*void Projectile::dealDamage(Enemy& enemy){
    //get access to enemies hp and reduct projectiles damage
}*/

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

bool Projectile::collision(Enemy& enemy) {

    if(this.getGlobalBounds().intersects(enemy.getGlobalBounds())){
        enemy.takeDamage(this.getDamage());
        Player::addToWallet() //send enemy worth as param
        delete this;
        return true;
    }
    return false;
}

void Projectile::shootDirection(Enemy& enemy) {
    sf::Vector2f direction = enemy.getPosition() - position_;

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
}

void Projectile::update(float dt, Enemy& enemy){
    //only move the projectile if it hasn't collided or gone out of range
    if(!collision(enemy)){
        if(!distToTower()){
            this.move(getDirection()*dt)
        }
    }
}