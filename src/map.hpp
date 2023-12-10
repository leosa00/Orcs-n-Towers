#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "tower.hpp"

class Tower; // Forward declaration

class Map : public sf::Drawable, public sf::Transformable {
    //friend class MainGame;
    //friend class TowerManagement;



public:
    sf::Texture texture;
    sf::Sprite background;
    Map();
    ~Map();

    void loadMap(const std::string& fileName);
    //void update();
    //bool canTowerBuild(const std::shared_ptr<Tower>& activeTower) const;
    //void buildTower(const std::shared_ptr<Tower>& activeTower);
    //void sellTower(Tower* sellingTower);
    std::vector<sf::FloatRect> unBuildable;

    sf::FloatRect getBackgroundBounds();

private:
    // std::vector<std::shared_ptr<Tower>> towers;
    

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // MAP_HPP