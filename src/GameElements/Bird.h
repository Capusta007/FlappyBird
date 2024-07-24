#pragma once
#include <vector>

class Bird {
public:

	Bird(float x, float y, float fallingSpeed = 0, float acceleration = 1, float jumpStrength = 2);
	Bird() = delete;
	~Bird() = default;

	void fly();
	bool isDead();
	void fall();
	float getX() { return m_xCoord; }
	float getY() { return m_yCoord; }

private:
	float m_acceleration;
	float m_fallingSpeed;
	bool m_isDead;
	float m_xCoord;
	float m_yCoord;
	float m_jumpStrength;
};