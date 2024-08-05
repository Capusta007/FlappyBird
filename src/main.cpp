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
const int distanceBetweenPipes = 80;

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

	Bird bird(windowWidth / 4, windowHeight / 2, resourceManager.getTexture("bluebird-upflap"));
	bird.changeHitboxSize(bird.getHitbox().getSize() - sf::Vector2f{ 10,4 });

	// Creating flap animation
	std::vector<sf::Texture> flapAnimationTextures;
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-downflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-midflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-upflap"));

	bird.loadFlapAnimation(flapAnimationTextures, 0.2);




	sf::Texture pipeTexture = resourceManager.getTexture("pipe-green");
	const int pipeMaxY = pipeTexture.getSize().y;
	const int pipeMinY = windowHeight - pipeTexture.getSize().y - distanceBetweenPipes;
	float pipeCenterY = getRandomNumberInRange(pipeMinY, pipeMaxY);

	Pipe downPipe(200, pipeCenterY - pipeTexture.getSize().y, pipeTexture);

	Pipe upPipe(200, downPipe.getY() + downPipe.getHitbox().getSize().y + distanceBetweenPipes, pipeTexture);
	upPipe.flipSpriteVertically();

	// Hitboxes 
	sf::RectangleShape birdHitboxSprite(bird.getHitbox().getSize());
	birdHitboxSprite.setFillColor(sf::Color::Red);



	int c = 0;
	while (!bird.isDead() && window.isOpen())
	{

		std::cout << getRandomNumberInRange(1, 2) << "\n";
		// ��������� �������
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

		if (bird.getHitbox().isCollide(downPipe.getHitbox()) || bird.getHitbox().isCollide(upPipe.getHitbox())) {
			std::cout << "Collision! " << c++ << "\n";
			bird.die();
		}


		// ������� ���������
		bird.fall();
		bird.updateHitboxPosition({ 5,1 });
		downPipe.move(-1, 0);
		upPipe.move(-1, 0);
		if (downPipe.getX() < 0) {
			float pipeCenterY = getRandomNumberInRange(pipeMinY, pipeMaxY);
			downPipe.setPos(200, pipeCenterY - pipeTexture.getSize().y);
			upPipe.setPos(200, downPipe.getY() + downPipe.getHitbox().getSize().y + distanceBetweenPipes);
		}
		downPipe.updateHitboxPosition();
		upPipe.updateHitboxPosition();

		// ��� �������� ��� �������
		bird.updateSprite(bird.getX(), windowHeight - bird.getY());
		birdHitboxSprite.setPosition(bird.getHitbox().getX(), windowHeight - bird.getHitbox().getY() - bird.getHitbox().getSize().y);
		downPipe.updateSprite(downPipe.getX(), windowHeight - downPipe.getY());
		upPipe.updateSprite(upPipe.getX(), windowHeight - upPipe.getY());




		// ���������
		window.clear();
		window.draw(backgroundSprite);
		window.draw(birdHitboxSprite);
		window.draw(bird.getSprite());
		window.draw(downPipe.getSprite());
		window.draw(upPipe.getSprite());

		window.display();
	}

	return 0;
}