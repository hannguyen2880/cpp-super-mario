#pragma once
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "tileson.h"
#include "raylib-cpp.hpp"
#include "box2d/box2d.h"
//#include "ResourceManager.h"
#include "TileMap2DLoader.h"

namespace tson {
	class Layer;
	class Map;
};

class b2World;

class TileMap2D
{
public:
	
	TileMap2D(const std::string& fileName, const std::string& groundLayerName = "GroundWall");

	virtual ~TileMap2D() = default;

	void draw(const Camera2D& camera, float worldScale, const Color& tint = WHITE);

	/** Draws the ground layer's grid.
	*/
	void drawGrid(const Camera2D& camera, float worldScale, const Color& color = DARKGRAY);

	/** Draws the ground layer's collision shapes.
	 */
	void drawCollisionShapes(const Camera2D& camera, float worldScale, const Color& color = BLUE);

	/** Update animations.
	 */
	void updateAnimations(float elapsedTime);

	/** Generate the physics objects for this tile-map.
	 */
	void generatePhysicsObjects(b2World& physicsWorld, float worldScale);

	/** The tile map's size in pixels.
	 */
	Vector2 getMapSize() const;

private:
	/** Draws a single layer.
	 */
	void drawLayer(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset, const Color& tint);

	void drawTileLayer(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset, const Color& tint);

	void drawImageLayer(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset, const Color& tint);

	/** Calculates a layer's offset.
	 *
	 * @param layer the layer
	 * @param camera the camera viewing the layer
	 * @param worldScale the scale factor that converts from world coordinates to display coordinates
	 * @param offset a base offset to add to the layer's own offsets
	 */
	const Vector2 calcLayerOffset(tson::Layer& layer, const Camera2D& camera, float worldScale, const Vector2& offset = {0,0});

	/** Loads the given image as a texture.
	 * NOTE: This can be safely called on the same image multiple times. Image
	 * files will only be loaded once.
	 *
	 * @param baseDir the base directory that all image files are relative to
	 * @param fileName the image's file name
	 */
	void loadImage(const std::string& baseDir, const std::string& fileName);
	// Function to load a tile layer from a map file
	void loadTileLayers(const std::string& fileName);

	std::unique_ptr<tson::Map> tileMap;

	std::unordered_map<std::string, std::shared_ptr<raylib::Texture>> textures;

	/** Which layer is the ground that actors walk on and/or collide with?
	 */
	unsigned TerrainLayerIdx;
};
