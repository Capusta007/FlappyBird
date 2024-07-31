#include "Bird.h"
#include <vector>

Bird::Bird(float x, float y, sf::Vector2f hitboxSize, float fallingSpeed, float acceleration, float jumpSpeed) : m_hitbox(x,y,hitboxSize)
{
	m_xCoord = x;
	m_yCoord = y;
	m_fallingSpeed = fallingSpeed;
	m_acceleration = acceleration;
	m_jumpStrength = jumpSpeed;
	m_isDead = false;
}

void Bird::fly()
{
	m_fallingSpeed = -m_jumpStrength;
}

bool Bird::isDead() const
{
	return m_isDead;
}

void Bird::die()
{
	m_isDead = true;
}

void Bird::fall()
{
	m_fallingSpeed += m_acceleration;
	m_yCoord -= m_fallingSpeed;
}

void Bird::updateHitboxPosition(sf::Vector2f shift)
{
	m_hitbox.setPos({m_xCoord + shift.x, m_yCoord + shift.y});
}

void Bird::changeHitboxSize(sf::Vector2f newSize)
{
	m_hitbox.setSize(newSize);
}
