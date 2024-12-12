#include "Movement.h"


Movement::Movement(int speed, int verticalSpeed, Direction direction, Direction verticalDirection) 
	: speed(speed), verticalSpeed(verticalSpeed), direction(direction), verticalDirection(verticalDirection) {}

int Movement::getSpeed() const
{
	return speed;
}

int Movement::getVerticalSpeed() const
{
	return verticalSpeed;
}

Direction Movement::getDirection() const
{
	return direction;
}

Direction Movement::getVerticalDirection() const
{
	return verticalDirection;
}

void Movement::setSpeed(int speed)
{ //speed = 1 => cham, speed = 2 => nhanh
	if (speed > 0 && speed < 3) {
		this->speed = speed;
	}
}

void Movement::setVerticalSpeed(int verticalSpeed)
{
	if (speed > 0 && speed < 5) {
		this->verticalSpeed = verticalSpeed;
	}
}

void Movement::setDirection(Direction direction)
{
	if (direction == Direction::LEFT || direction == Direction::RIGHT || direction == Direction::NONE) {
		this->direction = direction;
	}
}

void Movement::setVerticalDirection(Direction verticalDirection)
{
	if (verticalDirection == Direction::UP || verticalDirection == Direction::DOWN || verticalDirection == Direction::NONE) {
		this->verticalDirection = verticalDirection;
	}
}