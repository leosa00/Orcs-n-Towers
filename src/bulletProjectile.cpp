#include "bulletProjectile.hpp"

bool BulletProjectile::hasHitEnemy(std::shared_ptr<Enemy> enemy) {

    if(this.getGlobalBounds().intersects(enemy.getGlobalBounds())){
        enemy.takeDamage(this.getDamage());
        return true;
    }
    return false;
}

void BulletProjectile::update(float dt, std::list<std::shared_ptr<Enemy>>& Enemies){
    //only move the projectile if it hasn't collided or gone out of range
    if(hasHitEnemy(targetEnemy_)){
        delete this;
        //has hit an enemy --> fullfilled its purpose
    }
    else{
        if(distToTower()){
            delete this;
            //bullet has gone out of range;
        }
        else{
            this.move(getShootDir().x * speed_ * dt, getShootDir().y * speed_ * dt);
            //shootDirection dictates towards where, speed how fast, dt makes it consistent across framerates
        }
    }
}

