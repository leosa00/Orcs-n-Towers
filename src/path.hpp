#ifndef PATH_HPP
#define PATH_HPP
#include <queue>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp> 
#include <vector>
#include <random>

class path {
    friend class enemy;
public:
    /**
     * Constructs a path by reading coordinate values from a file, 
     * randomly chooses one of the paths and adds the coordinates to the \p waypoints containers.
     * @param src is the source of the path information file to be read
     * @see readPath()
    */
    path(const std::string& src) : src_(src) {
        readPath();

        std::random_device rd;
        std::uniform_int_distribution<int> range(0, paths_.size()-1);

        auto gamePath = paths_[range(rd)];

        for(const auto& point: gamePath){
            addWaypoint(point);
        }

    }

    //creates a path and populates the waypoints queue with
    //all the waypoints required for the enemy class to traverse the path

    
    ~path() {
        
    }

    /**
     * Reads the source file provided in the constructor. Disregards the first line as it is the formatting example. \n 
     * Reads the values into a vector of SFML vector coordinates, 
     * and then adds that vector containing the path into a a vector that contains all the paths from the file.
    */
    void readPath();

    /**
     * Returns
    */
    bool readingSuccessfull();


    void addWaypoint(const sf::Vector2f& point);
    
    std::queue<sf::Vector2f> getWaypoints() const;
    void makeUnBuildablePath();
    static const float width;
    std::queue<sf::Vector2f> waypoints_;
    std::vector <sf::Vector2f> wayPoints;
    std::vector <sf::FloatRect> unBuildable;

    std::vector<std::vector<sf::Vector2f>> paths_;

private:
    const std::string& src_;
    bool readingSuccess_;

};

#endif