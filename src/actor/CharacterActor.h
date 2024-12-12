#include "Actor.h"
#include "../InputHandler.h"
#include "box2d/box2d.h"
#include "../map/TileMap2D.h"
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>

enum Direction { LEFT, RIGHT };
enum MotionState { STILL, WALK, AIRBORNE };
void LoadSpriteGroup(std::vector<Texture2D>& spriteGroup, const std::vector<std::string>& spritePaths);
class CharacterActor : public Actor {
private:
    float maxCameraX;
public:
    CharacterActor();
    CharacterActor(std::vector<std::string> spritePathsLeft, std::vector<std::string> spritePathsRight);
    virtual ~CharacterActor() {
        for (auto texture : FramesLeft) {
            UnloadTexture(texture);
        }
        for (auto texture : FramesRight) {
            UnloadTexture(texture);
        }
    }
    std::vector<Texture2D> FramesLeft, FramesRight;
    float positionX, positionY;
    float velocityX, velocityY;
    float targetVelocityX;
    Direction heading;
    MotionState motionState;
    int animationFrame;
    int currentFrame;
    int animationTimer;
    int jumpTime; // Track the jump time
    int spriteWidth; // Default sprite width
    void ApplyHorizontalVelocity();
    void BoundPlayerPosition();
    void UpdateCamera(Camera2D& camera);
    void UpdatePlayerAndCamera(Camera2D& camera, TileMap2D& map);
    void UpdateAnimation();
    void draw(float scale);
};
