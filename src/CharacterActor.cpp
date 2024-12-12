#include "CharacterActor.h"
#include "InputHandler.h"
#include <cmath>
#include <vector>
#include <string>

#define MOVING_FRICTION 0.2f
#define STANDING_FRICTION 1.0f

float CharacterActor::getPositionX() const {
    return physicsBody->GetPosition().x;
}

float CharacterActor::getPositionY() const {
    return physicsBody->GetPosition().y;
}

b2Vec2 CharacterActor::getPosition() const {
    return physicsBody->GetPosition();
}

CharacterActor::CharacterActor(float widthScale) :
    groundSensor(NULL), torsoPhysicsObject(this), legsFrictionAdjuster(this) {
    init(widthScale);
}

CharacterActor::~CharacterActor() {
    for (Texture2D texture : marioFramesLeft) {
        UnloadTexture(texture);
    }
    for (Texture2D texture : marioFramesRight) {
        UnloadTexture(texture);
    }
}

void CharacterActor::init(float widthScale) {
    facingRight = true;
    groundContactCount = 0;
    setFriction(MOVING_FRICTION);

    walkSpeed = 12;
    jumpSpeed = 2.2f * walkSpeed;

    this->widthScale = widthScale;
    animationFrame = 0;
    currentFrame = 0;
    animationTimer = 12;
    spriteWidth = 16;

    std::vector<std::string> spritePathsLeft = {
        "../mario_imgs/mario_left1.png",
        "../mario_imgs/mario_left2.png",
        "../mario_imgs/mario_left3.png",
        "../mario_imgs/mario_left4.png",
        "../mario_imgs/mario_left_jump1.png"
    };
    std::vector<std::string> spritePathsRight = {
        "../mario_imgs/mario_right1.png",
        "../mario_imgs/mario_right2.png",
        "../mario_imgs/mario_right3.png",
        "../mario_imgs/mario_right4.png",
        "../mario_imgs/mario_right_jump1.png"
    };
    loadSpriteGroup(marioFramesLeft, spritePathsLeft);
    loadSpriteGroup(marioFramesRight, spritePathsRight);
}

void CharacterActor::createPhysicsBody(b2World& world, float worldScale, const b2Vec2& position, const b2Vec2& velocity) {
    raylib::Rectangle boundingBox = getBoundingBox(worldScale);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position = position;
    bodyDef.linearVelocity = velocity;

    float halfWidth = boundingBox.width * widthScale / 2.0f;
    float halfHeight = boundingBox.height / 2.0f;

    legsFrictionAdjuster.setPreSolveFunc([this](PhysicsObject* thisObject, PhysicsObject* otherObject, b2Contact* contact, const b2Manifold* oldManifold) {
        float otherFriction = friction;
        thisObject->getOurFixture(contact)->SetFriction(friction);
        b2Fixture* otherFixture = thisObject->getOtherFixture(contact);
        if (otherFixture) { otherFriction = otherFixture->GetFriction(); }
        float adjustedFriction = sqrtf(friction * otherFriction);
        contact->SetFriction(adjustedFriction);
        });

    physicsBody = world.CreateBody(&bodyDef);

    float torsoHeight = boundingBox.height - halfWidth;
    float torsoHalfHeight = torsoHeight / 2.0f;

    b2PolygonShape torsoShape;
    b2Vec2 boxCentre(0.0f, -boundingBox.height + torsoHalfHeight);
    torsoShape.SetAsBox(halfWidth, torsoHalfHeight, boxCentre, 0.0f);
    b2FixtureDef torsoDef;
    torsoDef.shape = &torsoShape;
    torsoDef.density = 1.0f;
    torsoPhysicsObject.attachToFixture(torsoDef);
    physicsBody->CreateFixture(&torsoDef);

    b2CircleShape legsShape;
    legsShape.m_radius = halfWidth + 1.0f / worldScale;
    legsShape.m_p.y = -halfWidth;
    b2FixtureDef legsDef;
    legsDef.shape = &legsShape;
    legsDef.density = 1.0f;
    legsFrictionAdjuster.attachToFixture(legsDef);
    physicsBody->CreateFixture(&legsDef);

    groundSensor.setContactHandler([this](PhysicsObject* thisObject, PhysicsObject* otherObject, b2Contact* contact, bool contactBegin) {
        groundContactCount += contactBegin ? 1 : -1;
        isOnGround = (groundContactCount != 0);
        });

    float footSensorOffset = 3.0f / worldScale;
    b2CircleShape footSensor;
    footSensor.m_radius = halfWidth;
    footSensor.m_p.y = legsShape.m_p.y + footSensorOffset;
    b2FixtureDef footSensorDef;
    footSensorDef.shape = &footSensor;
    footSensorDef.isSensor = true;
    groundSensor.attachToFixture(footSensorDef);
    physicsBody->CreateFixture(&footSensorDef);
}

void CharacterActor::updateFromInput(InputHandler& input) {
    if (input.isJumpPressed() && isOnGround) {
        b2Vec2 velocity = getVelocity();
        velocity.y = -jumpSpeed;
        setVelocity(velocity);
    }

    if (input.isMoveLeftPressed()) {
        b2Vec2 velocity = getVelocity();
        velocity.x = -walkSpeed;
        setVelocity(velocity);
        facingRight = false;
    }
    else if (input.isMoveRightPressed()) {
        b2Vec2 velocity = getVelocity();
        velocity.x = walkSpeed;
        setVelocity(velocity);
        facingRight = true;
    }
    else {
        b2Vec2 velocity = getVelocity();
        velocity.x = 0;
        setVelocity(velocity);
    }
}

void CharacterActor::updateAnimation() {
    animationTimer--;
    if (animationTimer <= 0) {
        animationTimer = 12;
        if (motionState == WALK) {
            animationFrame = (animationFrame + 1) % 3;
        }
        else {
            animationFrame = (animationFrame + 1) % 2;
        }
    }

    if (motionState == STILL) {
        currentFrame = 0;
    }
    else if (motionState == WALK) {
        currentFrame = 1 + animationFrame;
    }
    else if (motionState == AIRBORNE) {
        currentFrame = 4;
    }
}

void CharacterActor::loadSpriteGroup(std::vector<Texture2D>& spriteGroup, const std::vector<std::string>& spritePaths) {
    for (const auto& path : spritePaths) {
        Texture2D sprite = LoadTexture(path.c_str());
        spriteGroup.push_back(sprite);
    }
}

void CharacterActor::draw(float scale) {
    Vector2 position = { physicsBody->GetPosition().x, physicsBody->GetPosition().y };
    if (facingRight) {
        DrawTextureEx(marioFramesRight[currentFrame], position, 0.0f, scale, WHITE);
    }
    else {
        DrawTextureEx(marioFramesLeft[currentFrame], position, 0.0f, scale, WHITE);
    }
}
