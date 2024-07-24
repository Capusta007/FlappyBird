#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:

	Animation(std::vector<sf::Texture> textures, float oneFrameTime);

	bool isAnimated() { return m_isAnimated; }
	void startAnimation();
	sf::Texture* getCurrentFrame();

private:
	std::vector<sf::Texture> m_textures;
	int m_frameCounter;
	float m_oneFrameTime;
	float m_totalTime;
	bool m_isAnimated;
	sf::Clock timer;


	void stopAnimation();
	
};