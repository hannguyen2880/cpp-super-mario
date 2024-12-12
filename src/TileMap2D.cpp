#include "TileMap2D.h"
#include "nlohmann/json.hpp"
#include <fstream>

static raylib::Rectangle toRayLibRect(tson::Rect rect) {
	return raylib::Rectangle((float)rect.x, (float)rect.y, (float)rect.width, (float)rect.height);
}

TileMap2D::TileMap2D(const std::string& fileName, const std::string& groundLayerName) {
	tileMap = loadTileMap(fileName);

	if (tileMap->getStatus() != tson::ParseStatus::OK) {
		throw std::runtime_error(TextFormat("Failed to load tile-map %s. Error: %s",
			fileName.c_str(), tileMap->getStatusMessage().c_str()));
	}

	loadTileLayers(fileName);

	// Find the ground layer
	TerrainLayerIdx = 0;
	auto& layers = tileMap->getLayers();
	for (auto& layer : layers) {
		if (groundLayerName.compare(layer.getName()) == 0 && layer.getType() == tson::LayerType::objectgroup) {
			// Found
			break;
		}
		++TerrainLayerIdx;
	}

	//std::cout << "DEBUG: TerrainLayerIdx = " << TerrainLayerIdx << std::endl;

	bool foundGround = TerrainLayerIdx < layers.size();
	if (!foundGround) {
		throw std::runtime_error(TextFormat("Couldn't find ground layer %s in tile-map %s",
			groundLayerName.c_str(), fileName.c_str()));
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
		//std::cout << "DEBUG: TerrainLayerIdx = " << TerrainLayerIdx << std::endl;
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
	const float lineThickness = 2 / worldScale;

	// Get all layers from the tileMap
	auto& layers = tileMap->getLayers();

	// Check if TerrainLayerIdx corresponds to a valid ObjectGroup layer
	if (TerrainLayerIdx < layers.size()) {
		auto& layer = layers[TerrainLayerIdx];

		// Ensure the layer is of type ObjectGroup
		if (layer.getType() != tson::LayerType::objectgroup) {
			std::cout << "DEBUG: Selected layer is not an ObjectGroup. Layer type: " << (int)layer.getType() << std::endl;
			return;
		}

		raylib::Vector2 offset = calcLayerOffset(layer, camera, worldScale);

		// Iterate over objects in the ObjectGroup layer
		for (auto& object : layer.getObjects()) {
			// Skip invisible objects
			if (!object.isVisible()) {
				continue;
			}

			auto objectType = object.getObjectType();
			auto shapePos = object.getPosition();
			raylib::Vector2 shapeOffset = raylib::Vector2((float)shapePos.x, (float)shapePos.y) / worldScale + offset;

			switch (objectType) {
			case tson::ObjectType::Rectangle:
			{
				auto rectSize = object.getSize();
				raylib::Rectangle rect(
					(float)shapeOffset.x, (float)shapeOffset.y,
					(float)rectSize.x / worldScale, (float)rectSize.y / worldScale
				);
				DrawRectangleLinesEx(rect, lineThickness, color);
				/*std::cout << "DEBUG: Rectangle drawn at (" << rect.x << ", " << rect.y
					<< "), size (" << rect.width << ", " << rect.height << ")." << std::endl;*/
				break;
			}
			case tson::ObjectType::Polygon:
			{
				auto& polygon = object.getPolygons();
				if (!polygon.empty()) {
					auto lastPoint = polygon.back();
					raylib::Vector2 prevPos = raylib::Vector2((float)lastPoint.x, (float)lastPoint.y) / worldScale + shapeOffset;

					// Draw each line segment of the polygon
					for (auto& currPoint : polygon) {
						raylib::Vector2 currPos = raylib::Vector2((float)currPoint.x, (float)currPoint.y) / worldScale + shapeOffset;
						DrawLineEx(prevPos, currPos, lineThickness, color);
						prevPos = currPos;
					}
					//std::cout << "DEBUG: Polygon drawn with " << polygon.size() << " points." << std::endl;
				}
				break;
			}
			case tson::ObjectType::Polyline:
			{
				auto& polyline = object.getPolygons();
				if (!polyline.empty()) {
					auto prevPos = raylib::Vector2((float)polyline.front().x, (float)polyline.front().y) / worldScale + shapeOffset;

					// Draw each line segment of the polyline
					for (auto& currPoint : polyline) {
						raylib::Vector2 currPos = raylib::Vector2((float)currPoint.x, (float)currPoint.y) / worldScale + shapeOffset;
						DrawLineEx(prevPos, currPos, lineThickness, color);
						prevPos = currPos;
					}
					//std::cout << "DEBUG: Polyline drawn with " << polyline.size() << " points." << std::endl;
				}
				break;
			}
			default:
				TraceLog(LOG_WARNING, "Unrecognized object type: %u", objectType);
				break;
			}
		}
	}
	else {
		std::cout << "DEBUG: TerrainLayerIdx is out of bounds or invalid." << std::endl;
	}
}

void TileMap2D::updateAnimations(float elapsedTime) {
	// ##### FIXME! ###### To-do
}

//we just have polyline(polygons) and rectangle shapes
void TileMap2D::generatePhysicsObjects(b2World& physicsWorld, float worldScale) {
	// Create vertices variable here to avoid repeated construction/destruction overhead (for every tile)
	std::vector<b2Vec2> vertices;
	const float defaultFriction = 1.0f;

	auto& layers = tileMap->getLayers();
	auto tileSizeTson = tileMap->getTileSize();
	b2Vec2 tileSize_2(tileSizeTson.x / (2.0f * worldScale), tileSizeTson.y / (2.0f * worldScale));
	if (TerrainLayerIdx < layers.size()) {
		auto& layer = layers[TerrainLayerIdx];

		auto layerOffsetTson = layer.getOffset();
		b2Vec2 layerOffset(layerOffsetTson.x / worldScale, layerOffsetTson.y / worldScale);


		for (auto& [pos, tileObject] : layer.getTileObjects()) {
			tson::Tile* tile = tileObject.getTile();
			auto tilePos = tileObject.getPosition();
			b2Vec2 tileOffset = b2Vec2(tilePos.x / worldScale, tilePos.y / worldScale) + layerOffset;

			auto& objectGroup = tile->getObjectgroup();
			auto collisionShapes = objectGroup.getObjects();

			for (auto& shape : collisionShapes) {
				auto& shapePos = shape.getPosition();
				b2Vec2 shapeOffset = b2Vec2((float)shapePos.x / worldScale,
					(float)shapePos.y / worldScale) + tileOffset;

				b2BodyDef bodyDef;
				bodyDef.type = b2_staticBody;
				bodyDef.fixedRotation = true;
				bodyDef.position = shapeOffset + tileSize_2; //note: center of the tile
				b2Body* tileBody = physicsWorld.CreateBody(&bodyDef);
				b2Fixture* tileFixture = NULL;

				float tileFriction = defaultFriction;

				switch (shape.getObjectType()) {
				case tson::ObjectType::Polygon:
				case tson::ObjectType::Polyline: // NOTE: Treating a polyline as a polygon for collision
				{
					vertices.clear();
					auto& polygon = shape.getPolygons();
					if (polygon.size() >= 3) {
						for (auto& currPoint : polygon) {
							b2Vec2 currPos = b2Vec2((float)currPoint.x / worldScale,
								(float)currPoint.y / worldScale) - tileSize_2;
							vertices.push_back(currPos);
						}
						b2ChainShape shape;
						shape.CreateLoop(vertices.data(), (int32)vertices.size());
						tileFixture = tileBody->CreateFixture(&shape, 0.0f);
					}
					break;
				}
				case tson::ObjectType::Rectangle:
				{
					auto& rectSize = shape.getSize();
					raylib::Rectangle rect((float)shapeOffset.x, (float)shapeOffset.y,
						(float)rectSize.x / worldScale, (float)rectSize.y / worldScale);
					b2PolygonShape shape;
					shape.SetAsBox((float)rectSize.x / (2.0f * worldScale),
						(float)rectSize.y / (2.0f * worldScale));
					tileFixture = tileBody->CreateFixture(&shape, 0.0f);
					break;
				}
				default:
					TraceLog(LOG_ERROR, "Error: Unrecognized collision shape object type: %u", shape.getObjectType());
				}

				if (tileFixture) {
					tileFixture->SetFriction(tileFriction);
				}
			}
		}
	}
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

