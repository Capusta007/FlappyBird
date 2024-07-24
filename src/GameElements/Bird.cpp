#include "Bird.h"
#include <vector>

Bird::Bird(float x, float y, float fallingSpeed, float acceleration, float jumpSpeed)
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

bool Bird::isDead()
{
	return m_isDead;
}

void Bird::fall()
{
	m_fallingSpeed += m_acceleration;
	m_yCoord -= m_fallingSpeed;
}
