#pragma once

#include <SFML/Graphics.hpp>

class Hitbox {

public:
	Hitbox();
	Hitbox(float x, float y, sf::Vector2f size);

	float getX() { return m_xCoord; }
	float getY() { return m_yCoord; }
	sf::Vector2f getSize() { return m_size; }
	
	bool isCollide(Hitbox& other);
	void move(sf::Vector2f v);
	void setPos(sf::Vector2f pos);
	void setSize(sf::Vector2f newSize);

private:
	float m_xCoord;
	float m_yCoord;
	sf::Vector2f m_size;

};