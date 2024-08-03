#include "Pipe.h"

Pipe::Pipe(float x, float y, sf::Vector2f hitboxSize) : m_hitbox(x, y, hitboxSize)
{
	m_xCoord = x;
	m_yCoord = y;
}

void Pipe::updateHitboxPosition()
{
	m_hitbox.setPos({ m_xCoord, m_yCoord });
}

void Pipe::setPos(float x, float y)
{
	m_xCoord = x;
	m_yCoord = y;
}

void Pipe::move(float dx, float dy)
{
	this->setPos(m_xCoord + dx, m_yCoord + dy);
}
