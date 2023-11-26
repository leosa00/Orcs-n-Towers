#include "enemy.hpp"
#include <string>
#include "game.hpp"
#include "player.hpp"
#include <cmath>

void Enemy::moveEnemy(sf::Vector2f movement) { 
    this->move(movement);
    //add more implementations for moving other textures
}
//get time variable from game::getTime() function
void Enemy::update(sf::Time time) {
	sf::Vector2f movement = velocity*time.asSeconds();

    if (slowed_ > 0) {
        //the actual amount the enemy is slowed will be tweaked, for now it is 0.2 f
        movement -= velocity * 0.2f * time.asSeconds();
    }
	
	moveEnemy(movement);

	if (isWaypointPassed(movement))
	{
		findNewWaypoint();
		setVelocity();
	}
    slowedDamage();
    poisonDamage();

}
//checks if the current way point has been passed, returns trur
//if it has otherwise false
bool Enemy::isWaypointPassed(sf::Vector2f movement) {

    float currentDistance = fabs(getCenter().x - currentWaypoint_.x) + 
		fabs(getCenter().y - currentWaypoint_.y);
    

    float nextDistance = fabs(getCenter().x + movement.x - currentWaypoint_.x) +
		fabs(getCenter().y + movement.y - currentWaypoint_.y);

    if (nextDistance < currentDistance) {
        return false;
    } else {
        return true;
    }
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

	velocity.x = distance.x * speed_ / fabs(distance.x + distance.y);
	velocity.y = distance.y * speed_ / fabs(distance.x + distance.y);

	if (fabs(velocity.x) > fabs(velocity.y))
	{
		if (velocity.x > 0)
		{
			velocity.x = speed_;
			velocity.y = 0.f;
			direction_ = 2;
		}
		else
		{
			velocity.x = -speed_;
			velocity.y = 0.f;
			direction_ = 1;
		}
	}
	else
	{
		if (velocity.y > 0)
		{
			velocity.x = 0.f;
			velocity.y = speed_;
			direction_ = 0;
		}
		else
		{
			velocity.x = 0.f;
			velocity.y = -speed_;
			direction_ = 3;
		}
	}

}

sf::Vector2f Enemy::getLocation() {
    return this->getPosition();
}

void Enemy::findNewWaypoint() {
	waypoints_.pop();
	currentWaypoint_ = waypoints_.front();
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
        player_.addMoney(goldWorth_);
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
