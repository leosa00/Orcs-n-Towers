#ifndef PATH_HPP
#define PATH_HPP
#include <queue>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp> 

class path {
    friend class enemy;
public:
    path();//creates a path and populates the waypoints queue with
    //all the waypoints required for the enemy class to traverse the path

    
    ~path() {
        
    }
    std::queue<sf::Vector2f> getWaypoints();
private:
    std::queue<sf::Vector2f> waypoints_;
};

#endif