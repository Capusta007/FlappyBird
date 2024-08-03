#pragma once

#include <SFML/System/Vector2.hpp>
#include "Hitbox.h"

class Pipe {

public:
	Pipe(float x, float y, sf::Vector2f hitboxSize);
	

	float getX() const{ return m_xCoord; }
	float getY() const{ return m_yCoord; }
	Hitbox getHitbox() const { return m_hitbox; }
	void updateHitboxPosition();

	void setPos(float x, float y);
	void move(float dx, float dy);

private:
	float m_xCoord;
	float m_yCoord;
	Hitbox m_hitbox;
};