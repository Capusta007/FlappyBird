#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>

#include "Resourses/ResourceManager.h"
#include "Resourses/Animation.h"
#include "GameElements/Bird.h"
#include "GameElements/Hitbox.h"


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
	backgroundSprite.setTexture(backgroundTexture);

	sf::Sprite birdSprite;
	Bird bird(windowWidth / 4, windowHeight / 2, sf::Vector2f(resourceManager.getTexture("bluebird-downflap").getSize()));
	bird.changeHitboxSize(bird.getHitbox().getSize() - sf::Vector2f{7, 3});

	// Creating flap animation
	std::vector<sf::Texture> flapAnimationTextures;
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-downflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-midflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-upflap"));
	Animation flapAnimation(flapAnimationTextures, 0.2, resourceManager.getTexture("bluebird-upflap"));


	// Hitboxes
	sf::RectangleShape birdHitboxSprite(bird.getHitbox().getSize());
	birdHitboxSprite.setFillColor(sf::Color::Red);

	Hitbox pikeHitbox(bird.getX(), 100, { 20,20 });
	sf::RectangleShape pike({ 20,20 });
	pike.setPosition({ pikeHitbox.getX(),windowHeight - pikeHitbox.getY() });

	int c = 0;
	while (window.isOpen())
	{
		// ќбработка событий
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

		if (bird.getHitbox().isCollide(pikeHitbox)) {
			std::cout << "Collision!" << c++ << "\n";
		}


		// »гровые изменени€
		bird.fall();
		bird.updateHitboxPosition({3,-2});



		// “ут мен€ютс€ все спрайты
		birdSprite.setPosition({ bird.getX(), windowHeight - bird.getY() });
		birdSprite.setTexture(*flapAnimation.getCurrentFrame());
		birdHitboxSprite.setPosition(bird.getHitbox().getX(), windowHeight - bird.getHitbox().getY());


		// ќтрисовка
		window.clear();
		window.draw(backgroundSprite);
		window.draw(birdHitboxSprite);
		window.draw(birdSprite);
		window.draw(pike);

		window.display();
	}

	return 0;
}