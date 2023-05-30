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

const std::string GAME_NAME = "Minestories";
const std::vector<std::string> SUBTITLES{
	"Pirate edition", "c++ sucks", ":(", "Eita, guapitoo!!"
};

class Game {
public:
	sf::RenderWindow* window;
	sf::Sprite curSprite;
	sf::Image * window_icon;
	sf::IntRect cur_tex_rect;

	Player* player;

	int count_spr_sort = 0;
	bool paused = false;

	Camera* camera;

	sf::Clock deltaTime;

	Physics physics;

	SpriteBatch* batch;
	
	DialogBox* dialog;

	LocationManager* locationManager;

	float framesPerSeconds = 60;

	bool verticalSync = false;

	float framerate = 0;

	Game() {
		srand(time(NULL)); //generate random seed

		int rand_subtitle_pos = rand() % SUBTITLES.size();

		window = new sf::RenderWindow(sf::VideoMode(1024, 640), GAME_NAME + ": " + SUBTITLES[rand_subtitle_pos]);
		window->setVerticalSyncEnabled(verticalSync);
		window->setFramerateLimit(framesPerSeconds);

		Resources::Resources();

		window_icon = new sf::Image();
		window_icon->loadFromFile("Assets/Textures/w_icon.png");
		
		window->setIcon(16, 16, window_icon->getPixelsPtr());

		cur_tex_rect.height = 8;
		cur_tex_rect.width = 8;
		
		curSprite.setTexture(*Resources::IconsTexture);
		curSprite.setTextureRect(cur_tex_rect);
		curSprite.setScale(sf::Vector2f(1.2, 1.2));
		

		player = new Player("player", sf::Vector2f(10, 10));

		camera = new Camera();
		camera->view->setSize(window->getSize().x / 2, window->getSize().y / 2);

		//res = new Resources;

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

			window->draw(*AnimatedSprite::getSpritesList()[i]);
		}

	}

	void startWorld() {
		//start world here

		Player* clone;
		clone = new Player("npc", sf::Vector2f(-30, -30));
	}

	void update(float dt) {
		//locationManager->draw(window);

		for (int i = 0; i < locationManager->locations.size(); i++) {
			if (locationManager->locations[i]->name == locationManager->currentLocation) {
				locationManager->locations[i]->draw();

				for (LocationLayer* layer : locationManager->locations[i]->layers) {
					window->draw(layer->vArr, &locationManager->locations[i]->texture);

					if (layer->name == "Grass")
						sortSprites();
				}

				camera->FollowCharacter(*player, *window, dt);

				if ((camera->view->getSize().x / 2) + camera->view->getCenter().x > locationManager->locations[i]->mapWidth * locationManager->locations[i]->tileSizeX) {
					camera->view->setCenter((locationManager->locations[i]->mapWidth * locationManager->locations[i]->tileSizeX) - (camera->view->getSize().x / 2), camera->view->getCenter().y);
				}

				if (camera->view->getCenter().x < (camera->view->getSize().x / 2) + 0) {
					camera->view->setCenter((camera->view->getSize().x / 2), camera->view->getCenter().y);
				}

				if ((camera->view->getSize().y) + (camera->view->getCenter().y) > locationManager->locations[i]->mapHeight * locationManager->locations[i]->tileSizeY) {
					camera->view->setCenter(camera->view->getCenter().x, (locationManager->locations[i]->mapHeight * locationManager->locations[i]->tileSizeY) - (camera->view->getSize().y));
				}

				if (camera->view->getCenter().y < (camera->view->getSize().y / 2) + 0) {
					camera->view->setCenter(camera->view->getCenter().x, (camera->view->getSize().y / 2));
				}
			}
		}

		physics.update(dt);
		

		sf::Vector2f impulse;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			impulse.x = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			impulse.x = 1;
		else
			impulse.x = 0;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			impulse.y = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			impulse.y = 1;
		else
			impulse.y = 0;
		
		player->moveTo(impulse.x, impulse.y);

		for (Character* chara : Character::getCharactersList()) {
			chara->draw(*window);
			chara->update(dt);

			BoundingBox m(1, 1, curSprite.getPosition().x, curSprite.getPosition().y);

			if (chara->hitbox->intersects(m)) {
				Resources::DefaultFont->drawString(*batch, "<" + chara->name + ">", chara->getPivot() - sf::Vector2f(0, 16), 8, sf::Color::Yellow);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					dialog->setCurrentDialog(8, 14);
				}
			}

		}

		dialog->update();

		Resources::DefaultFont->drawString(*batch, std::to_string((int)framerate), window->mapPixelToCoords(sf::Vector2i(0, 0)), 8, sf::Color(255, 255, 255, 155));
	}

	void Listen(sf::Event& event) {
		if (event.type == sf::Event::Closed) {
			this->window->close();
		}
		if (event.type == sf::Event::Resized) {
			this->camera->view->setSize(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
		}
		if (event.type == sf::Event::MouseEntered) {
			this->window->setMouseCursorVisible(false);
		}
		if (event.type == sf::Event::MouseLeft) {
			this->window->setMouseCursorVisible(true);
		}
		if (event.type == sf::Event::LostFocus) {
			paused = true;
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left)
				if (dialog->isOnConversation)
					if (dialog->touchNext == true)
						dialog->nextDialogue();
		}
	}

	void run() {
		while (window->isOpen()) {
			sf::Event e;
			
			while (window->pollEvent(e)) {
				Listen(e);
			}

			curSprite.setPosition(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));

			window->setView(*camera->view);
			
			window->clear();

			framerate = 1 / deltaTime.getElapsedTime().asSeconds();

			update(deltaTime.restart().asSeconds());	

			window->draw(curSprite);

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