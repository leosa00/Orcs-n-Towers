#ifndef TEXTURE_CONTAINER
#define TEXTURE_CONTAINER
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

// Enums for different textures
namespace Textures{
    
    // NOTE: these could also be stored in one big enum...
    enum TowerID {Tower1, Tower2, Tower3, Tower4, Tower5};
    enum EnemyID {Enemy1, Enemy2, Enemy3, Enemy4, Enemy5};
    enum ProjectileID{Proj1, Proj2, Proj3};

}

/**
 * Template class for loading and storing textures and sounds
 * 
 */
template <typename T_enum, typename T_resource>
class AssetContainer {
public:

    void load(T_enum, std::string filename); // Does this need the enum input
    const T_resource& get(T_enum) const;

private:
    std::map<T_enum, std::unique_ptr<T_resource>> resources_;


};

#endif