#include "bulletProjectile.hpp"
#include "game.hpp"
#include <cmath>

bool BulletProjectile::hasHitEnemy(std::shared_ptr<Enemy>& enemy) {

    if(this->getGlobalBounds().intersects(enemy->getGlobalBounds())){
        enemy->takeDamage(this->getDamage());
        std::cout << "hit enemy" << std::endl;
        return true;
    }
    return false;
}
float BulletProjectile::rotationAngle() const {
    return std::atan2(getShootDir().x, getShootDir().y) * (180.f / static_cast<float>(M_PI));
}

//without targetEnemy (makes more sense if bullet can hit any enemy), logic might be clumsy
void BulletProjectile::update(Game& game){
    float dt = game.getTime().asSeconds();
    //only move the projectile if it hasn't collided or gone out of range
    if(distToTower()){
        destroy();
        //out of range
    }
    else{
         for(auto enemy : game.enemies_){
            if(hasHitEnemy(enemy)){
                destroy();
                break;
            }
        }
        if(!isDestroyed()){
            this->move(getShootDir().x * getSpeed() * dt, getShootDir().y * getSpeed() * dt);
        }
    }
}



/*void BulletProjectile::update(Game& game){
    float dt = game.getElapsedTime().asSeconds();
    //only move the projectile if it hasn't collided or gone out of range
    if(hasHitEnemy(targetEnemy_)){
        destroy();
        //has hit an enemy --> fullfilled its purpose
    }
    else{
        if(distToTower()){
            destroy();
            //bullet has gone out of range;
        }
        else{
            this->move(getShootDir().x * getSpeed() * dt, getShootDir().y * getSpeed() * dt);
            //shootDirection dictates towards where, speed how fast, dt makes it consistent across framerates
        }
    }
}*/