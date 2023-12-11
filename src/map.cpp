#include "map.hpp"

void Map::loadMap(const std::string& fileName) {
    if (!texture.loadFromFile("textures/" + fileName)) {

        return;
    }

    background.setTexture(texture);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
} 
