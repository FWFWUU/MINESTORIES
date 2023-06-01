#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <memory>
#include "Player.h"
#include "Camera.h"
#include "Physics.h"
#include "Font.h"
#include "SpriteBatch.h"
#include "DialogBox.h"
#include "Location.h"
#include "Resources.h"
#include "Animation.h"
#include "NPC.h"

class Game {
public:
	const sf::String GAME_NAME = "Minestories";
	const sf::String GAME_VERSION_NAME = "1.0.0";

	sf::RenderWindow* window;
	
	sf::Sprite cursorSprite;
	
	sf::Image * window_icon;

	sf::IntRect cur_tex_rect;

	Player* player;
	
	bool gamePaused = false;

	Camera* camera;

	sf::Clock deltaTime;

	Physics physics;

	SpriteBatch* batch;
	
	DialogBox* dialog;

	LocationManager* locationManager;

	float fadeAlpha = 1;

	float framesPerSeconds = 60;

	bool verticalSync = false;

	float framerate = 0;

	bool debugMode = false;

	std::string command;

	Game() {
		srand(time(NULL)); //generate random seed

		window = new sf::RenderWindow(sf::VideoMode(1024, 640), GAME_NAME + " All copyright " + GAME_VERSION_NAME);

		Resources::Resources();

		//window_icon = new sf::Image();
		//window_icon->loadFromFile("Assets/Textures/w_icon.png");
		
		//window->setIcon(16, 16, window_icon->getPixelsPtr());

		//cur_tex_rect.height = 8;
		//cur_tex_rect.width = 8;
		
		cursorSprite.setTexture(Resources::IconsTexture);
		cursorSprite.setTextureRect(sf::IntRect(0,0,8,8));
		cursorSprite.setScale(sf::Vector2f(1.2, 1.2));
		

		player = new Player("player", sf::Vector2f(10, 130));

		camera = new Camera(*window);

		batch = new SpriteBatch(window);

		dialog = new DialogBox(batch, Resources::DefaultFont);
		dialog->loadDialog("Texts/Dialogs001.txt");

		locationManager = new LocationManager;
		locationManager->loadLocation("Assets/Locations/StartMap.tmx", "Start");
		locationManager->currentLocation = "Start";
	}

	void sortSprites() {
		for (int i = 0; i < AnimatedSprite::getSpritesList().size(); i++) {
			if (i + 1 < AnimatedSprite::getSpritesList().size()) {
				if (AnimatedSprite::getSpritesList()[i]->getLocalBounds().intersects(AnimatedSprite::getSpritesList()[i + 1]->getLocalBounds())) {
					if (AnimatedSprite::getSpritesList()[i]->getPosition().y > AnimatedSprite::getSpritesList()[i + 1]->getPosition().y) {
						std::iter_swap(AnimatedSprite::getSpritesList()[i], AnimatedSprite::getSpritesList()[i + 1]);
					}
				}
			}
		}

	}

	void startWorld() {
		NPC* npc = new NPC("npc", sf::Vector2f(100, 100));
	}

	void draw() {
		
		//draw location

		for (int i = 0; i < locationManager->locations.size(); i++) {
			if (locationManager->locations[i]->name == locationManager->currentLocation) {
				for (LocationLayer* layer : locationManager->locations[i]->layers) {
					window->draw(layer->vArr, &locationManager->locations[i]->texture);

					if (layer->name == "Grass") {
						
						//draw sprites

						for (sf::Sprite* s : AnimatedSprite::getSpritesList())
							window->draw(*s);

						//draw cursor

						float ceilX = floor(((cursorSprite.getPosition().x + 0) * 4) / (locationManager->locations[i]->mapWidth));
						float ceilY = floor(((cursorSprite.getPosition().y + 0) * 4) / (locationManager->locations[i]->mapHeight));

						if (locationManager->locations[i]->getTile("Dirt", ceilX, ceilY) > 0) {
							batch->draw(Resources::IconsTexture, sf::FloatRect(ceilX * 16, ceilY * 16, 16, 16), sf::IntRect(47, 0, 16, 16), sf::Color(255, 255, 255, 155));
						}
					}
				}
			}
		}

		for (Character* character : Character::getCharactersList()) {
			character->draw(*window);

			BoundingBox m(1, 1, cursorSprite.getPosition().x, cursorSprite.getPosition().y);

			if (character->hitbox->intersects(m)) {
				Resources::DefaultFont->drawString(*batch, "<" + character->name + ">", character->getPivot() - sf::Vector2f(0, 16), 8, sf::Color::Yellow);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					dialog->setCurrentDialog(8, 14);
				}
			}

		}

		//draw tools bar

		sf::FloatRect r(window->mapPixelToCoords(sf::Vector2i(0, 0)), sf::Vector2f(32, 32));

		batch->draw(Resources::IconsTexture, sf::FloatRect(r.left, r.top, r.width, r.height), sf::IntRect(63, 0, 16, 17));
		for (int i = 0; i < 6; i++)
			batch->draw(Resources::IconsTexture, sf::FloatRect((32 * i) + r.left + r.width, r.top, r.width, r.height), sf::IntRect(63 + 16, 0, 16, 17));
		batch->draw(Resources::IconsTexture, sf::FloatRect((32 * 7) + r.left, r.top, r.width, r.height), sf::IntRect(63 + 32, 0, 16, 17));

		//draw command input

		if (debugMode) {
			Resources::DefaultFont->drawString(*batch, ">" + command + "<", window->mapPixelToCoords(sf::Vector2i(0, window->getView().getSize().y - 8)), 8);
		}

		window->draw(cursorSprite);
	}

	void update(float dt) {
		camera->attachTarget(*player);
		camera->update(dt);

		sortSprites();

		//build current location

		for (int i = 0; i < locationManager->locations.size(); i++) {
			if (locationManager->locations[i]->name == locationManager->currentLocation) {
				locationManager->locations[i]->build();

				//set camera limits

				if ((camera->view.getSize().x / 2) + camera->view.getCenter().x > locationManager->locations[i]->mapWidth * locationManager->locations[i]->tileSizeX) {
					camera->view.setCenter((locationManager->locations[i]->mapWidth * locationManager->locations[i]->tileSizeX) - (camera->view.getSize().x / 2), camera->view.getCenter().y);
				}

				if (camera->view.getCenter().x < (camera->view.getSize().x / 2) + 0) {
					camera->view.setCenter((camera->view.getSize().x / 2), camera->view.getCenter().y);
				}

				if ((camera->view.getSize().y) + (camera->view.getCenter().y) > locationManager->locations[i]->mapHeight * locationManager->locations[i]->tileSizeY) {
					camera->view.setCenter(camera->view.getCenter().x, (locationManager->locations[i]->mapHeight * locationManager->locations[i]->tileSizeY) - (camera->view.getSize().y));
				}

				if (camera->view.getCenter().y < (camera->view.getSize().y / 2) + 0) {
					camera->view.setCenter(camera->view.getCenter().x, (camera->view.getSize().y / 2));
				}
			}
		}

		//update characters

		for (Character* character : Character::getCharactersList())
			character->update(dt);

		dialog->update();

		//Temporary HUD

		window->setTitle(GAME_NAME + " fps:" + std::to_string((int)framerate));
		//Resources::DefaultFont->drawString(*batch, std::to_string((int)framerate), window->mapPixelToCoords(sf::Vector2i(0, 0)), 8, sf::Color(255, 255, 255, 155));
	}

	void Listen(sf::Event& event) {
		if (event.type == sf::Event::Closed) {
			this->window->close();
		}
		if (event.type == sf::Event::Resized) {
			this->camera->view.setSize(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
		}
		if (event.type == sf::Event::MouseEntered) {
			this->window->setMouseCursorVisible(false);
		}
		if (event.type == sf::Event::MouseLeft) {
			this->window->setMouseCursorVisible(true);
		}
		if (event.type == sf::Event::LostFocus) {
			gamePaused = true;
		}
		if (event.type == sf::Event::GainedFocus) {
			gamePaused = false;
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left)
				if (dialog->isOnConversation)
					if (dialog->touchNext == true)
						dialog->nextDialogue();
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Slash) debugMode = !debugMode;
		}

		if (debugMode) {
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::Backspace:
						if (command.size() > 0) command.pop_back();
						break;

					case sf::Keyboard::A:
						command += "a";
						break;

					case sf::Keyboard::B:
						command += "b";
						break;

					case sf::Keyboard::C:
						command += "c";
						break;

					case sf::Keyboard::D:
						command += "d";
						break;

					case sf::Keyboard::E:
						command += "e";
						break;
				}
			}
		}
	}

	void run() {
		window->setVerticalSyncEnabled(verticalSync);
		window->setFramerateLimit(framesPerSeconds);

		while (window->isOpen()) {
			sf::Event e;
			
			while (window->pollEvent(e)) {
				Listen(e);
			}

			window->clear();

			draw();

			framerate = 1 / deltaTime.getElapsedTime().asSeconds();

			if (gamePaused == false)
				update(deltaTime.restart().asSeconds());
			
			cursorSprite.setPosition(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));

			window->display();
		}
	}
};

int main()
{
	
	Game* game = new Game();
	game->startWorld();
	game->run();
	
	return 0;
}