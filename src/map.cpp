//
// Created by Tuan Vu on 06/11/2023.
//
//
// Created by Tuan Vu on 06/11/2023.
//
#include "map.hpp"
#include "mainGame.hpp"

map::map() {
    // Initialize your members in the member initialization list if needed
}

map::~map() {
    // Use nullptr to indicate null pointers
}

void map::loadMap(const std::string fileName) {
    if (!texture.loadFromFile("Textury/" + fileName)) {
        MessageBox(0, "Unable to open fileName to load map, please call to Bartek", 0, 0);
        return;
    }

    background.setTexture(texture);
}

void map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    size_t towerCircleIt;
    bool drawLast = false;

    for (const auto& tower : towers) {
        if (tower->isActive()) {
            towerCircleIt = i;
            drawLast = true;
            continue;
        }
        target.draw(*tower);
    }

    if (drawLast)
        target.draw(*towers[int(towerCircleIt)]);
}

void map::update() {
    // Your update logic here
}

bool map::canTowerBuild(const std::shared_ptr<tower>& activeTower) const {
    const int vertexes = 4;
    sf::Vector2f towerVertexes[vertexes];

    towerVertexes[0] = activeTower->getPosition();
    // ...

    for (const auto& tower : towers) {
        if (activeTower->getGlobalBounds().intersects(tower->getGlobalBounds())) {
            return false;
        }
    }

    return true;
}

void map::buildTower(const std::shared_ptr<tower>& activeTower) {
    std::shared_ptr<tower> newTower = activeTower->getClassObject();
    newTower->setPosition(activeTower->getPosition());
    newTower->activateHUD();
    newTower->build();
    towers.push_back(newTower);
}

void map::sellTower(tower* sellingTower) {
    for (size_t i = 0; i < towers.size(); ++i) {
        if (towers[i].get() == sellingTower) {
            towers.erase(towers.begin() + i);
            break; // Exit the loop once the tower is found and removed
        }
    }
}

sf::FloatRect map::getBackgroundBounds() {
    return background.getGlobalBounds();
}

