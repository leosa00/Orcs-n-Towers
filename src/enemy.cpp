#include "enemy.hpp"
#include <string>

Enemy::Enemy(int hp, float speed, EnemyType type, int gold)
    :hp_(hp), speed_(speed), type_(type), goldWorth_(gold), setVelocity(), findNewWaypoint() {}


void Enemy::move(sf::vector2f movement){
    this->move(movement);
    //add more implementations for moving other textures
}
void Enemy::update() {
    time = game::getTime();
	sf::Vector2f movement = velocity_*time.asSeconds();

    if (slowed_ > 0) {
        //the actual amount the enemy is slowed will be tweaked, for now it is 0.2 f
        movement -= velocity_ * 0.2f * time.asSeconds();
    }
	
	move(movement);

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

//void Enemy::setTexture(sf::Texture * texture)
//{
//	sprite_.setTexture(*texture);
//}

//void Enemy::draw(sf::RenderTarget & target) const {
//    target.draw(sprite_);
//}

//sf::Vector2f Enemy::getLocation() {
//    return sprite_.getPosition();
//}

//sf::FloatRect Enemy::getGlobalBounds()
//{
//	return sprite_.getGlobalBounds();
//}

sf::Vector2f Enemy::getCenter()
{
	sf::Vector2f enemyCenter;
	enemyCenter.x = sprite_.getPosition().x + sprite_.getGlobalBounds().width / 2;
	enemyCenter.y = sprite_.getPosition().y + sprite_.getGlobalBounds().height / 2;

	return enemyCenter;
}

void Enemy::setVelocity() {

    sf::Vector2f distance;
	distance = *currentWaypoint - getCenter();

	velocity.x = distance.x * speed_ / fabs(distance.x + distance.y);
	velocity.y = distance.y * speed_ / fabs(distance.x + distance.y);

	if (fabs(velocity.x) > fabs(velocity.y))
	{
		if (isPositive(velocity.x))
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
		if (isPositive(velocity.y))
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
    dead_ = true;
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
