#pragma once
#include "../actor/MarioCharacter.h"
#include "../actor/Enemy/Enemy.h"
#include "../actor/Items/Item.h"
#include "../map/TileMap2D.h"
#include <vector>

class CollisionManager {
public:
    static bool CheckCollision(Rectangle rect1, Rectangle rect2);
    
    static void HandlePlayerMapCollision(MarioCharacter& player, TileMap2D& map);
    
    static void HandlePlayerEnemyCollisions(MarioCharacter& player, std::vector<Enemy*>& enemies);
    
    static void HandlePlayerItemCollisions(MarioCharacter& player, std::vector<Item*>& items);
};