#include "map.hpp"
//#include "mainGame.hpp"
//#include "MessageBox.h" // Assuming MessageBox is a custom function you've defined

/* Map::Map() {
    // Initialize your members in the member initialization list if needed
}*/

/* Map::~Map() {
    // Use nullptr to indicate null pointers
}*/ 

void Map::loadMap(const std::string& fileName) {
    if (!texture.loadFromFile("textures/" + fileName)) {

        return;
    }

    background.setTexture(texture);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    /* std::shared_ptr<Tower> towerCircleIt;
    bool drawLast = false;

    for (const auto& tower : towers) {
        if (tower->isActive()) {
            towerCircleIt = tower;
            drawLast = true;
            continue;
        }
        target.draw(*tower);
    }

    if (drawLast)
        target.draw(*towerCircleIt);*/ 
} 

/* void Map::update() {
    // Your update logic here
}*/

/*bool Map::canTowerBuild(const std::shared_ptr<Tower>& activeTower) const {
    const int vertexes = 4;
    sf::Vector2f towerVertexes[vertexes] = {
            activeTower->getPosition(),
            { activeTower->getPosition().x + activeTower->getSize().x, activeTower->getPosition().y },
            { activeTower->getPosition().x, activeTower->getPosition().y + activeTower->getSize().y },
            { activeTower->getPosition().x + activeTower->getSize().x, activeTower->getPosition().y + activeTower->getSize().y }
    };

    for (const auto& vertex : towerVertexes) {
        if (!background.getGlobalBounds().contains(vertex)) {
            return false;
        }
    }

    for (const auto& unBuildableRect : unBuildable) {
        if (activeTower->getGlobalBounds().intersects(unBuildableRect)) {
            return false;
        }
    }

    for (const auto& tower : towers) {
        if (activeTower->getGlobalBounds().intersects(tower->getGlobalBounds())) {
            return false;
        }
    }

    return true;
}*/


/*void Map::sellTower(Tower * sellingTower)
{
    for (size_t i = 0; i < towers.size(); ++i)
    {
        if (towers[i].get() == sellingTower)
            towers.erase(towers.begin() + i);
    }
}*/

/*sf::FloatRect Map::getBackgroundBounds() {
    return background.getGlobalBounds();
}*/ 
