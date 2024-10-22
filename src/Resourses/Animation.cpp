#include "Animation.h"

Animation::Animation(std::vector<sf::Texture> textures, float oneFrameTime, sf::Texture frameAfterEndOfAnimation)
{
	for (sf::Texture texture : textures) {
		m_textures.push_back(texture);
	}
	m_frameCounter = 0;
	m_oneFrameTime = oneFrameTime;
	m_isAnimated = false;
	m_totalTime = 0;
	m_frameWhenNotAnimated = frameAfterEndOfAnimation;
}

void Animation::startAnimation()
{
	stopAnimation();
	timer.restart();
	m_isAnimated = true;
}

sf::Texture* Animation::getCurrentFrame()
{
	if (!m_isAnimated) return &m_frameWhenNotAnimated;

	m_totalTime = timer.getElapsedTime().asSeconds();
	if (m_totalTime < m_oneFrameTime) {
		return &m_textures[m_frameCounter];
	}
	if (m_frameCounter + 1 < m_textures.size()) {
		timer.restart();
		m_totalTime = timer.getElapsedTime().asSeconds();
		return  &m_textures[++m_frameCounter];
	}
	stopAnimation();

	return &m_frameWhenNotAnimated;
}

void Animation::stopAnimation()
{
	m_isAnimated = false;
	m_totalTime = 0;
	m_frameCounter = 0;
}
