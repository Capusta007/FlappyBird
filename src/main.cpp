#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>

#include "Resourses/ResourceManager.h"
#include "Resourses/Animation.h"
#include "GameElements/Bird.h"


const int windowWidth = 288;
const int windowHeight = 512;
const int distanceBetweenPipes = 50;

int main(int argc, char** argv)
{
	srand(time(0));
	ResourceManager resourceManager(argv[0]);
	if (!resourceManager.loadAllTexturesFromFolder("res/sprites")) {
		std::cerr << "Can't load textures from res/sprites";
		return 1;
	}


	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Flappy Bird!");
	window.setFramerateLimit(100);


	sf::Texture backgroundTexture = resourceManager.getTexture("background-day");

	sf::Sprite backgroundSprite;
	sf::Sprite birdSprite;
	backgroundSprite.setTexture(backgroundTexture);

	Bird bird(windowWidth / 4, windowHeight / 2);

	std::vector<sf::Texture> flapAnimationTextures;
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-downflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-midflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-upflap"));

	Animation flapAnimation(flapAnimationTextures, 0.2, resourceManager.getTexture("bluebird-upflap"));

	while (window.isOpen())
	{
		bird.fall();


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


		// “ут мен€ютс€ все спрайты
		birdSprite.setPosition({ bird.getX(), windowHeight - bird.getY() });
		birdSprite.setTexture(*flapAnimation.getCurrentFrame());


		// ќтрисовка
		window.clear();
		window.draw(backgroundSprite);
		window.draw(birdSprite);

		window.display();
	}

	return 0;
}