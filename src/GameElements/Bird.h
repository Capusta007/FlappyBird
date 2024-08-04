#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "../GameElements/Hitbox.h"
#include "../Resourses/Animation.h"

class Bird {
public:

	Bird(float x, float y, sf::Texture texture, float fallingSpeed = 0, float acceleration = 0.1, float jumpStrength = 3);
	Bird() = delete;
	~Bird();

	void fly();
	bool isDead() const;
	void die();
	void fall();
	void updateHitboxPosition(sf::Vector2f shift = { 0,0 });
	void changeHitboxSize(sf::Vector2f newSize);
	void loadFlapAnimation(std::vector<sf::Texture> textures, float oneFrameTime);
	void updateSprite(float x, float y);
	void startFlapAnimation();

	float getX() const { return m_xCoord; }
	float getY() const { return m_yCoord; }
	Hitbox getHitbox() const { return m_hitbox; }
	sf::Sprite getSprite() const { return m_sprite; }


private:
	float m_acceleration;
	float m_fallingSpeed;
	bool m_isDead;
	float m_xCoord;
	float m_yCoord;
	float m_jumpStrength;
	Hitbox m_hitbox;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Animation* p_flapAnimation;
};