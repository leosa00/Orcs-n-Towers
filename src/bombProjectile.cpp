#include "bombProjectile.hpp"

bool BombProjectile::hasHitEnemy(std::shared_ptr<Enemy> enemy){
    sf::Vector2f currPos = this.getPosition(); //function from transformable class

    double dist = sqrt(pow((enemy.getPosition().x - currPos.x),2) + pow((enemy.getPosition().y - currPos.y),2))

    if(dist <= blastRange_)
    {
        enemy.takeDamage(this.getDamage());
        return true;
    }
    return false;
}

void BombProjectile::update(float dt, std::list<std::shared_ptr<Enemy>>& Enemies){
    //bomb should stop moving at a certain distance
        if(distToTower()){
            //has reached "landing spot"
            //"detonates" <-- should there be some kind of animation?
            //checks all of the enemies within its range and cause damage to them
            for(auto enemy : Enemies){
                hasHitEnemy(enemy);
            }
            //fullfilled it's purpose
            delete this;
        }
        else{
            this.move(getShootDir().x * speed_ * dt, getShootDir().y * speed_ * dt);
            //shootDirection dictates towards where, speed how fast, dt makes it consistent across framerates
        }
}