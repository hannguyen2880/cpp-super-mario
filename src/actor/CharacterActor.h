#include "Actor.h"
#include "../InputHandler.h"
#include "../map/TileMap2D.h"
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>
#include "../game/GameConfig.h"

enum Direction { LEFT, RIGHT };
enum MotionState { STILL, WALK, AIRBORNE };
void LoadSpriteGroup(std::vector<Texture2D>& spriteGroup, const std::vector<std::string>& spritePaths);

class CharacterActor : public Actor {
public:
    float maxCameraX;
    
public:
    CharacterActor();
    CharacterActor(std::vector<std::string> spritePathsLeft, std::vector<std::string> spritePathsRight);
    virtual ~CharacterActor() {
        for (auto texture : FramesLeft) UnloadTexture(texture);
        for (auto texture : FramesRight) UnloadTexture(texture);
    }

    std::vector<Texture2D> FramesLeft, FramesRight;
    float targetVelocityX;
    Direction heading;
    MotionState motionState;
    int animationFrame;
    int currentFrame;
    int animationTimer;
    int jumpTime;

    void ApplyHorizontalVelocity();
    void BoundPlayerPosition();
    void UpdateCamera(Camera2D& camera);
    void UpdatePlayerAndCamera(Camera2D& camera, TileMap2D& map);
    void UpdateAnimation();
    void draw(float scale);
    
    // Override collision box if needed
    Rectangle getBoundingBox() const override {
        return Rectangle{
            positionX + 4.0f,  // Adjust hitbox to be slightly smaller than sprite
            positionY + 4.0f,
            width - 8.0f,
            height - 8.0f
        };
    }
};
