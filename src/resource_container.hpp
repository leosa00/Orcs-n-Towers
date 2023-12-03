#ifndef RESOURCE_CONTAINER
#define RESOURCE_CONTAINER
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

// Enums for different textures
namespace Textures{
    
    // NOTE: these could also be stored in one big enum...
    enum TowerID {BulletTower, BombTower, MissileTower, Tower4, Tower5};
    enum EnemyID {Enemy1, Enemy2, Enemy3, Enemy4, Enemy5};
    enum ProjectileID{Bullet, Bomb, Missile};
    enum Various {Pause};
}

// template class for loading and storing textures and other resources

template <typename T_enum, typename T_resource>
class ResourceContainer {
public:

    // Load resource into container
    void load(T_enum type, std::string filename){
        std::unique_ptr<T_resource> resource(new T_resource());

        if (!resource->loadFromFile(filename)){
            //TODO: Handle texture loading error
        }
        // The function move should avoid creating a copy of the object recource, when inserting it into the map
        resources_.insert(std::make_pair(type, std::move(resource)));
        } 

    // Find wanted resource, return reference
    T_resource& get(T_enum type) const {
        auto wanted = resources_.find(type);
        return *wanted->second;
    }


private:
    std::map<T_enum, std::unique_ptr<T_resource>> resources_;


};

#endif