#pragma once

#include "raylib-cpp.hpp"
#include <memory>
#include <unordered_map>

template <class T>
class ResourceManager {
public:
    ResourceManager() {}
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager(ResourceManager&& other) = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;

    ~ResourceManager() {}
    static std::shared_ptr<T> load(const std::string &filename) {
        auto &resourceManager = instance();
        std::shared_ptr<T> resource;
        auto resIter = resourceManager.resources.find(filename);
        if(resIter != resourceManager.resources.end()) {
            resource = resIter->second.lock();
        }

        if(!resource) {
            resource = std::make_shared<T>(filename);
            resourceManager.resources[filename] = resource;
        }

        return resource;
    }
    static auto& instance(){
        static ResourceManager resourceManager;
        return resourceManager;
    }

private:
    std::unordered_map<std::string, std::weak_ptr<T>> resources;
};
typedef ResourceManager<raylib::Texture> TextureManager;
typedef ResourceManager<raylib::Sound> SoundManager;
typedef ResourceManager<raylib::Music> MusicManager;