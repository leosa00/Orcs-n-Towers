#include "enemy.hpp"
#include <string>
#include <cmath>

// Sprite has move with essentially this exact implementation
//void Enemy::move(sf::vector2f movement){//Implement a function that allows the sprite to move
////update the state of the enemy with relation to the game
//    sprite.move(movement);
//    //add more implementations for moving other textures
//}

void Enemy::update() {
//game based reference to the time, use this with velocity
//use movement function to move the enemy taking the distance 
//moved based on time and velocity calculation 
    float timeVariable; //this is just a placeholder varaible for the time
//variable derived from the game instance
    sf::Vector2f movement = velocity_ * timeVariable; //enemy velocity variable
    //is multiplied by the derived time variable
    //will add a way to change movement based on if the character is slowed
    move(movement);

}

sf::Vector2f Enemy::getCenter()
{
	sf::Vector2f enemyCenter;
	enemyCenter.x = getPosition().x + getGlobalBounds().width / 2;
	enemyCenter.y = getPosition().y + getGlobalBounds().height / 2;

	return enemyCenter;
}


//checks if the current way point has been passed, returns trur
//if it has otherwise false
bool Enemy::isWaypointPassed(sf::Vector2f movement) {

    float currentDistance = std::abs(getCenter().x - currentWaypoint_->x) + 
		fabs(getCenter().y - currentWaypoint_->y);
    

    float nextDistance = fabs(getCenter().x + movement.x - currentWaypoint_->x) +
		fabs(getCenter().y + movement.y - currentWaypoint_->y);

    if (nextDistance < currentDistance) {
        return false;
    } else {
        return true;
    }
}

// Sprite has setTexture
//void Enemy::setTexture(sf::Texture * texture)
//{
//	sprite_.setTexture(*texture);
//}

// Sprite handles drawing
//void Enemy::draw(sf::RenderTarget & target) const {
//    target.draw(sprite_);
//}

// Sprite has getPosition()
//sf::Vector2f Enemy::getLocation() {
//    return sprite_.getPosition();
//}

// Sprite has getGlobalBounds()
//sf::FloatRect Enemy::getGlobalBounds()
//{
//	return sprite_.getGlobalBounds();
//}

void Enemy::setVelocity() {

    sf::Vector2f distance;
	distance = *currentWaypoint_ - getCenter();

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

int Enemy::hp() {
    return hp_;
}

int Enemy::speed() {
    return speed_;
}

/*type Enemy::type() {
    return type_;
}*/

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