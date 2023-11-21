#include "path.hpp"

std::queue<sf::Vector2f> path::getWaypoints() {
    return waypoints_;
}