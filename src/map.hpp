#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

class Tower; // Forward declaration

class Map : public sf::Drawable, public sf::Transformable {
    friend class MainGame;
    friend class TowerManagement;

    sf::Texture texture;
    sf::Sprite background;

public:
    Map();
    ~Map();

    void loadMap(const std::string fileName);
    void update();
    bool canTowerBuild(const std::shared_ptr<Tower>& activeTower);
    void buildTower(const std::shared_ptr<Tower>& activeTower);
    void sellTower(Tower* sellingTower);

    sf::FloatRect getBackgroundBounds();

private:
    std::vector<std::shared_ptr<Tower>> towers;
    std::vector<sf::FloatRect> unBuildable;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // MAP_HPP