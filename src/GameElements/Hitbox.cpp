#include "Hitbox.h"
#include <iostream>
#include <cmath>

Hitbox::Hitbox()
{
	m_xCoord = 0;
	m_yCoord = 0;
	m_size = { 1,1 };
}

Hitbox::Hitbox(float x, float y, sf::Vector2f size)
{
	if (size.x < 0 || size.y < 0) {
		std::cerr << "Bad size initialization in Hitbox::Hitbox\n";
		return;
	}
	m_xCoord = x;
	m_yCoord = y;
	m_size = size;
}

bool Hitbox::isCollide(Hitbox& other)
{
	if (fmaxf(m_xCoord, other.m_xCoord) <= fminf(m_xCoord + m_size.x, other.m_xCoord + other.m_size.x)) { // Collision on y axes
		if (fmaxf(m_yCoord, other.m_yCoord) <= fminf(m_yCoord + m_size.y, other.m_yCoord + other.m_size.y)) { // Collision on x axes
			return true;
		}
	}

	return false;
}

void Hitbox::move(sf::Vector2f v)
{
	m_xCoord += v.x;
	m_yCoord += v.y;
}

void Hitbox::setPos(sf::Vector2f pos)
{
	m_xCoord = pos.x;
	m_yCoord = pos.y;
}

void Hitbox::setSize(sf::Vector2f newSize)
{
	m_size = newSize;
}
