#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>

#include "Resourses/ResourceManager.h"
#include "Resourses/Animation.h"
#include "GameElements/Bird.h"
#include "GameElements/Hitbox.h"
#include "GameElements/Pipe.h"


const int windowWidth = 288;
const int windowHeight = 512;
const int distanceBetweenPipesY = 100;
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



	sf::Texture backgroundTexture = resourceManager.getTexture("background-night");
	sf::Texture baseTexture = resourceManager.getTexture("base");
	sf::Texture pipeTexture = resourceManager.getTexture("pipe-green");

	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	sf::Sprite baseSprite1;
	baseSprite1.setTexture(baseTexture);
	baseSprite1.setPosition(0, windowHeight - baseTexture.getSize().y);

	sf::Sprite baseSprite2;
	baseSprite2.setTexture(baseTexture);
	baseSprite2.setPosition(baseTexture.getSize().x, windowHeight - baseTexture.getSize().y);



	Bird bird(windowWidth / 4, windowHeight / 2, resourceManager.getTexture("bluebird-upflap"));
	bird.changeHitboxSize(bird.getHitbox().getSize() - sf::Vector2f{ 10,4 });

	std::vector<sf::Texture> flapAnimationTextures;
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-downflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-midflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-upflap"));

	bird.loadFlapAnimation(flapAnimationTextures, 0.2);




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


	int counter = 0;
	sf::Texture zeroTexture = resourceManager.getTexture("0");
	std::vector<sf::Sprite> counterSprites;
	counterSprites.push_back(sf::Sprite(zeroTexture));
	counterSprites[0].setPosition(windowWidth / 2 - zeroTexture.getSize().x / 2, 10);

	while (!bird.isDead() && window.isOpen())
	{
		// Обработка событий
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


		// Игровые изменения
		bird.fall();
		bird.updateHitboxPosition({ 5,1 });
		for (int i = 0; i < numberOfPipes; i++) {

			if (bird.getHitbox().isCollide(downPipes[i].getHitbox()) ||
				bird.getHitbox().isCollide(upPipes[i].getHitbox()) ||
				bird.getY() <= baseTexture.getSize().y ||
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


		// Меняем счетчик
		if (downPipes[counter % numberOfPipes].getX() < bird.getX()) {
			counter++;
			std::cout << "counter " << std::to_string(counter) << "\n";

			bool shouldChange = false;
			if (std::to_string(counter).size() > counterSprites.size()) {
				counterSprites.push_back(sf::Sprite(zeroTexture));
				counterSprites[counterSprites.size() - 1].setPosition(counterSprites[0].getPosition());
				counterSprites[counterSprites.size() - 1].move(zeroTexture.getSize().x * (counterSprites.size() - 1), 0);
				shouldChange = true;
			}

			int temp = counter;
			for (int i = 0; i < counterSprites.size(); i++) {
				if (shouldChange) {
					counterSprites[i].move(-(int)zeroTexture.getSize().x / 2, 0);
				}
				counterSprites[counterSprites.size() - i - 1].setTexture(resourceManager.getTexture(std::to_string(temp % 10)));
				temp /= 10;
			}
		}







		// Тут меняются все спрайты
		bird.updateSprite(bird.getX(), windowHeight - bird.getY());
		baseSprite1.setPosition(baseSprite1.getPosition().x - pipeSpeed, baseSprite1.getPosition().y);
		baseSprite2.setPosition(baseSprite2.getPosition().x - pipeSpeed, baseSprite2.getPosition().y);
		if (baseSprite1.getPosition().x <= -(int)baseTexture.getSize().x) {
			baseSprite1.setPosition(baseSprite2.getPosition());
			baseSprite2.setPosition(baseTexture.getSize().x, baseSprite2.getPosition().y);
		}


		// Отрисовка
		window.clear();
		window.draw(backgroundSprite);
		window.draw(bird.getSprite());
		for (int i = 0; i < numberOfPipes; i++) {
			window.draw(upPipes[i].getSprite());
			window.draw(downPipes[i].getSprite());
		}
		window.draw(baseSprite1);
		window.draw(baseSprite2);
		for (sf::Sprite counterSprite : counterSprites) {
			window.draw(counterSprite);
		}

		window.display();
	}


	return 0;
}