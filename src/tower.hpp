#ifndef TOWER_H
#define TOWER_H
#include <string>
#include <SFML/System/Vector2.hpp>
class tower {
    public:
    private:
        std::string type;
        sf::Vector2f position;
        int baseCost;
        float fireRate;
        int currentLvl;
};
#endif //TOWER_H