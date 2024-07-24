#include <SFML/Graphics.hpp>

#include <iostream>

#include "Resourses/ResourceManager.h"
#include "GameElements/Bird.h"

const int windowWidth = 288;
const int windowHeight = 512;

int main(int argc, char** argv)
{
	ResourceManager resourceManager(argv[0]);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Flappy Bird!");
	window.setFramerateLimit(60);



	resourceManager.loadTexture("background-day", "res/sprites/background-day.png");
	resourceManager.loadTexture("bluebird-downflap", "res/sprites/bluebird-downflap.png");

	sf::Texture backgroundTexture = resourceManager.getTexture("background-day");
	sf::Texture birdDownFlap = resourceManager.getTexture("bluebird-downflap");


	sf::Sprite backgroundSprite;
	sf::Sprite birdSprite;
	backgroundSprite.setTexture(backgroundTexture);
	birdSprite.setTexture(birdDownFlap);

	Bird bird(windowWidth / 4, windowHeight / 2, -3, 0.1, 3);

	std::vector<sf::Texture> BirdAnimation;
	BirdAnimation.push_back(birdDownFlap);


	while (window.isOpen())
	{
		bird.fall();
		birdSprite.setPosition({ bird.getX(), windowHeight - bird.getY() });
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					bird.fly();
				}
			}
		}


		window.clear();
		window.draw(backgroundSprite);
		window.draw(birdSprite);

		window.display();
	}

	return 0;
}