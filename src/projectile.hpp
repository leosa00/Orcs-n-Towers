#ifndef PROJECTILE
#define PROJECTILE

#include "tower.hpp"
//#include <SFML/System/Vector2.hpp>

class Projectile
{
    private:
        double speed_;
        sf::Vector2f velocity_;
        sf::Vector2f position_;
        Tower* owner_;
        std::string type_;
        int damage_;
    public:
        Projectile(Tower* owner) : speed_(), velocity_(), position_(), owner_(owner), type_(), damage_(){}
        ~Projectile() {}
        double getSpeed() const;
        sf::Vector2f getVelocity() const;
        Tower* getOwner() const;
        std::string& getType() const;
        void dealDamage(Enemy* enemy);

};

#endif