#ifndef LEVELMANAGER
#define LEVELMANAGER

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <fstream>
#include <sstream>
#include <random>

#include "enemy.hpp"
#include "game.hpp"
#include "path.hpp"

class LevelManager {

    public:
    //this requires c++17
    /**
     * @brief to allow the map holding level information to use different types
    */
    using variantData = std::variant<int, float, std::vector<int>>;

    /**
     * Initialises a levelManager
     * reads the level information from file
     * @see readLevels()
     * intitial current level is zero (= level one) to follow indexing convention of level specifications container
     * to allow easier accessing
     * @param src is the source of level information file that is to be read
     * @param path is a reference to the path instance that creates the path of the game
     * @param game is a reference to the running game instance
    */
    LevelManager(const std::string& src, path& path, Game& game) : src_(src), path_(path), game_(game) {
        readLevels();

        currLevel_ = 0;
        waitTime_ = 0;
        timeBtwnLevels_ = 5.0;
        levelTotal_ = levelSpecs_.size();
    }
    ~LevelManager(){}

    /**
     * @brief returns the current level
    */
    int getCurrentLevel();
    
    /**
     * @brief returns the total number of levels definend
    */
    int getLevelTotal();

    /**
     * Updates the level manager, called while game is running
     * Counts down the wait time between waves of enemies
     * Initiates more enemies once waitTime becomes zero, if there is waves left for the level
     * Moves to a new level once previous is complete
     * @see initiateEnemies()
     * @param game is a reference to the game instance that is responsible for calling update
    */
    void update();

    /**
     * returns status flag for reading level info from file
     * true if reading was successfull
     * false if not
    */
    bool readingSuccessfull(); //need to abort game if reading fails, use this to check

    private:

    /**
     * Reads from the source file provided in constructor
     * Disregards first line of file as it is the formatting example
     * Then reads one line at a time:
     *  - number of enemies per wave, number of waves, wait time between waves into variables
     *  - allowed enemy types into a vector
     * Adds the collected values into a map which gets pushed into the vector container that holds all levels
     * Increases the level amount 
    */
    void readLevels();

    /**
     * Initiates the amount of enemies that is allowed for the level
     * Randomly chooses which type of enemy to initiate based on the allowed types for the level
     * Uses a switch case to initiate the right kind of enemy and adds it to the container of enemies
     * Resets the wait time and decreases waves
    */
    void initiateEnemies();
    
    
    /**
     * @brief container to hold all the levels
     * One entry in the outer container is one level, meaning index 0 is level one
     * The inner map holds all information regarding the specific map
     * Map keys:
     *  - "enemyAmount" : the number of enemies allowed per wave (int)
     *  - "waves" : the number of waves of enemeis allowed per level (int)
     *  - "waitTime" : the time (in seconds) between waves (float)
     *  - "enemyTypes" : a vector containing the types of enemies allowed for the level 
     * @see Enemy class' type enum
     * @see @param variantData
    */
    std::vector<std::map<std::string, variantData>> levelSpecs_;

    int currLevel_;
    const std::string& src_;
    bool readingSuccess_; //game should check if reading was successfull before starting
    int levelTotal_;
    bool waiting_;
    float waitTime_;
    float timeBtwnLevels_;

    path& path_;
    Game& game_;
};

#endif