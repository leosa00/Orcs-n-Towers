#include "enemy.hpp"
#include <string>

void Enemy::move()//Implement a function that allows the sprite to move
//update the state of the enemy with relation to the game
void Enemy::update() {
//game based reference to the time, use this with velocity
//use movement function to move the enemy taking the distance 
//moved based on time and velocity calculation 
    float timeVariable //this is just a placeholder varaible for the time
//variable derived from the game instance
    sf::Vector2f movement = velocity_ * timeVariable; //enemy velocity variable
    //is multiplied by the derived time variable
    //will add a way to change movement based on if the character is slowed
    move(movement)

}
//checks if the current way point has been passed, returns trur
//if it has otherwise false
bool isWaypointPassed(sf::Vector2f movement) {

    float currentDistance = fabs(getCenter().x - currentWaypoint->x) + 
		fabs(getCenter().y - currentWaypoint->y);
    

    float nextDistance = fabs(getCenter().x + movement.x - currentWaypoint->x) +
		fabs(getCenter().y + movement.y - currentWaypoint->y);

    if (nextDistance < currentDistance) {
        return false;
    } else {
        return true;
    }
}
int Enemy::hp() {
    return hp_;
}

int Enemy::speed() {
    return speed_;
}

std::string Enemy::type() {
    return type_;
}

int Enemy::poisonStatus() {
    return poison_;
}

int Enemy::slowedStatus() {
    return slowed_;
}

void Enemy::kill() {
    //need to implement a way to deposite money to the players wallet
    //based on the goldWorth of the enemy
    this->~monster()
}

void Enemy::takeDamage(int damage) {
    if(damage >= hp_) {
        kill();
    } else {
        hp_ -= damage;
    }
}

void Enemy::applyPoison(int duration) {
    if(poison_ == 0) {
        poison_+=duration;
    }

}

void Enemy::poisonDamage() {
    if(poison_ > 0) {
        takeDamage(1);
        poison_-=1;
    }
}

void Enemy::applySlowed(int duration) {
    if(slowed_ == 0) {
        slowed_+=duration;
        speed_-=2;
    }
}

void Enemy::slowedDamage() {
    if(slowed_ > 0) {
        slowed_-=1;
    } else {
        speed_+=2;
    }
}