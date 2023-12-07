#include "levelManager.hpp"
#include "game.hpp"

int LevelManager::getCurrentLevel(){
    return currLevel_;
}

int LevelManager::getLevelTotal(){
    return levelTotal_;
}

bool LevelManager::readingSuccessfull(){
    return readingSuccess_;
}

/*void LevelManager::printLevelSpecs(){
    std::cout << "Num of enemies: " << std::get<int>(levelSpecs_[currLevel_]["enemyAmount"]) << std::endl;
    std::cout << "num of waves: " << std::get<int>(levelSpecs_[currLevel_]["waves"]) << std::endl;
    std::cout << "wait time: " << std::get<float>(levelSpecs_[currLevel_]["waitTime"]) << std::endl;
    std::cout << "allowed enemies: " << std::endl;
    auto pair = levelSpecs_[currLevel_].find("enemyTypes");
    const std::vector<int>& vec = std::get<std::vector<int>>(pair->second);
    for(auto& i : vec){
        std::cout << i << std::endl;
    }
}*/

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


void LevelManager::update(){
    //this needs to come from game
    float dt = game_.getTime().asSeconds();

    waitTime_ -= dt;

    if(waitTime_ > 0) {
        return;} //time left, return early

    //if there are waves left for the level

    //std::cout << "waves: " << std::get<int>(levelSpecs_[currLevel_]["waves"]) << std::endl;

    if(std::get<int>(levelSpecs_[currLevel_]["waves"]) > 0) {
        
        std::cout << "Initialising enemies..." << std::endl;
        initiateEnemies(); 
    }
    else { 
        // Check if all enemies are dead before advancing level
        if (game_.enemies_.empty()) {

        
            std::cout << "Leveling up" << std::endl;
            player_.addMoney(10*currLevel_);
            currLevel_ ++; //move to next level
            player_.levelUp();
            
            if (game_.alternativeMenu_) {
                delete game_.alternativeMenu_;
            }
            game_.alternativeMenu_ = new Menu();
            game_.alternativeMenu_->createMenu(MenuType::Level, &game_);
            game_.paused_ = true;

            // Pressing the advance to next level button will now unpause game
            // and new enemies will be spawned -Otto
        }
    }

}

void LevelManager::initiateEnemies(){
    //gets the vector of different types
    auto entry = levelSpecs_[currLevel_].find("enemyTypes");
    const std::vector<int>& enemyTypes = std::get<std::vector<int>>(entry->second);

    //provided more variance than rand()
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
            Enemy enemy(30, 60, EnemyType::Ground, 10, game_.getPath().getWaypoints());
            enemy.setPosition(100,0);
            enemy.setTexture(game_.enemy_textures_.get(Textures::Enemy1));
            game_.enemies_.push_back(std::make_shared<Enemy>(enemy));
            break;
        }
        case 1:
        {
            Enemy enemy(10, 80, EnemyType::Split, 10, game_.getPath().getWaypoints());
            enemy.setPosition(100, 0);
            enemy.setTexture(game_.enemy_textures_.get(Textures::Enemy1));
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