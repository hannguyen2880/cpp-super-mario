#pragma once
#include "tileson/tileson.h"

#include <string>
#include <memory>

std::unique_ptr<tson::Map> loadTileMap(const std::string& fileName);