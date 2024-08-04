#include "Bird.h"
#include <vector>

Bird::Bird(float x, float y, sf::Texture texture, float fallingSpeed, float acceleration, float jumpSpeed) : m_hitbox(x,y,(sf::Vector2f)texture.getSize())
{
	m_xCoord = x;
	m_yCoord = y;
	m_fallingSpeed = fallingSpeed;
	m_acceleration = acceleration;
	m_jumpStrength = jumpSpeed;
	m_texture = texture;
	m_isDead = false;
	m_sprite.setOrigin(0, m_hitbox.getSize().y);
	m_sprite.setTexture(m_texture);
	p_flapAnimation = nullptr;
}

Bird::~Bird()
{
	delete p_flapAnimation;
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

void Bird::loadFlapAnimation(std::vector<sf::Texture> textures, float oneFrameTime)
{
	p_flapAnimation = new Animation(textures, oneFrameTime, m_texture);
}

void Bird::updateSprite(float x, float y)
{
	m_sprite.setPosition(x, y);
	if (p_flapAnimation->isAnimated()){
   		m_sprite.setTexture(*p_flapAnimation->getCurrentFrame());
	}
}

void Bird::startFlapAnimation()
{
	p_flapAnimation->startAnimation();
}
