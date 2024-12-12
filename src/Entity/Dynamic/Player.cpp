#include "Player.h"

static const b2Vec2 zeroVec(0.0f, 0.0f);

Player::Player() {
    body = nullptr;
    isOnGround = false;
    wasOnGround = false;
}
Player::Player(b2World* world, Vector2 position, Texture2D texture) : DynamicEntity(world, position, texture) {
    // Additional initialization if needed
}

Player::~Player() {
    deletePhysicsBody();
}

void Player::Update() {
    // Implement player-specific update logic here
}

void Player::Draw() {
    //DynamicEntity::Draw();
}

void Player::setPosition(const b2Vec2 &position) {
	if(body) {
		return body->SetTransform(position, 0);
	} else {
		//throw std::runtime_error("Can't set actor's position, because it has no physics body.");
	}
}
	
const b2Vec2& Player::getVelocity() const {
	if(body) {
		return body->GetLinearVelocity();
	} else {
		return zeroVec;
	}
}

const b2Vec2& Player::getPosition() const {
	if(body) {
		return body->GetPosition();
	} else {
		return zeroVec;
	}
}

void Player::deletePhysicsBody() {
	if(body) {
		body->GetWorld()->DestroyBody(body);
		body = NULL;
	}
}