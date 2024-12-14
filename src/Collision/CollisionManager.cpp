#include "CollisionManager.h"

bool CollisionManager::CheckCollision(Rectangle rect1, Rectangle rect2) {
    return CheckCollisionRecs(rect1, rect2);
}

void CollisionManager::HandlePlayerMapCollision(MarioCharacter& player, TileMap2D& map) {
    Rectangle playerRect = {
        player.getPositionX(),
        player.getPositionY(),
        player.getWidth(),
        player.getHeight()
    };

    float nextX = player.getPositionX() + player.getVelocityX();
    float nextY = player.getPositionY() + player.getVelocityY();
    auto solidTiles = map.getSolidTiles();
    std::cout << "Number of solid tiles: " << solidTiles.size() << std::endl;

    // Check horizontal movement first
    Rectangle horizontalRect = {
        nextX, player.getPositionY(),
        player.getWidth(), player.getHeight()
    };

    // Check vertical movement
    Rectangle verticalRect = {
        player.getPositionX(), nextY,
        player.getWidth(), player.getHeight()
    };

    for (const auto& tile : map.getSolidTiles()) {
        if (CheckCollisionRecs(playerRect, tile)) {
            std::cout << "Collision detected!" << std::endl;
            std::cout << "Player: " << playerRect.x << "," << playerRect.y << std::endl;
            std::cout << "Tile: " << tile.x << "," << tile.y << std::endl;
        }
        // Horizontal collision
        if (CheckCollisionRecs(horizontalRect, tile)) {
            if (player.getVelocityX() > 0) {
                player.setPosition(tile.x - player.getWidth(), player.getPositionY());
            } else if (player.getVelocityX() < 0) {
                player.setPosition(tile.x + tile.width, player.getPositionY());
            }
            player.setVelocityX(0);
        }

        // Vertical collision
        if (CheckCollisionRecs(verticalRect, tile)) {
            if (player.getVelocityY() > 0) {
                player.setPosition(player.getPositionX(), tile.y - player.getHeight());
                player.isOnGround = true;
            } else if (player.getVelocityY() < 0) {
                player.setPosition(player.getPositionX(), tile.y + tile.height);
            }
            player.setVelocityY(0);
        }
    }
}

void CollisionManager::HandlePlayerEnemyCollisions(MarioCharacter& player, std::vector<Enemy*>& enemies) {
    return;
}

void CollisionManager::HandlePlayerItemCollisions(MarioCharacter& player, std::vector<Item*>& items) {
    return;
}