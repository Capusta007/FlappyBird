#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>

#include "Resourses/ResourceManager.h"
#include "Resourses/Animation.h"
#include "GameElements/Bird.h"
#include "GameElements/Hitbox.h"
#include "GameElements/Pipe.h"


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

	Bird bird(windowWidth / 4, windowHeight / 2, sf::Vector2f(resourceManager.getTexture("bluebird-downflap").getSize()));
	bird.changeHitboxSize(bird.getHitbox().getSize() - sf::Vector2f{ 7,3 });
	sf::Sprite birdSprite;
	birdSprite.setOrigin(0, bird.getHitbox().getSize().y);

	// Creating flap animation
	std::vector<sf::Texture> flapAnimationTextures;
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-downflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-midflap"));
	flapAnimationTextures.push_back(resourceManager.getTexture("bluebird-upflap"));
	Animation flapAnimation(flapAnimationTextures, 0.2, resourceManager.getTexture("bluebird-upflap"));





	Pipe pipe(200, 0, (sf::Vector2f)resourceManager.getTexture("pipe-green").getSize());
	sf::Texture pipeTexture = resourceManager.getTexture("pipe-green");
	sf::Sprite pipeSprite(pipeTexture);
	pipeSprite.setOrigin(0, pipe.getHitbox().getSize().y);

	// Hitboxes
	sf::RectangleShape birdHitboxSprite(bird.getHitbox().getSize());
	birdHitboxSprite.setFillColor(sf::Color::Red);



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
				if (event.key.code == sf::Keyboard::Left) {
					pipe.setPos(pipe.getX() - 1, pipe.getY());
				}
				if (event.key.code == sf::Keyboard::Right) {
					pipe.setPos(pipe.getX() + 1, pipe.getY());
				}
				if (event.key.code == sf::Keyboard::Up) {
					pipe.setPos(pipe.getX(), pipe.getY() + 1);
				}
				if (event.key.code == sf::Keyboard::Down) {
					pipe.setPos(pipe.getX(), pipe.getY() - 1);
				}
			}
		}

		if (bird.getHitbox().isCollide(pipe.getHitbox())) {
			std::cout << "Collision!" << c++ << "\n";
		}


		// »гровые изменени€
		bird.fall();
		bird.updateHitboxPosition({ 3,-2 });
		pipe.move(-0.3, 0);
		if (pipe.getX() < 0) {
			pipe.setPos(200, pipe.getY());
		}
		pipe.updateHitboxPosition();


		// “ут мен€ютс€ все спрайты
		birdSprite.setPosition({ bird.getX(), windowHeight - bird.getY() });
		birdSprite.setTexture(*flapAnimation.getCurrentFrame());
		birdHitboxSprite.setPosition(bird.getHitbox().getX(), windowHeight - bird.getHitbox().getY() - bird.getHitbox().getSize().y);
		pipeSprite.setPosition({ pipe.getX(),windowHeight - pipe.getY() });


		// ќтрисовка
		window.clear();
		window.draw(backgroundSprite);
		window.draw(birdHitboxSprite);
		window.draw(birdSprite);
		window.draw(pipeSprite);

		window.display();
	}

	return 0;
}