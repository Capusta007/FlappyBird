#include <SFML/Graphics.hpp>

#include <iostream>

#include "Resourses/ResourceManager.h"
#include "Resourses/Animation.h"
#include "GameElements/Bird.h"


const int windowWidth = 288;
const int windowHeight = 512;

int main(int argc, char** argv)
{
	ResourceManager resourceManager(argv[0]);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Flappy Bird!");
	window.setFramerateLimit(100);



	resourceManager.loadTexture("background-day", "res/sprites/background-day.png");
	resourceManager.loadTexture("bluebird-downflap", "res/sprites/bluebird-downflap.png");
	resourceManager.loadTexture("bluebird-midflap", "res/sprites/bluebird-midflap.png");
	resourceManager.loadTexture("bluebird-upflap", "res/sprites/bluebird-upflap.png");

	sf::Texture backgroundTexture = resourceManager.getTexture("background-day");
	sf::Texture birdTexture = resourceManager.getTexture("bluebird-upflap");


	sf::Sprite backgroundSprite;
	sf::Sprite birdSprite;
	backgroundSprite.setTexture(backgroundTexture);
	birdSprite.setTexture(birdTexture);

	Bird bird(windowWidth / 4, windowHeight / 2, 0, 0.1, 3);

	std::vector<sf::Texture> flapAnimationTextures;
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-downflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-midflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-upflap"));

	Animation flapAnimation(flapAnimationTextures, 0.2);

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
					flapAnimation.startAnimation();
				}
			}
		}

		if (flapAnimation.isAnimated()) {
			birdSprite.setTexture(*flapAnimation.getCurrentFrame());
		}
		else {
			birdSprite.setTexture(birdTexture);
		}


		window.clear();
		window.draw(backgroundSprite);
		window.draw(birdSprite);

		window.display();
	}

	return 0;
}