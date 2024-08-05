#pragma once

#include <SFML/System/Vector2.hpp>
#include "Hitbox.h"

class Pipe {

public:
	Pipe(float x, float y, sf::Texture texture);
	Pipe(const Pipe& other);

	float getX() const{ return m_xCoord; }
	float getY() const{ return m_yCoord; }
	Hitbox getHitbox() const { return m_hitbox; }
	sf::Sprite getSprite() const { return m_sprite; }
	void flipSpriteVertically();

	void updateHitboxPosition();
	void updateSprite(float x, float y);
	void setPos(float x, float y);
	void move(float dx, float dy);

private:
	float m_xCoord;
	float m_yCoord;
	Hitbox m_hitbox;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool m_isSpriteFlipped;
};