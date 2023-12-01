#include "missileProjectile.hpp"
#include "game.hpp"
#include <cmath>

bool MissileProjectile::hasHitEnemy(std::shared_ptr<Enemy>& enemy) {

    if(this->getGlobalBounds().intersects(enemy->getGlobalBounds())){
        enemy->takeDamage(this->getDamage());
        std::cout << "missile hit enemy" << std::endl;
        return true;
    }
    return false;
}

void MissileProjectile::update(Game& game){
    float dt = game.getElapsedTime().asSeconds();
    
    /**
     * for now most of the time results in segfault or bus error if enemy is dead
     * occassionally works tho and prints
    */

    if(targetEnemy_ != nullptr && targetEnemy_.use_count() > 0){ //hasn't been destroyed
        if(hasHitEnemy(targetEnemy_)){
            destroy();
        }
        else{
            sf::Vector2f direction = targetEnemy_->getPosition() - this->getPosition();

             //need to normalise the directional vector to control the speed
            float len = sqrt(pow(direction.x,2)+ pow(direction.y,2));
            if(len != 0){
                direction.x = direction.x / len;
                direction.y = direction.y / len;
            }
            this->move(direction.x * getSpeed() * dt, direction.y * getSpeed() * dt);
        }
    } else{
        destroy();
        std::cout << "target dead, missile destroyed" <<std::endl;
    }
}