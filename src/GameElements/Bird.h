#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "../GameElements/Hitbox.h"

class Bird {
public:

	Bird(float x, float y, sf::Vector2f hitboxSize, float fallingSpeed = 0, float acceleration = 0.1, float jumpStrength = 3);
	Bird() = delete;
	~Bird() = default;

	void fly();
	bool isDead() const;
	void die();
	void fall();
	void updateHitboxPosition(sf::Vector2f shift = {0,0});
	void changeHitboxSize(sf::Vector2f newSize);

	float getX() const { return m_xCoord; }
	float getY() const { return m_yCoord; }
	Hitbox getHitbox() const { return m_hitbox; }
	

private:
	float m_acceleration;
	float m_fallingSpeed;
	bool m_isDead;
	float m_xCoord;
	float m_yCoord;
	float m_jumpStrength;
	Hitbox m_hitbox;
};