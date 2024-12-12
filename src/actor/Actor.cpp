#include "Actor.h"
#include "Functions.hpp"
#include "Text.hpp"

#include <cfloat>

static const b2Vec2 zeroVec(0.0f, 0.0f);
Actor::Actor() {
    isAlive = true;
	physicsBody = NULL;
	isOnGround = false;
	wasOnGround = false;
}

void Actor::createPhysicsBody(b2World& world, float worldScale, const b2Vec2& position, const b2Vec2& velocity) {}

void Actor::deletePhysicsBody() {
	if (physicsBody) {
		physicsBody->GetWorld()->DestroyBody(physicsBody);
		physicsBody = NULL;
	}
}

void Actor::die() {
    isAlive = false;
}

bool Actor::isMoving() const {
	return getVelocity().LengthSquared() > 10.0f * FLT_EPSILON;
}
const b2Vec2& Actor::getVelocity() const {
	if (physicsBody) {
		return physicsBody->GetLinearVelocity();
	}
	else {
		return zeroVec;
	}
}

void Actor::setVelocity(const b2Vec2& velocity) {
	if (physicsBody) {
		return physicsBody->SetLinearVelocity(velocity);
	}
	else {
		throw std::runtime_error("Can't set actor's velocity, because it has no physics body.");
	}
}

const b2Vec2& Actor::getPosition() const {
	if (physicsBody) {
		return physicsBody->GetPosition();
	}
	else {
		return zeroVec;
	}
}

void Actor::setPosition(const b2Vec2& position) {
	if (physicsBody) {
		return physicsBody->SetTransform(position, 0);
	}
	else {
		throw std::runtime_error("Can't set actor's position, because it has no physics body.");
	}
}

raylib::Rectangle Actor::getBoundingBox() {
	const auto& position = getPosition();
	return raylib::Rectangle(position.x, position.y);
}

void Actor::drawBoundingBox(const Color& color) {
	auto boundingBox = getBoundingBox();

	float lineThickness = 2.0f * 0.5;
	DrawRectangleLinesEx(boundingBox, lineThickness, color);
}