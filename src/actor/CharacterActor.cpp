#include "CharacterActor.h"
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define FLOOR_HEIGHT 192
#define GRAVITY 0.3f
#define MAX_FALL_SPEED 4.5
#define JUMP_SPEED -4.5
#define MAX_JUMP_TIME 10 // Maximum frames for holding the jump button
#define MAPHEIGHT 240.0
#define MAPWIDTH 2400.0
#define MAP_SCALE 1.0

void LoadSpriteGroup(std::vector<Texture2D>& spriteGroup, const std::vector<std::string>& spritePaths) {
    for (const auto& path : spritePaths) {
        Texture2D sprite = LoadTexture(path.c_str());
        spriteGroup.push_back(sprite);
    }
}

CharacterActor::CharacterActor() {
    this->positionX = 0.0f;
    this->positionY = FLOOR_HEIGHT;
    this->velocityX = 0.0f;
    this->velocityY = 0.0f;
    this->targetVelocityX = 0.0f;
    this->heading = RIGHT;
    this->motionState = STILL;
    this->animationFrame = 0;
    this->currentFrame = 0;
    this->animationTimer = 12;
    this->jumpTime = 0;
    this->spriteWidth = 16;
    this->maxCameraX = 0.0f;
}

CharacterActor::CharacterActor(std::vector<std::string> spritePathsLeft, std::vector<std::string> spritePathsRight): CharacterActor() {
    LoadSpriteGroup(FramesLeft, spritePathsLeft);
    LoadSpriteGroup(FramesRight, spritePathsRight);
}
void CharacterActor::ApplyHorizontalVelocity() {
    if (velocityX < targetVelocityX) {
        this->velocityX += 0.2f; 
    } else if (velocityX > targetVelocityX) {
        this->velocityX -= 0.2f; 
    }

    if (std::fabs(velocityX) < 0.1f) {
        this->velocityX = 0.0f;
    }
}

void CharacterActor::BoundPlayerPosition() {
    if (positionX < 0) positionX = 0;
    if (positionX > MAPWIDTH - (FramesLeft[currentFrame].width) * 1.5f) 
        positionX = MAPWIDTH - (FramesLeft[currentFrame].width  * 1.5f);
}

void CharacterActor::UpdateCamera(Camera2D& camera) {
    const float cameraSpeed = 0.1f; 
    float targetCameraX = this->positionX;

    if (targetCameraX < SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = SCREEN_WIDTH / 2.0f / camera.zoom;
    if (targetCameraX > MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom) targetCameraX = MAPWIDTH - SCREEN_WIDTH / 2.0f / camera.zoom;

    if (targetCameraX > maxCameraX) {
        maxCameraX = targetCameraX;
    }

    camera.target.x += (maxCameraX - camera.target.x) * cameraSpeed;
    camera.target.y = MAPHEIGHT / 2.0f;
}

void CharacterActor::UpdatePlayerAndCamera(Camera2D& camera, TileMap2D& map) {
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && this->motionState != AIRBORNE) {
        this->velocityY = JUMP_SPEED;
        this->motionState = AIRBORNE;
        this->jumpTime = 0;
    }

    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP)) && this->motionState == AIRBORNE && this->jumpTime < MAX_JUMP_TIME) {
        this->velocityY = JUMP_SPEED;
        this->jumpTime++;
    }

    if (this->motionState == AIRBORNE) {
        this->velocityY += GRAVITY;
        if (this->velocityY > MAX_FALL_SPEED) this->velocityY = MAX_FALL_SPEED;
        this->positionY += this->velocityY;

        if (this->positionY >= FLOOR_HEIGHT) {
            this->positionY = FLOOR_HEIGHT;
            this->motionState = STILL;
            this->velocityY = 0;
        }
    }

    if (IsKeyDown(KEY_RIGHT)) {
        this->targetVelocityX = 1.5f;
        this->heading = RIGHT;
        if (this->motionState != AIRBORNE) {
            this->motionState = WALK;
        }
    } else if (IsKeyDown(KEY_LEFT)) {
        this->targetVelocityX = -1.5f;
        this->heading = LEFT;
        if (this->motionState != AIRBORNE) {
            this->motionState = WALK;
        }
    } else {
        this->targetVelocityX = 0.0f;
        if (this->motionState != AIRBORNE) {
            this->motionState = STILL;
        }
    }

    ApplyHorizontalVelocity();
    this->positionX += this->velocityX;
    float minX = camera.target.x - (SCREEN_WIDTH / 2.0f / camera.zoom);
    if (this->positionX < minX) {
        this->positionX = minX;
        this->velocityX = 0;
    }

    BoundPlayerPosition();
    UpdateCamera(camera);
}

void CharacterActor::UpdateAnimation() {
    this->animationTimer--;
    if (this->animationTimer <= 0) {
        this->animationTimer = 12;
        if (this->motionState == WALK) {
            this->animationFrame = (this->animationFrame + 1) % 3;
        } else this->animationFrame = (this->animationFrame + 1) % 2;
    }

    if (this->motionState == STILL) {
        this->currentFrame = 0;
    } else if (this->motionState == WALK) {
        this->currentFrame = 1 + this->animationFrame;
    } else if (this->motionState == AIRBORNE) {
        this->currentFrame = 4;
    }
}

void CharacterActor::draw(float scale) {
    Vector2 position = { positionX, positionY };
    if (heading == LEFT) {
        DrawTextureEx(FramesLeft[currentFrame], position, 0.0f, scale, WHITE);
    } else {
        DrawTextureEx(FramesRight[currentFrame], position, 0.0f, scale, WHITE);
    }
}