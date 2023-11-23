#include "path.hpp"

void path::addWaypoint(const sf::Vector2f& point) {
    waypoints_.push(point);
}

std::queue<sf::Vector2f> path::getWaypoints() {
    return waypoints_;
}