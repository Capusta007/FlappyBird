#include "Pipe.h"

Pipe::Pipe(float x, float y, sf::Texture texture) : m_hitbox(x, y, sf::Vector2f(texture.getSize()))
{
	m_xCoord = x;
	m_yCoord = y;
	m_texture = texture;
	m_sprite.setOrigin(0, texture.getSize().y);
	m_sprite.setTexture(m_texture);
	m_isSpriteFlipped = false;
}

void Pipe::flipSpriteVertically()
{
	if (m_isSpriteFlipped) {
		m_isSpriteFlipped = false;
	}
	else {
		m_isSpriteFlipped = true;
	}
	m_sprite.rotate(180);
}

void Pipe::updateHitboxPosition()
{
	m_hitbox.setPos({ m_xCoord, m_yCoord });
}

void Pipe::updateSprite(float x, float y)
{
	m_sprite.setPosition(x, y);
	if (m_isSpriteFlipped) {
		m_sprite.move(m_texture.getSize().x, -(int)m_texture.getSize().y);
	}
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
