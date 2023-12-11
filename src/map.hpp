#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "tower.hpp"

class Tower; // Forward declaration

class Map : public sf::Drawable, public sf::Transformable {
public:
    sf::Texture texture;
    sf::Sprite background;

    void loadMap(const std::string& fileName);

    std::vector<sf::FloatRect> unBuildable;


private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // MAP_HPP