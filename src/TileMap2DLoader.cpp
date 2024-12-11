#include "TileMap2DLoader.h"

std::unique_ptr<tson::Map> loadTileMap(const std::string& fileName) {
    tson::Tileson tileson;
    std::unique_ptr<tson::Map> map = tileson.parse(fileName);
    if (map && map->getStatus() == tson::ParseStatus::OK) {
        return map;
    }
    return nullptr;
}

