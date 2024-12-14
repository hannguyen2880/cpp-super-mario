#pragma once
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "tileson.h"
#include "raylib-cpp.hpp"
#include "TileMap2DLoader.h"

namespace tson {
	class Layer;
	class Map;
};

class TileMap2D {
public:
	TileMap2D(const std::string& fileName, const std::string& groundLayerName = "Ground");

	virtual ~TileMap2D() = default;

	void draw(const Camera2D& camera, float worldScale, const Color& tint = WHITE);

	void drawGrid(const Camera2D& camera, float worldScale, const Color& color = DARKGRAY);

	void drawCollisionShapes(const Camera2D& camera, float worldScale, const Color& color = BLUE);

	void updateAnimations(float elapsedTime);

	Vector2 getMapSize() const;
	std::vector<Rectangle> getSolidTiles() const;

private:
	void drawLayer(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset, const Color& tint);
	void drawTileLayer(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset, const Color& tint);
	void drawImageLayer(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset, const Color& tint);
	const Vector2 calcLayerOffset(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset = {0,0});
	void loadImage(const std::string& baseDir, const std::string& fileName);
	void loadTileLayers(const std::string& fileName);
	std::unique_ptr<tson::Map> tileMap;
	std::unordered_map<std::string, std::shared_ptr<raylib::Texture>> textures;
	unsigned TerrainLayerIdx;
	std::vector<Rectangle> solidTiles;
};