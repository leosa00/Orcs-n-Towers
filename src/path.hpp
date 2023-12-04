#ifndef PATH_HPP
#define PATH_HPP
#include <queue>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class path {
    friend class enemy;
public:
    path();//creates a path and populates the waypoints queue with
    //all the waypoints required for the enemy class to traverse the path


    ~path() {

    }

    void addWaypoint(const sf::Vector2f& point);

    std::queue<sf::Vector2f> getWaypoints() const;
    void makeUnBuildablePath();
    static const float width;
    std::queue<sf::Vector2f> waypoints_;
    std::vector <sf::Vector2f> wayPoints;
    std::vector <sf::FloatRect> unBuildable;

private:

};

#endif