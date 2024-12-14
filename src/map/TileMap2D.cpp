#include "TileMap2D.h"
#include "nlohmann/json.hpp"
#include <fstream>

static raylib::Rectangle toRayLibRect(tson::Rect rect) {
	return raylib::Rectangle((float)rect.x, (float)rect.y, (float)rect.width, (float)rect.height);
}

// In TileMap2D.cpp
TileMap2D::TileMap2D(const std::string& fileName, const std::string& groundLayerName) {
    tileMap = loadTileMap(fileName);
    
    if (tileMap->getStatus() != tson::ParseStatus::OK) {
        throw std::runtime_error("Failed to load tile-map");
    }

    loadTileLayers(fileName);

    // Find the ground layer
    auto& layers = tileMap->getLayers();
    for (size_t i = 0; i < layers.size(); ++i) {
        auto& layer = layers[i];
        if (layer.getName() == groundLayerName && layer.getType() == tson::LayerType::objectgroup) {
            TerrainLayerIdx = i;
            // Load collision objects from ground layer
            auto& objects = layer.getObjects();
            for (auto& obj : objects) {
                Rectangle rect = {
                    (float)obj.getPosition().x,
                    (float)obj.getPosition().y,
                    (float)obj.getSize().x,
                    (float)obj.getSize().y
                };
                solidTiles.push_back(rect);
            }
            break;
        }
    }
}

void TileMap2D::loadTileLayers(const std::string& fileName) {
	// Load the main JSON file
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open JSON file: " + fileName);
	}

	nlohmann::json jsonData;
	file >> jsonData;
	file.close();

	std::string baseDir = GetDirectoryPath(fileName.c_str());

	// Parse the tilesets from the JSON data
	auto tilesets = jsonData["tilesets"];
	for (const auto& tileset : tilesets) {
		if (tileset.contains("source")) {
			// Load external JSON file
			std::string sourceFile = baseDir + "/" + tileset["source"].get<std::string>();
			std::ifstream sourceFileStream(sourceFile);
			if (!sourceFileStream.is_open()) {
				throw std::runtime_error("Failed to open source JSON file: " + sourceFile);
			}

			nlohmann::json sourceJson;
			sourceFileStream >> sourceJson;
			sourceFileStream.close();

			std::string image = sourceJson["image"];
			if (!image.empty()) {
				loadImage(baseDir, image);
			}
		}
		else if (tileset.contains("image")) {
			// Inline tileset definition
			std::string image = tileset["image"];
			if (!image.empty()) {
				loadImage(baseDir, image);
			}
		}
	}
}


void TileMap2D::draw(const Camera2D& camera, float worldScale, const Color& tint) {
	auto& layers = tileMap->getLayers();
	for (auto& layer : layers) {
		drawLayer(layer, camera, worldScale, raylib::Vector2(0, 0), tint);
	}
}

void TileMap2D::drawGrid(const Camera2D& camera, float worldScale, const Color& color) {
	auto& layers = tileMap->getLayers();
	if (TerrainLayerIdx < layers.size()) {
		std::cout << "DEBUG: TerrainLayerIdx = " << TerrainLayerIdx << std::endl;
		auto& layer = layers[TerrainLayerIdx];
		Vector2 offset = calcLayerOffset(layer, camera, worldScale);
		//auto mapSize = layer.getSize();
		auto mapSize = tileMap->getSize();
		auto tileSize = tileMap->getTileSize();

		const float lineThickness = 2 * 0.5 / worldScale;
		for (int y = 0; y < mapSize.y; ++y) {
			float yPos = offset.y + y * tileSize.y / worldScale;
			raylib::Vector2 startPos(offset.x, yPos);
			raylib::Vector2 endPos(offset.x + mapSize.x * tileSize.x, yPos);
			DrawLineEx(startPos, endPos, lineThickness, color);
		}
		for (int x = 0; x < mapSize.x; ++x) {
			float xPos = offset.x + x * tileSize.x / worldScale;
			raylib::Vector2 startPos(xPos, offset.y);
			raylib::Vector2 endPos(xPos, offset.y + mapSize.y * tileSize.y);
			DrawLineEx(startPos, endPos, lineThickness, color);
		}
	}
}

void TileMap2D::drawCollisionShapes(const Camera2D& camera, float worldScale, const Color& color) {
	//std::cout << "DEBUG: TerrainLayerIdx = " << TerrainLayerIdx << std::endl;
	const float lineThickness = 2 / worldScale;
	auto& layers = tileMap->getLayers();
	if (TerrainLayerIdx < layers.size()) {
		auto& layer = layers[TerrainLayerIdx];
		raylib::Vector2 offset = calcLayerOffset(layer, camera, worldScale);
		for (auto& [pos, tileObject] : layer.getTileObjects()) {
			tson::Tile* tile = tileObject.getTile();
			/*if (tile == nullptr) {
				std::cout << "DEBUG: tile is null\n" << std::endl;
				continue;
			}*/
			auto tilePos = tileObject.getPosition();
			raylib::Vector2 tileOffset = raylib::Vector2(tilePos.x, tilePos.y) / worldScale + offset;
			auto& objectGroup = tile->getObjectgroup();
			auto collisionShapes = objectGroup.getObjects();
			//std::cout << "DEBUG: collisionShapes = " << collisionShapes.size() << std::endl;
			for (auto& shape : collisionShapes) {
				auto& shapePos = shape.getPosition();
				raylib::Vector2 shapeOffset = raylib::Vector2((float)shapePos.x, (float)shapePos.y) / worldScale + tileOffset;

				switch (shape.getObjectType()) {
				case tson::ObjectType::Polygon:
				case tson::ObjectType::Polyline: // NOTE: Treating a polyline as a polygon for collision
				{
					auto& polygon = shape.getPolygons();
					if (polygon.size() > 0) {
						auto& lastPos = polygon[polygon.size() - 1];
						raylib::Vector2 prevPos = raylib::Vector2((float)lastPos.x, (float)lastPos.y) / worldScale + shapeOffset;
						for (auto& currPoint : polygon) {
							raylib::Vector2 currPos = raylib::Vector2((float)currPoint.x, (float)currPoint.y) / worldScale + shapeOffset;
							DrawLineEx(prevPos, currPos, lineThickness, color);
							std::cout << "DEBUG: DrawPolygon " << std::endl;
							prevPos = currPos;
						}
					}
					break;
				}
				case tson::ObjectType::Rectangle:
				{
					auto& rectSize = shape.getSize();
					raylib::Rectangle rect((float)shapeOffset.x, (float)shapeOffset.y,
						(float)rectSize.x / worldScale, (float)rectSize.y / worldScale);
					DrawRectangleLinesEx(rect, lineThickness, color);
					std::cout << "DEBUG: rectangle " << std::endl;
					break;
				}
				default:
					TraceLog(LOG_ERROR, "Error: Unrecognized collision shape object type: %u", shape.getObjectType());
				}
			}
		}
	}
}

void TileMap2D::updateAnimations(float elapsedTime) {
	// ##### FIXME! ###### To-do
}

Vector2 TileMap2D::getMapSize() const {
	auto size = tileMap->getSize();
	auto tileSize = tileMap->getTileSize();
	return raylib::Vector2((float)(size.x * tileSize.x), (float)(size.y * tileSize.y));
}

void TileMap2D::drawLayer(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset, const Color& tint) {
	Vector2 newOffset = calcLayerOffset(layer, camera, worldScale, offset);
	switch (layer.getType()) {
	case tson::LayerType::tilelayer:
		drawTileLayer(layer, camera, worldScale, newOffset, tint);
		break;
	case tson::LayerType::imagelayer:
		drawImageLayer(layer, camera, worldScale, newOffset, tint);
		break;
	case tson::LayerType::objectgroup:
		// Ignore
		break;
	case tson::LayerType::grouplayer:
	{
		for (auto& subLayer : layer.getLayers()) {
			drawLayer(subLayer, camera, worldScale, newOffset, tint);
		}
		break;
	}
	default:
		// Fail
		auto* errMsg = TextFormat("ERROR: Unsupported Tileson layer type %u",
			layer.getType());
		throw std::runtime_error(errMsg);
	}
}

void TileMap2D::drawTileLayer(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset, const Color& tint) {
	for (auto& [pos, tileObject] : layer.getTileObjects()) {
		tson::Tile* tile = tileObject.getTile();
		tson::Tileset* tileset = tile->getTileset();
		auto tileImage = tileset->getImage();
		auto imagePath = tileImage.empty() ? tile->getImage() : tileImage;
		auto texIter = textures.find(imagePath.string());
		if (texIter == textures.end()) {
			auto* errMsg = TextFormat("ERROR: Tile-map is missing image: %s\n",
				imagePath.string().c_str());
			throw std::runtime_error(errMsg);
		}
		auto& texture = texIter->second;

		raylib::Rectangle drawRect = toRayLibRect(tileObject.getDrawingRect());
		auto tilePos = tileObject.getPosition();
		raylib::Rectangle destRec(
			tilePos.x / worldScale + offset.x,
			tilePos.y / worldScale + offset.y,
			drawRect.width / worldScale,
			drawRect.height / worldScale);
		texture->Draw(drawRect, destRec, raylib::Vector2(0.0f, 0.0f), 0.0f, tint);
	}
}

void TileMap2D::drawImageLayer(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset, const Color& tint) {
	auto imageName = layer.getImage();
	auto texIter = textures.find(imageName);
	if (texIter == textures.end()) {
		auto* errMsg = TextFormat("ERROR: Tile-map is missing image: %s\n",
			imageName.c_str());
		throw std::runtime_error(errMsg);
	}
	auto& texture = texIter->second;

	bool repeatX = layer.hasRepeatX();
	bool repeatY = layer.hasRepeatY();

	auto screenOriginPos = GetScreenToWorld2D(raylib::Vector2(0.0f, 0.0f), camera);
	auto texWidth = texture->GetWidth();
	auto texHeight = texture->GetHeight();
	raylib::Rectangle sourceRec(
		0.0f, 0.0f, (float)texWidth, (float)texHeight);
	raylib::Rectangle destRec(
		repeatX ? screenOriginPos.x : offset.x,
		repeatY ? screenOriginPos.y : offset.y,
		repeatX ? (float)GetScreenWidth() : (float)texWidth,
		repeatY ? (float)GetScreenHeight() : (float)texHeight);
	raylib::Vector2 origin = raylib::Vector2(0.0f, 0.0f);
	texture->Draw(sourceRec, destRec, origin, 0.0f, tint);
}

const Vector2 TileMap2D::calcLayerOffset(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset) {
    auto pFactorTson = layer.getParallax();
    auto pOriginTson = layer.getMap()->getParallaxOrigin();
    raylib::Vector2 parallaxFactor(pFactorTson.x, pFactorTson.y);
    raylib::Vector2 parallaxOrigin(pOriginTson.x / worldScale, pOriginTson.y / worldScale);

    auto layerOffsetTson = layer.getOffset();
    raylib::Vector2 layerOffset(layerOffsetTson.x, layerOffsetTson.y);
    auto cameraOffset = Vector2Subtract(GetWorldToScreen2D(parallaxOrigin, camera), camera.offset);
	
    raylib::Vector2 newOffset = Vector2Add(offset , (layerOffset - Vector2Multiply(cameraOffset, (raylib::Vector2(1.0f, 1.0f) - parallaxFactor))) / worldScale);

    return newOffset;
}

void TileMap2D::loadImage(const std::string& baseDir, const std::string& fileName) {
	if (textures.find(fileName) != textures.end()) {
		// Already loaded
		return;
	}

	std::string fullPath = (baseDir.length() > 0) ?
		TextFormat("%s/%s", baseDir.c_str(), fileName.c_str()) :
		fileName;

	//textures[fileName] = TextureManager::load(fullPath);
	textures[fileName] = std::make_shared<raylib::Texture>(fullPath);
}

std::vector<Rectangle> TileMap2D::getSolidTiles() const {
    std::vector<Rectangle> tiles;
    auto& layers = tileMap->getLayers();
    
    if (TerrainLayerIdx < layers.size()) {
        auto& layer = layers[TerrainLayerIdx];
        auto& objects = layer.getObjects();
        
        for (auto& obj : objects) {
            // Handle different object types
            if (obj.getObjectType() == tson::ObjectType::Rectangle) {
                Rectangle rect = {
                    (float)obj.getPosition().x,
                    (float)obj.getPosition().y, 
                    (float)obj.getSize().x,
                    (float)obj.getSize().y
                };
                tiles.push_back(rect);
            }
            // Add handling for polygons if needed
        }
    }
    return tiles;
}