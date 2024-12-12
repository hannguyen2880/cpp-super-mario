#pragma once

#include "raylib-cpp.hpp"
#include <memory>
#include <unordered_map>

template <class T>
class ResourceManager {
public:
    ResourceManager() {}
    // Resource managers should NOT be copyable
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager(ResourceManager&& other) = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;

    ~ResourceManager() {}

    /** Load a resource. 
     */
    static std::shared_ptr<T> load(const std::string &filename) {
        auto &resourceManager = instance();
        std::shared_ptr<T> resource;

        // Check if the resource is already loaded
        auto resIter = resourceManager.resources.find(filename);
        if(resIter != resourceManager.resources.end()) {
            // The resource was loaded previously. Let's see if we can
            resource = resIter->second.lock();
        }

        if(!resource) {
            // Load the resource from disk
            resource = std::make_shared<T>(filename);
            resourceManager.resources[filename] = resource;
        }

        return resource;
    }

    /** Gets the global resource manager instance.
     */
    static auto& instance(){
        static ResourceManager resourceManager;
        return resourceManager;
    }

private:
    /** The constructor is private so that only the single instance can be used
     */
    

    /** The map of resources that have been loaded.  
     */
    std::unordered_map<std::string, std::weak_ptr<T>> resources;
};


// Predefined resource managers.

/** Manages loading of textures.
 */
typedef ResourceManager<raylib::Texture> TextureManager;

/** Manages loading of sounds. 
 */
typedef ResourceManager<raylib::Sound> SoundManager;

/** Manages loading of music. 
 */
typedef ResourceManager<raylib::Music> MusicManager;
