#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>
#include <windows.h>

#include "Resourses/ResourceManager.h"
#include "Resourses/Animation.h"
#include "GameElements/Bird.h"
#include "GameElements/Hitbox.h"
#include "GameElements/Pipe.h"


const int windowWidth = 288;
const int windowHeight = 512;
const int distanceBetweenPipesY = 80;
const int distanceBetweenPipesX = 150;
const int pipeSpeed = 1;
const int numberOfPipes = 3;

int getRandomNumberInRange(int min, int max) {
	return rand() % (max - min + 1) + min;
}

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

	sf::Texture baseTexture = resourceManager.getTexture("base");
	sf::Sprite baseSprite1;
	baseSprite1.setTexture(baseTexture);
	baseSprite1.setPosition(0, windowHeight - baseTexture.getSize().y);

	sf::Sprite baseSprite2;
	baseSprite2.setTexture(baseTexture);
	baseSprite2.setPosition(baseTexture.getSize().x, windowHeight - baseTexture.getSize().y);



	Bird bird(windowWidth / 4, windowHeight / 2, resourceManager.getTexture("bluebird-upflap"));
	bird.changeHitboxSize(bird.getHitbox().getSize() - sf::Vector2f{ 10,4 });

	// Creating flap animation
	std::vector<sf::Texture> flapAnimationTextures;
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-downflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-midflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-upflap"));

	bird.loadFlapAnimation(flapAnimationTextures, 0.2);




	sf::Texture pipeTexture = resourceManager.getTexture("pipe-green");
	const int pipeMaxY = pipeTexture.getSize().y + baseTexture.getSize().y / 2;
	const int pipeMinY = windowHeight - pipeTexture.getSize().y - distanceBetweenPipesY + baseTexture.getSize().y / 2;

	std::vector<Pipe> downPipes;
	std::vector<Pipe> upPipes;
	for (int i = 0; i < numberOfPipes; i++) {
		float pipeCenterY = getRandomNumberInRange(pipeMinY, pipeMaxY);
		downPipes.push_back(Pipe(windowWidth / 4 * 3 + distanceBetweenPipesX * i, pipeCenterY - pipeTexture.getSize().y, pipeTexture));
		upPipes.push_back(Pipe(windowWidth / 4 * 3 + distanceBetweenPipesX * i, pipeCenterY + distanceBetweenPipesY, pipeTexture));

		upPipes[i].flipSpriteVertically();
	}


	while (!bird.isDead() && window.isOpen())
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
					bird.startFlapAnimation();
				}
			}
		}


		// »гровые изменени€
		bird.fall();
		bird.updateHitboxPosition({ 5,1 });
		for (int i = 0; i < numberOfPipes; i++) {

			if (bird.getHitbox().isCollide(downPipes[i].getHitbox()) ||
				bird.getHitbox().isCollide(upPipes[i].getHitbox()) ||
				bird.getY() <= baseTexture.getSize().y||
				bird.getY() + bird.getHitbox().getSize().y >= windowHeight)
			{
				bird.die();
			}

			downPipes[i].move(-pipeSpeed, 0);
			upPipes[i].move(-pipeSpeed, 0);
			downPipes[i].updateHitboxPosition();
			upPipes[i].updateHitboxPosition();
			if (downPipes[i].getX() < -(int)pipeTexture.getSize().x) {
				float pipeCenterY = getRandomNumberInRange(pipeMinY, pipeMaxY);
				downPipes[i].setPos(downPipes[(i + numberOfPipes - 1) % numberOfPipes].getX() + distanceBetweenPipesX, pipeCenterY - pipeTexture.getSize().y);
				upPipes[i].setPos(upPipes[(i + numberOfPipes - 1) % numberOfPipes].getX() + distanceBetweenPipesX, pipeCenterY + distanceBetweenPipesY);
			}

			downPipes[i].updateSprite(downPipes[i].getX(), windowHeight - downPipes[i].getY());
			upPipes[i].updateSprite(upPipes[i].getX(), windowHeight - upPipes[i].getY());
		}



		// “ут мен€ютс€ все спрайты
		bird.updateSprite(bird.getX(), windowHeight - bird.getY());
		baseSprite1.setPosition(baseSprite1.getPosition().x - pipeSpeed, baseSprite1.getPosition().y);
		baseSprite2.setPosition(baseSprite2.getPosition().x - pipeSpeed, baseSprite2.getPosition().y);
		if (baseSprite1.getPosition().x <= -(int)baseTexture.getSize().x) {
			baseSprite1.setPosition(baseSprite2.getPosition());
			baseSprite2.setPosition(baseTexture.getSize().x, baseSprite2.getPosition().y);
		}


		// ќтрисовка
		window.clear();
		window.draw(backgroundSprite);
		window.draw(bird.getSprite());
		for (int i = 0; i < numberOfPipes; i++) {
			window.draw(upPipes[i].getSprite());
			window.draw(downPipes[i].getSprite());
		}
		window.draw(baseSprite1);
		window.draw(baseSprite2);

		window.display();
	}


	return 0;
}