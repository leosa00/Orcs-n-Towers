#include "enemy.hpp"
#include <string>
#include "game.hpp"
#include "player.hpp"
#include <cmath>
#include <memory>
#include <iostream>
void Enemy::moveEnemy(sf::Vector2f movement) { 
    this->move(movement);
    //add more implementations for moving other textures
}
//get time variable from game::getTime() function
void Enemy::update(sf::Time time) {
	sf::Vector2f movement = velocity_ * time.asSeconds();

    if (slowed_ > 0) {
        //the actual amount the enemy is slowed will be tweaked, for now it is 0.2 f
        movement -= velocity_ * 0.002f * time.asSeconds();
    }
	
	moveEnemy(movement);
    //std::cout << speed_;
	if (isWaypointPassed(movement))
	{
		findNewWaypoint();
		setVelocity();
	}
    //applySlowed(100);
    slowedDamage();
    //std::cout << dead_ << std::endl;
    //poisonDamage();

}
//checks if the current way point has been passed, returns trur
//if it has otherwise false
bool Enemy::isWaypointPassed(sf::Vector2f movement) {
    // Check if the enemy has crossed the waypoint's x-coordinate (for horizontal movement)
    if (velocity_.x != 0) {
        if ((velocity_.x > 0 && getCenter().x + movement.x >= currentWaypoint_.x) ||
            (velocity_.x < 0 && getCenter().x + movement.x <= currentWaypoint_.x)) {
            return true;
        }
    }

    // Check if the enemy has crossed the waypoint's y-coordinate (for vertical movement)
    if (velocity_.y != 0) {
        if ((velocity_.y > 0 && getCenter().y + movement.y >= currentWaypoint_.y) ||
            (velocity_.y < 0 && getCenter().y + movement.y <= currentWaypoint_.y)) {
            return true;
        }
    }

    return false;
}


sf::Vector2f Enemy::getCenter()
{
	sf::Vector2f enemyCenter;
	enemyCenter.x = this->getPosition().x + this->getGlobalBounds().width / 2;
	enemyCenter.y = this->getPosition().y + this->getGlobalBounds().height / 2;

	return enemyCenter;
}

void Enemy::setVelocity() {

    sf::Vector2f distance;
	distance = currentWaypoint_ - getCenter();

	velocity_.x = distance.x * speed_ / fabs(distance.x + distance.y);
	velocity_.y = distance.y * speed_ / fabs(distance.x + distance.y);

	if (fabs(velocity_.x) > fabs(velocity_.y))
	{
		if (velocity_.x > 0)
		{
			velocity_.x = speed_;
			velocity_.y = 0.f;
			direction_ = 2;
		}
		else
		{
			velocity_.x = -speed_;
			velocity_.y = 0.f;
			direction_ = 1;
		}
	}
	else
	{
		if (velocity_.y > 0)
		{
			velocity_.x = 0.f;
			velocity_.y = speed_;
			direction_ = 0;
		}
		else
		{
			velocity_.x = 0.f;
			velocity_.y = -speed_;
			direction_ = 3;
		}
	}

}

sf::Vector2f Enemy::getLocation() {
    return this->getPosition();
}

void Enemy::findNewWaypoint() {
    if (!waypoints_.empty()) {
        waypoints_.pop();
        if (!waypoints_.empty()) {
            currentWaypoint_ = waypoints_.front();
        } else {
            dead_ = true; // Mark the enemy as dead
        }
    }
}


bool Enemy::dead() {
    return dead_;
}
int Enemy::hp() {
    return hp_;
}

float Enemy::speed() {
    return speed_;
}

EnemyType Enemy::type() {
    return type_;
}

int Enemy::poisonStatus() {
    return poison_;
}

int Enemy::slowedStatus() {
    return slowed_;
}

void Enemy::kill() {
    if(!dead_) {
        dead_ = true;
    }
}

void Enemy::takeDamage(int damage) {
    if (dead_) {
        return;
    }
    if(damage >= hp_) {
        kill();
        return;
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
    }
}

void Enemy::slowedDamage() {
    if(slowed_ > 0) {
        slowed_-=1;
    } else {
        speed_=actualSpeed_;
    }
}
