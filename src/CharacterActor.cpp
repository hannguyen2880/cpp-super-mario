#include "CharacterActor.h"
#include "InputHandler.h"
#include <cmath>
#include <vector>
#include <string>
#include <iostream>


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

void CharacterActor::setFriction(float friction) {
    this->friction = friction;
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

    walkSpeed = 3.0;
    jumpSpeed = 1.5f * walkSpeed;

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

void CharacterActor::createPhysicsBody(b2World& world, float worldScale,
    const b2Vec2& position, const b2Vec2& velocity) {
    raylib::Rectangle boundingBox = getBoundingBox(worldScale, position);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position = position;
    bodyDef.linearVelocity = velocity;

    float halfWidth = boundingBox.width * widthScale / 2.0f;
    float halfHeight = boundingBox.height / 2.0f;

    // Need to tweak the friction depending on the situation
    legsFrictionAdjuster.setPreSolveFunc([this](PhysicsObject* thisObject, PhysicsObject* otherObject,
        b2Contact* contact, const b2Manifold* oldManifold) {
            // Increase the friction so that the character can stand still on slopes, but still 
            // walk them
            float otherFriction = friction;
            thisObject->getOurFixture(contact)->SetFriction(friction);
            b2Fixture* otherFixture = thisObject->getOtherFixture(contact);
            if (otherFixture) { otherFriction = otherFixture->GetFriction(); }
            float adjustedFriction = sqrtf(friction * otherFriction);
            contact->SetFriction(adjustedFriction);
        });

    // Approximating our character with a rectangle and a circle for feet.
    // The circle avoids the character catching at the vertices at tile edges.
    // See the following for a description of the problem: https://www.iforce2d.net/b2dtut/ghost-vertices
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
    // Make the radius slightly bigger, so the edge of the torso's rectangle can't accidentally act as a hook
    legsShape.m_radius = halfWidth + 1.0f / worldScale;
    legsShape.m_p.y = -halfWidth;
    b2FixtureDef legsDef;
    legsDef.shape = &legsShape;
    legsDef.density = 1.0f;
    legsFrictionAdjuster.attachToFixture(legsDef);
    physicsBody->CreateFixture(&legsDef);

    // Adding a ground sensor, for reliable "am I on the ground" detection
    groundSensor.setContactHandler([this](PhysicsObject* thisObject, PhysicsObject* otherObject,
        b2Contact* contact, bool contactBegin) {
            contactBegin = 1;
            groundContactCount += contactBegin ? 1 : -1;
            isOnGround = (groundContactCount != 0);
            std::cout << "Contact Begin: " << contactBegin << ", Ground Contact Count: " << groundContactCount << ", Is On Ground: " << isOnGround << std::endl;
        });

    // The foot sensor should stick out by a few pixels so slight floating-point inaccuracies don't trigger
    // repeated on/off the ground events when the character is actually walking
    float footSensorOffset = 2.0f / worldScale;
    b2CircleShape footSensor;
    footSensor.m_radius = halfWidth;
    footSensor.m_p.y = legsShape.m_p.y + footSensorOffset;
    b2FixtureDef footSensorDef;
    footSensorDef.shape = &footSensor;
    footSensorDef.isSensor = true;
    groundSensor.attachToFixture(footSensorDef);
    physicsBody->CreateFixture(&footSensorDef);
}

void CharacterActor::setInitialPosition(b2World& world, float worldScale, float x, float y) {
    b2Vec2 initialPosition(x / worldScale, y / worldScale);
    b2Vec2 initialVelocity(0.0f, 0.0f);
    createPhysicsBody(world, worldScale, initialPosition, initialVelocity);
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

    // Set sprite width and height based on the first loaded sprite
    //if (spriteGroup.size() == 1) {
    //    spriteWidth = static_cast<float>(sprite.width);   // Width of the sprite
    //    spriteHeight = static_cast<float>(sprite.height); // Height of the sprite
    //}
}

void CharacterActor::draw(float scale, bool first) {
    Vector2 position = { physicsBody->GetPosition().x, physicsBody->GetPosition().y };
    if (facingRight) {
        DrawTextureEx(marioFramesRight[currentFrame], position, 0.0f, scale, WHITE);
    }
    else {
        DrawTextureEx(marioFramesLeft[currentFrame], position, 0.0f, scale, WHITE);
    }

    // Draw the bounding box for debugging
    drawBoundingBox(GREEN, scale, { position.x, position.y }, first);
}
