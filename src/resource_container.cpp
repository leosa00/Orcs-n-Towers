#include "resource_container.hpp"


// Load resource into RecourceContainer
// Requires filename as str and an enum of the type of resorce as inputs

template <typename T_enum, typename T_resource>
void ResourceContainer<T_enum, T_resource>::load(T_enum type, std::string filename){
    std::unique_ptr<T_resource> resource(new T_resource());
    if (!resource->loadFromFile(filename)){
        // Handle texture loading error
    }
    // The function move should avoid creating a copy of the object recource, when inserting it into the map
    resources_.insert(std::make_pair(type, std::move(resource)));
}

// Find wanted resource in map, return reference to texture.
template <typename T_enum, typename T_resource>
const T_resource& ResourceContainer<T_enum, T_resource>::get(T_enum type) const {
    auto wanted = resources_.find(type);
    return *wanted->second;
}

