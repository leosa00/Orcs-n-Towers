#include "levelManager.hpp"

int LevelManager::getCurrentLevel(){
    return currLevel_;
}

int LevelManager::getLevelTotal(){
    return levelTotal_;
}

bool LevelManager::readingSuccessfull(){
    return readingSuccess_;
}

void LevelManager::readLevels(){
    std::ifstream file(src_);

    if(file.rdstate() & (file.failbit | file.badbit)){ //failure
        readingSuccess_ = false;
        return;
    } 

    std::string line;

    std::getline(file,line); //disregards first line which is the example

    while (std::getline(file,line))
    {
        int enemyNum, waveNum, enemyType;
        float waitTime;
        std::vector<int> enemyTypes;
        char comma;

        std::istringstream iss(line);

        iss >> enemyNum >> comma >> waveNum >> comma >> waitTime;
        // >> comma;

        if (iss.fail() || iss.bad()){ //failure
            readingSuccess_ = false;
            return;
        }

        while (iss >> comma >> enemyType)
        {
            enemyTypes.push_back(enemyType);
        }
        
        if (iss.fail() && !iss.eof()){ //failure
            readingSuccess_ = false;
            return;
        }

        std::map<std::string, variantData> entry;
        entry["enemyAmount"] = enemyNum;
        entry["waves"] = waveNum;
        entry["waitTime"] = waitTime;
        entry["enemyTypes"] = enemyTypes;

        levelSpecs_.push_back(entry);
        readingSuccess_ = true;
    }
}

/**
 * waitime between levels will be waittime of the previous level - one frame (i think)
 * alternatively there could be a universal waittime for between levels which gets set when leveling up
*/
void LevelManager::update(){
    //this needs to come from game
    float dt = 1.0;

    waitTime_ -= dt;

    std::cout << "waitTime: " << waitTime_ << std::endl;

    if(waitTime_ > 0) return; //time left, return early

    //if there are waves left for the level
    if(std::get<int>(levelSpecs_[currLevel_]["waves"]) > 0) {
        
        std::cout << "Initialising enemies..." << std::endl;
        initiateEnemies(); 
    }
    else { 
        std::cout << "Leveling up" << std::endl;
        currLevel_ ++; //move to next level
        waitTime_ = timeBtwnLevels_;
    }

}

void LevelManager::initiateEnemies(){
    //gets the vector of different types
    auto entry = levelSpecs_[currLevel_].find("enemyTypes");
    const std::vector<int>& enemyTypes = std::get<std::vector<int>>(entry->second);

    std::random_device rd;
    std::uniform_int_distribution<int> range (0, enemyTypes.size()-1);

    //generating enemies
    for(int i = 0; i < std::get<int>(levelSpecs_[currLevel_]["enemyAmount"]); i++){
        //randomly chooses which type from the allowed ones
        int enemyTypeIndex = range(rd);

        //creates said enemy --> pushes it to list of enemies
        switch (enemyTypes[enemyTypeIndex])
        {
        case 0:
        {
            Enemy enemy(30, 60, EnemyType::Ground, 10, path_.getWaypoints());
            game_.enemies_.push_back(std::make_shared<Enemy>(enemy));
            break;
        }
        case 1:
        {
            Enemy enemy(30, 60, EnemyType::Flying, 10, path_.getWaypoints());
            game_.enemies_.push_back(std::make_shared<Enemy>(enemy));
            break;
        }

        default:
            std::cout << "failed to initialise enemy" << std::endl;
            break;
        }
    }

    //resets the wait time
    waitTime_ = std::get<float>(levelSpecs_[currLevel_]["waitTime"]);

    //removes a wave
    std::get<int>(levelSpecs_[currLevel_]["waves"])--;
}